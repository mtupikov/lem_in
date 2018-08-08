/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants_utils_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:41:16 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:42:08 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		ants_at_end(t_ant *ants, int count_ants)
{
	int i;

	i = -1;
	while (++i < count_ants)
		if (!ants[i].finished)
			return (0);
	return (1);
}

void	ant_goes_to(t_lem *lem, t_ant *ant)
{
	ft_printf("L%d-%s ", ant->count, lem->rooms[ant->go_to].name);
	if (lem->rooms[ant->go_to].def == END)
	{
		ant->finished = 1;
		return ;
	}
	lem->rooms[ant->go_to].is_locked = 1;
	ant->now_in = ant->go_to;
}

void	get_levels_of_rooms(t_lem *lem, int room, int j)
{
	int	i;

	lem->rooms[room].level = j;
	lem->visited_rooms[room] = 1;
	i = -1;
	while (++i < lem->count_rooms)
	{
		if (room == lem->end_room || lem->rooms[i].is_locked)
			continue ;
		if ((!lem->visited_rooms[i] ||
				lem->rooms[i].level > lem->rooms[room].level + 1) &&
			(lem->rooms[i].level > lem->rooms[room].level ||
				lem->rooms[i].level == -1) && lem->links[room][i] == 1)
			get_levels_of_rooms(lem, i, j + 1);
	}
}

char	*get_all_paths_util(t_lem *lem)
{
	char *p;
	char *path;

	path = lem->rooms[lem->end_room].name;
	path = ft_strjoin(path, " ");
	p = get_shortest_path_name(lem, lem->end_room);
	if (!p)
	{
		ft_strdel(&path);
		return (NULL);
	}
	return (str_join_del(path, p));
}

int		count_free_ants(t_lem *lem)
{
	int count;
	int i;

	i = -1;
	count = 0;
	while (++i < lem->count_ants)
		if (lem->ants[i].init == 0)
			count++;
	return (count);
}
