/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtupikov <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:33:28 by mtupikov          #+#    #+#             */
/*   Updated: 2018/05/14 18:34:19 by mtupikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/visualise.h"

void		img_set_pixel(t_image *image, int x, int y, int color)
{
	if (x < 0 || x >= X_SCREEN_SIZE || y < 0 || y >= Y_SCREEN_SIZE)
		return ;
	*(int *)(image->ptr + ((x + y * X_SCREEN_SIZE) * image->bpp)) = color;
}

void		clear_image(t_mlx *mlx)
{
	int x;
	int y;

	x = X_SCREEN_SIZE;
	y = Y_SCREEN_SIZE;
	mlx->image->img = mlx_xpm_file_to_image(mlx->mlx, "lem_in_bg.xpm", &x, &y);
	mlx->image->ptr =
			mlx_get_data_addr(mlx->image->img, &mlx->image->bpp,
			&mlx->image->stride, &mlx->image->endian);
	mlx->image->bpp /= 8;
}

t_image		*del_image(t_mlx *mlx, t_image *img)
{
	if (img != NULL)
	{
		if (img->img != NULL)
			mlx_destroy_image(mlx->mlx, img->img);
		ft_memdel((void **)&img);
	}
	return (NULL);
}

t_image		*new_image(t_mlx *mlx)
{
	t_image	*img;
	int		x;
	int		y;

	x = X_SCREEN_SIZE;
	y = Y_SCREEN_SIZE;
	if (!(img = ft_memalloc(sizeof(t_image))))
		return (NULL);
	if (!(img->img = mlx_xpm_file_to_image(mlx->mlx, "lem_in_bg.xpm", &x, &y)))
		return (del_image(mlx, mlx->image));
	img->ptr =
			mlx_get_data_addr(img->img, &img->bpp, &img->stride, &img->endian);
	img->bpp /= 8;
	return (img);
}
