/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:17:19 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/08 14:20:08 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = 0;
}

int	ft_2d_array_len(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}

int	argb_to_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}