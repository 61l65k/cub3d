/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blend_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/27 18:00:30 by ttakala           #+#    #+#             */
/*   Updated: 2024/05/27 18:07:58 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

int	blend_colors(int c1, int c2, double alpha)
{
	const uint8_t	color1[3] = {
		(c1 >> 16) & 0xFF,
		(c1 >> 8) & 0xFF,
		c1 & 0xFF
	};
	const uint8_t	color2[3] = {
		(c2 >> 16) & 0xFF,
		(c2 >> 8) & 0xFF,
		c2 & 0xFF
	};
	const uint8_t	blend[3] = {
		(1 - alpha) * color1[0] + alpha * color2[0],
		(1 - alpha) * color1[1] + alpha * color2[1],
		(1 - alpha) * color1[2] + alpha * color2[2]
	};

	return ((blend[0] << 16) | (blend[1] << 8) | blend[2]);
}
