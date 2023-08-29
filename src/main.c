/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/08/29 09:25:48 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
    return ((r << 24) | (g << 16) | (b << 8) | a);
}

void ft_init(data_t *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!(data->map))
		exit(EXIT_FAILURE);
	data->player.x_pos = 64;
	data->player.y_pos = 64;
}

void draw_player(data_t *data)
{
	for (int i = 0; i < 16; i++)
		for (size_t j = 0; j < 16; j++)
			mlx_put_pixel(data->map, i, j, ft_pixel(255, 255, 255, 255));			
	mlx_image_to_window(data->mlx, data->map, (data->player.x_pos), (data->player.y_pos));
}

void ft_display(data_t *data)
{
	draw_player(data);
}

void ft_move_player(void* param)
{
	data_t *data;

	data = (data_t*) param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.y_pos -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.y_pos += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.x_pos -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.x_pos += 5;
	ft_display(data);
}

int main(void)
{
	data_t *data;

	data = malloc(sizeof(data_t));
	ft_init(data);
	ft_display(data);

	mlx_loop_hook(data->mlx, ft_move_player, data);

	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
