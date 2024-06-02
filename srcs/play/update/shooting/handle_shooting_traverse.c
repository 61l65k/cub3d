/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_shooting_traverse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:21:41 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/02 13:05:03 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool		check_for_hits(t_cubed *cubed, int map_x, int map_y, float damage);

static void	determine_steps_and_initial_side_distances(t_cubed *cubed,
		const t_ray *ray, t_apply_damage_helper *helper)
{
	if (cos(ray->angle) < 0)
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
	if (sin(ray->angle) < 0)
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
	char					c;

	helper = (t_apply_damage_helper){0};
	helper.current_distance = 0.0;
	helper.delta_dist_x = fabs(1 / cos(ray->angle));
	helper.delta_dist_y = fabs(1 / sin(ray->angle));
	helper.map_x = (int)cubed->player.x;
	helper.map_y = (int)cubed->player.y;
	determine_steps_and_initial_side_distances(cubed, ray, &helper);
	while (helper.current_distance < max_distance)
	{
		c = t_map_get(&cubed->scene.map, helper.map_x, helper.map_y);
		if (c == '1' || c == '\0')
		{
			return (false);
		}
		if (check_for_hits(cubed, helper.map_x, helper.map_y, damage))
			return (true);
		perform_dda_step(&helper);
	}
	return (false);
}
