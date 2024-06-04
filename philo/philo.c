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

int	p_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

void	p_perror(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, p_strlen(str));
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

int	checkargv(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		p_perror("Incorrect number of arguments (4 or 5)\n");
	else if (checkargnumeric(argc, argv) == 0)
		p_perror("Arguments must be positive integers\n");	
	else
		return (1);
	return (0);
}

int	p_atoi(const char *nptr)
{
	char	*temp;
	int		number;

	number = 0;
	temp = (char *) nptr;
	while ((*temp >= 9 && *temp <= 13) || *temp == 32)
		temp++;
	while (*temp >= '0' && *temp <= '9')
	{
		number = number * 10 + (*temp - '0');
		temp++;
	}
	printf("number: %d\n", number);
	return (number);
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
	{
		p_perror("Arguments must be positive integers\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_philosettings	g_settings;

	if (checkargv(argc, argv) == 1)
	{
		if (setupsettings(&g_settings, argc, argv) == 1)
		{
			printf("no_philo: %d\n", g_settings.no_philo);
			printf("time_to_die: %d\n", g_settings.time_to_die);
			printf("time_to_eat: %d\n", g_settings.time_to_eat);
			printf("time_to_sleep: %d\n", g_settings.time_to_sleep);
			printf("no_must_eat: %d\n", g_settings.no_must_eat);
		}
	}
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	struct timeval	time;
	
// 	(void)argc;
// 	(void)argv;
// 	gettimeofday(&time, NULL);
// 	printf("sec:  %ld\n", time.tv_sec);
// 	printf("usec: %ld\n", time.tv_usec);
// 	return (0);	
// }