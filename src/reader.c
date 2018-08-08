/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:44:28 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:45:15 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void	add_link(t_lem *lem, int **links, char **split)
{
	int r1;
	int r2;

	r1 = find_room(lem->rooms, lem->count_rooms, split[0]);
	r2 = find_room(lem->rooms, lem->count_rooms, split[1]);
	if (r1 < 0 || r2 < 0)
		error("No such room exist.");
	if (r1 == r2)
		return ;
	links[r1][r2] = 1;
	links[r2][r1] = 1;
}

int		get_links(t_lem *lem, char *line)
{
	int	i;

	if (lem->start_room < 0 || lem->end_room < 0)
		error("No start or end room.");
	i = -1;
	lem->links = (int **)malloc(sizeof(int *) * lem->count_rooms * 10);
	while (++i < lem->count_rooms)
	{
		lem->links[i] = (int *)malloc(sizeof(int) * lem->count_rooms);
		ft_bzero(lem->links[i], sizeof(int) * lem->count_rooms);
	}
	get_link_util(lem, line);
	return (1);
}

int		get_rooms(t_lem *lem)
{
	char	*line;

	lem->rooms = NULL;
	lem->count_rooms = 0;
	get_next_line(STDIN_FILENO, &line);
	if (!line)
		error("No rooms.");
	while (!check_if_link(line))
	{
		if (!ft_strcmp(line, "##start"))
			room_util(lem, START, line);
		else if (!ft_strcmp(line, "##end"))
			room_util(lem, END, line);
		else if (line[0] == '#')
		{
			add_info(lem, line);
			ft_strdel(&line);
		}
		else
			room_util(lem, DEFAULT, line);
		get_next_line(0, &line);
		if (!line)
			error("Too few info.");
	}
	return (get_links(lem, line));
}

void	count_ants(t_lem *lem)
{
	char	*line;

	while (1)
	{
		get_next_line(STDIN_FILENO, &line);
		if (!line)
			error("Empty.");
		if (line[0] == '#')
		{
			add_info(lem, line);
			ft_strdel(&line);
			continue ;
		}
		add_info(lem, line);
		lem->count_ants = check_number(line);
		if (lem->count_ants <= 0)
			error("Number of ants must be bigger than zero.");
		ft_strdel(&line);
		break ;
	}
}

int		reader(t_lem *lem)
{
	lem->start_room = -1;
	lem->end_room = -1;
	count_ants(lem);
	return (get_rooms(lem));
}
