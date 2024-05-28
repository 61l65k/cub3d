/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 09:54:37 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int			extract_scene_extras(t_scenedata *scene, char **data);

static int	get_resolution(char *res_buffer, t_resolution *resolution)
{
	char	**res;

	res = ft_splits(res_buffer, "x");
	if (!res)
		return (perror(CUB_ERROR_MALLOC "get_resolution()"), -1);
	if (ft_2d_array_len(res) != 2 || !ft_strisdigit(res[0])
		|| !ft_strisdigit(res[1]))
		return (perror(ERR_RESOLUTION), free_2d_array(res), -1);
	resolution->width = ft_atoi(res[0]);
	resolution->height = ft_atoi(res[1]);
	return (free_2d_array(res), 0);
}

int	fill_texture(char *texture_path, t_texture *texture)
{
	if (!texture->path)
	{
		texture->path = ft_strdup(texture_path);
		if (!texture->path)
			return (perror(CUB_ERROR_MALLOC "fill_texture()"), -1);
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
		return (perror(CUB_ERROR_MALLOC "get_color_rgb()"), -1);
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
		return (get_resolution(data[1], &scene->resol));
	else if (is_valid_game_identifier("NO", data))
		return (fill_texture(data[1], &scene->north_texture));
	else if (is_valid_game_identifier("SO", data))
		return (fill_texture(data[1], &scene->south_texture));
	else if (is_valid_game_identifier("WE", data))
		return (fill_texture(data[1], &scene->west_texture));
	else if (is_valid_game_identifier("EA", data))
		return (fill_texture(data[1], &scene->east_texture));
	else if (extract_scene_extras(scene, data) < 0)
		return (-1);
	else if (data[0][0] != '\n')
		return (ft_fprintf(2, "Error\nUnknown identifier: %s", data[0]), -1);
	return (0);
}

int	extract_scene(t_cubed *cubed, char *line)
{
	char	**splitted_data;

	splitted_data = ft_splits(line, CUB_MAP_SPLIT_DELIMITERS);
	if (!splitted_data)
		return (-1);
	if (extract_game_data(&cubed->scene, splitted_data) < 0)
	{
		free_null_2d_array(&splitted_data);
		return (-1);
	}
	free_null_2d_array(&splitted_data);
	return (0);
}
