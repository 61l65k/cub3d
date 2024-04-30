/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:01:33 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 13:58:09 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	run_cub3d(int ac, char **av)
{
	t_cubed	cubed;

	cubed = (t_cubed){0};
	extract_scene(ac, av);
	check_scene(&cubed);
	// ft_start_tmap(&a.parse);
	// cub_extract(&a.parse, fd);
	/*if (a.parse.error)
	{
		printf("there was an error while extracting");
		return (0);
	}*/
	/*if (!ft_parse_cub(a.parse.text, &a.parse))
	{
		ft_freetext(a.parse.text);
		free_all_texts(&a.parse);
		return (0);
	}*/
	// start_game(&a);
	return (1);
}

int	main(int ac, char **av)
{
	if (ac > 2)
	{
		if (!is_cubfile(av[1]))
		{
			ft_fprintf(STDERR_FILENO, NOT_CUB_ERROR_MSG);
			ft_clean_exit(CUB_OPEN_ERROR_MSG);
		}
		run_cub3d(ac, av);
	}
	else if (ac < 2)
		ft_fprintf(STDERR_FILENO, ARG_ERROR_MSG);
	else
		ft_fprintf(STDERR_FILENO, "WRONG");
}
