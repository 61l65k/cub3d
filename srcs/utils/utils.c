/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:06 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/04 17:35:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_cubfile(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}

bool	is_valid_game_identifier(const char *identifier, char **data)
{
	return (!ft_strcmp(data[0], identifier) && data[1] != 0 && data[2] == 0);
}

int	is_start_of_map(char *line)
{
	int	check;

	check = 0;
	while (*line)
	{
		if (!ft_strchr("012NSEW \n\t\v\f\r", *line))
			return (0);
		else if (*line == '1')
			check = 1;
		line++;
	}
	return (check);
}

bool	is_valid_color_value(int *color, char *value)
{
	if (!ft_strisdigit(value))
		return (false);
	*color = ft_atoi(value);
	if (*color < 0 || *color > 255)
		return (false);
	return (true);
}
