/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_destroy_data_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:10:27 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 09:45:58 by ayakoubi         ###   ########.fr       */
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
		data->f[i] = -1;
		data->c[i] = -1;
	}
	data->map = malloc(sizeof(char *) * 1);
	data->posplayer = malloc(sizeof(t_corMap));
	data->map[0] = 0;
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
	free(data->posplayer);
	if (status == FALSE)
		exit(EXIT_FAILURE);
}
