/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:51:28 by hulim             #+#    #+#             */
/*   Updated: 2024/07/14 20:09:17 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	gettimepassed(t_philosopher *philosopher)
{
	struct timeval	now;
	long			timepassed;

	pthread_mutex_lock(&philosopher->last_meal_lock);
	gettimeofday(&now, NULL);
	timepassed = (now.tv_sec - philosopher->last_meal.tv_sec) * 1000
		+ (now.tv_usec - philosopher->last_meal.tv_usec) / 1000;
	pthread_mutex_unlock(&philosopher->last_meal_lock);
	return (timepassed);
}

void	countwhoeaten(t_philosopher *philosopher, t_philosettings *settings,
		int *whoeaten)
{
	pthread_mutex_lock(&philosopher->no_times_eaten_lock);
	if (settings->no_must_eat != -1
		&& philosopher->no_times_eaten >= settings->no_must_eat)
	{
		(*whoeaten)++;
	}
	pthread_mutex_unlock(&philosopher->no_times_eaten_lock);
}

void	*gameover(t_philosettings *settings)
{
	settings->gameover = 1;
	return (NULL);
}

void	*monitorgameover(void *voidphilo)
{
	long			timepassed;
	t_philosopher	*philosophers;
	t_philosettings	*settings;
	int				whoeaten;
	int				i;

	philosophers = (t_philosopher *)voidphilo;
	settings = philosophers[0].settings;
	while (1)
	{
		i = 0;
		whoeaten = 0;
		while (i < settings->no_philo)
		{
			timepassed = gettimepassed(&philosophers[i]);
			if (timepassed > settings->time_to_die)
			{
				printstate(settings, philosophers[i].id, "died");
				return (gameover(settings));
			}
			countwhoeaten(&philosophers[i++], settings, &whoeaten);
		}
		if (whoeaten == settings->no_philo)
			return (gameover(settings));
	}
}
