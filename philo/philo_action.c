/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 16:04:28 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/11 00:08:08 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_eating(t_philo *philo_info, int fork[2])
{
	struct timeval	cur;

	if (philo_info->n_must_eat != -1 && ++philo_info->n_has_eaten \
		== philo_info->n_must_eat)
		philo_info->unified->after_meal++;
	if (philo_info->unified->after_meal \
		== philo_info->unified->n_philo)
		philo_print(philo_info, "is eating", 1);
	else
		philo_print(philo_info, "is eating", 0);
	gettimeofday(&cur, NULL);
	philo_io_time(philo_info, 'w', &cur);
	if (philo_io_end(philo_info, 'r') != 1)
	{
		usleep(philo_info->timeeat * 1000);
		gettimeofday(&(cur), NULL);
		philo_info->last_act = cur;
	}
	pthread_mutex_unlock(&((philo_info->unified->fork)[fork[0]]));
	pthread_mutex_unlock(&((philo_info->unified->fork)[fork[1]]));
}

void	philo_eat(t_philo *philo_info, int fork[2])
{
	if (philo_info->a_name % 2 == 1)
		usleep(300);
	pthread_mutex_lock(&((philo_info->unified->fork)[fork[0]]));
	if (philo_io_end(philo_info, 'r') == 1)
		return ;
	philo_print(philo_info, "has taken a fork", 0);
	pthread_mutex_lock(&((philo_info->unified->fork)[fork[1]]));
	if (philo_io_end(philo_info, 'r') == 1)
		return ;
	philo_print(philo_info, "has taken a fork", 0);
	philo_eating(philo_info, fork);
}

void	philo_think(t_philo *philo_info)
{
	struct timeval	cur;

	philo_print(philo_info, "is thinking", 0);
	gettimeofday(&(cur), NULL);
	philo_info->last_act = cur;
}

void	philo_sleep(t_philo *philo_info)
{
	struct timeval	cur;

	gettimeofday(&(cur), NULL);
	philo_print(philo_info, "is sleeping", 0);
	gettimeofday(&(cur), NULL);
	usleep(philo_info->timesleep * 1000);
	gettimeofday(&(cur), NULL);
	philo_info->last_act = cur;
}
