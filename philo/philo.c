/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:58:24 by hulim             #+#    #+#             */
/*   Updated: 2024/07/17 19:31:38 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	startsimulation(t_philosettings *set, t_philosopher *philosophers)
{
	int			i;
	pthread_t	deaththread;

	gettimeofday(&set->start, NULL);
	i = 0;
	while (i < set->no_philo)
	{
		pthread_create(&philosophers[i].lifethread, NULL, livingthelife,
			&philosophers[i]);
		i++;
	}
	pthread_create(&deaththread, NULL, monitorgameover, (void *)philosophers);
	pthread_join(deaththread, NULL);
	i = 0;
	while (i < set->no_philo)
	{
		pthread_join(philosophers[i].lifethread, NULL);
		i++;
	}
}

int	createphilosophers(t_philosettings *set, t_philosopher **philosophers)
{
	int	i;

	*philosophers = p_calloc(set->no_philo + 1, sizeof(t_philosopher));
	if (*philosophers == NULL)
		return (p_perror("Failed to allocate memory for philosophers\n"));
	i = 0;
	while (i < set->no_philo)
	{
		(*philosophers)[i].id = i + 1;
		(*philosophers)[i].no_times_eaten = 0;
		(*philosophers)[i].last_meal = set->start;
		pthread_mutex_init(&(*philosophers)[i].forklock, NULL);
		pthread_mutex_init(&(*philosophers)[i].last_meal_lock, NULL);
		(*philosophers)[i].settings = set;
		(*philosophers)[i].next = &(*philosophers)[(i + 1) % set->no_philo];
		i++;
	}
	decideforks(set, philosophers);
	return (1);
}

void	cleanphilos(t_philosettings *set, t_philosopher *philosophers)
{
	int	i;

	i = 0;
	while (i < set->no_philo)
	{
		pthread_mutex_destroy(&philosophers[i].forklock);
		pthread_mutex_destroy(&philosophers[i].last_meal_lock);
		pthread_mutex_destroy(&philosophers[i].no_times_eaten_lock);
		i++;
	}
	pthread_mutex_destroy(&set->printlock);
	free(philosophers);
}

int	main(int argc, char **argv)
{
	t_philosettings	g_settings;
	t_philosopher	*philosophers;

	if (checkargv(argc, argv) == 1)
	{
		if (setupsettings(&g_settings, argc, argv) == 1)
		{
			if (createphilosophers(&g_settings, &philosophers) == 1)
			{
				startsimulation(&g_settings, philosophers);
				cleanphilos(&g_settings, philosophers);
			}
		}
	}
	return (0);
}
