/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_img.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:12:49 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/18 13:23:52 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    check_img(t_data *dta)
{
	if (dta->floor.img == 0)
		ft_exit(dta, "Warning wrong path of image !\n", 1);
	if (dta->north.img == 0)
		ft_exit(dta, "Warning wrong path of image !\n", 1);
	if (dta->south.img == 0)
		ft_exit(dta, "Warning wrong path of image !\n", 1);
	if (dta->west.img == 0)
		ft_exit(dta, "Warning wrong path of image !\n", 1);
	if (dta->east.img == 0)
		ft_exit(dta, "Warning wrong path of image !\n", 1);
}

int	put_img(t_data *dta)
{
	dta->size = 64;
	dta->floor.img = mlx_xpm_file_to_image(dta->mlx,
		dta->floor.path, &dta->size, &dta->size);
	dta->north.img = mlx_xpm_file_to_image(dta->mlx,
		dta->north.path, &dta->size, &dta->size);
	dta->south.img = mlx_xpm_file_to_image(dta->mlx,
		dta->south.path, &dta->size, &dta->size);
	dta->west.img = mlx_xpm_file_to_image(dta->mlx,
		dta->west.path, &dta->size, &dta->size);
	dta->east.img = mlx_xpm_file_to_image(dta->mlx,
		dta->east.path, &dta->size, &dta->size);
	while(dta->map[dta->posy])
	{
		dta->posx = 0;
		while(dta->map[dta->posy][dta->posx])
		{
			if(dta->map[dta->posy][dta->posx] == 'N')
				return (1);
			else if(dta->map[dta->posy][dta->posx] == 'S')
				return (2);
			else if(dta->map[dta->posy][dta->posx] == 'E')
				return (3);
			else if(dta->map[dta->posy][dta->posx] == 'W')
				return (4);
			dta->posx++;
		}
		dta->posy++;
	}
	return (0);
}
