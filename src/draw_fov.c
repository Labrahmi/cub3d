/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:23:23 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/03 00:29:50 by macbook          ###   ########.fr       */
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
			if (y > (int)(data->game->height / 2))
				mlx_put_pixel(data->game, x, y, data->f_color);
			else
				mlx_put_pixel(data->game, x, y, data->c_color);
		}
	}
}

common_data_t	init_common_data(float angle, data_t *data, hitRay_t *ray)
{
	common_data_t	comm;

	comm.ray = ray;
	comm.ray->is_facing_down = (angle > 0 && angle <= 180);
	comm.ray->is_facing_up = !comm.ray->is_facing_down;
	comm.ray->is_facing_right = (angle < 90 || angle > 270);
	comm.ray->is_facing_left = !comm.ray->is_facing_right;
	comm.wall_hit_x = INT_MAX;
	comm.wall_hit_y = INT_MAX;
	comm.x_to_check = 0;
	comm.y_to_check = 0;
	comm.gx = 0;
	comm.gy = 0;
	return (comm);
}

void	difination_ray(hitRay_t *ray, data_t *data, float angle)
{
	hitRay_t	hor;
	hitRay_t	ver;
	int			var[2];
	common_data_t	comm;

	comm = init_common_data(angle, data, ray);
	hor = get_horizontal_intersect(data, angle, comm);
	ver = get_vertical_intersect(data, angle, comm);
	var[0] = 0;
	var[1] = 0;
	if (hor.distance < ver.distance)
		var[0] = 1;
	else
		var[1] = 1;
	ray->distance = (var[0] * hor.distance) + (ver.distance * var[1]);
	ray->is_horizontal = (var[0] * 1) + (var[1] * 0);
	ray->x_hit = (var[0] * hor.x_hit) + (var[1] * ver.x_hit);
	ray->y_hit = (var[0] * hor.y_hit) + (var[1] * ver.y_hit);
	ray->is_facing_down = (var[0] * hor.is_facing_down)
		+ (var[1] * ver.is_facing_down);
	ray->is_facing_up = (var[0] * hor.is_facing_up) + (var[1] * ver.is_facing_up);
	ray->is_facing_left = (var[0] * hor.is_facing_left)
		+ (var[1] * ver.is_facing_left);
	ray->is_facing_right = (var[0] * hor.is_facing_right)
		+ (var[1] * ver.is_facing_right);
}

hitRay_t	draw_line_with_angle(data_t *data, float angle, int i)
{
	hitRay_t	ray;
	t_utils		utils;

	difination_ray(&ray, data, angle);
	utils.color = ft_pixel(180, 32, 32, 150);
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
			mlx_put_pixel(data->minimap, utils.x / 1.50,
				utils.y / 1.50, utils.color);
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
	int			i;

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
