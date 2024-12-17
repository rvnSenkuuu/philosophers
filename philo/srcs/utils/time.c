/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:49:51 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/13 10:34:47 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(t_data *data)
{
	t_time	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec - data->time_start.tv_sec) * 1000
		+ (time.tv_usec - data->time_start.tv_usec) / 1000);
}

static int	philo_still_alive(t_data *data)
{
	pthread_mutex_lock(&data->dead_lock);
	if (data->dead == 0)
	{
		pthread_mutex_unlock(&data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&data->dead_lock);
	return (0);
}

void	ft_usleep(long ms, t_data *data)
{
	long	time;

	time = get_time(data);
	while (philo_still_alive(data) == 1 && get_time(data) - time < ms)
		usleep(50);
}
