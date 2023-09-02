/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/02 22:15:58 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_player(data_t *data)
{
	int x_center, y_center, x, y, i, j, radius;

	x_center = data->player.x;
	y_center = data->player.y;

	// Get the top-left starting position of the bounding square
	x = data->player.x - PLAYER_WIDTH;
	y = data->player.y - PLAYER_HEIGHT;

	radius = (PLAYER_WIDTH < PLAYER_HEIGHT) ? PLAYER_WIDTH : PLAYER_HEIGHT; // Choose the smaller of the two dimensions

	i = 0;
	while (i < (PLAYER_HEIGHT * 2))
	{
		j = 0;
		while (j < (PLAYER_WIDTH * 2))
		{
			// Calculate the distance from the current point to the center of the circle
			int dist_x = (x + j) - x_center;
			int dist_y = (y + i) - y_center;

			// If the point is inside the circle, draw it
			if (dist_x * dist_x + dist_y * dist_y <= radius * radius)
			{
				mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(192, 0, 0, 255));
			}
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

int set_ray_color(ray_num, total_rays)
{
	if ((ray_num < 20) || (ray_num > (total_rays - 20)))
		return (ft_pixel(192, 0, 0, 255));
	else
		return (ft_pixel(19, 37, 66, 255));
}

void draw_line_with_angle(data_t *data, double angle, int ray_num, int total_rays)
{
	int i;
	int steps;
	double x;
	double y;
	double end_x;
	double end_y;
	double dx;
	double dy;
	double xIncrement;
	double yIncrement;

	x = (double)data->player.x;
	y = (double)data->player.y;
	end_x = x + (GAME_HEIGHT * GAME_WIDTH) * cos(angle);
	end_y = y + (GAME_HEIGHT * GAME_WIDTH) * sin(angle);
	dx = (end_x - x);
	dy = (end_y - y);
	steps = fabs(dy);
	if (fabs(dx) > fabs(dy))
		steps = fabs(dx);
	xIncrement = (dx / steps);
	yIncrement = (dy / steps);
	i = 0;
	while (i <= steps)
	{
		int gridX = round(x) / GRID_WIDTH;
		int gridY = round(y) / GRID_HEIGHT;
		// ---------- Corner Case Fix -------------
		if (((y / GRID_WIDTH) > 0 && (x / GRID_WIDTH) > 0))
			if (data->map_grid[(int)(y / GRID_WIDTH)][(int)(x / GRID_WIDTH)] == '1')
				break;
		if (data->map_grid[(int)((y + dy / steps) / GRID_WIDTH)][(int)(x / GRID_WIDTH)] == '1')
			if (data->map_grid[(int)(y / GRID_WIDTH)][(int)((x + dx / steps) / GRID_WIDTH)] == '1')
				break;
		// -----------------------
		if ((gridX >= 0) && (gridY >= 0) && (gridX < GAME_WIDTH) && (gridY < GAME_HEIGHT))
		{
			if (data->map_grid[gridY][gridX] == '1')
				break;
		}
		int ray_color = set_ray_color(ray_num, total_rays);
		mlx_put_pixel(data->minimap, round(x), round(y), ray_color);
		x += xIncrement;
		y += yIncrement;
		i++;
	}
}

void draw_fov(data_t *data)
{
	double start_angle = data->player.rotation_angle - FOV_ANGLE;
	double end_angle = data->player.rotation_angle + FOV_ANGLE;
	double step = (M_PI / 180.0 / 32);
	int total_rays = (end_angle - start_angle) / step;
	int ray_num = 0;
	for (double angle = start_angle; angle <= end_angle; angle += step, ray_num++)
		draw_line_with_angle(data, angle, ray_num, total_rays);
}

void draw_map(data_t *data)
{
	draw_pixels_to_map(data);
	draw_fov(data);
	draw_player(data);
}
