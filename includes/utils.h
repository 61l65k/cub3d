/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:37 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 16:54:36 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "libft.h"

# define ARG_ERROR_MSG "Remember to give the cub file name ./cub3d <example.cub>\n"
# define NOT_CUB_ERROR_MSG "The file is not a .cub file\n"
# define CUB_OPEN_ERROR_MSG "Error: .cub open()\n"

int		is_cubfile(char *file);
void	ft_clean_exit(char *msg);
int		is_start_of_map(char *line);

#endif