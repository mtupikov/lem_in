/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:26:42 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:28:13 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void	add_img(t_mlx *mlx, char *room, t_image **img)
{
	int	x;
	int	y;

	x = 200;
	y = 200;
	*img = ft_memalloc(sizeof(t_image));
	(*img)->img = mlx_xpm_file_to_image(mlx->mlx, room, &x, &y);
	(*img)->ptr =
			mlx_get_data_addr((*img)->img, &(*img)->bpp, &(*img)->stride,
			&(*img)->endian);
	(*img)->bpp /= 8;
}

void	put_room(t_mlx *mlx, int i)
{
	if (mlx->lem->rooms[i].def == START)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->start_room->img, mlx->lem->rooms[i].x, mlx->lem->rooms[i].y);
	else if (mlx->lem->rooms[i].def == END)
		mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->end_room->img, mlx->lem->rooms[i].x, mlx->lem->rooms[i].y);
	else
		mlx_put_image_to_window(mlx->mlx, mlx->win,
		mlx->room->img, mlx->lem->rooms[i].x, mlx->lem->rooms[i].y);
	mlx_string_put(mlx->mlx, mlx->win, mlx->lem->rooms[i].x + 10,
	mlx->lem->rooms[i].y + 7, 0x000000, mlx->lem->rooms[i].name);
}

void	put_lines(t_mlx *mlx)
{
	int i;
	int j;

	i = -1;
	while (++i < mlx->lem->count_rooms)
	{
		j = -1;
		while (++j < mlx->lem->count_rooms)
		{
			if (mlx->lem->links[i][j])
				mlx_put_line(get_vector(mlx->lem->rooms[i].x + 15,
				mlx->lem->rooms[i].y + 15),
				get_vector(mlx->lem->rooms[j].x + 15,
				mlx->lem->rooms[j].y + 15), mlx, 0xFFFFFF);
		}
	}
}

void	render(t_mlx *mlx, char *commands)
{
	char	**split;
	int		i;
	int		j;

	clear_image(mlx);
	i = -1;
	split = ft_strsplit(commands, ' ');
	if (ft_strsplit_count(split) < 1)
		return ;
	put_lines(mlx);
	while (split[++i])
		ant_go_to(mlx, split[i]);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	i = -1;
	while (split[++i])
		put_ant_index(mlx, split[i]);
	j = -1;
	while (++j < mlx->lem->count_rooms)
		put_room(mlx, j);
	render_info(mlx);
	ft_splitdel(&split);
}
