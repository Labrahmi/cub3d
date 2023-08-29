/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/08/29 09:08:38 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "MLX42.h"

#define HEIGHT 1024
#define WIDTH (HEIGHT * 2)

typedef struct player_s
{
    float x_pos;
    float y_pos;
}   player_t;

typedef struct data_s
{
    player_t player;
    mlx_image_t *map;
    mlx_t *mlx;
}   data_t;
