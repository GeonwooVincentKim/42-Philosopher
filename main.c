/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:59:23 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/09 22:56:18 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philo.h"

int	init_all(t_philo **philo_info, char **argv, pthread_t **phis, int argc)
{
	t_unified	*unified;

	unified = init_uni(argv);
	if (unified == NULL)
		return (-1);
	*phis = (pthread_t *)malloc(sizeof(pthread_t) * unified->n_phi);
	if (*phis == NULL)
		return (clean_uni(&unified), -1);
	*philo_info = (t_philo *)malloc(sizeof(t_philo) * unified->n_phi);
	if (*philo_info == NULL)
		return (free(*phis), clean_uni(&unified), -1);
	if (init_phi(philo_info, &unified, argv, argc) == -1)
		return (free(*philo_info), free(*phis), clean_uni(&unified), -1);
	return (0);
}

int	main(int argc, char **argv)
{
	int			i;
	pthread_t	*phis;
	pthread_t	grimreaper;
	t_philo		*philo_info;

	if (argc < 5 || argc > 6 || is_valid_arg(argc, argv) != 1)
		return (write(2, "Error\n", 6), 1);
	if (init_all(&(philo_info), argv, &phis, argc) == -1)
		return (-1);
	i = 0;
	while (i < philo_info[0].unified->n_philo)
	{
		pthread_create(&phis[i], NULL, philosophers, &(philo_info[i]));
		i++;
	}
	pthread_create(&grimreaper, NULL, grim, &philo_info);
	i = 0;
	pthread_join(grimreaper, NULL);
	while (i < philo_info[0].unified->n_philo)
	{
		pthread_join(phis[i++], NULL);
	}
	cleanup_all(&philo_info, &phis);
}
