/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/23 11:54:28 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 23:13:35 by ylabrahm         ###   ########.fr       */
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
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	if (mode == 1)
		return (max);
	if (mode == 2)
		return (i);
	return (0);
}

int	ft_destroy_textures(mlx_texture_t **texts)
{
	int	ids[4];
	int	err;
	int	i;

	i = -1;
	err = 0;
	while (++i < 4)
	{
		ids[i] = 0;
		if (!texts[i])
		{
			err = 1;
			ids[i] = 1;
		}
	}
	i = -1;
	while (++i < 4 && err)
	{
		if (ids[i] == 0)
			mlx_delete_texture(texts[i]);
	}
	return (err);
}

void	ft_check_textures(t_data *data, t_data_maps *map)
{
	mlx_texture_t	*texts[4];
	int				mode;

	texts[0] = mlx_load_png(map->textures[0]);
	texts[1] = mlx_load_png(map->textures[1]);
	texts[2] = mlx_load_png(map->textures[2]);
	texts[3] = mlx_load_png(map->textures[3]);
	mode = ft_destroy_textures(texts);
	if (mode)
	{
		free(data);
		destroy_data_map(map, FALSE);
	}
	data->texture_n = texts[0];
	data->texture_s = texts[1];
	data->texture_e = texts[2];
	data->texture_w = texts[3];
}

void	fill_data_from_datamap(t_data *data, t_data_maps *map)
{
	int	i;

	ft_check_textures(data, map);
	data->columns = calculate_res(map->map, 1);
	data->rows = calculate_res(map->map, 2);
	data->map_grid = (char **)calloc(sizeof(char *), data->rows + 1);
	i = -1;
	while (map->map[++i])
		data->map_grid[i] = ft_strtrim(map->map[i], "\n");
	data->c_color = ft_pixel(map->c[0], map->c[1], map->c[2], 255);
	data->f_color = ft_pixel(map->f[0], map->f[1], map->f[2], 255);
}

void	ft_init(t_data *data, t_data_maps *map)
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
	destroy_data_map(map, TRUE);
	data->player.rot_ang = (map->posplayer->dir);
	data->player.rotation_speed = 2;
	data->player.move_speed = 2;
	data->fov_angle = 60;
	data->minimap = mlx_new_image(data->mlx, data->map_width, data->map_height);
	data->game = mlx_new_image(data->mlx, 1080, 1000);
	draw_map(data);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 15, 15);
}
