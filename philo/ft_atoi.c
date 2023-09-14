/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akazuki <akazuki@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 10:55:06 by akazuki           #+#    #+#             */
/*   Updated: 2023/08/23 15:35:15 by akazuki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static long int	ft_check(int negative, unsigned long num, char str)
{
	unsigned long	number;
	unsigned long	x;
	unsigned long	y;

	x = LONG_MAX / 10;
	y = LONG_MAX % 10;
	number = str - '0';
	if (negative == 1)
	{
		if (x < num)
			return (1);
		else
		{
			if (y < number && x == num)
				return (1);
			else
				return (str);
		}
	}
	return (str);
}

static long int	ft_check_n(int negative, long int num, char str)
{
	long int	number;
	long int	x;
	long int	y;

	x = LONG_MIN / 10;
	y = LONG_MIN % 10;
	number = str - '0';
	if (negative == -1)
	{
		if (x > num * negative)
			return (-1);
		else
		{
			if (y > number * negative && x == num * negative)
				return (-1);
			else
				return (num);
		}
	}
	return (num);
}

int	ft_atoi(const char *str)
{
	int			negative;
	long int	num;

	num = 0;
	negative = 1;
	while (*str == ' ' || *str == '\n' || *str == '\t'\
	||*str == '\v' || *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = -negative;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		if (ft_check (negative, num, *str) == 1)
			return (-1);
		if (ft_check_n (negative, num, *str) == -1)
			return (-1);
		num = num * 10 + *str - '0';
		str++;
	}
	num = num * negative;
	return (num);
}

// #include<stdio.h>
// #include<string.h>
// int main(void)
// {
// 	// char a[100]= "9223372036854775807";
// 	// // long int x;
// 	// // long int y;
// 	// printf("%d\n", ft_atoi(a));
// 	// x = LONG_MIN % 10;
// 	// y = long min / 10;
// 	// printf ("%ld\n, x);
// 	// printf("%ld", y);
// 	printf("%d",atoi("9223372036854775805"));
// 	printf("%d",atoi("9223372036854775806"));
// 	printf("%d",atoi("9223372036854775807"));
// 	printf("%d",atoi("9223372036854775808"));
// 	printf("%d",atoi("9223372036854775808"));
// 	printf("%d",atoi("9223372036854775809"));
// 	printf("%d",atoi("9223372036854775810"));
// 	printf("%d",atoi("9223372036854775811"));
// }