/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 13:38:23 by aldalmas          #+#    #+#             */
/*   Updated: 2024/12/18 13:22:55 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    init_struct(t_map *m, char *map_path)
{
    m->fd = open(map_path, O_RDONLY);
    if (m->fd == -1)
        ft_error("Wrong map file");
}
