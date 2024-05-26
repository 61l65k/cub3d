/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting_traverse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:21:41 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/25 17:38:45 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		check_for_hits(t_cubed *cubed, int map_x, int map_y, float damage);

static void	determine_steps_and_initial_side_distances(t_cubed *cubed,
		const t_ray *ray, t_apply_damage_helper *helper)
{
	if (ray->dir_x < 0)
	{
		helper->step_x = -1;
		helper->side_dist_x = (cubed->player.x - helper->map_x)
			* helper->delta_dist_x;
	}
	else
	{
		helper->step_x = 1;
		helper->side_dist_x = (helper->map_x + 1.0 - cubed->player.x)
			* helper->delta_dist_x;
	}
	if (ray->dir_y < 0)
	{
		helper->step_y = -1;
		helper->side_dist_y = (cubed->player.y - helper->map_y)
			* helper->delta_dist_y;
	}
	else
	{
		helper->step_y = 1;
		helper->side_dist_y = (helper->map_y + 1.0 - cubed->player.y)
			* helper->delta_dist_y;
	}
}

static void	perform_dda_step(t_apply_damage_helper *helper)
{
	if (helper->side_dist_x < helper->side_dist_y)
	{
		helper->side_dist_x += helper->delta_dist_x;
		helper->map_x += helper->step_x;
		helper->current_distance = helper->side_dist_x;
	}
	else
	{
		helper->side_dist_y += helper->delta_dist_y;
		helper->map_y += helper->step_y;
		helper->current_distance = helper->side_dist_y;
	}
}

bool	traverse_and_apply_damage(t_cubed *cubed, const t_ray *ray,
		double max_distance, float damage)
{
	t_apply_damage_helper	helper;

	helper = (t_apply_damage_helper){0};
	helper.current_distance = 0.0;
	helper.delta_dist_x = fabs(1 / ray->dir_x);
	helper.delta_dist_y = fabs(1 / ray->dir_y);
	helper.map_x = (int)cubed->player.x;
	helper.map_y = (int)cubed->player.y;
	determine_steps_and_initial_side_distances(cubed, ray, &helper);
	while (helper.current_distance < max_distance)
	{
		perform_dda_step(&helper);
		if (check_for_hits(cubed, helper.map_x, helper.map_y, damage))
			return (true);
	}
	return (false);
}
