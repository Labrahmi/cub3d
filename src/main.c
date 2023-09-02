/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/02 20:56:57 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int is_corner(data_t *data, int x, int y)
{
	if ((x - 1 >= 0) && (y - 1 >= 0))
	{
		if ((data->map_grid[y][x - 1] == '1') && (data->map_grid[y - 1][x] == '1'))
		{
			return 1;
		}
	}
	return 0;
}

int populate_corners(data_t *data)
{
	int corner_count = 0;
	for (int y = 0; y < ROWS; y++)
	{
		for (int x = 0; x < COLUMNS; x++)
		{
			if (is_corner(data, x, y))
			{
				data->corners[corner_count].x = x;
				data->corners[corner_count].y = y;
				corner_count++;
			}
		}
	}
	return corner_count;
}

void ft_init(data_t *data)
{
	data->mlx = mlx_init(GAME_WIDTH, GAME_HEIGHT, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->minimap = mlx_new_image(data->mlx, GAME_WIDTH, GAME_HEIGHT);
	// -
	data->player.x = (GAME_WIDTH / 2);
	data->player.y = (GAME_HEIGHT / 2);
	data->player.rotation_angle = (2 * Pi);
	data->player.rotation_speed = 0.03;
	data->player.move_speed = 2;
	// -
	char map_grid[ROWS][COLUMNS] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '1', '1', '0', '0', '1', '1', '0', '1', '1', '1', '1', '0', '1', '1', '1', '1', '0', '1'},
		{'1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '1', '0', '1', '1', '1', '0', '0', '0', '0', '0', '1', '0', '1', '1', '0', '1', '0', '1', '1'},
		{'1', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '1', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
		{'1', '0', '1', '0', '1', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '0', '1', '0', '1', '1'},
		{'1', '0', '1', '1', '1', '0', '1', '0', '1', '1', '1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'}
	};
	memcpy(data->map_grid, map_grid, sizeof(map_grid));
	data->corner_count = populate_corners(data);
	{
		for (size_t i = 0; i < data->corner_count; i++)
		{
			printf("(%d, %d)\n", data->corners[i].x, data->corners[i].y);
		}
	}
	// exit(0);
	// -
	draw_map(data);
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
