/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 14:55:40 by akazuki           #+#    #+#             */
/*   Updated: 2023/09/11 18:13:41 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	is_str_digit(char *str)
{
	size_t	i;

	i = 0;
	if (str == NULL)
		return (1);
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || '9' < str[i])
			return (1);
		i++;
	}
	return (0);
}

static int	check_digit(char **argv)
{
	size_t	i;

	i = 1;
	while (argv[i] != NULL)
	{
		if (is_str_digit(argv[i]) == 1 || ft_atoi(argv[i]) == -1)
			return (1);
		i++;
	}
	return (0);
}

int	check_error(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (1);
	else
		return (check_digit(argv));
}
