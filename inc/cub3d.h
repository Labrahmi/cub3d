/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayakoubi <ayakoubi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 08:30:09 by ylabrahm          #+#    #+#             */
/*   Updated: 2023/10/04 11:43:14 by ayakoubi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <unistd.h>
# include <math.h>
# include "MLX42.h"
# include <limits.h>
# include <fcntl.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"

// ============     PARSER  =============

# define FALSE 0
# define TRUE 1

typedef enum e_dir
{
	NORTH = 45,
	SOUTH = 90,
	WEST = 180,
	EAST = 0
}	t_dir;

typedef struct s_corMap
{
	int		x;
	int		y;
	t_dir	dir;
}	t_corMap;

typedef struct s_data_maps
{
	char		*textures[4];
	int			f[3];
	int			c[3];
	char		**map;
	t_corMap	*posplayer;
	int			count;
}	t_data_maps;

typedef struct s_listMap
{
	int					x;
	int					y;
	struct s_listMap	*next;
}	t_listMap;

typedef struct player_s
{
	double	x;
	double	y;
	int		move_speed;
	float	rotation_speed;
	float	rot_ang;
}	t_player;

typedef struct data_s
{
	mlx_t			*mlx;
	t_player		player;
	mlx_image_t		*minimap;
	mlx_image_t		*game;
	char			**map_grid;
	int				columns;
	int				rows;
	int				grid_size;
	int				map_height;
	int				map_width;
	float			fov_angle;
	mlx_texture_t	*texture_n;
	mlx_texture_t	*texture_s;
	mlx_texture_t	*texture_w;
	mlx_texture_t	*texture_e;
	mlx_texture_t	*texture;
	int32_t			c_color;
	int32_t			f_color;
}	t_data;

typedef struct vect_s
{
	double	x;
	double	y;
}	t_vect;

typedef struct int_vect_s
{
	int	x;
	int	y;
}	t_int_vect;

typedef struct hitRay_s
{
	double	distance;
	int		is_horizontal;
	double	x_hit;
	double	y_hit;
	int		is_facing_down;
	int		is_facing_up;
	int		is_facing_right;
	int		is_facing_left;
}	t_hit_ray;

typedef struct s_utils
{
	int		color;
	double	x;
	double	y;
	double	end_x;
	double	end_y;
	double	steps;
	double	x_inc;
	double	y_inc;
}	t_utils;

typedef struct s_3d_data
{
	t_int_vect	v1;
	t_int_vect	v2;
	uint8_t		*pixeli;
	uint8_t		*pixelx;
}	t_3d_data;

typedef struct draw_3d_walls_s
{
	float			ch;
	mlx_texture_t	*texture;
	t_data			*data;
	t_vect			c_img;
	t_vect			c_tex;
}	t_draw_3d_walls;

typedef struct common_data_s
{
	t_vect		intercept;
	double		ystep;
	double		xstep;
	double		wall_hit_x;
	double		wall_hit_y;
	t_hit_ray	*ray;
	double		x_to_check;
	double		y_to_check;
	int			gx;
	int			gy;
}	t_comm_t_data;

// =========	parsing map functions	=========
void			init_data_map(t_data_maps *data);
void			destroy_data_map(t_data_maps *data, int status);
int				read_map(int fd, char *fileMap, t_data_maps *data);
void			get_textures(char *line, t_data_maps *data, int *pos);
int				get_color(char *line, t_data_maps *data, int *pos);
int				check_input_colors(char **str);
int				count_line_map(char *line, int fd);
void			get_map(char *fileMap, t_data_maps *data, int pos, int count);
int				check_errors(t_data_maps *data);
int				check_errors_textures(char **textures);
int				check_path_textures(char **textures);
int				check_errors_colors(t_data_maps *data);
int				check_errors_map(t_data_maps *data);
int				loop_for_map(char **map, int count);

// ==========	PARSING UTILS FUNCTIONS	==============
void			free_2d_array(char **str);
int				split_color(t_data_maps *data, char *line, char c);
t_corMap		*init_cor_map(char **map);
int				check_intruder_map(char **map);
int				supp_check_path(char **textures, int start, int len, int i);
int				aspects_zero(char **map, int i, int j, int count);

// ==========   INIT DATA & MLX         =============
void			ft_init(t_data *data, t_data_maps *map);
void			fill_data_from_datamap(t_data *data, t_data_maps *map);
int				calculate_res(char **map, int mode);
void			ft_check_textures(t_data *data, t_data_maps *map);
int				ft_destroy_textures(mlx_texture_t **texts);

// ==========   DRAW_MAP FUNCTIONS      ===============

//  DRAW_PIXELS===========================
void			draw_pixels_to_map(t_data *data);
void			draw_one_grid(t_data *data, int x, int y, int sq_color);
int				set_color(char position);
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
//  DRAW_FOV===============================
void			draw_fov(t_data *data);
float			normalize_angle(float angle);
void			clear_screen(t_data *data);
t_hit_ray		draw_line_with_angle(t_data *data, float angle, int i);
void			difination_ray(t_hit_ray *ray, t_data *data, float angle);
t_hit_ray		get_horizontal_intersect(t_data*d, double a, t_comm_t_data c);
t_hit_ray		get_vertical_intersect(t_data *d, double a, t_comm_t_data c);

// ----------------- Function Prototypes --------------------

// Drawing
int32_t			ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a);
int				set_color(char position);
void			draw_player(t_data *data, int32_t clr);
void			draw_map(t_data *data);

// ===========	HOOKS ==============
void			ft_move_player(void *param);
int				is_valid_position(t_data *data, int x, int y);
void			ft_turn_player(void *param);
void			ft_hooks(t_data *data);

// ===========	3D ==============
void			draw_3d_walls(t_data *data, t_hit_ray ray, int ray_num);
t_draw_3d_walls	ft_get_hor_3d_data(t_data *data, t_hit_ray ray);
t_draw_3d_walls	ft_get_ver_3d_data(t_data *data, t_hit_ray ray);

#endif