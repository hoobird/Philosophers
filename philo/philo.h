/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:59:12 by hulim             #+#    #+#             */
/*   Updated: 2024/07/17 20:27:56 by hulim            ###   ########.fr       */
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

typedef struct s_philosettings	t_philosettings;
typedef struct s_philosopher	t_philosopher;

struct s_philosettings
{
	int				no_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				no_must_eat;
	int				gameover;
	pthread_mutex_t	gameoverlock;
	pthread_mutex_t	printlock;
	struct timeval	start;
};

struct s_philosopher
{
	int				id;
	t_philosettings	*settings;
	pthread_t		lifethread;
	pthread_mutex_t	last_meal_lock;
	struct timeval	last_meal;
	pthread_mutex_t	no_times_eaten_lock;
	int				no_times_eaten;
	pthread_mutex_t	forklock;
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
	t_philosopher	*next;
};

// tools.c
void	*p_calloc(size_t nmemb, size_t size);
int		p_strlen(char *str);
int		p_perror(char *str);
int		p_atoi(const char *nptr);

// philo.c
void	startsimulation(t_philosettings *set, t_philosopher *philosophers);
int		createphilosophers(t_philosettings *set, t_philosopher **philosophers);
void	cleanphilos(t_philosettings *set, t_philosopher *philosophers);

// setup.c
int		checkargv(int argc, char **argv);
int		checkargnumeric(int argc, char **argv);
int		setupsettings(t_philosettings *set, int argc, char **argv);
void	decideforks(t_philosettings *set, t_philosopher **philosophers);

// task.c
void	*livingthelife(void *voidphilo);
void	updatetimeseaten(t_philosopher *philo, t_philosettings *settings);
void	printstate(t_philosettings *settings, int id, char *status);

// monitor.c
long	gettimepassed(t_philosopher *philosopher);
void	countwhoeaten(t_philosopher *philosopher, t_philosettings *settings,
			int *whoeaten);
void	*setgameover(t_philosettings	*settings);
int		getgameover(t_philosettings *settings);
void	*monitorgameover(void *voidphilo);

#endif