/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:01:33 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 13:50:54 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	extract_scene(int ac, char **av)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_fprintf(STDERR_FILENO, CUB_OPEN_ERROR_MSG);
		exit(EXIT_FAILURE);
	}
}

static int	run_cub3d(int ac, char **av)
{
	int	fd;

	extract_scene(ac, av);
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
			exit(EXIT_FAILURE);
		}
		run_cub3d(ac, av);
	}
	else if (ac < 2)
		ft_fprintf(STDERR_FILENO, ARG_ERROR_MSG);
	/*else if (argc == 3)
	{
		if (!(ft_strncmp("--save", argv[2], ft_strlen(argv[2])))
			&& ft_strlen(argv[2]) == 6)
			screenshot(argv[1]);
		else
			printf("WRONG");
	}*/
	else
		ft_fprintf(STDERR_FILENO, "WRONG");
}
