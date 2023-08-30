/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/08/30 19:38:44 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "MLX42.h"

#define GRID_HEIGHT 128
#define GRID_WIDTH 128

#define COLUMNS 16
#define ROWS 8

#define GAME_HEIGHT (GRID_HEIGHT * ROWS)
#define GAME_WIDTH (GRID_WIDTH * COLUMNS)

#define PLAYER_HEIGHT 16
#define PLAYER_WIDTH 16

#define Pi 3.14159265359

typedef struct player_s
{
    int x;
    int y;
    int rotation_angle;
}   player_t;

typedef struct data_s
{
    mlx_t *mlx;
    mlx_image_t *minimap;
    player_t player;
    char map_grid[ROWS][COLUMNS];
}   data_t;


// ----------------- Function Prototypes --------------------

// Drawing
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int set_color(char position);
