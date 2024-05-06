/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/06 17:02:04 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define ARG_ERROR_MSG "Remember to give the cub file name ./cub3d <example.cub>\n"
# define CUB_OPEN_ERROR_MSG "Error: .cub open()\n"
# define CUB_ERROR_COLOR \
	"Error: get_color_rgb()\
	- color value out of range\n"
# define CUB_ERROR_MALLOC "Error: malloc() in -> "
# define CUB_MAP_SPLIT_DELIMITERS " \n\t\v\f\r"
# define ERR_RGB "Error: get_color_rgb() - invalid rgb value\n"
# define ERR_RESOLUTION "Error: get_resolution() - invalid resolution value\n"
# define ERR_INVALID_EXTENSION "Error: invalid file extension %s\n"
# define ERR_POORLY_FORMATTED "Error: poorly formatted %s \n"
# define ERR_OPENTEXT "Error\nCould not open the %s: %s.\n"

# define MAX_X_RES 1920
# define MAX_Y_RES 1080

#endif