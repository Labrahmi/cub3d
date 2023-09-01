/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/01 01:15:51 by ylabrahm         ###   ########.fr       */
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

#define FOV_ANGLE (30.0 * (M_PI / 180.0))  // 30 degrees in radians

typedef struct player_s
{
    int x;
    int y;
    int move_speed;
    double rotation_speed;
    double rotation_angle;
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

void draw_pixels_to_map(data_t *data);
void draw_player(data_t *data);
void draw_one_grid(data_t *data, int x, int y, int sq_color);
void draw_pixels_to_map(data_t *data);
void draw_map(data_t *data);
void draw_line(data_t *data);

// hooks()
void ft_hooks(data_t *data);
