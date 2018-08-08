/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_ants.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:37:57 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:39:05 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

void			count_sh_paths(t_lem *lem)
{
	int i;

	i = -1;
	while (++i < lem->path_count)
	{
		if (lem->paths[i].length == lem->shortest_path_len)
			lem->count_sh_paths++;
	}
}

void			go_ants(t_lem *lem)
{
	int i;
	int t;

	go_ants_util_1(lem);
	i = 0;
	while (!ants_at_end(lem->ants, lem->count_ants))
	{
		go_ants_util_2(lem, &i);
		if (!lem->ants[i].finished)
		{
			if (lem->ants[i].queue > 0 &&
				!lem->rooms[lem->ants[i].queue].is_locked)
			{
				lem->ants[i].go_to = lem->ants[i].queue;
				lem->ants[i].queue = -1;
				ant_goes_to(lem, &lem->ants[i]);
				i++;
				continue ;
			}
			go_ants_util_3(lem, &i, &t);
		}
		i++;
	}
	ft_printf("\n");
}
