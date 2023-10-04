/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fov.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 12:23:23 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 11:35:06 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	clear_screen(t_data *data)
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

t_comm_t_data	init_common_data(float angle, t_hit_ray *ray, int *v1, int *v2)
{
	t_comm_t_data	comm;

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
	*v1 = 0;
	*v2 = 0;
	return (comm);
}

void	difination_ray(t_hit_ray *ray, t_data *data, float angle)
{
	t_hit_ray		hor;
	t_hit_ray		ver;
	int				var1;
	int				var2;
	t_comm_t_data	comm;

	comm = init_common_data(angle, ray, &var1, &var2);
	hor = get_horizontal_intersect(data, angle, comm);
	ver = get_vertical_intersect(data, angle, comm);
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

t_hit_ray	draw_line_with_angle(t_data *data, float angle, int i)
{
	t_hit_ray	ray;
	t_utils		utils;

	difination_ray(&ray, data, angle);
	utils.color = ft_pixel(180, 32, 32, 150);
	utils.x = data->player.x;
	utils.y = data->player.y;
	utils.end_x = utils.x + ((ray.distance) * cos(angle * M_PI / 180.0));
	utils.end_y = utils.y + ((ray.distance) * sin(angle * M_PI / 180.0));
	if (fabs(utils.end_x - utils.x) > fabs(utils.end_y - utils.y))
		utils.steps = fabs(utils.end_x - utils.x);
	else
		utils.steps = fabs(utils.end_y - utils.y);
	utils.x_inc = ((utils.end_x - utils.x) / utils.steps);
	utils.y_inc = ((utils.end_y - utils.y) / utils.steps);
	while (++i <= utils.steps)
	{
		if ((utils.x >= 0 && utils.x < data->map_width)
			&& (utils.y >= 0 && utils.y < data->map_height))
			mlx_put_pixel(data->minimap, utils.x / 1.50,
				utils.y / 1.50, utils.color);
		utils.x += utils.x_inc;
		utils.y += utils.y_inc;
	}
	return (ray);
}

void	draw_fov(t_data *data)
{
	float		angle;
	float		step;
	t_hit_ray	ray;
	int			ray_num;
	int			i;

	angle = (data->player.rot_ang - (data->fov_angle / 2));
	angle = normalize_angle(angle);
	step = (data->fov_angle / data->game->width);
	ray_num = 0;
	clear_screen(data);
	while (ray_num < (int) data->game->width)
	{
		i = -1;
		ray = draw_line_with_angle(data, angle, i);
		ray.distance = ray.distance
			* cos((angle - data->player.rot_ang) * (M_PI / 180.0));
		draw_3d_walls(data, ray, ray_num);
		ray_num++;
		angle += step;
		angle = normalize_angle(angle);
	}
}
