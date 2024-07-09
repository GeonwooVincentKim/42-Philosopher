/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:13:25 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/09 23:19:41 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	pmu(pthread_mutex_t *p)
{
	return (pthread_mutex_unlock(p));
}

void	*grim(void *p_i)
{
	struct timeval	now;
	struct timeval	lastmeal;
	int				i;

	while (1)
	{
		i = 0;
		while (i < (*(t_philo **)p_i)[0].unified->n_philo)
		{
			if (philosophers_rw_end((*(t_philo **)p_i), 'r') == 1)
				return (NULL);
			philosophers_rw_time(&((*(t_philo **)p_i)[i]), 'r', &lastmeal);
			gettimeofday(&(now), NULL);
			if (get_elspsed_time(lastmeal, now) > (*(t_philo **)p_i)[i].timedie)
			{
				philosophers_print(&((*(t_philo **)p_i)[i]), "died", 1);
				i = -1;
				while (++i < (*(t_philo **)p_i)[0].unified->n_philo)
					pmu(&(((*(t_philo **)p_i)->unified->fork)[i]));
				return (NULL);
			}
			i++;
		}
		usleep(10);
	}
}
