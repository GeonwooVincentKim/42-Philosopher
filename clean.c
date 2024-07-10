/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:13:53 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 23:31:16 by geonwkim         ###   ########.fr       */
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

void	clean_all(t_philo **p_info, pthread_t **pt)
{
	pthread_mutex_unlock(&((*p_info)[0].unified->print));
	pthread_mutex_destroy(&((*p_info)[0].unified->print));
	pthread_mutex_unlock(&((*p_info)[0].unified->io));
	pthread_mutex_destroy(&((*p_info)[0].unified->io));
	destroy_fork((*p_info)[0].unified->fork, (*p_info)[0].unified->n_philo);
	destroy_io(p_info, (*p_info)[0].unified->n_philo);
	free((*p_info)[0].unified->fork);
	free((*p_info)[0].unified);
	free(*p_info);
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

static void	destroy_io(t_philo **philo_info, int num)
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
