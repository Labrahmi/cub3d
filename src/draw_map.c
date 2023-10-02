/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/03 00:41:38 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_player(data_t *data, int32_t clr)
{
	int	x;
	int	y;
	int	i;
	int	j;
	int	size;

	size = 4;
	x = data->player.x - size / 2;
	y = data->player.y - size / 2;
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			mlx_put_pixel(data->minimap, (x + j) / 1.50, (y + i) / 1.50, clr);
			j++;
		}
		i++;
	}
}

hitRay_t	calculate_ray_len(common_data_t comm, data_t *data)
{
	comm.ray->distance = sqrt(pow(comm.wall_hit_x - data->player.x, 2)
			+ pow(comm.wall_hit_y - data->player.y, 2));
	comm.ray->x_hit = comm.wall_hit_x;
	comm.ray->y_hit = comm.wall_hit_y;
	return (*comm.ray);
}

void	init_vert_inter_data(common_data_t *comm, data_t *data, float angle)
{
	comm->intercept.x = floor(data->player.x / data->grid_size)
		* data->grid_size;
	if (comm->ray->is_facing_right)
		comm->intercept.x += data->grid_size;
	comm->intercept.y = data->player.y + (comm->intercept.x - data->player.x)
		* tan(angle * (DEG_TO_RAD));
	comm->xstep = data->grid_size;
	if (comm->ray->is_facing_left)
		comm->xstep *= -1;
	comm->ystep = data->grid_size * tan(angle * (DEG_TO_RAD));
	if (comm->ray->is_facing_up && (comm->ystep > 0))
		comm->ystep *= -1;
	if (comm->ray->is_facing_down && (comm->ystep < 0))
		comm->ystep *= -1;
}

hitRay_t	get_vertical_intersect(data_t *data, double ang, common_data_t c)
{
	init_vert_inter_data(&c, data, ang);
	while ((c.intercept.x >= 0 && c.intercept.x < data->minimap->width)
		&& (c.intercept.y >= 0 && c.intercept.y < data->minimap->height))
	{
		c.y_to_check = c.intercept.y;
		c.x_to_check = c.intercept.x;
		c.gx = floor(c.x_to_check / data->grid_size);
		if (c.ray->is_facing_left)
			c.gx = floor(c.x_to_check / data->grid_size) - 1;
		c.gy = floor(c.y_to_check / data->grid_size);
		if (c.gx < 0 || c.gx >= data->columns || c.gy < 0 || c.gy >= data->rows)
			break ;
		if (data->map_grid[c.gy][c.gx] != '0')
		{
			c.wall_hit_x = c.intercept.x;
			c.wall_hit_y = c.intercept.y;
			break ;
		}
		else
		{
			c.intercept.x += c.xstep;
			c.intercept.y += c.ystep;
		}
	}
	return (calculate_ray_len(c, data));
}

void	init_horz_inter_data(common_data_t *c, data_t *data, float angle)
{
	c->intercept.y = floor(data->player.y / data->grid_size) * data->grid_size;
	if (c->ray->is_facing_down)
		c->intercept.y += data->grid_size;
	c->intercept.x = data->player.x + (c->intercept.y - data->player.y)
		/ tan(angle * (DEG_TO_RAD));
	c->ystep = data->grid_size;
	if (c->ray->is_facing_up)
		c->ystep *= -1;
	c->xstep = data->grid_size / tan(angle * (DEG_TO_RAD));
	if (c->ray->is_facing_left && (c->xstep > 0))
		c->xstep *= -1;
	if (c->ray->is_facing_right && (c->xstep < 0))
		c->xstep *= -1;
}

hitRay_t	get_horizontal_intersect(data_t *data, double ang, common_data_t c)
{
	init_horz_inter_data(&c, data, ang);
	while ((c.intercept.x >= 0 && c.intercept.x < data->minimap->width)
		&& (c.intercept.y >= 0 && c.intercept.y < data->minimap->height))
	{
		c.x_to_check = c.intercept.x;
		c.y_to_check = c.intercept.y;
		c.gx = floor(c.x_to_check / data->grid_size);
		c.gy = floor(c.y_to_check / data->grid_size);
		if (c.ray->is_facing_up)
			c.gy = floor(c.y_to_check / data->grid_size) - 1;
		if (c.gx < 0 || c.gx >= data->columns || c.gy < 0 || c.gy >= data->rows)
			break ;
		if (data->map_grid[c.gy][c.gx] != '0')
		{
			c.wall_hit_x = c.intercept.x;
			c.wall_hit_y = c.intercept.y;
			break ;
		}
		else
		{
			c.intercept.x += c.xstep;
			c.intercept.y += c.ystep;
		}
	}
	return (calculate_ray_len(c, data));
}

void	draw_map(data_t *data)
{
	draw_pixels_to_map(data);
	draw_fov(data);
	draw_player(data, ft_pixel(30, 30, 192, 150));
}
