/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixels.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:55:04 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/02 11:23:57 by ayakoubi         ###   ########.fr       */
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

void	draw_one_grid(data_t *data, int x, int y, int sq_color)
{
	int	i;
	int	j;
	(void)	x;
	(void)	y;

	i = 0;
	while (i < (data->grid_size))
	{
		j = 0;
		while (j < (data->grid_size))
		{
			// if (i == 0 || j == 0)
			// 	mlx_put_pixel(data->minimap, (x + j) / 1.50, (y + i)
			// 		/ 1.50, ft_pixel(150, 150, 150, 150));
			// else
				mlx_put_pixel(data->minimap, (x + j) / 1.50, (y + i)
					/ 1.50, sq_color);
			j++;
		}
		i++;
	}
}

void	draw_pixels_to_map(data_t *data)
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
