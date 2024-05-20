/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_animation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 23:35:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/20 23:35:39 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_animation(t_animation *animation)
{
	if (animation->frame_timer == 0)
	{
		animation->curr_frame++;
		if (animation->curr_frame >= animation->frame_count)
		{
			animation->curr_frame = 0;
		}
		animation->frame_timer = animation->frame_delay;
	}
	else
	{
		animation->frame_timer--;
	}
}
