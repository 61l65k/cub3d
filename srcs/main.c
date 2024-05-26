/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:01:33 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/26 11:51:49 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		extract_from_cub_file(t_cubed *cubed, const char *path);

static int	run_cub3d(char **av)
{
	t_cubed	cubed;

	cubed = (t_cubed){0};
	extract_from_cub_file(&cubed, av[1]);
	validate_scene(&cubed);
	start_game(&cubed);
	ft_clean_exit(&cubed, NULL, cubed.reset);
	return (cubed.reset);
}

int	main(int ac, char **av)
{
	if (ac > 1 && (av + 1) && *(av + 1))
	{
		if (!has_extension(av[1], ".cub"))
		{
			ft_fprintf(STDERR_FILENO, ERR_INVALID_EXTENSION, av[1]);
			ft_clean_exit(NULL, CUB_OPEN_ERROR_MSG, 0);
		}
		while (run_cub3d(av))
			;
	}
	else if (ac < 2)
		ft_fprintf(STDERR_FILENO, ARG_ERROR_MSG);
	else
		ft_fprintf(STDERR_FILENO, "WRONG");
}
