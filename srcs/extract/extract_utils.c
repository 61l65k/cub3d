/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:06 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/06 19:13:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	has_extension(char *file, char *ext)
{
	const int	file_len = ft_strlen(file);
	const int	ext_len = ft_strlen(ext);

	if (file_len < ext_len)
		return (0);
	return (ft_strncmp(file + file_len - ext_len, ext, ext_len) == 0);
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

bool	does_texture_exist(char *texture_path, char *texture_name)
{
	int	fd;

	if (texture_path == 0)
		return (ft_fprintf(2, ERR_POORLY_FORMATTED, texture_name), false);
	if (!has_extension(texture_path, ".xpm"))
		return (ft_fprintf(2, ERR_INVALID_EXTENSION, texture_path), false);
	fd = open(texture_path, O_RDONLY);
	if (fd < 0)
		return (ft_fprintf(2, ERR_OPENTEXT, texture_name, texture_path), false);
	close(fd);
	return (true);
}
