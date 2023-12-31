/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:53:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/04 22:57:17 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_errors(t_data_maps *data)
{
	if (check_errors_textures(data->textures) == FALSE)
		return (ft_printf("Error in textures !\n"), FALSE);
	if (check_path_textures(data->textures) == FALSE)
		return (ft_printf("Error in PATH textures !\n"), FALSE);
	if (check_errors_colors(data) == FALSE)
		return (ft_printf("Error in colors !\n"), FALSE);
	if (check_errors_map(data) == FALSE)
		return (ft_printf("Error in map !\n"), FALSE);
	return (TRUE);
}

int	check_errors_textures(char **textures)
{
	int		i;
	int		count;
	char	**tmp;

	i = -1;
	count = 0;
	while (++i < 4)
	{
		if (textures[i])
			count++;
	}
	if (count != 4)
		return (FALSE);
	i = -1;
	while (++i < 4)
	{
		tmp = ft_split(textures[i], ' ');
		if (!tmp[1] || (tmp[1] && tmp[2]))
			return (free_2d_array(tmp), FALSE);
		free_2d_array(tmp);
	}
	return (TRUE);
}

int	check_path_textures(char **textures)
{
	int	i;
	int	len;
	int	start;
	int	status;

	i = -1;
	while (++i < 4)
	{
		len = ft_strlen(textures[i]);
		start = len;
		if (!ft_strchr(textures[i], '.'))
			return (FALSE);
		while (start-- > 0)
		{
			status = supp_check_path(textures, start, len, i);
			if (status == FALSE)
				return (FALSE);
			if (status == TRUE)
				break ;
		}
	}
	return (TRUE);
}

int	check_errors_colors(t_data_maps *data)
{
	int	i;

	i = -1;
	while (++i < 3)
	{
		if (data->f[i] < 0 || data->f[i] > 255)
			return (FALSE);
		if (data->c[i] < 0 || data->c[i] > 255)
			return (FALSE);
	}
	return (TRUE);
}

int	check_errors_map(t_data_maps *data)
{
	free(data->posplayer);
	data->posplayer = init_cor_map(data->map);
	if (data->posplayer == FALSE)
		return (FALSE);
	if (check_intruder_map(data->map) == FALSE)
		return (FALSE);
	if (loop_for_map(data->map, data->count) == FALSE)
		return (FALSE);
	return (TRUE);
}
