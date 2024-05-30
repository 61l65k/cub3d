/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_to_long.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 13:35:14 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/30 14:26:37 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static
void	skip_whitespace(const char **str)
{
	while (**str == ' ' || **str == '\t')
		(*str)++;
}

long	str_to_long(const char *str)
{
	long	result;
	long	sign;
	long	tmp;

	skip_whitespace(&str);
	sign = 1;
	if (*str == '-')
	{
		sign = -sign;
		str++;
	}
	result = 0;
	while (*str >= '0' && *str <= '9')
	{
		tmp = result;
		result = result * 10 + (*str++ - '0');
		if (tmp > result && sign == 1)
			return (LONG_MAX);
		else if (tmp > result && sign == -1)
			return (LONG_MIN);
	}
	return (result * sign);
}
