/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:49:24 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/18 14:23:47 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    open_win(t_data *dta)
{
	(void) dta;
	start();
	// int i = 0;
	// int j = 0;
	// dta->north.path = "north.xpm";
	// dta->east.path = "east.xpm";
	// dta->south.path = "south.xpm";
	// dta->west.path = "west.xpm";
	// dta->floor.path = "floor.xpm";
	// dta->size = 64;
	// dta->mlx = mlx_init();
	// dta->win = mlx_new_window(dta->mlx, 1500, 900, "cub3d");
	// //check_img(dta);
	// init_data(dta);
	// handle_img(dta);
	// put_mini(dta, i, j);
	// init_spawn(dta);
	// map_size(dta);
	// mlx_hook(dta->win, 2, (1L << 0), key_press, dta);
	// mlx_hook(dta->win, 17, (1L << 17), leave, dta);
	// mlx_loop(dta->mlx);
	
}

int	leave(int key, t_data *dta)
{
	(void)key;
	ft_exit(dta, RED"RAGE QUIT !?\n"RESET, 0);
	return (0);
}

// Exemple de carte (1 = mur, 0 = vide)
int world_map[MAP_HEIGHT][MAP_WIDTH] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 1, 0, 0, 0, 1, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 1},
    {1, 0, 1, 1, 1, 1, 1, 1, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
};

void draw_line(void *mlx, void *win, int x, int start, int end, int color)
{
    for (int y = start; y <= end; y++) {
        mlx_pixel_put(mlx, win, x, y, color);
    }
}

void render(t_data *data)
{
    for (int x = 0; x < WIN_WIDTH; x++)
	{
        double ray_angle = data->player_angle - (FOV / 2) * (PI / 180) + (x * (FOV / WIN_WIDTH) * (PI / 180));
        double ray_x = cos(ray_angle);
        double ray_y = sin(ray_angle);
        double dist = 0;
        int hit = 0;
        while (!hit && dist < 20)
		{
            dist += 0.1;
            int map_x = (int)(data->player_x + ray_x * dist);
            int map_y = (int)(data->player_y + ray_y * dist);
            if (map_x >= 0 && map_x < MAP_WIDTH && map_y >= 0 && map_y < MAP_HEIGHT) {
                if (world_map[map_y][map_x] == 1) hit = 1;
            }
        }
        int line_height = (int)(WIN_HEIGHT / (dist * cos(ray_angle - data->player_angle)));
        int start = WIN_HEIGHT / 2 - line_height / 2;
        int end = WIN_HEIGHT / 2 + line_height / 2;
        draw_line(data->mlx, data->win, x, start, end, RED2);
    }
}

int key_press(int keycode, t_data *data)
{
    if (keycode == LEFT)
        data->player_angle -= 0.1;
    if (keycode == RIGHT)
        data->player_angle += 0.1;
    if (keycode == UP)
	{
        data->player_x += cos(data->player_angle);
        data->player_y += sin(data->player_angle);
    }
    if (keycode == DOWN)
	{
        data->player_x -= cos(data->player_angle);
        data->player_y -= sin(data->player_angle);
    }
    mlx_clear_window(data->mlx, data->win);
    render(data);
    return (0);
}

int start(void)
{
    t_data data;
    data.mlx = mlx_init();
    data.win = mlx_new_window(data.mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
    data.player_x = 5.0;
    data.player_y = 5.0;
    data.player_angle = PI / 4;
    render(&data);
    mlx_key_hook(data.win, key_press, &data);
    mlx_loop(data.mlx);
    return (0);
}
