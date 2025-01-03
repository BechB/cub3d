/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 17:04:08 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/18 14:46:25 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	readmap(t_data	*dta, char	**argv)
{
	int		fd;
	int		len;
	char	buf[1000000];

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit(dta, "Warning check argument !\n", 1);
	len = read(fd, buf, 999999);
	buf[len] = '\0';
	dta->map = ft_split(buf, '\n');
	dta->mapa = ft_split(buf, '\n');
	close(fd);
}

void    init_struct(t_map *m, char *map_path)
{
    m->fd = open(map_path, O_RDONLY);
    if (m->fd == -1)
        ft_error("Wrong map file");
}
