/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulim <hulim@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 19:42:37 by hulim             #+#    #+#             */
/*   Updated: 2024/07/14 20:11:03 by hulim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*p_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

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

int	p_perror(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, p_strlen(str));
	return (0);
}

int	p_atoi(const char *nptr)
{
	char	*temp;
	int		number;

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
