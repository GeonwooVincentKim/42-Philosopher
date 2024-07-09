/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: geonwkim <geonwkim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:59:23 by geonwkim          #+#    #+#             */
/*   Updated: 2024/07/09 20:59:24 by geonwkim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	init_all(t_phi **phi_info, char **av, pthread_t **phis, int ac)
{
	t_uni	*uni;

	uni = init_uni(av);
	if (uni == NULL)
		return (-1);
	*phis = (pthread_t *)malloc(sizeof(pthread_t) * uni->n_phi);
	if (*phis == NULL)
		return (clean_uni(&uni), -1);
	*phi_info = (t_phi *)malloc(sizeof(t_phi) * uni->n_phi);
	if (*phi_info == NULL)
		return (free(*phis), clean_uni(&uni), -1);
	if (init_phi(phi_info, &uni, av, ac) == -1)
		return (free(*phi_info), free(*phis), clean_uni(&uni), -1);
	return (0);
}

int	main(int ac, char **av)
{
	int			i;
	pthread_t	*phis;
	pthread_t	grimreaper;
	t_phi		*phi_info;

	if (ac < 5 || ac > 6 || is_valid_arg(ac, av) != 1)
		return (write(2, "Error\n", 6), 1);
	if (init_all(&(phi_info), av, &phis, ac) == -1)
		return (-1);
	i = 0;
	while (i < phi_info[0].uni->n_phi)
	{
		pthread_create(&phis[i], NULL, philosophers, &(phi_info[i]));
		i++;
	}
	pthread_create(&grimreaper, NULL, grim, &phi_info);
	i = 0;
	pthread_join(grimreaper, NULL);
	while (i < phi_info[0].uni->n_phi)
	{
		pthread_join(phis[i++], NULL);
	}
	cleanup_all(&phi_info, &phis);
}
