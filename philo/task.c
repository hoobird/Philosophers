/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   task.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:47:32 by hulim             #+#    #+#             */
/*   Updated: 2024/07/17 20:25:47 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printstate(t_philosettings *settings, int id, char *status)
{
	struct timeval	now;
	long			timepassed;

	if (getgameover(settings) == 1)
		return ;
	gettimeofday(&now, NULL);
	pthread_mutex_lock(&settings->printlock);
	timepassed = (now.tv_sec - settings->start.tv_sec) * 1000 + (now.tv_usec
			- settings->start.tv_usec) / 1000;
	printf("%ld %d %s\n", timepassed, id, status);
	pthread_mutex_unlock(&settings->printlock);
}

void	updatetimeseaten(t_philosopher *philo, t_philosettings *settings)
{
	pthread_mutex_lock(&philo->last_meal_lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->last_meal_lock);
	printstate(settings, philo->id, "is eating");
	pthread_mutex_lock(&philo->no_times_eaten_lock);
	philo->no_times_eaten++;
	pthread_mutex_unlock(&philo->no_times_eaten_lock);
}

void	*livingthelife(void *voidphilo)
{
	t_philosopher	*philo;

	philo = (t_philosopher *)voidphilo;
	if (philo->id % 2 == 1)
		usleep(10000);
	while (getgameover(philo->settings) == 0)
	{
		pthread_mutex_lock(*(&philo->first));
		printstate(philo->settings, philo->id, "has taken a fork");
		if (philo->first == philo->second)
		{
			pthread_mutex_unlock(*(&philo->first));
			return (NULL);
		}
		pthread_mutex_lock(*(&philo->second));
		printstate(philo->settings, philo->id, "has taken a fork");
		updatetimeseaten(philo, philo->settings);
		usleep(philo->settings->time_to_eat * 1000);
		printstate(philo->settings, philo->id, "is sleeping");
		pthread_mutex_unlock(*(&philo->first));
		pthread_mutex_unlock(*(&philo->second));
		usleep(philo->settings->time_to_sleep * 1000);
		printstate(philo->settings, philo->id, "is thinking");
	}
	return (NULL);
}
