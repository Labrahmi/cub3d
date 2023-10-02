/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/02 19:19:50 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void draw_player(data_t *data)
{
	int x;
	int y;
	int i;
	int j;
	int size;

	size = 4;
	x = data->player.x - size / 2;
	y = data->player.y - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(data->minimap, (x + j) / 1.50, (y + i) / 1.50, ft_pixel(30, 30, 192, 150));
			j++;
		}
		i++;
	}
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
	// if (is_facing_left)
	// 	intercept.x -= 0.0001;
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
		double x_to_check = 0;
		double y_to_check = 0;
		int grid_x = 0, grid_y = 0;
		while ((intercept.x >= 0 && intercept.x < data->minimap->width) && (intercept.y >= 0 && intercept.y < data->minimap->height))
		{
			y_to_check = intercept.y;
			x_to_check = intercept.x;
			grid_x = floor(x_to_check / data->grid_size) - ((is_facing_left) ? 1 : 0);
			grid_y = floor(y_to_check / data->grid_size);
			if (grid_x < 0 || grid_x >= data->columns || grid_y < 0 || grid_y >= data->rows)
				break;
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
	ray.is_facing_down = is_facing_down;
	ray.is_facing_up = is_facing_up;
	ray.is_facing_left = is_facing_left;
	ray.is_facing_right = is_facing_right;
	ray.distance = sqrt(pow(wall_hit_x - data->player.x, 2) + pow(wall_hit_y - data->player.y, 2));
	ray.x_hit = wall_hit_x;
	ray.y_hit = wall_hit_y;
	return (ray);
}

hitRay_t ft_get_horizontal_intersection(data_t *data, double angle)
{
	vect_t intercept;
	double ystep, xstep;
	int is_facing_down;
	int is_facing_up;
	int is_facing_right;
	int is_facing_left;
	double wall_hit_x;
	double wall_hit_y;

	wall_hit_x = INT_MAX;
	wall_hit_y = INT_MAX;
	is_facing_down = (angle > 0 && angle < 180);
	is_facing_up = !is_facing_down;
	is_facing_right = (angle < 90 || angle > 270);
	is_facing_left = !is_facing_right;
	//

	//
	intercept.y = floor(data->player.y / data->grid_size) * data->grid_size;
	if (is_facing_down)
		intercept.y += data->grid_size;
	// if (is_facing_up)
	// 	intercept.y -= 0.0001;
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
		double x_to_check;
		double y_to_check;
		int grid_x, grid_y;
		while ((intercept.x >= 0 && intercept.x < data->minimap->width) && (intercept.y >= 0 && intercept.y < data->minimap->height))
		{
			x_to_check = intercept.x;
			y_to_check = intercept.y;
			grid_x = floor(x_to_check / data->grid_size);
			grid_y = floor(y_to_check / data->grid_size) - (is_facing_up ? 1 : 0);
			if (grid_x < 0 || grid_x >= data->columns || grid_y < 0 || grid_y >= data->rows)
				break;
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
	ray.is_facing_down = is_facing_down;
	ray.is_facing_up = is_facing_up;
	ray.is_facing_left = is_facing_left;
	ray.is_facing_right = is_facing_right;
	ray.distance = sqrt(pow(wall_hit_x - data->player.x, 2) + pow(wall_hit_y - data->player.y, 2));
	ray.x_hit = wall_hit_x;
	ray.y_hit = wall_hit_y;
	return (ray);
}

void draw_map(data_t *data)
{
	draw_pixels_to_map(data);
	draw_fov(data);
	draw_player(data);
}
