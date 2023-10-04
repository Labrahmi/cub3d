/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 23:33:13 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/04 22:36:50 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int	is_valid_position(t_data *data, int x, int y)
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
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
	{
		data->player.rot_ang -= data->player.rotation_speed;
		if (data->player.rot_ang < 0)
			data->player.rot_ang += 360;
		else if (data->player.rot_ang > 360)
			data->player.rot_ang -= 360;
		draw_map(data);
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
	{
		data->player.rot_ang += data->player.rotation_speed;
		if (data->player.rot_ang < 0)
			data->player.rot_ang += 360;
		else if (data->player.rot_ang > 360)
			data->player.rot_ang -= 360;
		draw_map(data);
	}
}

void	ft_general_hooks(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
}

void	mouse_hook(double xpos, void *param)
{
	static int	old_xpos;
	static int	i;
	t_data		*data;

	data = (t_data *) param;
	if (old_xpos == 0)
		old_xpos = xpos;
	if (i++ == 1)
	{
		if (old_xpos > xpos)
			data->player.rot_ang -= (data->player.rotation_speed * 1.5);
		if (old_xpos < xpos)
			data->player.rot_ang += (data->player.rotation_speed * 1.5);
		i = 0;
		old_xpos = xpos;
		draw_map(data);
	}
	if (data->player.rot_ang < 0)
		data->player.rot_ang += 360;
	else if (data->player.rot_ang > 360)
		data->player.rot_ang -= 360;
}

void	ft_hooks(t_data *data)
{
	mlx_loop_hook(data->mlx, ft_move_player, data);
	mlx_loop_hook(data->mlx, ft_turn_player, data);
	mlx_loop_hook(data->mlx, ft_general_hooks, data);
}
