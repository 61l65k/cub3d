/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttakala <ttakala@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:37 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/29 16:35:10 by ttakala          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "definitions.h"
# include "libft.h"

typedef struct s_cubed		t_cubed;
typedef struct s_map		t_map;
typedef struct s_rectangle	t_floor_ceiling;
typedef struct s_ray		t_ray;
typedef struct s_wall		t_wall;
typedef struct s_resolution	t_resolution;
typedef struct s_player		t_player;
typedef struct s_animation	t_animation;
typedef struct s_texture	t_texture;
typedef struct s_mlx		t_mlx;

int							has_extension(char *file, char *ext);
void						ft_clean_exit(t_cubed *cubed, char *msg,
								bool reset);
int							is_start_of_map(char *line);
void						free_2d_array(char **array);
void						free_null(char **ptr_to_ptr);
void						free_null_2d_array(char ***ptr_to_ptrarray);
int							ft_2d_array_len(char **array);
bool						is_valid_game_identifier(const char *identifier,
								char **data);
bool						is_valid_color_value(int *color, char *value);
bool						does_texture_exist(char *texture_path,
								char *texture_name);
void						prepare_events(t_cubed *cubed);
int							argb_to_int(int a, int r, int g, int b);
int							is_map_surrounded_by_walls(const t_map *map);
int							has_one_start_position(char **map);
double						deg2rad(double deg);
void						render_wall_column(t_wall *wall, int *img,
								t_resolution *res, t_ray *ray);
void						update_player_position(t_player *player,
								const t_map *t_map);
void						update_player_orientation(t_player *player);
int							is_ray_facing_south(double angle);
int							is_ray_facing_west(double angle);
double						normalize_radian(double radian);
int							is_wall(t_map *map, double x, double y, t_ray *ray);
void						draw_rectangle(t_floor_ceiling *rec, int *img,
								int res_x);
double						get_hypotenuse(double a, double b);
void						draw_vertical_line(t_cubed *cubed, int draw_x,
								int draw_y, int color);
bool						is_not_transparent(int color);
void						load_texture(t_cubed *cubed, void *mlx,
								t_texture *texture);
void						free_texture(t_mlx *mlx, t_texture *texture);
int							key_press_game_menu(int keycode, t_cubed *cubed);
int							blend_colors(int c1, int c2, double alpha);
double						get_distance(double x1, double y1, double x2,
								double y2);

#endif
