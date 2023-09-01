/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:33:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/01 00:45:34 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_move_player(void *param)
{
    data_t *data;

    data = (data_t *)param;
    int dx = data->player.move_speed * cos(data->player.rotation_angle);
    int dy = data->player.move_speed * sin(data->player.rotation_angle);
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        data->player.x += dx;
        data->player.y += dy;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        data->player.x -= dx;
        data->player.y -= dy;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        data->player.x -= dy;
        data->player.y += dx;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        data->player.x += dy;
        data->player.y -= dx;
    }
    draw_map(data);
}

void ft_turn_player(void *param)
{
    data_t *data;
    
    data = (data_t *)param;
    data->player.rotation_speed = 0.1;
    if (mlx_is_key_down(data->mlx, MLX_KEY_Q))
        data->player.rotation_angle -= data->player.rotation_speed;
    if (mlx_is_key_down(data->mlx, MLX_KEY_E))
        data->player.rotation_angle += data->player.rotation_speed;
    // --------------
    if (data->player.rotation_angle < 0)
        data->player.rotation_angle += 2 * M_PI;
    else if (data->player.rotation_angle > 2 * M_PI)
        data->player.rotation_angle -= 2 * M_PI;
    draw_map(data);
}

void ft_close_game(void *param)
{
    data_t *data;

    data = (data_t *)param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
}

void ft_hooks(data_t *data)
{
    mlx_loop_hook(data->mlx, ft_move_player, data);
    mlx_loop_hook(data->mlx, ft_turn_player, data);
    mlx_loop_hook(data->mlx, ft_close_game, data);
}