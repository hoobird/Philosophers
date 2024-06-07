/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:59:12 by hulim             #+#    #+#             */
/*   Updated: 2024/06/03 22:43:34 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <string.h>

typedef struct	s_philosettings
{
	int				no_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_must_eat;
	pthread_mutex_t	printlock;
	struct timeval	start;
}				t_philosettings;

// state: 0 = thinking 1 = eating 2 = sleeping 3 = dead
typedef struct	s_philosopher
{
	int				id;
	t_philosettings	*settings;
	pthread_t		thread;
	struct timeval	last_meal;
	int				no_times_eaten;
	pthread_mutex_t forklock;
	int				forkgone;
}				t_philosopher;


#endif