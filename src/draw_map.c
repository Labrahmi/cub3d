/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/01 01:51:36 by ylabrahm         ###   ########.fr       */
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
			mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(32, 32, 32, 255));
			j++;
		}
		i++;
	}
}

void draw_one_grid(data_t *data, int x, int y, int sq_color)
{
	int i = 0;
	int color;

	while (i < (GRID_HEIGHT))
	{
		int j = 0;
		while (j < (GRID_WIDTH))
		{
			if (i == 0 || j == 0)
				mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(32, 32, 32, 255));
			else
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
}

void draw_line_with_angle(data_t *data, double angle)
{
	int dx, dy, sx, sy, err, e2;
	int x = data->player.x;
	int y = data->player.y;
	int end_x = x + 2560 * cos(angle);
	int end_y = y + 2560 * sin(angle);
	dx = abs(end_x - x);
	dy = abs(end_y - y);
	sx = (x < end_x) ? 1 : -1;
	sy = (y < end_y) ? 1 : -1;
	err = (dx > dy) ? dx / 2 : -dy / 2;
	while (1)
	{
		// printf("%d %d\n", x , y);
		if (x / 128 >= 0 && y / 128 >= 0 && x / 128 < GAME_WIDTH && y / 128 < GAME_HEIGHT && data->map_grid[y / 128][x / 128] == '1')
			break;
		mlx_put_pixel(data->minimap, x, y, ft_pixel(255, 0, 0, 255));
		if (x == end_x && y == end_y)
			break;
		e2 = err;
		if (e2 > -dx)
		{
			err -= dy;
			x += sx;
		}
		if (e2 < dy)
		{
			err += dx;
			y += sy;
		}
	}
}

void draw_fov(data_t *data)
{
	double start_angle = data->player.rotation_angle - FOV_ANGLE;
	double end_angle = data->player.rotation_angle + FOV_ANGLE;
	double step = M_PI / 180.0 / 4;

	for (double angle = start_angle; angle <= end_angle; angle += step)
		draw_line_with_angle(data, angle);
}

void draw_map(data_t *data)
{
	draw_pixels_to_map(data);
	draw_player(data);
	draw_fov(data);
	// draw_line(data);
}
