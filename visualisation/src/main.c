/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:34:28 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:34:53 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void	get_ants(t_lem *lem)
{
	int i;

	i = -1;
	lem->ants = ft_memalloc(sizeof(t_ant) * lem->count_ants);
	while (++i < lem->count_ants)
	{
		lem->ants[i].count = i;
		lem->ants[i].now_in = lem->start_room;
	}
}

void	error(char *perke)
{
	ft_putendl_fd(perke, 2);
	exit(2);
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
	t_mlx *mlx;

	if (!(mlx = init_mlx("lem_in")))
		error("<==== error when initializng mlx ====>");
	mlx->lem->info = ft_memalloc(sizeof(char *) * 1000);
	mlx->count_comm = 0;
	reader(mlx->lem);
	get_ants(mlx->lem);
	print_info(mlx->lem);
	add_img(mlx, "end_room.xpm", &mlx->end_room);
	add_img(mlx, "start_room.xpm", &mlx->start_room);
	add_img(mlx, "room.xpm", &mlx->room);
	mlx->lem->visited_rooms = ft_memalloc(sizeof(int) * mlx->lem->count_rooms);
	get_levels_of_rooms(mlx->lem, mlx->lem->start_room, 0);
	ft_bzero(mlx->lem->visited_rooms, sizeof(int) * mlx->lem->count_rooms);
	get_all_paths(mlx->lem);
	render_bg(mlx);
	mlx_hook(mlx->win, 2, 5, hook_keydown, mlx);
	mlx_loop(mlx->mlx);
	return (0);
}
