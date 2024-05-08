/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/08 14:50:20 by apyykone         ###   ########.fr       */
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
# define ERR_MAP_NOT_SURROUNDED "Error: map is not surrounded by walls\n"
# define ERR_MISSING_MAP "Error: map is missing\n"
# define ERR_START_POSITION "Error: map has invalid start position\n"

# define MAX_X_RES 1920
# define MAX_Y_RES 1080

# define VALID_CHARS "012NSEW "

# ifndef linux
#  define K_ESC 53
#  define K_W 13
#  define K_A 0
#  define K_S 1
#  define K_D 2
#  define K_LEFT_ARROW 123
#  define K_RIGHT_ARROW 124
# else
#  define K_ESC 65307
#  define K_W 122
#  define K_A 113
#  define K_S 115
#  define K_D 100
#  define K_LEFT_ARROW 65361
#  define K_RIGHT_ARROW 65363
# endif

# ifndef linux
#  define DESTROY_NOTIFY 17
#  define KEY_PRESS 02
#  define KEY_RELEASE 03
#  define M_DESTROY_NOTIFY 131072
#  define M_KEY_PRESS 1
#  define M_KEY_RELEASE 2
# else
#  define DESTROY_NOTIFY 33
#  define KEY_PRESS 02
#  define KEY_RELEASE 03
#  define M_DESTROY_NOTIFY 0
#  define M_KEY_PRESS 1
#  define M_KEY_RELEASE 2
# endif

#endif