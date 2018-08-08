/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utils_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:30:27 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:32:23 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

t_2d			get_vector(int x, int y)
{
	t_2d ret;

	ret.y = y;
	ret.x = x;
	return (ret);
}

int				get_room_num(t_mlx *mlx, char *line)
{
	int i;

	i = -1;
	while (++i < mlx->lem->count_rooms)
	{
		if (!ft_strcmp(mlx->lem->rooms[i].name, line))
			return (i);
	}
	return (-1);
}

static int		line_g(t_mlx *mlx, t_line *l, t_2d *p1, t_2d *p2)
{
	if (p1->x < 0 || p1->x >= X_SCREEN_SIZE ||
		p1->y < 0 || p1->y >= Y_SCREEN_SIZE ||
		p2->x < 0 || p2->x >= X_SCREEN_SIZE ||
		p2->y < 0 || p2->y >= Y_SCREEN_SIZE ||
		(p1->x == p2->x && p1->y == p2->y))
		return (1);
	img_set_pixel(mlx->image, p1->x, p1->y, l->color);
	if (l->color == 0xFF0000)
	{
		img_set_pixel(mlx->image, p1->x + 1, p1->y - 1, l->color);
		img_set_pixel(mlx->image, p1->x + 1, p1->y + 1, l->color);
		img_set_pixel(mlx->image, p1->x - 1, p1->y - 1, l->color);
	}
	l->err2 = l->err;
	if (l->err2 > -l->dx)
	{
		l->err -= l->dy;
		p1->x += l->sx;
	}
	if (l->err2 < l->dy)
	{
		l->err += l->dx;
		p1->y += l->sy;
	}
	return (0);
}

void			mlx_put_line(t_2d p1, t_2d p2, t_mlx *mlx, int color)
{
	t_line line;

	line.color = color;
	line.start = p1;
	line.stop = p2;
	line.dx = ABS(p2.x - p1.x);
	line.sx = p1.x < p2.x ? 1 : -1;
	line.dy = ABS(p2.y - p1.y);
	line.sy = p1.y < p2.y ? 1 : -1;
	line.err = ((line.dx > line.dy) ? line.dx : -line.dy) / 2;
	while (1)
		if (line_g(mlx, &line, &p1, &p2))
			break ;
}
