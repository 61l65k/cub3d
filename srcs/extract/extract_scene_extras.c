/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_screne_extras.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 09:47:17 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 09:58:04 by apyykone         ###   ########.fr       */
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
		return (fill_texture(data[1], &scene->sprite_info.spawner_texture));
	else if (is_valid_game_identifier("DOOR_CLOSED", data))
		return (fill_texture(data[1], &scene->sprite_info.spawner_texture));
	return (0);
}
