/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_stuff.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:22:23 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:22:44 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

t_mlx		*mlx_destroyer(t_mlx *mlx)
{
	if (mlx->win != NULL)
		mlx_destroy_window(mlx->mlx, mlx->win);
	if (mlx->image != NULL)
		del_image(mlx, mlx->image);
	ft_memdel((void **)&mlx);
	return (NULL);
}

t_mlx		*init_mlx(char *title)
{
	t_mlx	*ret;

	if (!(ret = (t_mlx *)malloc(sizeof(t_mlx))))
		return (mlx_destroyer(ret));
	if (!(ret->mlx = mlx_init()) ||
		(!(ret->win = mlx_new_window(ret->mlx,
		X_SCREEN_SIZE, Y_SCREEN_SIZE, title))) ||
		(!(ret->image = new_image(ret))) ||
		(!(ret->lem = ft_memalloc(sizeof(t_lem)))))
		return (mlx_destroyer(ret));
	return (ret);
}
