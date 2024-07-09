/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:10:18 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/09 20:33:17 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include	<pthread.h>
# include	<unistd.h>
# include	<stdio.h>
# include	<stdint.h>
# include	<stdlib.h>
# include	<string.h>
# include	<limits.h>

/* philosopher.c */

/* Attribute from LIBFT, but didn't get the LIBFT File-directory */
int		ft_atoi(const char *str);
long	ft_atol(const char *str);

#endif