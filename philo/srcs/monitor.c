/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 15:37:27 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/15 13:20:41 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_eating_monitor(t_data *data, t_philo *philo, int i)
{
	pthread_mutex_lock(&data->eat_lock);
	if (data->n_meal > 0 && philo[i].meal_count >= data->n_meal)
		data->end_eating++;
	pthread_mutex_unlock(&data->eat_lock);
}

static int	finish_eating_monitor(t_data *data)
{
	pthread_mutex_lock(&data->eat_lock);
	if (data->end_eating >= data->n_philo)
	{
		data->eat = 1;
		pthread_mutex_unlock(&data->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->eat_lock);
	return (0);
}

void	monitor(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data->n_philo == 1)
		return ;
	while (1)
	{
		while (i < data->n_philo)
		{
			if (philo_dead(&philo[i]) == 1)
				return ;
			check_eating_monitor(data, philo, i);
			i++;
		}
		if (finish_eating_monitor(data) == 1)
			return ;
		i = 0;
		data->end_eating = 0;
		usleep(50);
	}
}
