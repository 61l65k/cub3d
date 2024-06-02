/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_load_items.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:19:42 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 15:22:57 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_more_item_textures(t_cubed *cubed, t_item_textures *i)
{
	const char	*boots = "./assets/default/items/boots.xpm";
	const char	*cloak = "./assets/default/items/cloak.xpm";
	const char	*bread = "./assets/default/items/bread.xpm";

	i->boots.path = ft_strdup(boots);
	i->cloak.path = ft_strdup(cloak);
	i->bread.path = ft_strdup(bread);
	if (!i->boots.path || !i->cloak.path || !i->bread.path)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->boots);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->cloak);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->bread);
}

void	load_all_item_textures(t_cubed *cubed)
{
	t_item_textures	*i;
	const char		*health = "./assets/default/items/health.xpm";
	const char		*poison = "./assets/default/items/poison.xpm";

	i = &cubed->scene.sprite_info.item_info.item_textures;
	i->health.path = ft_strdup(health);
	i->poison.path = ft_strdup(poison);
	if (!i->health.path || !i->poison.path)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->health);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->poison);
	load_more_item_textures(cubed, i);
}
