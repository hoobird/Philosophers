/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 13:58:24 by hulim             #+#    #+#             */
/*   Updated: 2024/06/03 23:05:40 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *p_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	memset(ptr, 0, nmemb * size);
	return (ptr);
}

int p_strlen(char *str)
{
	int i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int p_perror(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, p_strlen(str));
	return (0);
}

int checkargnumeric(int argc, char **argv)
{
	int i;
	int j;

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

int checkargv(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (p_perror("Incorrect number of arguments (4 or 5)\n"));
	else if (checkargnumeric(argc, argv) == 0)
		return (p_perror("Arguments must be positive integers\n"));
	return (1);
}

int p_atoi(const char *nptr)
{
	char *temp;
	int number;

	number = 0;
	temp = (char *)nptr;
	while ((*temp >= 9 && *temp <= 13) || *temp == 32)
		temp++;
	while (*temp >= '0' && *temp <= '9')
	{
		number = number * 10 + (*temp - '0');
		temp++;
	}
	return (number);
}

int setupsettings(t_philosettings *set, int argc, char **argv)
{
	set->no_philo = p_atoi(argv[1]);
	set->time_to_die = p_atoi(argv[2]) * 1000;
	set->time_to_eat = p_atoi(argv[3]) * 1000;
	set->time_to_sleep = p_atoi(argv[4]) * 1000;
	if (argc == 6)
		set->no_must_eat = p_atoi(argv[5]);
	else
		set->no_must_eat = -1;
	if (set->no_philo == 0 || set->time_to_die == 0 || set->time_to_eat == 0 || set->time_to_sleep == 0 || set->no_must_eat == 0)
		return (p_perror("Arguments must be positive integers\n"));
	pthread_mutex_init(&set->printlock, NULL);
	return (1);
}

int createphilosophers(t_philosettings *set, t_philosopher **philosophers)
{
	int i;

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
		(*philosophers)[i].settings = set;
		(*philosophers)[i].forkgone = 0;
		i++;
	}
	return (1);
}

void printstate(t_philosettings *settings, int id, char *status)
{
	struct timeval	now;
	long			timepassed;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&settings->printlock);
	timepassed = (now.tv_sec - settings->start.tv_sec) * 1000
					+ (now.tv_usec - settings->start.tv_usec) / 1000;
	printf("%ld %d %s\n", timepassed, id, status);
	pthread_mutex_unlock(&settings->printlock);
}

void *livingthelife(void *voidphilo)
{
	t_philosopher *philo = (t_philosopher *)voidphilo;
	t_philosettings *settings = philo->settings;
	t_philosopher *philosophers = (t_philosopher *)(settings + 1);

	int left_fork = philo->id - 1;
	int right_fork = ((philo->id) % settings->no_philo);

	while (1)
	{
		printstate(settings, philo->id, "is thinking");

		printf("philo%d attempt to lock my fork\n", philo->id);
		pthread_mutex_lock(&philosophers[left_fork].forklock);
		printf("philo%d attempt to lock next fork\n", philo->id);
		pthread_mutex_lock(&philosophers[right_fork].forklock);

		printstate(settings, philo->id, "has taken a fork (mine)");
		printstate(settings, philo->id, "has taken a fork (next)");

		gettimeofday(&philo->last_meal, NULL);
		printstate(settings, philo->id, "is eating");
		usleep(settings->time_to_eat);

		printstate(settings, philo->id, "is sleeping");
		pthread_mutex_unlock(&philosophers[left_fork].forklock);
		pthread_mutex_unlock(&philosophers[right_fork].forklock);

		usleep(settings->time_to_sleep);
	}
	return NULL;
}

void *monitordeath(void *voidphilo)
{
	struct timeval now;
	t_philosopher *philosophers = (t_philosopher *)voidphilo;
	t_philosettings *settings = philosophers->settings;

	while (1)
	{
		for (int i = 0; i < settings->no_philo; i++)
		{
			gettimeofday(&now, NULL);
			long elapsed_time = (now.tv_sec - philosophers[i].last_meal.tv_sec) * 1000
								+ (now.tv_usec - philosophers[i].last_meal.tv_usec) / 1000;

			if (elapsed_time > settings->time_to_die)
			{
				printstate(settings, philosophers[i].id, "died");
				return NULL;
			}
		}
		usleep(1000); // Check every 1 millisecond
	}
	return NULL;
}

void startsimulation(t_philosettings *set, t_philosopher *philosophers)
{
	int i;

	gettimeofday(&set->start, NULL);
	pthread_t deaththread;
	i = 0;
	while (i < set->no_philo)
	{
		pthread_create(&philosophers[i].thread, NULL, livingthelife, &philosophers[i]);
		i++;
	}
	pthread_create(&deaththread, NULL, monitordeath, (void *)philosophers);
	pthread_join(deaththread, NULL);
	i = 0;
	while (i < set->no_philo)
	{
		pthread_join(philosophers[i].thread, NULL);
		i++;
	}
}

int main(int argc, char **argv)
{
	t_philosettings g_settings;
	t_philosopher *philosophers;

	if (checkargv(argc, argv) == 1)
	{
		if (setupsettings(&g_settings, argc, argv) == 1)
		{
			if (createphilosophers(&g_settings, &philosophers) == 1)
			{
				printf("Number of philosophers: %d\n", g_settings.no_philo);
				printf("Time to die: %d\n", g_settings.time_to_die);
				printf("Time to eat: %d\n", g_settings.time_to_eat);
				printf("Time to sleep: %d\n", g_settings.time_to_sleep);
				startsimulation(&g_settings, philosophers);
			}
		}
	}
	return (0);
}
