/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:57:24 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/15 11:05:07 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_data(int argc, char **argv, t_data *data)
{
	data->n_philo = ft_atoi(argv[1]);
	data->time_die = ft_atoi(argv[2]);
	data->time_eat = ft_atoi(argv[3]);
	data->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->n_meal = ft_atoi(argv[5]);
	else
		data->n_meal = -1;
	pthread_mutex_init(&data->eat_lock, NULL);
	pthread_mutex_init(&data->write_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->after_lock, NULL);
}

void	init_philo(t_data *data)
{
	int	i;

	data->philo = ft_calloc(data->n_philo, sizeof(t_philo));
	if (!data->philo)
		return (free_data(data));
	i = 0;
	while (i < data->n_philo)
	{
		data->philo[i].id = i + 1;
		data->philo[i].data = data;
		data->philo[i].l_fork = &data->forks[i];
		data->philo[i].r_fork = &data->forks[(i + 1) % data->n_philo];
		if (pthread_create(&data->philo[i].thread_id, NULL,
				routine, &data->philo[i]) < 0)
			return (free_data(data));
		i++;
	}
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	data->forks = ft_calloc(data->n_philo, sizeof(t_mutex));
	if (!data->forks)
		return (free_data(data));
	while (i < data->n_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) < 0)
			return (free_data(data));
		i++;
	}
}

void	philo_join(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_join(data->philo[i].thread_id, NULL);
		i++;
	}
}
