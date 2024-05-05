/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apyykone <apyykone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 02:01:33 by apyykone          #+#    #+#             */
/*   Updated: 2024/05/05 19:19:29 by apyykone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	printalldata(t_cubed *cubed)
{
	ft_printf("Resolution: %d x %d\n", cubed->scene.resolution.width,
		cubed->scene.resolution.height);
	ft_printf("North texture: %s\n", cubed->scene.north_texture.path);
	ft_printf("South texture: %s\n", cubed->scene.south_texture.path);
	ft_printf("West texture: %s\n", cubed->scene.west_texture.path);
	ft_printf("East texture: %s\n", cubed->scene.east_texture.path);
	// ft_printf("Sprite texture: %s\n", cubed->scene.sprite_texture.path);
	ft_printf("Floor color: %d, %d, %d\n", cubed->scene.floor_color.red,
		cubed->scene.floor_color.green, cubed->scene.floor_color.blue);
	ft_printf("Ceiling color: %d, %d, %d\n", cubed->scene.ceiling_color.red,
		cubed->scene.ceiling_color.green, cubed->scene.ceiling_color.blue);
	for (int i = 0; i < cubed->scene.map.height; i++)
		printf("%s\n", cubed->scene.map.grid[i]);
}

static int	run_cub3d(char **av)
{
	t_cubed	cubed;

	cubed = (t_cubed){0};
	extract_scene(&cubed, av);
	printalldata(&cubed);
	validate_scene(&cubed);
	start_game(&cubed);
	ft_clean_exit(&cubed, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac > 1 && (av + 1) && *(av + 1))
	{
		if (!has_extension(av[1], ".cub"))
		{
			ft_fprintf(STDERR_FILENO, NOT_CUB_ERROR_MSG);
			ft_clean_exit(NULL, CUB_OPEN_ERROR_MSG);
		}
		run_cub3d(av);
	}
	else if (ac < 2)
		ft_fprintf(STDERR_FILENO, ARG_ERROR_MSG);
	else
		ft_fprintf(STDERR_FILENO, "WRONG");
}
