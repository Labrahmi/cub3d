/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_3d_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/03 16:49:03 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/16 06:59:41 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void clear_screen(data_t *data)
{
    for (int y = 0; y < data->game->height; y++)
    {
        for (int x = 0; x < data->game->width; x++)
        {
            if (y > (data->game->height / 2))
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

void draw_one_culumn_textur(data_t *data, vect_t c_img, vect_t c_tex, float columnHeight, mlx_texture_t *texture)
{
    int x = c_tex.x;
    int x2 = c_img.x;
    int y2 = c_img.y;

    uint8_t *pixelx;
    uint8_t *pixeli;
    uint32_t y = 0;
    if (columnHeight > data->game->height)
    {
        y = (columnHeight - data->game->height) / 2;
    }
    if (y2 < 0)
        y2 = 0;
    while (y2 < data->game->height /*y < data->texture->height - (c_img.y * 2)*/)
    {
        c_tex.y = y * ((float) texture->height / (float) columnHeight);
        if (c_tex.y < texture->height
            && (((int) c_tex.y * texture->width) + x) < texture->width * texture->height)
        {
            pixelx = &texture->pixels[(((int) c_tex.y * texture->width) + x) * texture->bytes_per_pixel];
            pixeli = &data->game->pixels[((y2 * data->game->width) + x2) * texture->bytes_per_pixel];
            memmove(pixeli, pixelx, texture->bytes_per_pixel);
        }
        y2++;
        y++;
    }
}

void draw_wall_column(data_t *data, vect_t v1, float columnHeight, hitRay_t ray)
{
    vect_t c_img, c_tex;
    mlx_texture_t *texture;
    int thick = 1;
    int color = ft_pixel((ray.is_horizontal ? 180 : 32), 32, 32, columnHeight > 255 ? 255 : columnHeight);

    c_img.x = v1.x;
    c_img.y = v1.y;
    float width_ratio;
    if (ray.is_horizontal)
    {
        texture = data->texture_1;
        if (ray.is_facing_up)
            texture = data->texture_2;
        width_ratio = (float) ((float)texture->width / (float) data->grid_size);
        c_tex.x = fmod(ray.x_hit , data->grid_size) * (width_ratio);
    }
    else
    {
        texture = data->texture_3;
        if (ray.is_facing_left)
            texture = data->texture_4;
        width_ratio = (float) ((float)texture->width / (float) data->grid_size);
        c_tex.x = fmod(ray.y_hit , data->grid_size) * (width_ratio);
    }
    draw_one_culumn_textur(data, c_img, c_tex, columnHeight, texture);
    
    // for (int y = v1.y; y < v1.y + columnHeight; y++)
    // {
    //     for (int x = v1.x; x < v1.x + thick; x++)
    //     {
    //         if ((x >= 0 && x < data->game->width) && (y >= 0 && y < data->game->height))
    //         {
    //             mlx_put_pixel(data->game, x, y, color);
    //         }
    //     }
    // }
}


void draw_3d_walls(data_t *data, hitRay_t ray, int ray_num)
{
    vect_t v1;
    v1.x = ray_num;
    v1.y = ((data->game->height / 2) - (((data->game->height / 2) * (data->grid_size)) / ray.distance));
    float ch = data->game->height - (v1.y * 2);
    draw_wall_column(data, v1, ch, ray);
    // 
}
