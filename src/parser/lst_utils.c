/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 10:08:53 by ayakoubi          #+#    #+#             */
/*   Updated: 2023/09/17 10:08:56 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_listMap	*newlist(int x, int y)
{
	t_listMap	*node;

	node = malloc(sizeof(t_listMap));
	if (!node)
		return (0);
	node->x = x;
	node->y = y;
	node->next = NULL;
	return (node);
}


int	lstadd(t_listMap *lst, t_listMap *newnode, char	**map, int var)
{
	t_listMap	*tmp;

	if (!newnode || !lst)
		return (TRUE);
	tmp = lst;
//	printf("========= lst ==============\n");
	while (tmp->next)
	{
		if (tmp->x == newnode->x && tmp->y == newnode->y)
		{
			free(newnode);
			return (TRUE);
		}
		tmp = tmp->next;
	}
	if (tmp->x == newnode->x && tmp->y == newnode->y)
	{
		free(newnode);
		return (TRUE);
	}
	if (var == -1 && map[newnode->y][newnode->x] != '1' && map[newnode->y][newnode->x] != '0')
	{
		printf("%d, %d, %c\n", newnode->y, newnode->x, map[newnode->y][newnode->x]);
		return (FALSE);
	}
	//printf("%d, %d, %c\n", tmp->y, tmp->x, map[tmp->y][tmp->x]);
	tmp->next = newnode;
	return (TRUE);
}
