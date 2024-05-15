/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:27:36 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/15 21:36:27 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_texture(t_cubed *cubed, void *mlx, t_texture *texture)
{
	texture->img.img_ptr = mlx_xpm_file_to_image(mlx, texture->path,
			&texture->width, &texture->height);
	if (!texture->img.img_ptr)
		ft_clean_exit(cubed, "mlx_xpm_file_to_image() failed\n");
	texture->img.data = (int *)mlx_get_data_addr(texture->img.img_ptr,
			&texture->img.bpp, &texture->img.size_l, &texture->img.endian);
	if (!texture->img.data)
		ft_clean_exit(cubed, "mlx_get_data_addr() failed\n");
}

void	prepare_textures(t_cubed *cubed)
{
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.north_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.south_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.west_texture);
	load_texture(cubed, cubed->mlx.mlx_ptr, &cubed->scene.east_texture);
}
