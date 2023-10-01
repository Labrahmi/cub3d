/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:53:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/10/01 12:30:33 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_errors(t_data_maps *data)
{
	if (check_errors_textures(data->textures) == FALSE)
		return (FALSE);
	if (check_path_textures(data->textures) == FALSE)
		return (FALSE);
	if (check_errors_colors(data) == FALSE)
		return (FALSE);
	if (check_errors_map(data) == FALSE)
		return (FALSE);
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
		if (data->F[i] < 0 || data->F[i] > 255)
			return (FALSE);
		if (data->C[i] < 0 || data->C[i] > 255)
			return (FALSE);
	}
	return (TRUE);
}

int	check_errors_map(t_data_maps *data)
{
	t_corMap	*pos_start;

	pos_start = init_cor_map(data->map);
	if (pos_start == FALSE)
		return (FALSE);
	if (check_intruder_map(data->map) == FALSE)
		return (FALSE);
	data->posplayer = pos_start;
	if (loop_for_map(data->map, data->count) == FALSE)
		return (FALSE);
	return (TRUE);
}
