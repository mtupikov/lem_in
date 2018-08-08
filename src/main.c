/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/13 16:46:41 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/13 16:47:05 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lem_in.h"

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
			continue;
		}
		split = ft_strsplit(line, '-');
		if (!ft_strcmp(line, ""))
			break ;
		if (ft_strsplit_count(split) != 2)
			error("Bad link.");
		add_link(lem, lem->links, split);
		ft_strdel(&line);
		ft_splitdel(&split);
		get_next_line(STDIN_FILENO, &line);
	}
}

void	error(char *perke)
{
	ft_putendl_fd(perke, 2);
	exit(2);
}

void	get_ants(t_lem *lem)
{
	int i;

	i = -1;
	lem->ants = ft_memalloc(sizeof(t_ant) * lem->count_ants);
	while (++i < lem->count_ants)
	{
		lem->ants[i].count = i;
		lem->ants[i].finished = 0;
		lem->ants[i].now_in = lem->start_room;
		lem->ants[i].go_to = -1;
		lem->ants[i].queue = -1;
		lem->ants[i].path = -1;
		lem->ants[i].init = 0;
	}
}

void	print_info(t_lem *lem)
{
	int i;

	i = -1;
	while (lem->info[++i])
		ft_printf("%s\n", lem->info[i]);
	ft_printf("\n");
}

int		main(void)
{
	t_lem lem;

	lem.info = ft_memalloc(sizeof(char *) * 100000);
	if (!reader(&lem))
		error("Error");
	get_ants(&lem);
	print_info(&lem);
	go_ants(&lem);
	return (0);
}
