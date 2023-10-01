/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:33:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/01 12:40:19 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_position(data_t *data, int x, int y)
{
	int	gridx;
	int	gridy;

	gridx = (x / data->grid_size);
	gridy = (y / data->grid_size);
	if ((gridx >= data->columns) || (gridy >= data->rows)
		|| (gridx < 0) || (gridy < 0))
		return (0);
	if (data->map_grid[gridy][gridx] == '1')
		return (0);
	return (1);
}

void	ft_turn_player(void *param)
{
	data_t	*data;

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
}

void	ft_general_hooks(void *param)
{
	data_t	*data;

	data = (data_t *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	mouse_hook(double xpos, void *param)
{
	static int	old_xpos;
	static int	i;
	data_t		*data;

	data = (data_t *) param;
	if (old_xpos == 0)
		old_xpos = xpos;
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
	if (data->player.rotation_angle < 0)
		data->player.rotation_angle += 360;
	else if (data->player.rotation_angle > 360)
		data->player.rotation_angle -= 360;
}

void	ft_hooks(data_t *data)
{
	mlx_loop_hook(data->mlx, ft_move_player, data);
	mlx_loop_hook(data->mlx, ft_turn_player, data);
	mlx_loop_hook(data->mlx, ft_general_hooks, data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data->mlx, (mlx_cursorfunc) mouse_hook, data);
}
