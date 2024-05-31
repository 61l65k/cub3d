/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_scene_extras.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:47:17 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/31 16:35:50 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	fill_texture(char *texture_path, t_texture *texture);

int	extract_scene_extras(t_scenedata *scene, char **data)
{
	if (is_valid_game_identifier("SPRITE", data))
		return (fill_texture(data[1], &scene->sprite_info.sprite_texture));
	else if (is_valid_game_identifier("SPAWNER", data))
		return (fill_texture(data[1], &scene->sprite_info.spawner_texture));
	else if (is_valid_game_identifier("DOOR_OPEN", data))
		return (fill_texture(data[1], &scene->sprite_info.door_open_texture));
	else if (is_valid_game_identifier("DOOR_CLOSED", data))
		return (fill_texture(data[1], &scene->sprite_info.door_closed_texture));
	else if (data[0][0] != '\n')
		return (ft_fprintf(2, "Error\nUnknown identifier: %s", data[0]), -1);
	return (0);
}
