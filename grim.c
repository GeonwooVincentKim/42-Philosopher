/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 23:13:25 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 23:32:46 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	pt_mutex_unlock(pthread_mutex_t *p)
{
	return (pthread_mutex_unlock(p));
}

// To avoid Explicit Conversion (明示的キャストを避けるために使用)
void	*grim(void *p_i)
{
	grim_philo((t_philo **philo_info)p_i);
	return (NULL);
}

void	*grim_philo(t_philo **philo_info)
{
	struct timeval	now;
	struct timeval	lastmeal;
	int				i;

	while (1)
	{
		i = 0;
		while (i < (*(philo_info))[0].unified->n_philo)
		{
			if (philosophers_rw_end((*(philo_info)), 'r') == 1)
				return (NULL);
			philosophers_rw_time(&((*(philo_info))[i]), 'r', &lastmeal);
			gettimeofday(&(now), NULL);
			if (philo_elasped_time(lastmeal, now) > (*(philo_info))[i].timedie)
			{
				philosophers_print(&((*(philo_info))[i]), "died", 1);
				i = -1;
				while (++i < (*(philo_info))[0].unified->n_philo)
					pt_mutex_unlock(&(((*(philo_info))->unified->fork)[i]));
				return (NULL);
			}
			i++;
		}
		usleep(10);
	}
}
