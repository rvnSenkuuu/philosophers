/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 09:53:36 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/13 16:37:48 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <unistd.h>

# define ERR_ARG	"[Error]Usage: ./philo\n[number_of_philosophers]\n[time_to_die]\n\
[time_to_eat]\n[time_to_sleep]\n\
[number_of_times_each_philosopher_must_eat](optional)\n"
# define ERR_NEGATIVE_ARG	"[Error]Handling only positive numbers\n"
# define ERR_INVALD_NUMBER	"[Error]Invalid arguments use valid number\n"

# define FORK	"has taken a fork"
# define EAT	"is eating"
# define SLEEP	"is sleeping"
# define THINK	"is thinking"
# define DEAD	"is dead"

typedef pthread_mutex_t	t_mutex;
typedef struct timeval	t_time;
typedef struct s_data	t_data;

typedef struct s_philo
{
	int			id;
	int			meal_count;
	long		last_meal;
	pthread_t	thread_id;
	t_mutex		*l_fork;
	t_mutex		*r_fork;
	t_data		*data;
}			t_philo;

typedef struct s_data
{
	int		n_philo;
	int		n_meal;
	int		time_die;
	int		time_eat;
	int		time_sleep;
	int		dead;
	int		eat;
	int		end_eating;
	int		one_print;
	t_time	time_start;
	t_philo	*philo;
	t_mutex	*forks;
	t_mutex	eat_lock;
	t_mutex	write_lock;
	t_mutex	dead_lock;
	t_mutex	after_lock;
}			t_data;

void	free_data(t_data *data);
void	ft_usleep(long ms, t_data *data);
void	print_philo(t_philo *philo, char *action, long time);
int		ft_isdigit(int c);
int		ft_atoi(const char *nptr);
int		check_argv(int argc, char **argv);
long	get_time(t_data *data);
void	*ft_calloc(size_t nmemb, size_t size);

void	init_data(int argc, char **argv, t_data *data);
void	init_philo(t_data *data);
void	init_forks(t_data *data);
void	philo_join(t_data *data);

int		one_print(t_philo *philo);
int		one_philo(t_philo *philo);
int		philo_eating(t_philo *philo);
int		philo_dead(t_philo *philo);
int		check_dead(t_philo *philo);
int		check_after_action(t_philo *philo);

void	monitor(t_data *data, t_philo *philo);
void	*routine(void *arg);

#endif