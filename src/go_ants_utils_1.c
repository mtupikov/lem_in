/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants_utils_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:39:30 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:39:59 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int		check_way_out(t_lem *lem)
{
	int i;

	i = -1;
	while (++i < lem->count_rooms)
		if (lem->links[lem->end_room][i] == 1)
			return (1);
	return (0);
}

static void		open_rooms(t_lem *lem)
{
	int i;

	i = -1;
	while (++i < lem->count_rooms)
		lem->rooms[i].is_locked = 0;
}

void			go_ants_util_1(t_lem *lem)
{
	if (!check_way_out(lem))
		error("No way to end room.");
	lem->visited_rooms = ft_memalloc(sizeof(int) * lem->count_rooms);
	get_levels_of_rooms(lem, lem->start_room, 0);
	ft_bzero(lem->visited_rooms, sizeof(int) * lem->count_rooms);
	lem->shortest_path_len = get_shortest_path(lem, lem->end_room);
	if (lem->shortest_path_len < 0)
		error("No way to end room.");
	lem->coef = (double)lem->count_ants / 3.7f;
	get_all_paths(lem);
	open_rooms(lem);
	lem->count_sh_paths = 0;
	count_sh_paths(lem);
}

void			go_ants_util_2(t_lem *lem, int *i)
{
	if (*i == lem->count_ants)
	{
		*i = 0;
		ft_printf("\n");
	}
	if (lem->ants[*i].path < 0)
	{
		if (lem->count_sh_paths > 1)
			choose_path_1(lem, &lem->ants[*i]);
		else
			choose_path_2(lem, &lem->ants[*i]);
	}
}

void			go_ants_util_3(t_lem *lem, int *i, int *t)
{
	if (lem->ants[*i].go_to >= 0)
		free_cell(lem, &lem->ants[*i]);
	*t = get_path(lem, &lem->ants[*i]);
	if (lem->rooms[*t].is_locked)
		lem->ants[*i].queue = *t;
	else
		lem->ants[*i].go_to = *t;
	if (lem->ants[*i].go_to >= 0)
		ant_goes_to(lem, &lem->ants[*i]);
}
