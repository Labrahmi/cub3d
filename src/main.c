/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/08/30 19:38:33 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_player(data_t *data)
{
	int x, y, i, j;

	x = data->player.x - (PLAYER_WIDTH);
	y = data->player.y - (PLAYER_HEIGHT);
	i = 0;
	while (i < (PLAYER_HEIGHT * 2))
	{
		j = 0;
		while (j < (PLAYER_WIDTH * 2))
		{
			mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(83, 171, 237, 255));
			j++;
		}
		i++;
	}
}

void draw_one_grid(data_t *data, int x, int y, int sq_color)
{
	int i = 1;
	while (i < (GRID_HEIGHT - 1))
	{
		int j = 1;
		while (j < (GRID_WIDTH - 1))
		{
			mlx_put_pixel(data->minimap, (x + j), (y + i), sq_color);
			j++;
		}
		i++;
	}
}

void draw_pixels_to_map(data_t *data)
{
	int r, c, x, y;
	int sq_color;

	r = 0;
	while (r < ROWS)
	{
		c = 0;
		while (c < COLUMNS)
		{
			sq_color = set_color(data->map_grid[r][c]);
			draw_one_grid(data, (c * GRID_WIDTH), (r * GRID_HEIGHT), sq_color);
			c++;
		}
		r++;
	}
	draw_player(data);
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
	data->player.rotation_angle = (Pi / 2);
	// -
	char map_grid[ROWS][COLUMNS] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '1'},
		{'1', '1', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '1', '1', '1', '0', '0', '0', '1', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '1', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	memcpy(data->map_grid, map_grid, sizeof(map_grid));
	// -
	draw_pixels_to_map(data);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
}

void ft_move_player(void *param)
{
	data_t *data;
	data = (data_t *)param;
}

int main(void)
{
	data_t *data;

	data = malloc(sizeof(data_t));
	ft_init(data);
	mlx_loop_hook(data->mlx, ft_move_player, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (free(data), EXIT_SUCCESS);
}
