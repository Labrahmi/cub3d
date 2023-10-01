/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:23:23 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/01 15:55:24 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, 360.0f);
	if (angle < 0)
		angle += 360.0f;
	return (angle);
}

void	clear_screen(data_t *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < (int) data->game->height)
	{
		x = -1;
		while (++x < (int) data->game->width)
		{
			if (y > (int) (data->game->height / 2))
				mlx_put_pixel(data->game, x, y, data->f_color);
			else
				mlx_put_pixel(data->game, x, y, data->c_color);
		}
	}
}

void	difination_ray(hitRay_t *ray, data_t *data, float angle)
{
	hitRay_t	hor;
	hitRay_t	ver;
	int			var1;
	int			var2;

	hor = ft_get_horizontal_intersection(data, angle);
	ver = ft_get_vertical_intersection(data, angle);
	var1 = 0;
	var2 = 0;
	if (hor.distance < ver.distance)
		var1 = 1;
	else
		var2 = 1;
	ray->distance = (var1 * hor.distance) + (ver.distance * var2);
	ray->is_horizontal = (var1 * 1) + (var2 * 0);
	ray->x_hit = (var1 * hor.x_hit) + (var2 * ver.x_hit);
	ray->y_hit = (var1 * hor.y_hit) + (var2 * ver.y_hit);
	ray->is_facing_down = (var1 * hor.is_facing_down)
		+ (var2 * ver.is_facing_down);
	ray->is_facing_up = (var1 * hor.is_facing_up) + (var2 * ver.is_facing_up);
	ray->is_facing_left = (var1 * hor.is_facing_left)
		+ (var2 * ver.is_facing_left);
	ray->is_facing_right = (var1 * hor.is_facing_right)
		+ (var2 * ver.is_facing_right);
}

hitRay_t	draw_line_with_angle(data_t *data, float angle, int i)
{
	hitRay_t	ray;
	t_utils		utils;

	difination_ray(&ray, data, angle);
	utils.color = ft_pixel(180, 32, 32, 150);
	if (ray.is_horizontal)
		utils.color = ft_pixel(32, 32, 180, 150);

	utils.x = data->player.x;
	utils.y = data->player.y;
	utils.end_x = utils.x + ((ray.distance) * cos(angle * DEG_TO_RAD));
	utils.end_y = utils.y + ((ray.distance) * sin(angle * DEG_TO_RAD));
	if (fabs(utils.end_x - utils.x) > fabs(utils.end_y - utils.y))
		utils.steps = fabs(utils.end_x - utils.x);
	else
		utils.steps = fabs(utils.end_y - utils.y);
	utils.xIncrement = ((utils.end_x - utils.x) / utils.steps);
	utils.yIncrement = ((utils.end_y - utils.y) / utils.steps);
	while (++i <= utils.steps)
	{
		if ((utils.x >= 0 && utils.x < data->map_width)
			&& (utils.y >= 0 && utils.y < data->map_height))
			mlx_put_pixel(data->minimap, utils.x / 1.00,
				utils.y / 1.00, utils.color);
		utils.x += utils.xIncrement;
		utils.y += utils.yIncrement;
	}
	return (ray);
}

void	draw_fov(data_t *data)
{
	float		angle;
	float		step;
	hitRay_t	ray;
	int			ray_num;
	int i;

	angle = (data->player.rotation_angle - (data->fov_angle / 2));
	angle = normalize_angle(angle);
	step = (data->fov_angle / data->game->width);
	ray_num = 0;
	clear_screen(data);
	while (ray_num < (int) data->game->width)
	{
		i = -1;
		ray = draw_line_with_angle(data, angle, i);
		ray.distance = ray.distance
			* cos((angle - data->player.rotation_angle) * (DEG_TO_RAD));
		draw_3d_walls(data, ray, ray_num);
		ray_num++;
		angle += step;
		angle = normalize_angle(angle);
	}
}
