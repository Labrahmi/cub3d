/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/17 08:55:21 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

int calculate_res(t_data_maps *map, int mode)
{
	int i = 0;
	int max;
	while (map->map[i])
	{
		if (i == 0)
			max = strlen(map->map[i]);
		if (strlen(map->map[i]) > max)
			max = strlen(map->map[i]);
		i++;
	}
	if (mode == 1)
		return (max);
	if (mode == 2)
		return (i);
	return 0;
}

void ft_init(data_t *data, t_data_maps *map)
{
	int i = -1;
	while (map->map[++i])
	{
		if (map->map[i][strlen(map->map[i]) - 1] == 10)
			map->map[i][strlen(map->map[i]) - 1] = '\0';
	}
	data->mlx = mlx_init(1000, 512, "cub3d", false);
	if (!(data->mlx))
		exit(EXIT_FAILURE);
	data->columns = calculate_res(map, 1);
	data->rows = calculate_res(map, 2);
	data->grid_size = 30;
	data->map_height = data->grid_size * data->rows;
	data->map_width = data->grid_size * data->columns;
	data->player.x = 60; // (data->map_width / 2);
	data->player.y = 60; // (data->map_height / 2);
	data->player.rotation_angle = (0);
	data->player.rotation_speed = 2;
	data->player.move_speed = 3;
	data->fov_angle = 90;
	// -
	data->minimap = mlx_new_image(data->mlx, data->map_width, data->map_height);
	data->game = mlx_new_image(data->mlx, 1000, 512);
	// -
	data->map_grid = (char **) calloc(sizeof(char *), data->rows + 1);
	i = -1;
	while (map->map[++i])
		data->map_grid[i] = map->map[i];
	// -
	data->texture_1 = mlx_load_png("assets/des_1.png");
	data->texture_2 = mlx_load_png("assets/des_2.png");
	data->texture_3 = mlx_load_png("assets/des_3.png");
	data->texture_4 = mlx_load_png("assets/des_4.png");
	draw_map(data);
	mlx_image_to_window(data->mlx, data->game, 0, 0);
	mlx_image_to_window(data->mlx, data->minimap, 0, 0);
	//
}

int main(int ac, char **av)
{
	data_t *data;
	t_data_maps data_map;
	t_list list;

	if (ac != 2)
		return (1);
	init_data(&data_map);
	int fd = open(av[1], O_RDONLY);
	if (read_map(fd, av[1], &data_map) == FALSE)
		return (printf("ERROR\n"), 1);
	if (check_errors(&data_map, &list) == FALSE)
		return (printf("ERROR\n"), 1);
	data = malloc(sizeof(data_t));
	ft_init(data, &data_map);
	ft_hooks(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	system("clear");
	return (free(data), EXIT_SUCCESS);
}
