/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualise.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:35:28 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:37:50 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALISE_H
# define VISUALISE_H

/*
** <--- INCLUDES --->
*/

# include "../miniLibX/mlx.h"
# include "../../libft/includes/libft.h"
# include "../../libft/includes/ft_printf.h"
# include <stdio.h>
# include <math.h>
# include "keys.h"
# include <fcntl.h>

/*
** <--- DEFINES --->
*/

# define X_SCREEN_SIZE	1920
# define Y_SCREEN_SIZE	1080
# define EXIT_SUCC		1
# define ABS(x)			((x) < 0 ? -(x) : (x))
# define DEFAULT		0
# define START			1
# define END			2

/*
** <--- STRUCTS --->
*/

typedef struct
{
	int			count;
	int			now_in;
}				t_ant;

typedef struct	s_room
{
	char		*name;
	int			is_locked;
	int			num;
	int			def;
	int			x;
	int			y;
	int			level;
}				t_room;

typedef struct	s_path
{
	char		*name;
	int			length;
	int			is_locked;
}				t_path;

typedef struct
{
	int			count_ants;
	int			count_rooms;
	int			**links;
	int			*visited_rooms;
	int			start_room;
	int			end_room;
	int			path_count;
	int			shortest_path_len;
	char		**info;
	double		coef;
	t_room		*rooms;
	t_ant		*ants;
	t_path		*paths;
}				t_lem;

typedef struct	s_2d
{
	int			x;
	int			y;
}				t_2d;

typedef struct	s_image
{
	void		*img;
	char		*ptr;
	int			bpp;
	int			stride;
	int			endian;
}				t_image;

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
	int			is_playable;
	int			count_comm;
	t_image		*image;
	t_image		*start_room;
	t_image		*end_room;
	t_image		*room;
	t_lem		*lem;
}				t_mlx;

typedef struct	s_line
{
	t_2d		start;
	t_2d		stop;
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			err2;
	int			ant_n;
	int			color;
}				t_line;

/*
** <--- PROTOTYPES --->
*/

/*
** main.c
*/

void			error(char *perke);
void			print_info(t_lem *lem);

/*
** mlx_stuff.c
*/

t_mlx			*init_mlx(char *title);

/*
** image.c
*/

void			img_set_pixel(t_image *image, int x, int y, int color);
void			clear_image(t_mlx *mlx);
t_image			*del_image(t_mlx *mlx, t_image *img);
t_image			*new_image(t_mlx *mlx);

/*
** reader_v.c
*/

int				reader(t_lem *lem);
void			add_link(t_lem *lem, int **links, char **split);

/*
** render.c
*/

void			render(t_mlx *mlx, char *commands);
void			add_img(t_mlx *mlx, char *room, t_image **img);
void			put_room(t_mlx *mlx, int i);
void			put_lines(t_mlx *mlx);

/*
** hook_keydown.c
*/

int				hook_keydown(int key, t_mlx *mlx);
void			render_bg(t_mlx *mlx);
void			render_info(t_mlx *mlx);

/*
** room_utils.c
*/

void			room_util(t_lem *lem, int room_info, char *line);
void			add_info(t_lem *lem, char *line);

/*
** utils_of_room_utils.c
*/

void			check_room_util(char *line);
int				find_room(t_room *rooms, int count_rooms, char *name);
int				util_of_room_util(t_lem *lem, char *line, int room_info);
int				check_number(char *line);
int				check_if_link(char *line);

/*
** get_paths.c
*/

void			get_all_paths(t_lem *lem);
void			get_levels_of_rooms(t_lem *lem, int room, int j);

/*
** vis_utils_1.c
*/

void			initializer_util(int *t, int *i, int *j);
void			get_link_util(t_lem *lem, char *line);
void			close_rooms(t_lem *lem, char **split);
char			*str_join_del(char *s1, char *s2);

/*
** vis_utils_2.c
*/

void			put_path(t_mlx *mlx, char **split, int *x, int *y);
void			put_path_len(t_mlx *mlx, int *x, int *y, int path_len);
void			put_count_comm(t_mlx *mlx);
void			ant_go_to(t_mlx *mlx, char *line);
void			put_ant_index(t_mlx *mlx, char *line);

/*
** vis_utils_3.c
*/

t_2d			get_vector(int x, int y);
int				get_room_num(t_mlx *mlx, char *line);
void			mlx_put_line(t_2d p1, t_2d p2, t_mlx *mlx, int color);

#endif
