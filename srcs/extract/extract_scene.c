/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/16 15:22:58 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static int	get_resolution(char *res_buffer, t_resolution *resolution)
{
	char	**res;

	res = ft_splits(res_buffer, "x");
	if (!res)
		return (perror(CUB_ERROR_MALLOC "get_resolution()\n"), -1);
	if (ft_2d_array_len(res) != 2 || !ft_strisdigit(res[0])
		|| !ft_strisdigit(res[1]))
		return (perror(ERR_RESOLUTION), free_2d_array(res), -1);
	resolution->width = ft_atoi(res[0]);
	resolution->height = ft_atoi(res[1]);
	return (free_2d_array(res), 0);
}

static int	fill_texture(char *texture_path, t_texture *texture)
{
	if (!texture->path)
	{
		texture->path = ft_strdup(texture_path);
		if (!texture->path)
			return (perror(CUB_ERROR_MALLOC "fill_texture()\n"), -1);
	}
	else
		texture->path = 0;
	return (0);
}

static int	get_validate_rgb(char *color_buffer, t_color *color)
{
	char	**rgb;

	rgb = ft_splits(color_buffer, ",");
	if (!rgb)
		return (perror(CUB_ERROR_MALLOC "get_color_rgb()\n"), -1);
	if (ft_2d_array_len(rgb) != 3)
		return (perror(ERR_RGB), free_2d_array(rgb), -1);
	if (!is_valid_color_value(&color->red, rgb[0])
		|| !is_valid_color_value(&color->green, rgb[1])
		|| !is_valid_color_value(&color->blue, rgb[2]))
		return (perror(ERR_RGB), free_2d_array(rgb), -1);
	color->argb = argb_to_int(0, color->red, color->green, color->blue);
	return (free_2d_array(rgb), 0);
}

static int	extract_game_data(t_scenedata *scene, char **data)
{
	if (data[0] == 0)
		return (0);
	if (is_valid_game_identifier("C", data))
		return (get_validate_rgb(data[1], &scene->ceiling_color));
	else if (is_valid_game_identifier("F", data))
		return (get_validate_rgb(data[1], &scene->floor_color));
	else if (is_valid_game_identifier("R", data))
		return (get_resolution(data[1], &scene->resolution));
	else if (is_valid_game_identifier("NO", data))
		return (fill_texture(data[1], &scene->north_texture));
	else if (is_valid_game_identifier("SO", data))
		return (fill_texture(data[1], &scene->south_texture));
	else if (is_valid_game_identifier("WE", data))
		return (fill_texture(data[1], &scene->west_texture));
	else if (is_valid_game_identifier("EA", data))
		return (fill_texture(data[1], &scene->east_texture));
	else if (data[0][0] != '\n')
		return (ft_fprintf(2, "Error\nUnknown identifier: %s", data[0]), -1);
	return (0);
}

void	extract_scene(t_cubed *cubed, char **av)
{
	const int	fd = open(av[1], O_RDONLY);
	char		*line;
	char		**splitted_data;

	line = NULL;
	splitted_data = NULL;
	if (fd < 0)
		ft_clean_exit(NULL, CUB_OPEN_ERROR_MSG);
	while (gnl(fd, &line))
	{
		if (!is_start_of_map(line))
		{
			splitted_data = ft_splits(line, CUB_MAP_SPLIT_DELIMITERS);
			if (!splitted_data)
				ft_clean_exit(cubed, CUB_ERROR_MALLOC "extract_scene()\n");
			if (extract_game_data(&cubed->scene, splitted_data) < 0)
				ft_clean_exit(cubed, NULL);
			free_2d_array(splitted_data);
			free(line);
			line = NULL;
		}
		else
			extract_map(cubed, fd, line);
	}
	return (close(fd), free(line));
}
