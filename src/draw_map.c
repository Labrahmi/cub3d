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

void	draw_map(data_t *data)
{
	draw_pixels_to_map(data);
	draw_fov(data);
	draw_player(data, ft_pixel(30, 30, 192, 150));
}
