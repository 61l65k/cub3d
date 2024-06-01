/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 17:41:22 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/01 17:41:43 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	prepare_rays(t_cubed *cubed)
{
	cubed->rays.ray_array = ft_calloc(cubed->scene.resol.width, sizeof(t_ray));
	if (!cubed->rays.ray_array)
		ft_clean_exit(cubed, CUB_ERROR_MALLOC CUB_ERROR_MALLOC, 0);
	cubed->rays.ray_count = cubed->scene.resol.width;
	cubed->rays.field_of_view = deg2rad(FOV);
	cubed->rays.proj_plane_dist = ((double)cubed->scene.resol.width / 2)
		/ tan(cubed->rays.field_of_view / 2);
}
