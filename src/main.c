/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/09 22:51:49 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init(data_t *data)
{
	data->mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->minimap = mlx_new_image(data->mlx, MAP_WIDTH, MAP_HEIGHT);
	data->game = mlx_new_image(data->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	// -
	data->player.x = (GRID_SIZE * (18 / 2));
	data->player.y = (GRID_SIZE * (10 / 2));
	data->player.rotation_angle = (0);
	data->player.rotation_speed = 1;
	data->player.move_speed = 2;
	// -
	char map_grid[ROWS][COLUMNS] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	memcpy(data->map_grid, map_grid, sizeof(map_grid));
	// -
	draw_map(data);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
}

int main(void)
{
	data_t *data;

	data = malloc(sizeof(data_t));
	ft_init(data);
	ft_hooks(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	system("clear");
	return (free(data), EXIT_SUCCESS);
}
