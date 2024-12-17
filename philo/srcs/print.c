/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:40:52 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/15 11:29:48 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_print(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->write_lock);
	if (philo->data->one_print == 0)
	{
		pthread_mutex_unlock(&philo->data->write_lock);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->write_lock);
	return (1);
}

void	print_philo(t_philo *philo, char *action, long time)
{
	if (one_print(philo) == 0 && philo_dead(philo) == 0
		&& philo_eating(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		printf("%ld %d %s\n", time, philo->id, action);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
	else if (one_print(philo) == 0 && philo_eating(philo) == 1)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		philo->data->one_print = 1;
		printf("%ld all philo ate\n", time);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
	else if (one_print(philo) == 0 && philo_dead(philo) == 1)
	{
		pthread_mutex_lock(&philo->data->write_lock);
		philo->data->one_print = 1;
		printf("%ld %d %s\n", time, philo->id, DEAD);
		pthread_mutex_unlock(&philo->data->write_lock);
	}
}
