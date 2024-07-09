/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:29:05 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/09 22:00:41 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void	*philo_info)
{
	t_philo	*philo_new_info;
	int		fork[2];

	philo_new_info = (t_philo *)philo_info;
	fork[0] = philo_new_info->name;
	fork[1] = philo_new_info->name + 1;
	if (fork[1] >= (philo_new_info->unified->n_philo))
		fork[1] = 0;
	while (1)
	{
		if (philo_io_end(philo_new_info, 'r') == 1)
			break ;
		philo_eat(philo_new_info, fork);
		if (philo_io_end(philo_new_info, 'r') == 1)
			break ;
		philo_sleep(philo_new_info, fork);
		if (philo_io_end(philo_new_info, 'r') == 1)
			break ;
		philo_think(philo_new_info);
	}
	return (NULL);
}
