/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:49:03 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/02 22:57:29 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	ft_init_3d_data(t_3d_data *draw_data, draw_3d_walls_t x)
{
	draw_data->v1.y = 0;
	draw_data->v1.x = x.c_tex.x;
	draw_data->v2.x = x.c_img.x;
	draw_data->v2.y = x.c_img.y;
	if (draw_data->v2.y < 0)
		draw_data->v2.y = 0;
	if (x.ch > x.data->game->height)
		draw_data->v1.y = (x.ch - x.data->game->height) / 2;
}

void	draw_one_culumn_textur(draw_3d_walls_t x)
{
	t_3d_data	dw;
	int_vect_t	res;
	uint32_t	max;
	uint8_t		byp;

	ft_init_3d_data(&dw, x);
	while (dw.v2.y < (int) x.data->game->height)
	{
		x.c_tex.y = dw.v1.y * ((float) x.texture->height / (float) x.ch);
		max = x.texture->width * x.texture->height;
		if (x.c_tex.y < x.texture->height
			&& (((int) x.c_tex.y * x.texture->width) + dw.v1.x) < max)
		{
			byp = x.texture->bytes_per_pixel;
			res.x = (((int) x.c_tex.y * x.texture->width) + dw.v1.x) * byp;
			res.y = ((dw.v2.y * x.data->game->width) + dw.v2.x) * byp;
			dw.pixelx = &x.texture->pixels[res.x];
			dw.pixeli = &x.data->game->pixels[res.y];
			ft_memmove(dw.pixeli, dw.pixelx, byp);
		}
		(dw.v2.y)++;
		(dw.v1.y)++;
	}
}

void	draw_wall_column(data_t *data, vect_t v1, float ch, hitRay_t ray)
{
	draw_3d_walls_t	x;

	if (ray.is_horizontal)
		x = ft_get_hor_3d_data(data, ray);
	else
		x = ft_get_ver_3d_data(data, ray);
	x.c_img.x = v1.x;
	x.c_img.y = v1.y;
	x.ch = ch;
	x.data = data;
	draw_one_culumn_textur(x);
}

void	draw_3d_walls(data_t *data, hitRay_t ray, int ray_num)
{
	vect_t	v1;
	float	ch;

	v1.x = ray_num;
	v1.y = ((data->game->height / 2)
			- (((data->game->height / 2) * (data->grid_size)) / ray.distance));
	ch = data->game->height - (v1.y * 2);
	draw_wall_column(data, v1, ch, ray);
}
