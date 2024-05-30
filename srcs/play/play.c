/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 14:39:27 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 23:23:47 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		draw_crosshair(t_cubed *cubed);
void		draw_healthbars(t_cubed *cubed);
void		draw_minimap(t_img *img, const t_resolution *res, t_map *map,
				const t_player *player);

static void	prepare_game(t_cubed *cubed)
{
	prepare_player(cubed);
	prepare_map_specials(cubed);
	prepare_events(cubed);
	prepare_textures(cubed);
	prepare_rays(cubed);
}

static void	update_data(t_cubed *cubed)
{
	update_player_position(&cubed->player, &cubed->scene.map);
	update_player_orientation(&cubed->player);
	update_rays(cubed);
	update_sprite_render_info(cubed);
}

static void	draw_image(t_cubed *cubed)
{
	draw_ceiling(cubed);
	draw_floor(cubed);
	sort_and_draw_renderables(cubed);
	draw_gun_shooting(cubed);
	draw_take_damage(cubed);
	draw_minimap(&cubed->mlx.img, &cubed->scene.resol, &cubed->scene.map,
		&cubed->player);
	draw_healthbars(cubed);
	draw_crosshair(cubed);
}

static int	render_frames(void *data)
{
	t_cubed	*cubed;

	cubed = data;
	if (cubed->game_state == GAME_STATE_RUNNING)
	{
		update_data(cubed);
		draw_image(cubed);
		mlx_put_image_to_window(cubed->mlx.mlx_ptr, cubed->mlx.win,
			cubed->mlx.img.img_ptr, 0, 0);
	}
	if (cubed->game_state == GAME_STATE_OVER)
	{
		clear_screen(cubed);
		draw_game_over_screen(cubed);
		return (1);
	}
	if (cubed->game_state == GAME_STATE_MENU)
		draw_menu(cubed);
	return (1);
}

void	start_game(t_cubed *cubed)
{
	t_mlx	*mlx_data;

	mlx_data = &cubed->mlx;
	mlx_data->mlx_ptr = mlx_init();
	if (!cubed->mlx.mlx_ptr)
		ft_clean_exit(cubed, "mlx_init() failed\n", 0);
	mlx_data->win = mlx_new_window(mlx_data->mlx_ptr, cubed->scene.resol.width,
			cubed->scene.resol.height, "cub3D");
	if (!mlx_data->win)
		ft_clean_exit(cubed, "mlx_new_window() failed\n", 0);
	prepare_game(cubed);
	cubed->mlx.img.img_ptr = mlx_new_image(cubed->mlx.mlx_ptr,
			cubed->scene.resol.width, cubed->scene.resol.height);
	cubed->mlx.img.data = (int *)mlx_get_data_addr(cubed->mlx.img.img_ptr,
			&cubed->mlx.img.bpp, &cubed->mlx.img.size_l,
			&cubed->mlx.img.endian);
	mlx_loop_hook(mlx_data->mlx_ptr, render_frames, cubed);
	mlx_loop(mlx_data->mlx_ptr);
}
