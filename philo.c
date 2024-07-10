/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 21:29:05 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 23:53:39 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	fork[0] = Left fork index
	fork[1] = Right fork index

	Wrap around if the right fork index exceeds the number of philosophers
*/
void	*philo(void	*philo_info)
{
	t_philo	*philo_new_info;
	int		fork[2];

	philo_new_info = (t_philo *)philo_info;
	fork[0] = philo_new_info->a_name;
	fork[1] = philo_new_info->a_name + 1;
	if (fork[1] >= (philo_new_info->unified->n_philo))
		fork[1] = 0;
	while (1)
	{
		if (philo_io_end(philo_new_info, 'r') == 1)
			break ;
		philo_eat(philo_new_info, fork);
		if (philo_io_end(philo_new_info, 'r') == 1)
			break ;
		philo_sleep(philo_new_info);
		if (philo_io_end(philo_new_info, 'r') == 1)
			break ;
		philo_think(philo_new_info);
	}
	return (NULL);
}
