/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:33:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/17 08:33:11 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int is_valid_position(data_t *data, int x, int y)
{
    int gridX = (x / data->grid_size);
    int gridY = (y / data->grid_size);

    if ((gridX >= data->columns) || (gridY >= data->rows) || (gridX < 0) || (gridY < 0))
        return 0;
    if (data->map_grid[gridY][gridX] == '1')
        return 0;
    return 1;
}

void ft_move_player(void *param)
{
    data_t *data;
    int new_x, new_y;

    data = (data_t *)param;
    int dx = data->player.move_speed * cos(data->player.rotation_angle * (M_PI / 180.0));
    int dy = data->player.move_speed * sin(data->player.rotation_angle * (M_PI / 180.0));
    if (mlx_is_key_down(data->mlx, MLX_KEY_W))
    {
        new_x = data->player.x + dx;
        new_y = data->player.y + dy;
        if (is_valid_position(data, new_x, new_y) && is_valid_position(data, data->player.x, new_y) && is_valid_position(data, new_x, data->player.y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
        draw_map(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_S))
    {
        new_x = data->player.x - dx;
        new_y = data->player.y - dy;
        if (is_valid_position(data, new_x, new_y) && is_valid_position(data, data->player.x, new_y) && is_valid_position(data, new_x, data->player.y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
        draw_map(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_D))
    {
        new_x = data->player.x - dy;
        new_y = data->player.y + dx;
        if (is_valid_position(data, new_x, new_y) && is_valid_position(data, data->player.x, new_y) && is_valid_position(data, new_x, data->player.y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
        draw_map(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_A))
    {
        new_x = data->player.x + dy;
        new_y = data->player.y - dx;
        if (is_valid_position(data, new_x, new_y) && is_valid_position(data, data->player.x, new_y) && is_valid_position(data, new_x, data->player.y))
        {
            data->player.x = new_x;
            data->player.y = new_y;
        }
        draw_map(data);
    }
}

void ft_turn_player(void *param)
{
    data_t *data;

    data = (data_t *)param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
    {
        data->player.rotation_angle -= data->player.rotation_speed;
        if (data->player.rotation_angle < 0)
            data->player.rotation_angle += 360;
        else if (data->player.rotation_angle > 360)
            data->player.rotation_angle -= 360;
        draw_map(data);
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
    {
        data->player.rotation_angle += data->player.rotation_speed;
        if (data->player.rotation_angle < 0)
            data->player.rotation_angle += 360;
        else if (data->player.rotation_angle > 360)
            data->player.rotation_angle -= 360;
        draw_map(data);
    }
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - >
}

void ft_general_hooks(void *param)
{
    data_t *data;

    data = (data_t *)param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    if (mlx_is_key_down(data->mlx, MLX_KEY_KP_ADD))
    {
        if ((data->fov_angle + 1) < 160)
            data->fov_angle += 1;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_KP_SUBTRACT))
    {
        if ((data->fov_angle - 1) > 30)
            data->fov_angle -= 1;
    }
    
}

void mouse_hook(double xpos, double ypos, void *param)
{
	static int old_xpos;
	static int i;
	data_t *data;

    data = (data_t *) param;
	if (old_xpos == 0)
		old_xpos = xpos;
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - >
	if (i++ == 1)
	{
		if (old_xpos > xpos)
			data->player.rotation_angle -= (data->player.rotation_speed * 1.5);
		if (old_xpos < xpos)
			data->player.rotation_angle += (data->player.rotation_speed * 1.5);
		i = 0;
		old_xpos = xpos;
		draw_map(data);
	}
	// 
    if (data->player.rotation_angle < 0)
        data->player.rotation_angle += 360;
    else if (data->player.rotation_angle > 360)
        data->player.rotation_angle -= 360;
}

void ft_hooks(data_t *data)
{
    mlx_loop_hook(data->mlx, ft_move_player, data);
    mlx_loop_hook(data->mlx, ft_turn_player, data);
    mlx_loop_hook(data->mlx, ft_general_hooks, data);
    // mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	// mlx_cursor_hook(data->mlx,(mlx_cursorfunc) mouse_hook, data);
}
