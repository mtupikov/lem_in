/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:50:37 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:53:12 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"

/*
** <=== DEFINES ===>
*/

# define DEFAULT	0
# define START		1
# define END		2

/*
** <=== STRUCTS ===>
*/

typedef struct
{
	int			count;
	int			finished;
	int			now_in;
	int			go_to;
	int			queue;
	int			path;
	int			init;
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
	int			count_sh_paths;
	char		**info;
	double		coef;
	t_room		*rooms;
	t_ant		*ants;
	t_path		*paths;
}				t_lem;

/*
** <=== PROTOTYPES ===>
*/

/*
** main.c
*/

void			error(char *perke);
void			print_info(t_lem *lem);
void			get_link_util(t_lem *lem, char *line);

/*
** reader.c
*/

int				reader(t_lem *lem);
void			add_link(t_lem *lem, int **links, char **split);

/*
** room_utils.c
*/

void			room_util(t_lem *lem, int room_info, char *line);

/*
** go_ants.c
*/

void			go_ants(t_lem *lem);
void			count_sh_paths(t_lem *lem);

/*
** go_ants_utils_1.c
*/

void			go_ants_util_1(t_lem *lem);
void			go_ants_util_2(t_lem *lem, int *i);
void			go_ants_util_3(t_lem *lem, int *i, int *t);

/*
** go_ants_utils_2.c
*/

void			free_cell(t_lem *lem, t_ant *ant);
void			initializer_util(int *t, int *i, int *j);
void			close_rooms(t_lem *lem, char **split);
void			get_path_util(t_lem *lem, char **split, t_ant *ant, int *t);
char			*str_join_del(char *s1, char *s2);

/*
** go_ants_utils_3.c
*/

void			get_levels_of_rooms(t_lem *lem, int room, int j);
void			ant_goes_to(t_lem *lem, t_ant *ant);
int				ants_at_end(t_ant *ants, int count_ants);
int				count_free_ants(t_lem *lem);
char			*get_all_paths_util(t_lem *lem);

/*
** go_ants_utils_4.c
*/

void			add_info(t_lem *lem, char *line);
void			get_all_paths(t_lem *lem);
int				get_path(t_lem *lem, t_ant *ant);
int				get_shortest_path(t_lem *lem, int room);
char			*get_shortest_path_name(t_lem *lem, int room);

/*
** utils_of_room_utils.c
*/

void			check_room_util(char *line);
int				find_room(t_room *rooms, int count_rooms, char *name);
int				util_of_room_util(t_lem *lem, char *line, int room_info);
int				check_number(char *line);
int				check_if_link(char *line);

/*
** sh_paths.c
*/

void			choose_path_1(t_lem *lem, t_ant *ant);
void			choose_path_2(t_lem *lem, t_ant *ant);

#endif
