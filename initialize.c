/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:05:34 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 23:49:07 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_unified	*init_unified(char **argv)
{
	t_unified	*uni;

	uni = (t_unified *)malloc(sizeof(t_unified));
	if (uni == NULL)
		return (NULL);
	uni->n_philo = ft_atoi(argv[1]);
	if (uni->n_philo <= 0)
		return (free(uni), NULL);
	if (pthread_mutex_init(&(uni->print), NULL) != 0)
		return (free(uni), NULL);
	if (pthread_mutex_init(&(uni->io), NULL) != 0)
		return (pthread_mutex_destroy(&(uni->print)), free(uni), NULL);
	gettimeofday(&(uni->start), NULL);
	uni->fork = \
		(pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * uni->n_philo);
	if (uni->fork == NULL)
		return (pthread_mutex_destroy(&(uni->print)),
			pthread_mutex_destroy(&(uni->io)), free(uni), NULL);
	uni->end = 0;
	uni->after_meal = 0;
	return (uni);
}

static int	is_all_num(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != 0)
		{
			if (argv[i][j] < '0' || '9' < argv[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

static int	is_all_plus_int(int argc, char **argv)
{
	long	num;
	int		i;

	i = 1;
	while (i < argc)
	{
		num = ft_atol(argv[i]);
		if (num <= 0)
			return (0);
		if (num < (long)INT_MIN || (long)INT_MAX < num)
			return (0);
		i++;
	}
	return (1);
}

int	is_valid_arg(int argc, char **argv)
{
	return (is_all_num(argc, argv) * is_all_plus_int(argc, argv));
}

int	init_philo(t_philo **philo_info, t_unified **unified, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < (*unified)->n_philo)
	{
		(*philo_info)[i].timedie = ft_atoi(argv[2]);
		(*philo_info)[i].timeeat = ft_atoi(argv[3]);
		(*philo_info)[i].timesleep = ft_atoi(argv[4]);
		(*philo_info)[i].n_must_eat = -1;
		if (argc == 6)
			(*philo_info)[i].n_must_eat = ft_atoi(argv[5]);
		(*philo_info)[i].n_has_eaten = 0;
		(*philo_info)[i].a_name = i;
		(*philo_info)[i].unified = *unified;
		(*philo_info)[i].last_meal = (*unified)->start;
		(*philo_info)[i].last_act = (*philo_info)[i].last_meal;
		if (pthread_mutex_init(&((*unified)->fork[i]), NULL) != 0)
			return (destroy_fork((*unified)->fork, i),
				destroy_io(philo_info, i), -1);
		if (pthread_mutex_init(&((*philo_info)[i].id_io), NULL) != 0)
			return (destroy_fork((*unified)->fork, i + 1),
				destroy_io(philo_info, i), -1);
		i++;
	}
	return (0);
}
