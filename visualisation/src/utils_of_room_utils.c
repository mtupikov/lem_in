/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_of_room_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:47:40 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:23:10 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void	check_room_util(char *line)
{
	if (!line)
		error("Bad rooms.");
	if (line[0] == 'L')
		error("Not valid room name.");
}

int		find_room(t_room *rooms, int count_rooms, char *name)
{
	int i;

	i = -1;
	while (++i < count_rooms)
		if (!ft_strcmp(rooms[i].name, name))
			return (rooms[i].num);
	return (-1);
}

int		util_of_room_util(t_lem *lem, char *line, int room_info)
{
	if (line[0] == '#' && line[1] == '#')
		error("Command overwriting.");
	else if (line[0] == '#')
	{
		room_util(lem, room_info, line);
		return (1);
	}
	return (0);
}

int		check_number(char *line)
{
	long	num;
	int		neg;

	neg = 1;
	if (line[0] == '-')
	{
		line++;
		neg = -1;
	}
	if (!ft_strisdigit(line))
		error("Number not a digit!");
	num = ft_atoi(line) * neg;
	if (num < -2147483648 || num > 2147483647)
		error("Must be integer.");
	return ((int)num);
}

int		check_if_link(char *line)
{
	char	**split;

	split = ft_strsplit(line, ' ');
	if (ft_strsplit_count(split) == 3 || line[0] == '#')
	{
		ft_splitdel(&split);
		return (0);
	}
	ft_splitdel(&split);
	return (1);
}
