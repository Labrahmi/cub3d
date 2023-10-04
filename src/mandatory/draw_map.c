/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 22:44:46 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/04 11:29:55 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_hit_ray	calculate_ray_len(t_comm_t_data comm, t_data *data)
{
	comm.ray->distance = sqrt(pow(comm.wall_hit_x - data->player.x, 2)
			+ pow(comm.wall_hit_y - data->player.y, 2));
	comm.ray->x_hit = comm.wall_hit_x;
	comm.ray->y_hit = comm.wall_hit_y;
	return (*comm.ray);
}

void	init_vert_inter_data(t_comm_t_data *comm, t_data *data, float angle)
{
	comm->intercept.x = floor(data->player.x / data->grid_size)
		* data->grid_size;
	if (comm->ray->is_facing_right)
		comm->intercept.x += data->grid_size;
	comm->intercept.y = data->player.y + (comm->intercept.x - data->player.x)
		* tan(angle * (M_PI / 180.0));
	comm->xstep = data->grid_size;
	if (comm->ray->is_facing_left)
		comm->xstep *= -1;
	comm->ystep = data->grid_size * tan(angle * (M_PI / 180.0));
	if (comm->ray->is_facing_up && (comm->ystep > 0))
		comm->ystep *= -1;
	if (comm->ray->is_facing_down && (comm->ystep < 0))
		comm->ystep *= -1;
}

t_hit_ray	get_vertical_intersect(t_data *data, double ang, t_comm_t_data c)
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

void	init_horz_inter_data(t_comm_t_data *c, t_data *data, float angle)
{
	c->intercept.y = floor(data->player.y / data->grid_size) * data->grid_size;
	if (c->ray->is_facing_down)
		c->intercept.y += data->grid_size;
	c->intercept.x = data->player.x + (c->intercept.y - data->player.y)
		/ tan(angle * (M_PI / 180.0));
	c->ystep = data->grid_size;
	if (c->ray->is_facing_up)
		c->ystep *= -1;
	c->xstep = data->grid_size / tan(angle * (M_PI / 180.0));
	if (c->ray->is_facing_left && (c->xstep > 0))
		c->xstep *= -1;
	if (c->ray->is_facing_right && (c->xstep < 0))
		c->xstep *= -1;
}

t_hit_ray	get_horizontal_intersect(t_data *data, double ang, t_comm_t_data c)
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
