/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/14 19:35:00 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init(data_t *data)
{
	data->mlx = mlx_init(1024, 1024, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->grid_size = 50;
	data->map_height = data->grid_size * 10;
	data->map_width = data->grid_size * 18;
	data->player.x = (750);
	data->player.y = (400);
	data->player.rotation_angle = (-135);
	data->player.rotation_speed = 5;
	data->player.move_speed = 2;
	data->fov_angle = 60;
	data->columns = 18;
	data->rows = 10;
	// -
	data->minimap = mlx_new_image(data->mlx, data->map_width, data->map_height);
	data->game = mlx_new_image(data->mlx, 1024, 1024);
	// -
	char map_grid[10][18] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '1', '1', '1', '1', '1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	memcpy(data->map_grid, map_grid, sizeof(map_grid));
	// -
	data->texture = mlx_load_png("assets/ylabrahm.png");
	draw_map(data);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	// mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	mlx_put_string(data->mlx, "33-34", 10, 10);
	//
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
