/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 17:36:07 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 23:50:46 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_io_time(t_philo *philo_info, char state, struct timeval *time)
{
	pthread_mutex_lock(&(philo_info->id_io));
	if (state == 'r')
		*time = philo_info->last_meal;
	else if (state == 'w')
		philo_info->last_meal = *time;
	else
		printf("ERROR");
	pthread_mutex_unlock(&(philo_info->id_io));
}

int	philo_io_end(t_philo *philo_info, char state)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo_info->unified->io));
	if (state == 'r')
		ret = philo_info->unified->end;
	else if (state == 'w')
		philo_info->unified->end = 1;
	else
		printf("ERROR");
	pthread_mutex_unlock(&(philo_info->unified->io));
	return (ret);
}

void	philo_print(t_philo *philo_info, char *str, int last)
{
	struct timeval	time;

	pthread_mutex_lock(&(philo_info->unified->print));
	if (philo_io_end(((t_philo *)philo_info), 'r') == 1)
	{
		pthread_mutex_unlock(&(philo_info->unified->print));
		return ;
	}
	gettimeofday(&(time), NULL);
	printf("%ld ", (time.tv_sec - philo_info->unified->start.tv_sec) * 1000
		+ (time.tv_usec - philo_info->unified->start.tv_usec) / 1000);
	printf("%d %s\n", philo_info->a_name + 1, str);
	if (last)
		philo_io_end((philo_info), 'w');
	pthread_mutex_unlock(&(philo_info->unified->print));
}

long	philo_elasped_time(struct timeval begin, struct timeval current)
{
	return ((current.tv_sec - begin.tv_sec) * 1000L
		+ (current.tv_usec - begin.tv_usec) / 1000L);
}
