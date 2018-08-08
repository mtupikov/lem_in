/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   room_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:45:27 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:33:15 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

static t_room	*room_realloc(t_room *old, int new_size)
{
	t_room	*new;
	int		i;

	if (!old)
	{
		new = ft_memalloc(sizeof(t_room) * new_size);
		return (new);
	}
	new = ft_memalloc(sizeof(t_room) * new_size);
	i = -1;
	while (++i < new_size - 1)
		new[i] = old[i];
	ft_memdel((void **)&old);
	return (new);
}

static void		check_coord(t_lem *lem, t_room room)
{
	int i;

	i = -1;
	while (++i < lem->count_rooms)
	{
		if (lem->rooms[i].x == room.x && lem->rooms[i].y == room.y)
			error("Duplicate coordinates.");
		if (!ft_strcmp(lem->rooms[i].name, room.name))
			error("Duplicate room name.");
	}
}

static t_room	add_room(t_lem *lem, char **info,
						int room_info, int num_of_room)
{
	t_room ret;

	ret.name = ft_strjoin("", info[0]);
	ret.x = check_number(info[1]);
	ret.y = check_number(info[2]);
	check_coord(lem, ret);
	ret.def = room_info;
	ret.is_locked = 0;
	ret.num = num_of_room;
	ret.level = -1;
	return (ret);
}

void			add_info(t_lem *lem, char *line)
{
	lem->info[ft_strsplit_count(lem->info)] = ft_strjoin("", line);
}

void			room_util(t_lem *lem, int room_info, char *line)
{
	char **split;

	add_info(lem, line);
	if (room_info != DEFAULT)
	{
		ft_strdel(&line);
		get_next_line(STDIN_FILENO, &line);
		if (util_of_room_util(lem, line, room_info))
			return ;
		add_info(lem, line);
	}
	check_room_util(line);
	split = ft_strsplit(line, ' ');
	if (ft_strsplit_count(split) != 3)
		error("Wrong room info.");
	lem->rooms = room_realloc(lem->rooms, lem->count_rooms + 1);
	lem->rooms[lem->count_rooms] =
			add_room(lem, split, room_info, lem->count_rooms);
	if (room_info == START)
		lem->start_room = lem->count_rooms;
	else if (room_info == END)
		lem->end_room = lem->count_rooms;
	lem->count_rooms++;
	ft_splitdel(&split);
	ft_strdel(&line);
}
