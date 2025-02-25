/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   definitions.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:01:16 by apyykone          #+#    #+#             */
/*   Updated: 2024/06/03 19:42:58 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINITIONS_H
# define DEFINITIONS_H

# define ARG_ERROR_MSG \
	"Remember to give the cub file name ./cub3d \
<example.cub>\n"
# define CUB_OPEN_ERROR_MSG "Error: .cub open()\n"
# define CUB_ERROR_COLOR \
	"Error: get_color_rgb()\
	- color value out of range\n"
# define CUB_ERROR_MALLOC "Error: malloc() in -> "
# define CUB_MAP_SPLIT_DELIMITERS " \n\t\v\f\r"
# define ERR_RGB "Error: get_color_rgb() - invalid rgb value\n"
# define ERR_RESOLUTION "Error: get_resolution() - invalid resolution value\n"
# define ERR_INVALID_EXTENSION "Error: invalid file extension \'%s\'\n"
# define ERR_POORLY_FORMATTED "Error: poorly formatted %s \n"
# define ERR_OPENTEXT "Error\nCould not open the %s: %s.\n"
# define ERR_MAP_NOT_SURROUNDED "Error: map is not surrounded by walls\n"
# define ERR_MISSING_MAP "Error: map is missing\n"
# define ERR_START_POSITION "Error: map has invalid start position\n"
# define VALID_CHARS "012NSEW "
# define GUN_TEXTURE_PATH "assets/gun/akimbos.xpm"
# define ERR_LOAD_WEAPON "Error: load_weapon() - could not load weapon\n"
# define ERR_LOAD_TEXTURE "Error: load_texture() - could not load texture\n"
# define MAP_ERR_LOC "Error: Map not surrounded by walls at (%d, %d) \
	(From where the map started)\n"
# define MOUSE_SENSITIVITY 0.001
# define MOUSE_ESCAPE_THRESHOLD 20
# define ZOOM_FACTOR 2.0
# define RES_MAX_W 2440
# define RES_MAX_H 1320
# define RES_MAX_STR "2440x1320"
# define RES_DEFAULT_W 1920
# define RES_DEFAULT_H 1080
# define RES_DEFAULT_STR "1920x1080"
# define RES_MIN_W 320
# define RES_MIN_H 240
# define RES_MIN_STR "320x240"

# ifndef LINUX
#  define LINUX 0
# endif

# define WRAPPER_EXIT 42
# define GREY 0x555555
# define GREEN 0x008000
# define BLACK 0x000000
# define HBAR_GREEN 0x00FF00
# define LIGHT_GREEN 0x80FF80
# define WHITE 0xFFFFFF
# define RED 0xFF0000
# define GRAY 0x808080
# define PURPLE 0xAA08AA
# define YELLOW 0xFFFF00
# define LEFT_CLICK 1
# define SCROLL_UP 4
# define SCROLL_DOWN 5
# define FOV 60
# define TAB_SIZE 4
# ifndef linux
#  define RIGHT_CLICK 2
#  define K_ESC 53
#  define K_W 13
#  define K_A 0
#  define K_S 1
#  define K_D 2
#  define K_Q 12
#  define K_R 15
#  define K_F 3
#  define K_LEFT_ARROW 123
#  define K_RIGHT_ARROW 124
#  define K_SPACE 49
#  define K_M 46
#  define K_ENTER 36
#  define K_FORWARD_ARROW 126
#  define K_BACK_ARROW 125
#  define K_LEFT_SHIFT 257
#  define K_RIGHT_SHIFT 258
#  define K_CAPS_LOCK 48
#  define LEFT_CTRL 256
#  define K_1 18
#  define K_2 19
#  define K_3 20
#  define K_4 21
#  define K_5 23
# else
#  define RIGHT_CLICK 3
#  define K_ENTER 65293
#  define K_Q 113
#  define K_SPACE 32
#  define K_ESC 65307
#  define K_W 119
#  define K_A 97
#  define K_S 115
#  define K_D 100
#  define K_M 109
#  define K_LEFT_ARROW 65361
#  define K_RIGHT_ARROW 65363
#  define K_FORWARD_ARROW 65362
#  define K_BACK_ARROW 65364
#  define K_LEFT_SHIFT 65505
#  define K_RIGHT_SHIFT 65506
#  define K_CAPS_LOCK 65509
#  define LEFT_CTRL 65507
#  define K_1 49
#  define K_2 50
#  define K_3 51
#  define K_4 52
#  define K_5 53
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
