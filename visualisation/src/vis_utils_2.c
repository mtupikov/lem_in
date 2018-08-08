/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vis_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:29:01 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:30:14 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void	put_path(t_mlx *mlx, char **split, int *x, int *y)
{
	int	j;

	j = ft_strsplit_count(split);
	mlx_string_put(mlx->mlx, mlx->win, X_SCREEN_SIZE - *x,
	Y_SCREEN_SIZE - *y, 0xFF0000, split[j - 1]);
	--j;
	while (--j >= 0)
	{
		*x -= ft_strlen(split[j]) * 10;
		mlx_string_put(mlx->mlx, mlx->win, X_SCREEN_SIZE - *x,
		Y_SCREEN_SIZE - *y, 0xFF0000, "->");
		*x -= ft_strlen(split[j]) * 20;
		mlx_string_put(mlx->mlx, mlx->win, X_SCREEN_SIZE - *x,
		Y_SCREEN_SIZE - *y, 0xFF0000, split[j]);
	}
}

void	put_path_len(t_mlx *mlx, int *x, int *y, int path_len)
{
	char *len;
	char *temp;

	len = "^ length of ";
	temp = ft_itoa(path_len);
	len = ft_strjoin(len, temp);
	ft_strdel(&temp);
	*y -= 30;
	*x = 1900;
	mlx_string_put(mlx->mlx, mlx->win, X_SCREEN_SIZE - *x,
	Y_SCREEN_SIZE - *y, 0xFF0000, len);
	ft_strdel(&len);
}

void	put_count_comm(t_mlx *mlx)
{
	char *len;
	char *temp;

	len = "Steps count: ";
	temp = ft_itoa(mlx->count_comm);
	len = ft_strjoin(len, temp);
	ft_strdel(&temp);
	mlx_string_put(mlx->mlx, mlx->win, X_SCREEN_SIZE - 200,
	Y_SCREEN_SIZE - 1070, 0xFF0000, len);
	ft_strdel(&len);
}

void	ant_go_to(t_mlx *mlx, char *line)
{
	char	**split;
	int		ant_n;
	t_2d	v1;
	t_2d	v2;

	line++;
	split = ft_strsplit(line, '-');
	ant_n = (int)ft_atoi(split[0]);
	v1 = get_vector(mlx->lem->rooms[mlx->lem->ants[ant_n].now_in].x + 15,
	mlx->lem->rooms[mlx->lem->ants[ant_n].now_in].y + 15);
	v2 = get_vector(mlx->lem->rooms[get_room_num(mlx, split[1])].x + 15,
	mlx->lem->rooms[get_room_num(mlx, split[1])].y + 15);
	mlx_put_line(v1, v2, mlx, 0xFF0000);
	mlx_string_put(mlx->mlx, mlx->win, ABS(v1.x + v2.x) / 2,
	ABS(v1.y + v2.y) / 2, 0xFF0000, split[0]);
	ft_splitdel(&split);
}

void	put_ant_index(t_mlx *mlx, char *line)
{
	char	**split;
	int		ant_n;
	t_2d	v1;
	t_2d	v2;

	line++;
	split = ft_strsplit(line, '-');
	ant_n = (int)ft_atoi(split[0]);
	v1 = get_vector(mlx->lem->rooms[mlx->lem->ants[ant_n].now_in].x + 15,
	mlx->lem->rooms[mlx->lem->ants[ant_n].now_in].y + 15);
	v2 = get_vector(mlx->lem->rooms[get_room_num(mlx, split[1])].x + 15,
	mlx->lem->rooms[get_room_num(mlx, split[1])].y + 15);
	mlx_string_put(mlx->mlx, mlx->win, ABS(v1.x + v2.x) / 2 + 5,
	ABS(v1.y + v2.y) / 2 + 5, 0xFF0000, split[0]);
	mlx->lem->ants[ant_n].now_in = get_room_num(mlx, split[1]);
	ft_splitdel(&split);
}
