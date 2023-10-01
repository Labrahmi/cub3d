/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 16:50:47 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/29 17:31:29 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void get_cord_to_move(data_t *data, int *new_x, int *new_y, int key)
{
    int dx;
    int dy;

    dx = data->player.move_speed * cos(data->player.rotation_angle * (M_PI / 180.0));
    dy = data->player.move_speed * sin(data->player.rotation_angle * (M_PI / 180.0));
    if (key == MLX_KEY_W)
    {
        *new_x = data->player.x + dx;
        *new_y = data->player.y + dy;
    }
    if (key == MLX_KEY_S)
    {
        *new_x = data->player.x - dx;
        *new_y = data->player.y - dy;
    }
    if (key == MLX_KEY_D)
    {
        *new_x = data->player.x - dy;
        *new_y = data->player.y + dx;
    }
    if (key == MLX_KEY_A)
    {
        *new_x = data->player.x + dy;
        *new_y = data->player.y - dx;
    }
}

void draw_the_hook(data_t *data, int new_x, int new_y)
{
    if (is_valid_position(data, new_x, new_y) && is_valid_position(data, data->player.x, new_y) && is_valid_position(data, new_x, data->player.y))
    {
        data->player.x = new_x;
        data->player.y = new_y;
    }
    draw_map(data);
}

void ft_move_player(void *param)
{
    data_t *data;
    int new_x;
    int new_y;

    data = (data_t *)param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        get_cord_to_move(data, &new_x, &new_y, MLX_KEY_W);
        draw_the_hook(data, new_x, new_y);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        get_cord_to_move(data, &new_x, &new_y, MLX_KEY_S);
        draw_the_hook(data, new_x, new_y);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        get_cord_to_move(data, &new_x, &new_y, MLX_KEY_D);
        draw_the_hook(data, new_x, new_y);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        get_cord_to_move(data, &new_x, &new_y, MLX_KEY_A);
        draw_the_hook(data, new_x, new_y);
    }
}
