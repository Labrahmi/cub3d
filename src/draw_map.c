/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/10 22:19:08 by ylabrahm         ###   ########.fr       */
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
				mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(30, 30, 192, 255));
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

	while (i < (GRID_SIZE))
	{
		int j = 0;
		while (j < (GRID_SIZE))
		{
			if (i == 0 || j == 0)
				mlx_put_pixel(data->minimap, (x + j), (y + i), ft_pixel(150, 150, 150, 255));
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
			draw_one_grid(data, (c * GRID_SIZE), (r * GRID_SIZE), sq_color);
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

double ft_get_vertical_intersection(data_t *data, double angle)
{
	vect_t intercept;
	double ystep, xstep;
	int is_facing_down, is_facing_up, is_facing_right, is_facing_left;
	int wall_hit_x = 0, wall_hit_y = 0;

	is_facing_down = (angle > 0 && angle <= 180);
	is_facing_up = !is_facing_down;
	is_facing_right = (angle < 90 || angle > 270);
	is_facing_left = !is_facing_right;
	//
	intercept.x = floor(data->player.x / GRID_SIZE) * GRID_SIZE;
	if (is_facing_right)
		intercept.x += GRID_SIZE;
	//
	intercept.y = data->player.y + (intercept.x - data->player.x) * tan(angle * (DEG_TO_RAD));
	//
	xstep = GRID_SIZE;
	if (is_facing_left)
		xstep *= -1;
	//
	ystep = GRID_SIZE * tan(angle * (DEG_TO_RAD));
	if (is_facing_up && (ystep > 0))
		ystep *= -1;
	if (is_facing_down && (ystep < 0))
		ystep *= -1;
	//
	int next_x = intercept.x;
	int next_y = intercept.y;
	if (is_facing_left)
		next_x--;
	while ((next_x >= 0 && next_x <= MAP_WIDTH) && (next_y >= 0 && next_y <= MAP_HEIGHT))
	{
		if (data->map_grid[next_y / GRID_SIZE][next_x / GRID_SIZE] == '1')
		{
			wall_hit_x = next_x;
			wall_hit_y = next_y;
			break;
		}
		else
		{
			next_x += xstep;
			next_y += ystep;
		}
	}
	double distance = sqrt(pow(wall_hit_x - data->player.x, 2) + pow(wall_hit_y - data->player.y, 2));
	return (distance);
}

double ft_get_horizontal_intersection(data_t *data, double angle)
{
	vect_t intercept;
	double ystep, xstep;
	int is_facing_down, is_facing_up, is_facing_right, is_facing_left;
	int wall_hit_x = 0, wall_hit_y = 0;

	is_facing_down = (angle > 0 && angle < 180);
	is_facing_up = !is_facing_down;
	is_facing_right = (angle < 90 || angle > 270);
	is_facing_left = !is_facing_right;
	//
	intercept.y = floor(data->player.y / GRID_SIZE) * GRID_SIZE;
	if (is_facing_down)
		intercept.y += GRID_SIZE;
	//
	intercept.x = data->player.x + (intercept.y - data->player.y) / tan(angle * (DEG_TO_RAD));
	//
	ystep = GRID_SIZE;
	if (is_facing_up)
		ystep *= -1;
	//
	xstep = GRID_SIZE / tan(angle * (DEG_TO_RAD));
	if (is_facing_left && (xstep > 0))
		xstep *= -1;
	if (is_facing_right && (xstep < 0))
		xstep *= -1;
	//
	int next_x = intercept.x;
	int next_y = intercept.y;
	if (is_facing_up)
		next_y--;
	while ((next_x >= 0 && next_x <= MAP_WIDTH) && (next_y >= 0 && next_y <= MAP_HEIGHT))
	{
		if (data->map_grid[next_y / GRID_SIZE][next_x / GRID_SIZE] == '1')
		{
			wall_hit_x = next_x;
			wall_hit_y = next_y;
			break;
		}
		else
		{
			next_x += xstep;
			next_y += ystep;
		}
	}
	double distance = sqrt(pow(wall_hit_x - data->player.x, 2) + pow(wall_hit_y - data->player.y, 2));
	return (distance);
}

hitRay_t draw_line_with_angle(data_t *data, float angle)
{
	hitRay_t ray;

	double horizontal_intersection = ft_get_horizontal_intersection(data, angle);
	double vertical_intersection = ft_get_vertical_intersection(data, angle);
	double shortest = horizontal_intersection < vertical_intersection ? horizontal_intersection : vertical_intersection;
	//
	ray.distance = shortest;
	ray.is_horizontal = (horizontal_intersection < vertical_intersection) ? 1 : 0;

	double x = data->player.x, y = data->player.y;

	double end_x = x + ((shortest)*cos(angle * DEG_TO_RAD));
	double end_y = y + ((shortest)*sin(angle * DEG_TO_RAD));

	double steps = fabs(end_x - x) > fabs(end_y - y) ? fabs(end_x - x) : fabs(end_y - y);
	double xIncrement = ((end_x - x) / steps);
	double yIncrement = ((end_y - y) / steps);

	for (int i = 0; i <= steps; i++)
	{
		// if ((x >= 0 && x < MAP_WIDTH) && (y >= 0 && y < MAP_HEIGHT))
		// 	mlx_put_pixel(data->minimap, x, y, ft_pixel(255, 32, 32, 255));
		x += xIncrement;
		y += yIncrement;
	}
	return (ray);
}

float normalize_angle(float angle)
{
	angle = fmod(angle, 360.0f);
	if (angle < 0)
		angle += 360.0f;
	return angle;
}

void draw_fov(data_t *data)
{
	// first_angle
	float angle = (data->player.rotation_angle - (data->fov_angle / 2));
	angle = normalize_angle(angle);
	float step = (data->fov_angle / data->game->width);
	hitRay_t ray;
	int ray_num = 0;
	clear_screen(data);
	while (ray_num < data->game->width)
	{
		ray = draw_line_with_angle(data, angle);
		ray.distance = ray.distance * cos((angle - data->player.rotation_angle) * (DEG_TO_RAD));
		draw_3d_walls(data, ray, ray_num);
		ray_num++;
		angle += step;
		angle = normalize_angle(angle);
	}
}

void draw_map(data_t *data)
{
	// draw_pixels_to_map(data);
	// draw_player(data);
	draw_fov(data);
}
