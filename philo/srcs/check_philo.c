/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 11:05:53 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/15 11:00:59 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_dead(t_philo *philo)
{
	long	time;
	long	last_meal;

	pthread_mutex_lock(&philo->data->eat_lock);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->data->eat_lock);
	time = get_time(philo->data);
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	else if (time - last_meal > philo->data->time_die)
	{
		philo->data->dead = 1;
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

int	philo_eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->eat_lock);
	if (philo->data->eat == 1)
	{
		pthread_mutex_unlock(&philo->data->eat_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->eat_lock);
	return (0);
}

int	check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->dead_lock);
	if (philo->data->dead == 1)
	{
		pthread_mutex_unlock(&philo->data->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->dead_lock);
	return (0);
}

int	check_after_action(t_philo *philo)
{
	if (check_dead(philo) == 1 || philo_eating(philo) == 1)
	{
		pthread_mutex_lock(&philo->data->after_lock);
		print_philo(philo, "", get_time(philo->data));
		pthread_mutex_unlock(&philo->data->after_lock);
		return (1);
	}
	return (0);
}
