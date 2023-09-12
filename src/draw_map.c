/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/12 08:36:08 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_player(data_t *data)
{
	int x_center, y_center, x, y, i, j, radius;

	x_center = data->player.x;
	y_center = data->player.y;
	x = data->player.x - 6;
	y = data->player.y - 6;
	radius = (6 < 6) ? 6 : 6;
	i = 0;
	while (i < (6 * 2))
	{
		j = 0;
		while (j < (6 * 2))
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

	while (i < (data->grid_size))
	{
		int j = 0;
		while (j < (data->grid_size))
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
	while (r < data->rows)
	{
		c = 0;
		while (c < data->columns)
		{
			sq_color = set_color(data->map_grid[r][c]);
			draw_one_grid(data, (c * data->grid_size), (r * data->grid_size), sq_color);
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

hitRay_t ft_get_vertical_intersection(data_t *data, double angle)
{
	vect_t intercept;
	double ystep, xstep;
	int is_facing_down, is_facing_up, is_facing_right, is_facing_left;
	double wall_hit_x = INT_MAX, wall_hit_y = INT_MAX;

	is_facing_down = (angle > 0 && angle <= 180);
	is_facing_up = !is_facing_down;
	is_facing_right = (angle < 90 || angle > 270);
	is_facing_left = !is_facing_right;
	//
	intercept.x = floor(data->player.x / data->grid_size) * data->grid_size;
	if (is_facing_right)
		intercept.x += data->grid_size;
	//
	intercept.y = data->player.y + (intercept.x - data->player.x) * tan(angle * (DEG_TO_RAD));
	//
	xstep = data->grid_size;
	if (is_facing_left)
		xstep *= -1;
	//
	ystep = data->grid_size * tan(angle * (DEG_TO_RAD));
	if (is_facing_up && (ystep > 0))
		ystep *= -1;
	if (is_facing_down && (ystep < 0))
		ystep *= -1;
	//
	{
		float x_to_check;
		float y_to_check;
		int grid_x, grid_y;
		while (intercept.x >= 0 && intercept.x < data->minimap->width && intercept.y >= 0 && intercept.y < data->minimap->width)
		{
			y_to_check = intercept.y;
			x_to_check = intercept.x;
			grid_x = floor(x_to_check / data->grid_size) - ((is_facing_left) ? 1 : 0);
			grid_y = floor(y_to_check / data->grid_size);
			if (data->map_grid[grid_y][grid_x] == '1')
			{
				wall_hit_x = intercept.x;
				wall_hit_y = intercept.y;
				break;
			}
			else
			{
				intercept.x += xstep;
				intercept.y += ystep;
			}
		}
	}
	hitRay_t ray;
	ray.distance = sqrt(pow(wall_hit_x - data->player.x, 2) + pow(wall_hit_y - data->player.y, 2));
	ray.x_hit = wall_hit_x;
	ray.y_hit = wall_hit_y;
	return (ray);
}

hitRay_t ft_get_horizontal_intersection(data_t *data, double angle)
{
	vect_t intercept;
	double ystep, xstep;
	int is_facing_down, is_facing_up, is_facing_right, is_facing_left;
	double wall_hit_x = INT_MAX, wall_hit_y = INT_MAX;

	is_facing_down = (angle > 0 && angle < 180);
	is_facing_up = !is_facing_down;
	is_facing_right = (angle < 90 || angle > 270);
	is_facing_left = !is_facing_right;
	//
	intercept.y = floor(data->player.y / data->grid_size) * data->grid_size;
	if (is_facing_down)
		intercept.y += data->grid_size;
	//
	intercept.x = data->player.x + (intercept.y - data->player.y) / tan(angle * (DEG_TO_RAD));
	//
	ystep = data->grid_size;
	if (is_facing_up)
		ystep *= -1;
	//
	xstep = data->grid_size / tan(angle * (DEG_TO_RAD));
	if (is_facing_left && (xstep > 0))
		xstep *= -1;
	if (is_facing_right && (xstep < 0))
		xstep *= -1;
	//
	{
		float x_to_check;
		float y_to_check;
		int grid_x, grid_y;
		while (intercept.x >= 0 && intercept.x < data->minimap->width && intercept.y >= 0 && intercept.y < data->minimap->width)
		{
			x_to_check = intercept.x;
			y_to_check = intercept.y;
			grid_x = floor(x_to_check / data->grid_size);
			grid_y = floor(y_to_check / data->grid_size) - (is_facing_up ? 1 : 0);;
			if (data->map_grid[grid_y][grid_x] != '0')
			{
				wall_hit_x = intercept.x;
				wall_hit_y = intercept.y;
				break;
			}
			else
			{
				intercept.x += xstep;
				intercept.y += ystep;
			}
		}
	}
	hitRay_t ray;
	ray.distance = sqrt(pow(wall_hit_x - data->player.x, 2) + pow(wall_hit_y - data->player.y, 2));
	ray.x_hit = wall_hit_x;
	ray.y_hit = wall_hit_y;
	return (ray);
}

hitRay_t draw_line_with_angle(data_t *data, float angle)
{
	hitRay_t ray;
	hitRay_t hor = ft_get_horizontal_intersection(data, angle);
	hitRay_t ver = ft_get_vertical_intersection(data, angle);
	//
	ray.distance = (hor.distance < ver.distance) ? hor.distance : ver.distance;
	ray.is_horizontal = (hor.distance < ver.distance) ? 1 : 0;
	ray.x_hit = (hor.distance < ver.distance) ? hor.x_hit : ver.x_hit;
	ray.y_hit = (hor.distance < ver.distance) ? hor.y_hit : ver.y_hit;
	//
	{
		int color = ft_pixel((ray.is_horizontal ? 180 : 32), 32, 32, 255);
		double x = data->player.x, y = data->player.y;
		double end_x = x + ((ray.distance) * cos(angle * DEG_TO_RAD));
		double end_y = y + ((ray.distance) * sin(angle * DEG_TO_RAD));
		double steps = fabs(end_x - x) > fabs(end_y - y) ? fabs(end_x - x) : fabs(end_y - y);
		double xIncrement = ((end_x - x) / steps);
		double yIncrement = ((end_y - y) / steps);

		for (int i = 0; i <= steps; i++)
		{
			if ((x >= 0 && x < data->map_width) && (y >= 0 && y < data->map_height))
				mlx_put_pixel(data->minimap, x, y, color);
			x += xIncrement;
			y += yIncrement;
		}
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
	draw_pixels_to_map(data);
	draw_fov(data);
	draw_player(data);
}
