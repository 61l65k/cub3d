/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_load_items.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:19:42 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 14:20:18 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	load_more_item_textures(t_cubed *cubed, t_item_info *i)
{
	const char	*boots = "./assets/default/items/boots.xpm";
	const char	*cloak = "./assets/default/items/cloak.xpm";
	const char	*bread = "./assets/default/items/bread.xpm";

	i->textures[ITEM_BOOTS].path = ft_strdup(boots);
	i->textures[ITEM_CLOAK].path = ft_strdup(cloak);
	i->textures[ITEM_BREAD].path = ft_strdup(bread);
	if (!i->textures[ITEM_BOOTS].path || !i->textures[ITEM_CLOAK].path
		|| !i->textures[ITEM_BREAD].path)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->textures[ITEM_BOOTS]);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->textures[ITEM_CLOAK]);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->textures[ITEM_BREAD]);
}

void	load_all_item_textures(t_cubed *cubed)
{
	t_item_info	*i;
	const char	*health = "./assets/default/items/health.xpm";
	const char	*poison = "./assets/default/items/poison.xpm";
	const char	*book = "./assets/default/items/book_of_wisdom.xpm";

	i = &cubed->scene.sprite_info.item_info;
	i->textures[ITEM_HEALTH].path = ft_strdup(health);
	i->textures[ITEM_POISON].path = ft_strdup(poison);
	i->textures[ITEM_BOOK].path = ft_strdup(book);
	if (!i->textures[ITEM_HEALTH].path || !i->textures[ITEM_POISON].path
		|| !i->textures[ITEM_BOOK].path)
		ft_clean_exit(cubed, ERR_LOAD_TEXTURE, 0);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->textures[ITEM_HEALTH]);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->textures[ITEM_POISON]);
	load_texture(cubed, cubed->mlx.mlx_ptr, &i->textures[ITEM_BOOK]);
	load_more_item_textures(cubed, i);
}
