/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 18:00:06 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 10:31:06 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	is_cubfile(char *file)
{
	int	len;
	int	fd;

	len = ft_strlen(file);
	if (len < 4)
		return (0);
	return (ft_strncmp(file + len - 4, ".cub", 4) == 0);
}
