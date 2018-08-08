/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_keydown.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:23:24 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:26:04 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void	render_info(t_mlx *mlx)
{
	int		i;
	int		x;
	int		y;
	char	**split;

	x = 1900;
	y = 1070;
	i = -1;
	put_count_comm(mlx);
	mlx_string_put(mlx->mlx, mlx->win, X_SCREEN_SIZE - x,
	Y_SCREEN_SIZE - y, 0xFF0000, "	 PATHS	 ");
	while (++i < mlx->lem->path_count)
	{
		y -= 30;
		split = ft_strsplit(mlx->lem->paths[i].name, ' ');
		put_path(mlx, split, &x, &y);
		put_path_len(mlx, &x, &y, ft_strsplit_count(split) - 1);
		ft_splitdel(&split);
	}
}

void	render_bg(t_mlx *mlx)
{
	int	j;

	clear_image(mlx);
	put_lines(mlx);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->image->img, 0, 0);
	j = -1;
	while (++j < mlx->lem->count_rooms)
		put_room(mlx, j);
	render_info(mlx);
}

int		hook_keydown(int key, t_mlx *mlx)
{
	char	*line;

	if (key == ENTER)
	{
		get_next_line(STDIN_FILENO, &line);
		if (!line)
		{
			render_bg(mlx);
			return (0);
		}
		else
			render(mlx, line);
		mlx->count_comm++;
		ft_printf("%s\n", line);
		ft_strdel(&line);
	}
	if (key == KEY_ESC)
		exit(EXIT_SUCC);
	return (0);
}
