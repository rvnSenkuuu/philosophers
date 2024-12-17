/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:53:11 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/13 16:38:01 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_philo *philo)
{
	if (philo->data->n_philo == 1)
	{
		print_philo(philo, THINK, get_time(philo->data));
		print_philo(philo, FORK, get_time(philo->data));
		ft_usleep(philo->data->time_die, philo->data);
		philo->data->dead = 1;
		print_philo(philo, DEAD, get_time(philo->data));
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	gettimeofday(&data.time_start, NULL);
	if (check_argv(argc, argv))
		return (1);
	init_data(argc, argv, &data);
	init_forks(&data);
	init_philo(&data);
	monitor(&data, data.philo);
	philo_join(&data);
	free_data(&data);
	return (0);
}
