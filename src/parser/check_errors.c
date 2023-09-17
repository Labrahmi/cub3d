/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/13 10:53:24 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/17 10:33:55 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int check_errors(t_data_maps *data, t_list *list)
{
	if (check_errors_textures(data->textures) == FALSE)
		return (FALSE);
	if (check_errors_colors(data) == FALSE)
		return (FALSE);
	if (check_errors_map(data, list) == FALSE)
		return (FALSE);
	return (TRUE);
}

int	check_errors_textures(char **textures)
{
	int i;
	int	count;
	char **tmp;

	i = -1;
	count = 0;
	while (++i < 4)
	{
		if(textures[i])
			count++;
	}
	if (count != 4)
		return (FALSE);
	i = -1;
	while (++i < 4)
	{
		tmp = ft_split(textures[i], ' ');
		if (!tmp[1] || (tmp[1] && tmp[2]))
			return (FALSE);
		free(tmp);
	}
	return (TRUE);
}

int	check_errors_colors(t_data_maps *data)
{
	int i;

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

int check_errors_map(t_data_maps *data, t_list *list)
{
	(void) list;
	t_corMap *posStart;

	if (check_intruderInMap(data->map) == FALSE)
		return (FALSE);
	posStart = init_corMap(data->map);
	if (posStart == FALSE)
		return (FALSE);
	data->posplayer = posStart;
	/*if (loopForMap(data->map, posStart) == FALSE)
		return (FALSE);*/
	return (TRUE);
}
/*
int loopForMap(char **map, t_corMap *pos)
{
	t_listMap *cur;
	t_listMap *first;
	int	var;

	var = 0;
	first = newlist(pos->x, pos->y);
	cur = first;
	t_listMap *tmp;
	while (cur)
	{
		var = 0;
		printf("************=========>%d, %d  %c\n", cur->y, cur->x, map[cur->y][cur->x]);
		if (map[cur->y][cur->x] == '0')
		{
			var = -1;
			if (lstadd(first, newlist(cur->x + 1, cur->y), map, var) == FALSE)
				return (FALSE);
			if (lstadd(first, newlist(cur->x - 1, cur->y), map, var) == FALSE)
				return (FALSE);
			if (lstadd(first, newlist(cur->x, cur->y + 1), map, var) == FALSE)
				return (FALSE);
			if (lstadd(first, newlist(cur->x, cur->y - 1), map, var) == FALSE)
				return (FALSE);
		}
		else
		{
			if (cur->x < ft_strlen(map[cur->y]) && 
				(map[cur->y][cur->x + 1] == '1' || map[cur->y][cur->x + 1] == '0'))
					lstadd(first, newlist(cur->x + 1, cur->y), map, var);
			if (cur->x > 0 && (map[cur->y][cur->x - 1] == '1'
				|| map[cur->y][cur->x - 1] == '0'))
					lstadd(first, newlist(cur->x - 1, cur->y), map,var);
			if (cur->y < 13 && (map[cur->y + 1][cur->x] == '1'
				|| map[cur->y + 1][cur->x] == '0'))
					lstadd(first, newlist(cur->x, cur->y + 1), map, var);
			if (cur->y < 0 && (map[cur->y - 1][cur->x] == '1'
				|| map[cur->y - 1][cur->x] == '0'))
					lstadd(first, newlist(cur->x, cur->y - 1), map, var);
		}
		printf("after ==================\n%d, %d  %c\n", cur->y, cur->x, map[cur->y][cur->x]);
		tmp = first;
		printf("==================\n");
		while (tmp)
		{
			printf("%d , %d  === > %c\n", tmp->y, tmp->x, map[tmp->y][tmp->x]);
			tmp = tmp->next;
		}
		cur = cur->next;

	}
	tmp = first;
	while (tmp)
	{
		printf("%d , %d  === > %c\n", tmp->y, tmp->x, map[tmp->y][tmp->x]);
		tmp = tmp->next;
	}
	return (TRUE);
}	*/
