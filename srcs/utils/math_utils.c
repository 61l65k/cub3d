/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 20:14:59 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/30 13:04:26 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>

double	deg2rad(double deg)
{
	return (deg * (M_PI / 180.0));
}

// pythagorean theorem
double	get_hypotenuse(double a, double b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

int	argb_to_int(int a, int r, int g, int b)
{
	return (a << 24 | r << 16 | g << 8 | b);
}

double	get_distance(double x1, double y1, double x2, double y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

double	normalize_radian(double radian)
{
	const double	full_circle = deg2rad(360);

	radian = fmod(radian, full_circle);
	if (radian < 0)
		radian += full_circle;
	return (radian);
}
