/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 11:10:27 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/14 09:56:23 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_data(t_data_maps *data)
{
	int i;

	i = -1;
	while (++i < 4)
		data->textures[i] = NULL;
	i = -1;
	while (++i < 3)
	{
		data->F[i] = -1;
		data->C[i] = -1;
	}
	data->map = NULL;
}

