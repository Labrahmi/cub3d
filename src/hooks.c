/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:33:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/02 17:12:17 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

// Function to check if a position is valid (not a wall and within map bounds)
int is_valid_position(data_t *data, int x, int y)
{
    int gridX = x / GRID_WIDTH;
    int gridY = y / GRID_HEIGHT;

    // Check out-of-bounds
    if ((gridX >= COLUMNS) || (gridY >= ROWS) || (gridX < 0) || (gridY < 0))
        return 0;

    // Check if it's a wall
    if (data->map_grid[gridY][gridX] == '1')
        return 0;

    return 1; // Valid position
}

void ft_move_player(void *param)
{
    data_t *data;
    int new_x, new_y;

    data = (data_t *)param;
    int dx = data->player.move_speed * cos(data->player.rotation_angle);
    int dy = data->player.move_speed * sin(data->player.rotation_angle);
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        new_x = data->player.x + dx;
        new_y = data->player.y + dy;
        if (is_valid_position(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        new_x = data->player.x - dx;
        new_y = data->player.y - dy;
        if (is_valid_position(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        new_x = data->player.x - dy;
        new_y = data->player.y + dx;
        if (is_valid_position(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        new_x = data->player.x + dy;
        new_y = data->player.y - dx;
        if (is_valid_position(data, new_x, new_y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
    }
    draw_map(data);
}


void ft_turn_player(void *param)
{
    data_t *data;

    data = (data_t *)param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->player.rotation_angle -= data->player.rotation_speed;
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->player.rotation_angle += data->player.rotation_speed;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - >
    if (data->player.rotation_angle < 0)
        data->player.rotation_angle += 2 * M_PI;
    else if (data->player.rotation_angle > 2 * M_PI)
        data->player.rotation_angle -= 2 * M_PI;
    draw_map(data);
}

void ft_general_hooks(void *param)
{
    data_t *data;

    data = (data_t *)param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    if (mlx_is_key_down(data->mlx, MLX_KEY_KP_ADD))
    {
        data->player.move_speed += 1;
        data->player.rotation_speed += 0.01;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_KP_SUBTRACT))
    {
        data->player.move_speed -= 1;
        data->player.rotation_speed -= 0.01;
    }
}

void ft_hooks(data_t *data)
{
    mlx_loop_hook(data->mlx, ft_move_player, data);
    mlx_loop_hook(data->mlx, ft_turn_player, data);
    mlx_loop_hook(data->mlx, ft_general_hooks, data);
}
