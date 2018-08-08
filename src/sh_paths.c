/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_paths.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 19:56:38 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 19:56:39 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

static int		choose_path_util_1(t_lem *lem, t_ant *ant, int *k)
{
	int	i;

	i = -1;
	while (++i < lem->path_count)
		if (*k >= 1 && lem->paths[i].is_locked &&
			lem->paths[i].length == lem->shortest_path_len)
		{
			lem->paths[i].is_locked = 0;
		}
	i = -1;
	while (++i < lem->path_count)
	{
		if (!lem->paths[i].is_locked &&
			lem->paths[i].length == lem->shortest_path_len)
		{
			ant->path = i;
			ant->init = 1;
			lem->paths[i].is_locked = 1;
			*k = 0;
			return (0);
		}
	}
	return (1);
}

void			choose_path_1(t_lem *lem, t_ant *ant)
{
	static int	k = 0;
	int			i;

	if (!choose_path_util_1(lem, ant, &k))
		return ;
	if (ant->path < 0)
	{
		k++;
		i = -1;
		while (++i < lem->path_count)
		{
			if (!lem->paths[i].is_locked &&
				lem->coef < (double)count_free_ants(lem))
			{
				ant->path = i;
				ant->init = 1;
				return ;
			}
		}
	}
	choose_path_1(lem, ant);
}

static int		choose_path_util_2(t_lem *lem, t_ant *ant, int *k)
{
	int	i;

	i = -1;
	while (++i < lem->path_count)
	{
		if (*k > 1 && lem->paths[i].is_locked &&
			lem->paths[i].length == lem->shortest_path_len)
		{
			lem->paths[i].is_locked = 0;
			*k = 0;
		}
		if (!lem->paths[i].is_locked &&
			lem->paths[i].length == lem->shortest_path_len)
		{
			ant->path = i;
			ant->init = 1;
			lem->paths[i].is_locked = 1;
			return (0);
		}
	}
	return (1);
}

void			choose_path_2(t_lem *lem, t_ant *ant)
{
	static int	k = 0;
	int			i;

	if (!choose_path_util_2(lem, ant, &k))
		return ;
	if (ant->path < 0)
	{
		k++;
		i = -1;
		while (++i < lem->path_count)
		{
			if (!lem->paths[i].is_locked &&
				lem->coef < (double)count_free_ants(lem))
			{
				ant->path = i;
				ant->init = 1;
				return ;
			}
		}
	}
	ant->path = 0;
}
