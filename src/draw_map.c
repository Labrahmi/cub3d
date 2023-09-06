/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/06 01:22:52 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_player(data_t *data)
{
	int x_center, y_center, x, y, i, j, radius;

	x_center = data->player.x;
	y_center = data->player.y;
	x = data->player.x - PLAYER_WIDTH;
	y = data->player.y - PLAYER_HEIGHT;
	radius = (PLAYER_WIDTH < PLAYER_HEIGHT) ? PLAYER_WIDTH : PLAYER_HEIGHT;
	i = 0;
	while (i < (PLAYER_HEIGHT * 2))
	{
		j = 0;
		while (j < (PLAYER_WIDTH * 2))
		{
			int dist_x = (x + j) - x_center;
			int dist_y = (y + i) - y_center;
			if (dist_x * dist_x + dist_y * dist_y <= radius * radius)
			{
				mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(192, 0, 0, 200));
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
			if ((i == 0) || (j == 0))
				mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(115, 133, 117, 200));
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
		return (ft_pixel(192, 0, 0, 200));
	else
		return (ft_pixel(19, 37, 66, 200));
}

hitRay_t draw_line_with_angle(data_t *data, float angle, int mode)
{
	int gridX, gridY, nextGridX, nextGridY;
	float x, y, end_x, end_y, dx, dy, xIncrement, yIncrement, steps;
	int lenght = 32;
	int ray_color = ft_pixel(240, 0, 0, 200);
	hitRay_t ray;

	x = (float)data->player.x;
	y = (float)data->player.y;
	if (mode == 1)
	{
		lenght = (MAP_HEIGHT * MAP_WIDTH);
		ray_color = ft_pixel(19, 37, 66, 200);
	}
	end_x = x + ((lenght) * cos(angle * (M_PI / 180.0)));
	end_y = y + ((lenght) * sin(angle * (M_PI / 180.0)));
	dx = end_x - x;
	dy = end_y - y;
	steps = (fabs(dx) > fabs(dy)) ? fabs(dx) : fabs(dy);
	xIncrement = (dx / steps) / 16;
	yIncrement = (dy / steps) / 16;
	ray.is_horizontal = 1;
	for (int i = 0; i <= steps; i++)
	{
		gridX = (x / GRID_WIDTH);
		gridY = (y / GRID_HEIGHT);
		nextGridX = (x + xIncrement) / GRID_WIDTH;
		nextGridY = (y + yIncrement) / GRID_HEIGHT;
		if ((data->map_grid[nextGridY][gridX] == '1') && (data->map_grid[gridY][nextGridX] == '1'))
			break;
		if (gridX >= 0 && gridY >= 0 && gridX < MAP_WIDTH && gridY < MAP_HEIGHT)
		{
			if (data->map_grid[gridY][gridX] == '1')
				break;
			mlx_put_pixel(data->minimap, x, y, ray_color);
		}
		x += xIncrement;
		y += yIncrement;
	}
	ray.distance = sqrt(pow(x - data->player.x, 2) + pow(y - data->player.y, 2));
	return (ray);
}

void draw_fov(data_t *data)
{
	float start_angle = (data->player.rotation_angle - (FOV_ANGLE / 2));
	float end_angle = (data->player.rotation_angle + (FOV_ANGLE / 2));
	float step = (FOV_ANGLE / data->game->width); // M_PI / 180.0
	float distance;
	hitRay_t ray;
	int ray_num = 0;
	clear_screen(data);
	for (float angle = start_angle; angle <= end_angle; angle += step)
	{
		ray = draw_line_with_angle(data, angle, 1);
		ray.distance = ray.distance * cos((angle - data->player.rotation_angle) * (M_PI / 180.0));
		draw_3d_walls(data, ray, ray_num);
		ray_num++;
	}
}

void draw_map(data_t *data)
{
	draw_pixels_to_map(data);
	draw_player(data);
	draw_fov(data);
}
