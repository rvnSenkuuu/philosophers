/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkara2 <tkara2@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 11:25:18 by tkara2            #+#    #+#             */
/*   Updated: 2024/09/11 10:12:48 by tkara2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_digit(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i] && i < argc)
	{
		j = 0;
		if (!ft_isdigit(argv[i][j]))
		{
			printf(ERR_INVALD_NUMBER);
			return (1);
		}
		i++;
		j++;
	}
	return (0);
}

int	check_argv(int argc, char **argv)
{
	int	i;

	if (argc < 5)
	{
		printf(ERR_ARG);
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		if (ft_atoi(argv[i]) < 0)
		{
			printf(ERR_NEGATIVE_ARG);
			return (1);
		}
		i++;
	}
	if (check_if_digit(argc, argv))
		return (1);
	return (0);
}
