/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:52:48 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/02 00:19:19 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	extract_game_data(t_scenedata *scene, char **data)
{
	if (data[0] == 0)
		return ;
	else if (!ft_strcmp(data[0], "NO") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->no_tex);
	else if (!ft_strcmp(data[0], "SO") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->so_tex);
	else if (!ft_strcmp(data[0], "WE") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->we_tex);
	else if (!ft_strcmp(data[0], "EA") && data[1] != 0 && data[2] == 0)
		fill_texture(data[1], &scene->ea_tex);
	else if (data[0][0] != '\n')
	{
		printf("Error\nUnknown identifier: %s", data[0]);
		exit(EXIT_SUCCESS);
	}
}

void	extract_scene(t_scenedata *scene, char **av)
{
	const int fd = open(av[1], O_RDONLY);
	char *line;
	char **splitted_data;

	if (fd < 0)
		ft_clean_exit(CUB_OPEN_ERROR_MSG);
	while (gnl(fd, &line))
	{
		if (!is_start_of_map(line))
		{
			extract_map(scene, fd, line);
			break ;
		}
		else
		{
			splitted_data = ft_splits(line, "\n\t\v\f\r");
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