/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:00:55 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/15 13:16:34 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_fork(t_philo *philo, t_data *data)
{
	if (philo->id % 2 == 0)
	{
		print_philo(philo, FORK, get_time(data));
		pthread_mutex_lock(philo->l_fork);
		print_philo(philo, FORK, get_time(data));
		pthread_mutex_lock(philo->r_fork);
	}
	else
	{
		print_philo(philo, FORK, get_time(data));
		pthread_mutex_lock(philo->r_fork);
		print_philo(philo, FORK, get_time(data));
		pthread_mutex_lock(philo->l_fork);
	}
}

static void	philo_eat(t_philo *philo, t_data *data)
{
	take_fork(philo, philo->data);
	print_philo(philo, EAT, get_time(data));
	pthread_mutex_lock(&data->eat_lock);
	philo->last_meal = get_time(data);
	pthread_mutex_unlock(&data->eat_lock);
	ft_usleep(data->time_eat, data);
	pthread_mutex_lock(&data->eat_lock);
	philo->meal_count++;
	pthread_mutex_unlock(&data->eat_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

static void	philo_sleep(t_philo *philo, t_data *data)
{
	print_philo(philo, SLEEP, get_time(data));
	ft_usleep(data->time_sleep, data);
}

static void	philo_think(t_philo *philo, t_data *data)
{
	print_philo(philo, THINK, get_time(data));
	ft_usleep(data->time_die - data->time_eat - data->time_sleep - 10,
		philo->data);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (one_philo(philo) == 1)
		return (NULL);
	while (philo_dead(philo) == 0 && philo_eating(philo) == 0)
	{
		philo_eat(philo, philo->data);
		if (check_after_action(philo) == 1)
			break ;
		philo_sleep(philo, philo->data);
		if (check_after_action(philo) == 1)
			break ;
		philo_think(philo, philo->data);
		if (check_after_action(philo) == 1)
			break ;
	}
	return (NULL);
}
