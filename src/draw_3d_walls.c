/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:49:03 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/07 19:03:10 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void clear_screen(data_t *data)
{
    for (int y = 0; y < data->game->height; y++)
    {
        for (int x = 0; x < data->game->width; x++)
        {
            if (y > (SCREEN_HEIGHT / 2))
                mlx_put_pixel(data->game, x, y, ft_pixel(60, 60, 60, 255));
            else
                mlx_put_pixel(data->game, x, y, ft_pixel(200, 200, 200, 255));
        }
    }
}

float cast_ray(data_t *data, float angle)
{
    return 0;
}

void draw_wall_column(data_t *data, vect_t v1, int columnHeight, hitRay_t ray)
{
    int thick = 1;
    int color = ft_pixel((ray.is_horizontal ? 180 : 32), 32, 32, columnHeight > 255 ? 255 : columnHeight);
    for (int y = v1.y; y < v1.y + columnHeight; y++)
    {
        for (int x = v1.x; x < v1.x + thick; x++)
        {
            if ((x >= 0 && x < data->game->width) && (y >= 0 && y < data->game->height))
            {
                mlx_put_pixel(data->game, x, y, color);
            }
        }
    }
}

void draw_3d_walls(data_t *data, hitRay_t ray, int ray_num)
{
    vect_t v1;
    v1.x = ray_num;
    v1.y = ((SCREEN_HEIGHT / 2) - (((SCREEN_HEIGHT / 2) * (GRID_WIDTH)) / ray.distance));
    float ch = SCREEN_HEIGHT - (v1.y * 2);
    draw_wall_column(data, v1, ch, ray);
}
