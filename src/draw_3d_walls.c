/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:49:03 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/02 12:10:07 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void	draw_one_culumn_textur(data_t *data, vect_t c_img, vect_t c_tex, float columnHeight, mlx_texture_t *texture)
{
	uint32_t	y;
	uint8_t		*pixeli;
	uint8_t		*pixelx;
	int			x;
	int			x2;
	int			y2;

	y = 0;
	x = c_tex.x;
	x2 = c_img.x;
	y2 = c_img.y;
	if (columnHeight > data->game->height)
		y = (columnHeight - data->game->height) / 2;
	if (y2 < 0)
		y2 = 0;
	while (y2 < (int) data->game->height)
	{
		c_tex.y = y * ((float) texture->height / (float) columnHeight);
		if (c_tex.y < texture->height
			&& (((int) c_tex.y * texture->width) + x) < texture->width * texture->height)
		{
			pixelx = &texture->pixels[(((int) c_tex.y * texture->width) + x) * texture->bytes_per_pixel];
			pixeli = &data->game->pixels[((y2 * data->game->width) + x2) * texture->bytes_per_pixel];
			ft_memmove(pixeli, pixelx, texture->bytes_per_pixel);
		}
		y2++;
		y++;
	}
}

void	draw_wall_column(data_t *data, vect_t v1,
			float columnHeight, hitRay_t ray)
{
	vect_t			c_img;
	vect_t			c_tex;
	mlx_texture_t	*texture;
	float			width_ratio;

	c_img.x = v1.x;
	c_img.y = v1.y;
	if (ray.is_horizontal)
	{
		texture = data->texture_S;
		width_ratio = (float)((float)texture->width / (float) data->grid_size);
		c_tex.x = texture->width - fmod(ray.x_hit, data->grid_size) * (width_ratio);
		if (ray.is_facing_up)
		{
			texture = data->texture_N;
			c_tex.x = fmod(ray.x_hit, data->grid_size) * (width_ratio);
		}
	}
	else
	{
		texture = data->texture_W;
		width_ratio = (float)((float) texture->width / (float) data->grid_size);
		c_tex.x = fmod(ray.y_hit, data->grid_size) * (width_ratio);
		if (ray.is_facing_left)
		{
			texture = data->texture_E;
			c_tex.x = texture->width - fmod(ray.y_hit, data->grid_size) * (width_ratio);
		}
	}
	draw_one_culumn_textur(data, c_img, c_tex, columnHeight, texture);
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
