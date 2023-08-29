/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/08/29 23:31:34 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "MLX42.h"

#define HEIGHT 512
#define WIDTH 640

typedef struct player_s
{
    mlx_image_t *img;
}   player_t;

typedef struct data_s
{
    mlx_t *mlx;
    mlx_image_t *map;
    player_t player;
    char map_coords[8][10];
}   data_t;
