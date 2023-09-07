/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/07 19:33:49 by ylabrahm         ###   ########.fr       */
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
			if (i == 0 || j == 0) mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(32, 32, 32, 255));
			else mlx_put_pixel(data->minimap, (x + j), (y + i), sq_color);
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


hitRay_t draw_line_with_angle(data_t *data, float angle)
{
	hitRay_t ray;
	int adjacent, opposite, new_x_Grid, new_y_Grid, color = ft_pixel(255, 0, 0, 255);
	double hyp_v, hyp_h, new_x, new_y;
	// --------------------------------------------------------------------------------------------
	adjacent = (GRID_WIDTH - (data->player.x % GRID_WIDTH));
	opposite = (GRID_HEIGHT - (data->player.y % GRID_HEIGHT));
	// --------------------------------------------------------------------------------------------
	// Calculate hypotenuse on vertical Intersections
	for (int i = 1; i < COLUMNS; i += 1)
	{
		if (i > 1)
		{
			adjacent = GRID_WIDTH;
			opposite = GRID_HEIGHT;
		}
		hyp_v = fabs((adjacent * i) / cos(angle * DEG_TO_RAD));
		// 
		new_x = data->player.x + ((hyp_v) * cos(angle * DEG_TO_RAD));
		new_y = data->player.y + ((hyp_v) * sin(angle * DEG_TO_RAD));
		new_x_Grid = fabs(new_x / GRID_WIDTH);
		new_y_Grid = fabs(new_y / GRID_HEIGHT);
		if ((new_x_Grid >= 0 && new_x_Grid < COLUMNS) && (new_y_Grid >= 0 && new_y_Grid < ROWS))
			if (data->map_grid[new_y_Grid][new_x_Grid] == '1')
				break;
	}
	// --------------------------------------------------------------------------------------------
	adjacent = (GRID_WIDTH - (data->player.x % GRID_WIDTH));
	opposite = (GRID_HEIGHT - (data->player.y % GRID_HEIGHT));
	// --------------------------------------------------------------------------------------------
	// Calculate hypotenuse on horisontal Intersections
	for (int i = 1; i < ROWS; i += 1)
	{
		if (i > 1)
		{
			adjacent = GRID_WIDTH;
			opposite = GRID_HEIGHT;
		}
		hyp_h = fabs((opposite * i) / sin(angle * DEG_TO_RAD));
		// 
		new_x = data->player.x + ((hyp_h) * cos(angle * DEG_TO_RAD));
		new_y = data->player.y + ((hyp_h) * sin(angle * DEG_TO_RAD));
		new_x_Grid = fabs(new_x / GRID_WIDTH);
		new_y_Grid = fabs(new_y / GRID_HEIGHT);
		if ((new_x_Grid >= 0 && new_x_Grid < COLUMNS) && (new_y_Grid >= 0 && new_y_Grid < ROWS))
			if (data->map_grid[new_y_Grid][new_x_Grid] == '1')
				break;
	}
	// --------------------------------------------------------------------------------------------
	ray.distance = hyp_v < hyp_h ? hyp_v : hyp_h;
	ray.is_horizontal = hyp_v < hyp_h ? 1 : 0;
	for (int i = 0; i < ray.distance; i++)
	{
		new_x = data->player.x + (i * cos(angle * DEG_TO_RAD));
		new_y = data->player.y + (i * sin(angle * DEG_TO_RAD));
		if ((new_x >= 0) && (new_y >= 0) && (new_x < MAP_WIDTH) && (new_y < MAP_HEIGHT))
			mlx_put_pixel(data->minimap, new_x, new_y, color);
	}
	return (ray);
}

void draw_fov(data_t *data)
{
	float start_angle = (data->player.rotation_angle - (FOV_ANGLE / 2));
	float end_angle = (data->player.rotation_angle + (FOV_ANGLE / 2));
	float step = (FOV_ANGLE / data->game->width);
	hitRay_t ray;
	int ray_num = 0;
	clear_screen(data);
	ray = draw_line_with_angle(data, data->player.rotation_angle);
	for (float angle = start_angle; angle <= end_angle; angle += step)
	{
		ray = draw_line_with_angle(data, angle);
		ray.distance = ray.distance * cos((angle - data->player.rotation_angle) * (DEG_TO_RAD));
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
