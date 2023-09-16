/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/16 10:07:16 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

void ft_init(data_t *data)
{
	data->mlx = mlx_init(1280, 720, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->grid_size = 50;
	data->map_height = data->grid_size * 10;
	data->map_width = data->grid_size * 18;
	data->player.x = (750);
	data->player.y = (400);
	data->player.rotation_angle = (210);
	data->player.rotation_speed = 2;
	data->player.move_speed = 3;
	data->fov_angle = 60;
	data->columns = 18;
	data->rows = 10;
	// -
	data->minimap = mlx_new_image(data->mlx, data->map_width, data->map_height);
	data->game = mlx_new_image(data->mlx, 1280, 720);
	// -
	char map_grid[10][18] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	memcpy(data->map_grid, map_grid, sizeof(map_grid));
	// -
	data->texture_1 = mlx_load_png("assets/wall_1.png");
	data->texture_2 = mlx_load_png("assets/wall_2.png");
	data->texture_3 = mlx_load_png("assets/wall_3.png");
	data->texture_4 = mlx_load_png("assets/wall_4.png");
	draw_map(data);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	mlx_put_string(data->mlx, "33-34", 10, 10);
	//
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


int main(void)
{
	data_t *data;

	data = malloc(sizeof(data_t));
	ft_init(data);
	ft_hooks(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_DISABLED);
	mlx_cursor_hook(data->mlx,(mlx_cursorfunc) mouse_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	system("clear");
	return (free(data), EXIT_SUCCESS);
}
