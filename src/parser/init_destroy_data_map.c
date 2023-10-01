/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_data_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:10:27 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/01 12:58:56 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_data_map(t_data_maps *data)
{
	int	i;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	i = -1;
	while (++i < 3)
	{
		data->F[i] = -1;
		data->C[i] = -1;
	}
	data->map = malloc(sizeof(char *) * (0 + 1));
	data->map[0] = NULL;
}

void	destroy_data_map(t_data_maps *data, int status)
{
	int	i;

	i = -1;
	while (data->map[++i])
		free(data->map[i]);
	free(data->map);
	i = -1;
	while (++i < 4)
		free(data->textures[i]);
	if (status == FALSE)
		exit(EXIT_FAILURE);
}
