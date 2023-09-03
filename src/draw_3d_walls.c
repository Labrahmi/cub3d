/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:49:03 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/04 00:54:32 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void clear_screen(data_t *data)
{
    for (int y = 0; y < data->game->height; y++)
    {
        for (int x = 0; x < data->game->width; x++)
        {
            mlx_put_pixel(data->game, x, y, ft_pixel(32, 32, 32, 255));
        }
    }
}

double cast_ray(data_t *data, double angle)
{
    return 0;
}

void draw_wall_column(data_t *data, vect_t v1, int columnHeight, int h_v)
{
    int thick = 1;
    for (int y = v1.y; y < v1.y + columnHeight; y++)
    {
        for (int x = v1.x; x < v1.x + thick; x++)
        {
            if ((x >= 0 && x < data->game->width) && (y >= 0 && y < data->game->height))
            {
                if (h_v == 1)
                    mlx_put_pixel(data->game, x, y, ft_pixel(255, 0, 0, 255));
                else
                    mlx_put_pixel(data->game, x, y, ft_pixel(200, 0, 0, 255));
            }
        }
    }
}

void draw_3d_walls(data_t *data, hitRay_t ray, int ray_num)
{
    vect_t v1;
    v1.x = ray_num;
    v1.y = ((SCREEN_HEIGHT / 2) - (((SCREEN_HEIGHT / 2) * 30) / ray.distance));
    double ch = SCREEN_HEIGHT - (v1.y * 2);
    draw_wall_column(data, v1, ch, ray.h_v);
}
