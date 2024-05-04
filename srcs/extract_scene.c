/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/04 12:37:32 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	get_resolution(char *res_buffer, t_resolution *resolution)
{
	char	**res;

	res = ft_splits(res_buffer, "x");
	if (!res)
		ft_clean_exit("Error: get_resolution()\n");
	resolution->width = ft_atoi(res[0]);
	resolution->height = ft_atoi(res[1]);
	free_2d_array(res);
}

void	fill_texture(char *texture_path, t_texture *texture)
{
	if (!texture->path)
	{
		texture->path = ft_strdup(texture_path);
		if (!texture->path)
			ft_clean_exit("Error: get_texture()\n");
	}
	else
		texture->path = 0;
}

static void	get_color_rgb(char *color_buffer, t_color *color)
{
	char	**rgb;

	rgb = ft_splits(color_buffer, ",");
	if (!rgb)
		ft_clean_exit(CUB_ERROR_MALLOC "get_color_rgb()\n");
	color->red = ft_atoi(rgb[0]);
	color->green = ft_atoi(rgb[1]);
	color->blue = ft_atoi(rgb[2]);
	if (color->red < 0 || color->red > 255 || color->green < 0
		|| color->green > 255 || color->blue < 0 || color->blue > 255)
	{
		free_2d_array(rgb);
		ft_clean_exit(CUB_ERROR_COLOR);
	}
	free_2d_array(rgb);
}

static void	extract_game_data(t_scenedata *scene, char **data)
{
	if (data[0] == 0)
		return ;
	else if (!ft_strcmp(data[0], "C") && data[1] != 0 && data[2] == 0)
		get_color_rgb(data[1], &scene->ceiling_color);
	else if (!ft_strcmp(data[0], "F") && data[1] != 0 && data[2] == 0)
		get_color_rgb(data[1], &scene->floor_color);
	else if (!ft_strcmp(data[0], "R") && data[1] != 0 && data[2] == 0)
		get_resolution(data[1], &scene->resolution);
	else if (!ft_strcmp(data[0], "NO") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->north_texture);
	else if (!ft_strcmp(data[0], "SO") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->south_texture);
	else if (!ft_strcmp(data[0], "WE") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->west_texture);
	else if (!ft_strcmp(data[0], "EA") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->east_texture);
	else if (data[0][0] != '\n')
	{
		printf("Error\nUnknown identifier: %s", data[0]);
		exit(EXIT_SUCCESS);
	}
}

void	extract_scene(t_scenedata *scene, char **av)
{
	const int	fd = open(av[1], O_RDONLY);
	char		*line;
	char		**splitted_data;

	if (fd < 0)
		ft_clean_exit(CUB_OPEN_ERROR_MSG);
	while (gnl(fd, &line))
	{
		if (is_start_of_map(line))
		{
			extract_map(scene, fd, line);
			break ;
		}
		else
		{
			splitted_data = ft_splits(line, " \n\t\v\f\r");
			if (!splitted_data)
				ft_clean_exit("Error: ft_splits()\n");
			extract_game_data(scene, splitted_data);
			free_2d_array(splitted_data);
		}
		free(line);
	}
	free(line);
	close(fd);
}
