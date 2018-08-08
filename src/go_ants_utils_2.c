/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:40:14 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:41:06 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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

void	get_path_util(t_lem *lem, char **split, t_ant *ant, int *t)
{
	int	i;
	int	j;

	i = -1;
	*t = -1;
	while (split[++i])
	{
		j = -1;
		while (++j < lem->count_rooms)
			if (!ft_strcmp(split[i], lem->rooms[j].name) && j == ant->now_in)
			{
				*t = i;
				break ;
			}
		if (*t > 0)
			break ;
	}
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

void	free_cell(t_lem *lem, t_ant *ant)
{
	if (lem->rooms[ant->now_in].def != START)
		lem->rooms[ant->go_to].is_locked = 0;
	ant->go_to = -1;
}
