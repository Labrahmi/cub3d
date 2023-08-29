/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/08/29 23:59:58 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return ((r << 24) | (g << 16) | (b << 8) | a);
}

void draw_pixels_to_player(data_t *data)
{
	int center_x = (data->player.img->width / 2);
	int center_y = (data->player.img->height / 2);
	int radius = center_x < center_y ? center_x : center_y;
	for (int y = 0; y < data->player.img->height; y++)
	{
		for (int x = 0; x < data->player.img->width; x++)
		{
			int dist_x = x - center_x;
			int dist_y = y - center_y;
			if (dist_x * dist_x + dist_y * dist_y <= radius * radius)
			{
				mlx_put_pixel(data->player.img, x, y, ft_pixel(176, 20, 0, 250));
			}
		}
	}
}

void draw_pixels_to_map(data_t *data)
{
	mlx_image_t *square;

	{
		int32_t sq_color = 0;
		int i = 0;
		while (i < 8)
		{
			int j = 0;
			while (j < 10)
			{
				square = mlx_new_image(data->mlx, 64, 64);
				if (data->map_coords[i][j] == '0') sq_color = ft_pixel(240, 240, 240, 100);
				else sq_color = ft_pixel(64, 64, 64, 100);
				for (size_t i = 0; i < square->height; i++)
					for (size_t j = 0; j < square->width; j++)
						mlx_put_pixel(square, i, j, sq_color);
				mlx_image_to_window(data->mlx, square, j * 64, i * 64);
				j++;
			}
			printf("\n");
			i++;
		}
	}
}

void ft_init(data_t *data)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->map = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!(data->map))
		exit(EXIT_FAILURE);
	data->player.img = mlx_new_image(data->mlx, 64, 64);
	if (!(data->player.img))
		exit(EXIT_FAILURE);
	// init map
	char map_coords[8][10] = {
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '1', '0', '0', '1', '0', '0', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '0', '0', '1', '0', '0', '0', '1', '0', '1'},
		{'1', '0', '0', '0', '0', '0', '0', '0', '0', '1'},
		{'1', '1', '1', '1', '1', '1', '1', '1', '1', '1'},
	};
	memcpy(data->map_coords, map_coords, sizeof(map_coords));
	// init map
	draw_pixels_to_player(data);
	draw_pixels_to_map(data);
	mlx_image_to_window(data->mlx, data->map, (data->mlx->width / 2), (data->mlx->height / 2));
	mlx_image_to_window(data->mlx, data->player.img, (data->map->width / 2), (data->map->height / 2));
}

void ft_move_player(void *param)
{
	data_t *data;

	data = (data_t *)param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		data->player.img->instances[0].y -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		data->player.img->instances[0].y += 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		data->player.img->instances[0].x -= 5;
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		data->player.img->instances[0].x += 5;
}

int main(void)
{
	data_t *data;

	data = malloc(sizeof(data_t));
	ft_init(data);
	mlx_loop_hook(data->mlx, ft_move_player, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (EXIT_SUCCESS);
}
