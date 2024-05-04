/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:24:56 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/04 13:26:43 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_texture(t_texture *texture)
{
	if (texture->path)
		free(texture->path);
	if (texture->img.img_ptr || texture->img.data)
	{
		free(texture->img.data);
		free(texture->img.img_ptr);
		texture->img.data = 0;
		texture->img.img_ptr = 0;
	}
}

void	ft_clean_exit(t_cubed *cubed, char *msg)
{
	if (cubed)
	{
		free_texture(&cubed->scene.north_texture);
	}
	perror(msg);
	exit(EXIT_FAILURE);
}