/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:28:08 by macbook           #+#    #+#             */
/*   Updated: 2023/10/03 20:16:56 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

t_draw_3d_walls	ft_get_hor_3d_data(t_data *data, t_hit_ray ray)
{
	t_draw_3d_walls	x;
	float			r;

	x.texture = data->texture_s;
	r = (float)((float)x.texture->width / (float)data->grid_size);
	x.c_tex.x = x.texture->width - fmod(ray.x_hit, data->grid_size) * (r);
	if (ray.is_facing_up)
	{
		x.texture = data->texture_n;
		x.c_tex.x = fmod(ray.x_hit, data->grid_size) * (r);
	}
	return (x);
}

t_draw_3d_walls	ft_get_ver_3d_data(t_data *data, t_hit_ray ray)
{
	t_draw_3d_walls	x;
	float			r;

	x.texture = data->texture_w;
	r = (float)((float)x.texture->width / (float)data->grid_size);
	x.c_tex.x = fmod(ray.y_hit, data->grid_size) * (r);
	if (ray.is_facing_left)
	{
		x.texture = data->texture_e;
		x.c_tex.x = x.texture->width - fmod(ray.y_hit, data->grid_size) * (r);
	}
	return (x);
}
