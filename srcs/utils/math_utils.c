/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:14:59 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/28 10:17:07 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdbool.h>

double	deg2rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

// pythagorean theorem
double	get_hypotenuse(double a, double b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

bool	is_not_transparent(int color)
{
	return ((color & 0x00FFFFFF) != 0);
}

int	argb_to_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}
