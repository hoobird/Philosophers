/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:44:00 by hulim             #+#    #+#             */
/*   Updated: 2024/07/14 20:11:20 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	checkargv(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (p_perror("Incorrect number of arguments (4 or 5)\n"));
	else if (checkargnumeric(argc, argv) == 0)
		return (p_perror("Arguments must be positive integers\n"));
	return (1);
}

int	checkargnumeric(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	setupsettings(t_philosettings *set, int argc, char **argv)
{
	set->no_philo = p_atoi(argv[1]);
	set->time_to_die = p_atoi(argv[2]);
	set->time_to_eat = p_atoi(argv[3]);
	set->time_to_sleep = p_atoi(argv[4]);
	if (argc == 6)
		set->no_must_eat = p_atoi(argv[5]);
	else
		set->no_must_eat = -1;
	if (set->no_philo == 0 || set->time_to_die == 0 || set->time_to_eat == 0
		|| set->time_to_sleep == 0 || set->no_must_eat == 0)
		return (p_perror("Arguments must be positive integers\n"));
	pthread_mutex_init(&set->printlock, NULL);
	set->gameover = 0;
	gettimeofday(&set->start, NULL);
	return (1);
}

void	decideforks(t_philosettings *set, t_philosopher **philosophers)
{
	int	i;

	i = 0;
	while (i < set->no_philo - 1)
	{
		(*philosophers)[i].first = &(*philosophers)[i].forklock;
		(*philosophers)[i].second = &(*philosophers)[i + 1].forklock;
		(*philosophers)[i].next->first = &(*philosophers)[i].forklock;
		(*philosophers)[i].next->second = &(*philosophers)[i + 1].forklock;
		i += 2;
	}
	if (set->no_philo % 2 == 1)
	{
		(*philosophers)[set->no_philo - 1].second = &(*philosophers)[0].forklock;
		(*philosophers)[set->no_philo
			- 1].first = &(*philosophers)[set->no_philo - 1].forklock;
	}
}
