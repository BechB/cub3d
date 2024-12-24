/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:04:01 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/24 13:25:35 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_exit(t_data *dta, char *mess, int status)
{
	printf("%s\n", mess);
	exit (status);
	(void)dta;
}

void    init_data(t_data *dta)
{
    dta->dir_x = 60;
    dta->dir_y = 60;
}

void    pos_player(t_data *dta)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while(dta->map[i])
    {
        j = 0;
        while(dta->map[i][j])
        {
            if(dta->map[i][j] == 'N' || dta->map[i][j] == 'E' ||
                dta->map[i][j] == 'O' || dta->map[i][j] == 'S')
            {
                dta->player_x = j;
                dta->player_y = i;
                dta->map[i][j] = '0';
            }
            printf("x ; %f\n", dta->player_x);
            printf("y ; %f\n", dta->player_y);
            j++;
        }
        i++;
    }
}
