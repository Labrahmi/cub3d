/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:54:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/01 15:37:04 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	calculate_res(char **map, int mode)
{
	int	i;
	int	max;

	i = 0;
	while (map[i])
	{
		if (i == 0)
			max = ft_strlen(map[i]);
		if ((int) ft_strlen(map[i]) > max)
			max = strlen(map[i]);
		i++;
	}
	if (mode == 1)
		return (max);
	if (mode == 2)
		return (i);
	return (0);
}

void	fill_data_from_datamap(data_t *data, t_data_maps *map)
{
	int	i;

	data->columns = calculate_res(map->map, 1);
	data->rows = calculate_res(map->map, 2);
	data->map_grid = (char **) calloc(sizeof(char *), data->rows + 1);
	i = -1;
	while (map->map[++i])
	{
		data->map_grid[i] = ft_strtrim(map->map[i], "\n");
		free(map->map[i]);
	}
	free(map->map);
	data->texture_N = mlx_load_png(map->textures[0]);
	data->texture_S = mlx_load_png(map->textures[1]);
	data->texture_E = mlx_load_png(map->textures[2]);
	data->texture_W = mlx_load_png(map->textures[3]);
	i = -1;
	while (++i < 4)
		free(map->textures[i]);
	data->c_color = ft_pixel(map->C[0], map->C[1], map->C[2], 255);
	data->f_color = ft_pixel(map->F[0], map->F[1], map->F[2], 255);
}

void	ft_init(data_t *data, t_data_maps *map)
{
	fill_data_from_datamap(data, map);
	data->mlx = mlx_init(1080, 1000, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->grid_size = 12;
	data->map_height = data->grid_size * data->rows;
	data->map_width = data->grid_size * data->columns;
	data->player.x = (map->posplayer->x * data->grid_size)
		+ (data->grid_size / 2);
	data->player.y = (map->posplayer->y * data->grid_size)
		+ (data->grid_size / 2);
	data->player.rotation_angle = (map->posplayer->dir);
	data->player.rotation_speed = 2;
	data->player.move_speed = 2;
	data->fov_angle = 60;
	data->minimap = mlx_new_image(data->mlx, data->map_width, data->map_height);
	data->game = mlx_new_image(data->mlx, 1080, 1000);
	draw_map(data);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 15, 15);
}
