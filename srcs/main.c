/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:01:33 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 14:35:05 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	run_cub3d(char **av)
{
	t_cubed	cubed;

	cubed = (t_cubed){0};
	extract_scene(&cubed.scene, av);
	check_scene(&cubed);
	start_game(&cubed);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac > 2 && (av + 1) && *(av + 1))
	{
		if (!is_cubfile(av[1]))
		{
			ft_fprintf(STDERR_FILENO, NOT_CUB_ERROR_MSG);
			ft_clean_exit(CUB_OPEN_ERROR_MSG);
		}
		run_cub3d(av);
	}
	else if (ac < 2)
		ft_fprintf(STDERR_FILENO, ARG_ERROR_MSG);
	else
		ft_fprintf(STDERR_FILENO, "WRONG");
}
