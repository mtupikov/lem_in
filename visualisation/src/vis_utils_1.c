/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utils_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:28:28 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:28:50 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void	get_link_util(t_lem *lem, char *line)
{
	char	**split;

	while (line)
	{
		add_info(lem, line);
		if (line[0] == '#')
		{
			ft_strdel(&line);
			get_next_line(STDIN_FILENO, &line);
			continue ;
		}
		split = ft_strsplit(line, '-');
		if (ft_strsplit_count(split) == 0)
		{
			ft_strdel(&line);
			ft_splitdel(&split);
			return ;
		}
		if (ft_strsplit_count(split) != 2)
			error("Bad link.");
		add_link(lem, lem->links, split);
		ft_strdel(&line);
		ft_splitdel(&split);
		get_next_line(STDIN_FILENO, &line);
	}
}

void	close_rooms(t_lem *lem, char **split)
{
	int i;
	int j;

	i = -1;
	while (split[++i])
	{
		j = -1;
		while (++j < lem->count_rooms)
		{
			if (!ft_strcmp(split[i], lem->rooms[j].name) &&
				lem->rooms[j].num != lem->start_room &&
				lem->rooms[j].num != lem->end_room)
				lem->rooms[j].is_locked = 1;
		}
	}
	ft_splitdel(&split);
}

char	*str_join_del(char *s1, char *s2)
{
	char *temp1;
	char *temp2;

	temp2 = s1;
	s1 = ft_strjoin(s1, " ");
	ft_strdel(&temp2);
	temp1 = s1;
	temp2 = s2;
	s1 = ft_strjoin(temp1, temp2);
	if (temp2)
		ft_strdel(&temp2);
	if (temp1)
		ft_strdel(&temp1);
	return (s1);
}

void	initializer_util(int *t, int *i, int *j)
{
	*t = 9000;
	*i = -1;
	*j = -1;
}
