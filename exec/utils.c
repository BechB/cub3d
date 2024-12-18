/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:04:01 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/18 13:23:42 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_data *dta, char *mess, int status)
{
	printf("%s\n", mess);
	exit (status);
	(void)dta;
}

void    map_size(t_data *dta)
{
    while(dta->map[dta->height])
    {
        dta->width = 0;
        while(dta->map[dta->height][dta->width])
            dta->width++;
        dta->height++;
    }
    printf("height : %d\n", dta->height);
    printf("width : %d\n", dta->width);
}

void    init_data(t_data *dta)
{
    dta->dir_x = 60;
    dta->dir_y = 60;
}
