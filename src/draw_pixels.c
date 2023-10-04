/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:55:04 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 10:07:26 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

int	set_color(char position)
{
	int	sq_color;

	sq_color = ft_pixel(32, 32, 32, 0);
	if (position == '0')
		sq_color = ft_pixel(255, 245, 224, 150);
	if (position == '1')
		sq_color = ft_pixel(144, 159, 145, 150);
	return (sq_color);
}

void	draw_one_grid(t_data *data, int x, int y, int sq_color)
{
	int	i;
	int	j;

	i = 0;
	while (i < (data->grid_size))
	{
		j = 0;
		while (j < (data->grid_size))
		{
			mlx_put_pixel(data->minimap, (x + j) / 1.50, (y + i)
				/ 1.50, sq_color);
			j++;
		}
		i++;
	}
}

void	draw_pixels_to_map(t_data *data)
{
	int	r;
	int	c;
	int	sq_color;

	r = 0;
	while (data->map_grid[r])
	{
		c = 0;
		while (data->map_grid[r][c])
		{
			sq_color = set_color(data->map_grid[r][c]);
			draw_one_grid(data, (c * data->grid_size),
				(r * data->grid_size), sq_color);
			c++;
		}
		r++;
	}
}
