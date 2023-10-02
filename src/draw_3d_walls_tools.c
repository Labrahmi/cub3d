/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 20:28:08 by macbook           #+#    #+#             */
/*   Updated: 2023/10/02 22:59:18 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

draw_3d_walls_t	ft_get_hor_3d_data(data_t *data, hitRay_t ray)
{
	draw_3d_walls_t	x;
	float			r;

	x.texture = data->texture_S;
	r = (float)((float)x.texture->width / (float)data->grid_size);
	x.c_tex.x = x.texture->width - fmod(ray.x_hit, data->grid_size) * (r);
	if (ray.is_facing_up)
	{
		x.texture = data->texture_N;
		x.c_tex.x = fmod(ray.x_hit, data->grid_size) * (r);
	}
	return (x);
}

draw_3d_walls_t	ft_get_ver_3d_data(data_t *data, hitRay_t ray)
{
	draw_3d_walls_t	x;
	float			r;

	x.texture = data->texture_W;
	r = (float)((float)x.texture->width / (float)data->grid_size);
	x.c_tex.x = fmod(ray.y_hit, data->grid_size) * (r);
	if (ray.is_facing_left)
	{
		x.texture = data->texture_E;
		x.c_tex.x = x.texture->width - fmod(ray.y_hit, data->grid_size) * (r);
	}
	return (x);
}
