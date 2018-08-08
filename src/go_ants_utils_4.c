/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants_utils_4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:42:18 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:44:09 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

int		get_shortest_path(t_lem *lem, int room)
{
	static int	depth = 0;
	int			i;
	int			t;
	int			j;

	t = 9000;
	i = -1;
	j = -1;
	depth++;
	if (depth > 100)
		return (-10000);
	while (++i < lem->count_rooms)
	{
		if (lem->links[i][room] && i == lem->start_room)
			return (1);
		if (lem->links[i][room] && t > lem->rooms[i].level
			&& !lem->rooms[i].is_locked)
		{
			t = lem->rooms[i].level;
			j = i;
		}
	}
	return (get_shortest_path(lem, j) + t);
}

char	*get_shortest_path_name(t_lem *lem, int room)
{
	static int	depth = 0;
	int			i;
	int			t;
	int			j;
	char		*ret;

	initializer_util(&t, &i, &j);
	ret = NULL;
	depth++;
	if (depth > 100)
		return (NULL);
	while (++i < lem->count_rooms)
	{
		if (lem->links[i][room] && i == lem->start_room)
			return (ft_strjoin(lem->rooms[i].name, ""));
		if (lem->links[i][room] && t > lem->rooms[i].level
			&& !lem->rooms[i].is_locked)
		{
			t = lem->rooms[i].level;
			j = i;
			ret = ft_strjoin(lem->rooms[i].name, "");
		}
	}
	ret = str_join_del(ret, get_shortest_path_name(lem, j));
	return (ret);
}

int		get_path(t_lem *lem, t_ant *ant)
{
	int		t;
	int		i;
	char	**split;

	split = ft_strsplit(lem->paths[ant->path].name, ' ');
	get_path_util(lem, split, ant, &t);
	i = -1;
	while (++i < lem->count_rooms)
		if (!ft_strcmp(split[t - 1], lem->rooms[i].name))
		{
			ft_splitdel(&split);
			return (lem->rooms[i].num);
		}
	ft_splitdel(&split);
	return (-1);
}

void	get_all_paths(t_lem *lem)
{
	char	*path;
	int		i;
	int		j;

	lem->path_count = 0;
	lem->paths = ft_memalloc(sizeof(t_path) * 100);
	path = get_all_paths_util(lem);
	i = -1;
	while (++i >= 0)
	{
		lem->path_count++;
		lem->paths[i].name = ft_strjoin("", path);
		lem->paths[i].length = get_shortest_path(lem, lem->end_room);
		lem->paths[i].is_locked = 0;
		close_rooms(lem, ft_strsplit(path, ' '));
		ft_bzero(lem->visited_rooms, sizeof(int) * lem->count_rooms);
		j = -1;
		while (++j < lem->count_rooms)
			lem->rooms[j].level = -1;
		get_levels_of_rooms(lem, lem->start_room, 0);
		ft_strdel(&path);
		path = get_all_paths_util(lem);
		if (!path)
			break ;
	}
}

void	add_info(t_lem *lem, char *line)
{
	lem->info[ft_strsplit_count(lem->info)] = ft_strjoin("", line);
}
