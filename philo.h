/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:10:18 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/10 16:02:14 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdint.h>
# include	<stdlib.h>
# include	<string.h>
# include	<limits.h>
# include	<sys/time.h>

/*
memset, printf, malloc, free, write,
usleep, gettimeofday, pthread_create,
pthread_detach, pthread_join, pthread_mutex_init,
pthread_mutex_destroy, pthread_mutex_lock,
pthread_mutex_unlock
*/

/* Structure */
// Shared state and resources that are common to all philosophers
/*
	Name:	t_unified

	Args:
	- n_philo: The number of philosophers
	- end: 
		A flag indicating if the simulation should end.
		It is used to signal all threads to stop running
	- after_meal:
		A counter to track how many philosophers have finished eating
		the required number of items
	- print:
		A mutex to control access to the console or log output
		Ensure that messages from different threads do not get mixed up
	- io:
		Mutex for read/write access control.
		use for managing shared data
	- start:
		Start time, calculate elapsed time and manage timing events
	- fork:
		An array of mutexes, one for each fork
*/
typedef struct s_unified
{
	int				n_philo;
	int				end;
	int				after_meal;
	pthread_mutex_t	print;
	pthread_mutex_t	io;
	struct timeval	start;
	pthread_mutex_t	*fork;
}	t_unified;

// The state and properties of each individual philosophers
/*
	Name:	t_philo

	Args:
	- timedie:
		The maximum time a philosopher can go without eating before dying
	- timeeat:
		The duration a philosopher spends eating
	- timesleep:
		The duration a philosopher spends sleeping
	- n_time_philo_must_eat:
		Number of times each philosopher must eat
	- n_has_eaten:
		Number of times the philosopher has eaten so far
	- a_name:
		Attribute that defines the number of times of the philosopher
		has eaten so far
	- id_io:
		Individual read/write lock for the philosopher
	- last_act:
		Timestamp of the last action performed by the philosopher
	- last_meal:
		Timestamp of the last meal the philosopher had
		(Used to chek if the philosopher is starving)
	- unified:
		Get t_unified structure for allow each philospher's shared resources
*/
typedef struct s_philo
{
	int					timedie;
	int					timeeat;
	int					timesleep;
	int					n_time_philo_must_eat;
	int					n_has_eaten;
	int					a_name;
	pthread_mutex_t		id_io;
	struct timeval		last_act;
	struct timeval		last_meal;
	struct s_unified	*unified;
}	t_philo;

/* Attribute from LIBFT, but didn't get the LIBFT File-directory */
int		ft_atoi(const char *str);
long	ft_atol(const char *str);
int		ft_isdigit(int c);

/* philosopher.c */
void	*philo(void	*philo_info);

/* grim.c */
void	*grim(void *p_i);
void	*grim_philo(t_philo **philo_info);

/* main.c */
int		init_all(t_philo **philo_info, char **argv, pthread_t **pt, int argc);

#endif