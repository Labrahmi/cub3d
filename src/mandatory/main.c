/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 07:30:15 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/04 23:12:49 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_data_map(char **av, t_data *data)
{
	t_data_maps	data_map;
	int			fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		exit(EXIT_FAILURE);
	init_data_map(&data_map);
	if (read_map(fd, av[1], &data_map) == FALSE)
		destroy_data_map(&data_map, FALSE);
	if (check_errors(&data_map) == FALSE)
		destroy_data_map(&data_map, FALSE);
	ft_init(data, &data_map);
}

int	check_extantion(char *path)
{
	int		len;
	char	*res;

	if (!ft_strchr(path, '.'))
		return (FALSE);
	len = ft_strlen(path);
	res = ft_strnstr(path, ".cub", len);
	if (!res)
		return (FALSE);
	if (ft_strncmp(res, ".cub", -1))
		return (FALSE);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
		return (1);
	if (check_extantion(av[1]) == FALSE)
		return (ft_printf("Error\n"), 1);
	data = malloc(sizeof(t_data));
	check_data_map(av, data);
	ft_hooks(data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	return (free(data), EXIT_SUCCESS);
}
