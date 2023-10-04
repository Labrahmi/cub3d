/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_tool.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 18:32:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/04 10:16:30 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_data *data, int32_t clr)
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

void	draw_map(t_data *data)
{
	draw_pixels_to_map(data);
	draw_fov(data);
	draw_player(data, ft_pixel(30, 30, 192, 150));
}
