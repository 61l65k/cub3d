/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:01:33 by apyykone          #+#    #+#             */
/*   Updated: 2024/04/30 00:44:53 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	run_cub3d(char *cubname)
{
	int		fd;
	t_cubed	a;

	// ft_start_tmap(&a.parse);
	fd = open(cubname, O_RDONLY);
	if (fd <= 0)
		return (ft_fprintf(STDERR_FILENO, CUB_OPEN_ERROR_MSG));
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

int	main(int argc, char **argv)
{
	if (argc < 2)
		ft_fprintf(STDERR_FILENO, ARG_ERROR_MSG);
	else if (argc == 2)
	{
		if (!is_cubfile(argv[1]))
			return (ft_fprintf(STDERR_FILENO, NOT_CUB_ERROR_MSG));
		run_cub3d(argv[1]);
	}
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