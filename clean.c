/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:13:53 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 23:27:45 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phi.h"

void	clean_unified(t_unified **unified)
{
	if (*unified == NULL)
		return ;
	pthread_mutex_destroy(&((*unified)->print));
	pthread_mutex_destroy(&((*unified)->io));
	free((*unified)->fork);
	free(*unified);
	return ;
}

void	clean_all(t_philo **philo_info, pthread_t **pt)
{
	pthread_mutex_unlock(&((*philo_info)[0].unified->print));
	pthread_mutex_destroy(&((*philo_info)[0].unified->print));
	pthread_mutex_unlock(&((*philo_info)[0].unified->io));
	pthread_mutex_destroy(&((*philo_info)[0].unified->io));
	destroy_fork((*philo_info)[0].unified->fork, (*philo_info)[0].unified->n_philo);
	destroy_io(philo_info, (*philo_info)[0].unified->n_philo);
	free((*philo_info)[0].unified->fork);
	free((*philo_info)[0].unified);
	free(*philo_info);
	free(*pt);
}

void	destroy_fork(pthread_mutex_t *thread, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_unlock(&(thread[i]));
		pthread_mutex_destroy(&(thread[i]));
		i++;
	}
}

void	destroy_io(t_philo **philo_info, int num)
{
	int	i;

	i = 0;
	while (i < num)
	{
		pthread_mutex_unlock(&((*philo_info)[i].id_io));
		pthread_mutex_destroy(&((*philo_info)[i].id_io));
		i++;
	}
}
