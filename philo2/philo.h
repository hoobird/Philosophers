/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:59:12 by hulim             #+#    #+#             */
/*   Updated: 2024/06/08 21:56:35 by hulim            ###   ########.fr       */
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

typedef struct	s_philosettings t_philosettings;
typedef struct	s_philosopher t_philosopher;

struct	s_philosettings
{
	int				no_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_must_eat;
	int				gameover;
	int				forksavailable;
	pthread_mutex_t forklock;
	pthread_mutex_t printlock;
	struct timeval	start;
};

struct	s_philosopher
{
	int				id;
	t_philosettings	*settings;
	pthread_t		lifethread;
	struct timeval	last_meal;
	int				no_times_eaten;
	int				holdingforks;
	t_philosopher	*next;
};


#endif