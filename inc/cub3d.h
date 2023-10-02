/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/02 10:57:20 by ayakoubi         ###   ########.fr       */
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

typedef enum e_dir
{
	NORTH = 270,
	SOUTH = 90,
	WEST = 180,
	EAST = 0
} t_dir;

typedef struct s_corMap
{
	int x;
	int y;
	t_dir dir;
} t_corMap;

typedef struct s_data_maps
{
	char *textures[4];
	int F[3];
	int C[3];
	char **map;
	t_corMap *posplayer;
	int count;
} t_data_maps;

typedef struct s_listMap
{
	int x;
	int y;
	struct s_listMap *next;
}	t_listMap;

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
	mlx_texture_t *texture_N;
	mlx_texture_t *texture_S;
	mlx_texture_t *texture_W;
	mlx_texture_t *texture_E;
	mlx_texture_t *texture;
	int32_t c_color;
	int32_t f_color;
} data_t;

/*
	c_color = ft_pixel(0,1,2)
*/


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

typedef struct s_utils
{
	int		color;
	double	x;
	double	y;
	double	end_x;
	double	end_y;
	double	steps;
	double	xIncrement;
	double	yIncrement;
}	t_utils;

// =========	parsing map functions	=========
void	init_data_map(t_data_maps *data);
void	destroy_data_map(t_data_maps *data, int status);
int		read_map(int fd, char *fileMap, t_data_maps *data);
void	get_textures(char *line, t_data_maps *data, int *pos);
int		get_color(char *line, t_data_maps *data, int *pos);
int		check_input_colors(char **str);
int		count_line_map(char *line, int fd);
void	get_map(char *fileMap, t_data_maps *data, int pos, int count);
int		check_errors(t_data_maps *data);
int		check_errors_textures(char **textures);
int		check_path_textures(char **textures);
int		check_errors_colors(t_data_maps *data);
int		check_errors_map(t_data_maps *data);
int		loop_for_map(char **map, int count);

// ==========	PARSING UTILS FUNCTIONS	==============
void		free_2d_array(char **str);
int			split_color(t_data_maps *data, char *line, char c);
t_corMap	*init_cor_map(char **map);
int check_intruder_map(char **map);
int supp_check_path(char **textures, int start, int len, int i);
int aspects_zero(char **map, int i, int j, int count);

// ==========   INIT DATA & MLX         =============
void	ft_init(data_t *data, t_data_maps *map);
void	fill_data_from_datamap(data_t *data, t_data_maps *map);
int		calculate_res(char **map, int mode);
void	ft_check_textures(data_t *data, t_data_maps *map);
int		ft_destroy_textures(mlx_texture_t **texts);

// ==========   DRAW_MAP FUNCTIONS      ===============

//  DRAW_PIXELS===========================
void	draw_pixels_to_map(data_t *data);
void	draw_one_grid(data_t *data, int x, int y, int sq_color);
int		set_color(char position);
int32_t	ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
//  DRAW_FOV===============================
void		draw_fov(data_t *data);
float		normalize_angle(float angle);
void		clear_screen(data_t *data);
hitRay_t	draw_line_with_angle(data_t *data, float angle, int i);
void		difination_ray(hitRay_t *ray, data_t *data, float angle);
hitRay_t	ft_get_horizontal_intersection(data_t *data, double angle);
hitRay_t	ft_get_vertical_intersection(data_t *data, double angle);
// ----------------- Function Prototypes --------------------

// Drawing
int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int set_color(char position);

void draw_player(data_t *data);
void draw_map(data_t *data);


// ===========	HOOKS ==============
void ft_move_player(void *param);
int is_valid_position(data_t *data, int x, int y);
void ft_turn_player(void *param);
void ft_hooks(data_t *data);

// 3d
float cast_ray(data_t *data, float angle);
void draw_3d_walls(data_t *data, hitRay_t ray, int ray_num);


