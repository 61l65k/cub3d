/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:58:18 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/04 18:16:16 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	validate_resolution(t_resolution *resolution)
{
	if (resolution->width < 1 || resolution->height < 1)
	{
		printf("Invalid resolution or no resolution found from file\n");
		printf("Defaulting to 1920x1080\n");
		resolution->width = 1920;
		resolution->height = 1080;
	}
	if (resolution->width > MAX_X_RES)
		resolution->width = MAX_X_RES;
	if (resolution->height > MAX_Y_RES)
		resolution->height = MAX_Y_RES;
}

void	validate_scene(t_cubed *cubed)
{
	validate_resolution(&cubed->scene.resolution);
	(void)cubed;
}
