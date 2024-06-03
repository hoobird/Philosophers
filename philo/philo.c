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

int	main(int argc, char **argv)
{
	if (checkargv(argc, argv) == 1)
	{
		printf("Arguments are correct\n");
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