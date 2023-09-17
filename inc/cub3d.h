/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylabrahm <ylabrahm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/09/16 16:59:49 by ylabrahm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "MLX42.h"
#include <limits.h>
#include <fcntl.h>
#include "../gnl/get_next_line.h"
#include "../libft/libft.h"
#include "../ft_printf/ft_printf.h"

// --------
#define DEG_TO_RAD (M_PI / 180.0)

// ============     PARSER  =============

#define FALSE 0
#define TRUE 1

typedef struct s_data_maps
{
    char *textures[4];
    int F[3];
    int C[3];
    char **map;
} t_data_maps;

typedef struct s_corMap
{
    int x;
    int y;
} t_corMap;

typedef struct player_s
{
    double x;
    double y;
    int move_speed;
    float rotation_speed;
    float rotation_angle;
} player_t;

typedef struct data_s
{
    mlx_t *mlx;
    player_t player;
    mlx_image_t *minimap;
    mlx_image_t *game;
    char **map_grid;
    int columns;
    int rows;
    int grid_size;
    int map_height;
    int map_width;
    float fov_angle;
    mlx_texture_t *texture_1;
    mlx_texture_t *texture_2;
    mlx_texture_t *texture_3;
    mlx_texture_t *texture_4;
    mlx_texture_t *texture;
} data_t;

typedef struct vect_s
{
    double x;
    double y;
} vect_t;

typedef struct hitRay_s
{
    double distance;
    int is_horizontal;
    double x_hit;
    double y_hit;
	int is_facing_down, is_facing_up, is_facing_right, is_facing_left;
} hitRay_t;

// ----------------- Function Prototypes --------------------

// Drawing
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int set_color(char position);

void draw_pixels_to_map(data_t *data);
void draw_player(data_t *data);
void draw_one_grid(data_t *data, int x, int y, int sq_color);
void draw_pixels_to_map(data_t *data);
void draw_map(data_t *data);
void draw_fov(data_t *data);

// hooks()
void ft_hooks(data_t *data);

// 3d
float cast_ray(data_t *data, float angle);
void draw_3d_walls(data_t *data, hitRay_t ray, int ray_num);
void clear_screen(data_t *data);

// =========	parsing map functions	=========
void init_data(t_data_maps *data);
int read_map(int fd, char *fileMap, t_data_maps *data);
void get_textures(char *line, t_data_maps *data, int *pos);
int get_color(char *line, t_data_maps *data, int *pos);
int count_line_map(char *line, int fd);
void get_map(char *fileMap, t_data_maps *data, int pos, int count);
int check_errors(t_data_maps *data, t_list *list);
int check_errors_textures(char **textures);
int check_errors_colors(t_data_maps *data);
int check_errors_map(t_data_maps *data, t_list *list);

// ==========	PARSING UTILS FUNCTIONS	==============
void free_2d_array(char **str);
t_corMap *init_corMap(char **map);
int check_intruderInMap(char **map);
