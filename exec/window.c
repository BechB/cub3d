/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 16:49:24 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/24 13:35:32 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    open_win(t_data *data)
{
    data->mlx = mlx_init();
    data->win = mlx_new_window(data->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
    map_size(data);
    init_player(data);
    init_img(data);
    mlx_hook(data->win, 2, 1L << 0, key_press, data);
    render(data);
    mlx_loop(data->mlx);
}

int	leave(int key, t_data *dta)
{
	(void)key;
	ft_exit(dta, RED"RAGE QUIT !?\n"RESET, 0);
	return (0);
}

void draw_line(void *mlx, void *win, int x, int start, int end, int color) {
    if (start < 0) start = 0;
    if (end >= WIN_HEIGHT) end = WIN_HEIGHT - 1;
    for (int y = start; y <= end; y++) {
        mlx_pixel_put(mlx, win, x, y, color);
    }
}

int can_move(double new_x, double new_y, t_data *data) {
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height) {
        return data->map[map_y][map_x] == '0';
    }
    return 0;
}

void render(t_data *data)
{
    mlx_clear_window(data->mlx, data->win);
    for (int x = 0; x < WIN_WIDTH; x++)
    {
        double ray_angle = data->player_angle - (FOV / 2) * (PI / 180)
                           + (x * (FOV / WIN_WIDTH) * (PI / 180));
        double ray_x = cos(ray_angle);
        double ray_y = sin(ray_angle);
        double dist = 0;
        int hit = 0;
        int side = 0;

        while (!hit && dist < 20)
        {
            dist += 0.1;
            int map_x = (int)(data->player_x + ray_x * dist);
            int map_y = (int)(data->player_y + ray_y * dist);

            if (map_x >= 0 && map_x < data->map_width && map_y >= 0 && map_y < data->map_height)
            {
                if (data->map[map_y][map_x] == '1')
                {
                    hit = 1;
                    if (fabs(ray_x) > fabs(ray_y))
                        side = (ray_x > 0) ? 2 : 3;
                    else
                        side = (ray_y > 0) ? 0 : 1;
                }
            }
            else
                hit = 1;
        }

        if (!hit)
            break;
        int line_height = (int)(WIN_HEIGHT / (dist * cos(ray_angle - data->player_angle)));
        int start = WIN_HEIGHT / 2 - line_height / 2;
        int end = WIN_HEIGHT / 2 + line_height / 2;

        if (start < 0) start = 0;
        if (end >= WIN_HEIGHT) end = WIN_HEIGHT - 1;

        double wall_x;
        if (side == 0 || side == 1)
            wall_x = data->player_x + ray_x * dist;
        else
            wall_x = data->player_y + ray_y * dist;
        wall_x -= floor(wall_x);

        t_img *img = &data->img[side];
        int img_x = (int)(wall_x * (double)img->width);
        if ((side == 0 || side == 1) && ray_y > 0) img_x = img->width - img_x - 1;
        if ((side == 2 || side == 3) && ray_x < 0) img_x = img->width - img_x - 1;

        for (int y = start; y < end; y++)
        {
            int img_y = (int)((y - start) * ((double)img->height / line_height));
            int color = *(int *)(img->addr + (img_y * img->line_len + img_x * (img->bpp / 8)));
            if (color != 0)
                mlx_pixel_put(data->mlx, data->win, x, y, color);
        }
    }
}

int key_press(int keycode, t_data *data)
{
    if (keycode == ESC)
    {
        printf(RED"Rage quit!?\n"RESET);
        exit(0);
    }
    if (keycode == LEFT)
        data->player_angle -= 0.1;
    if (keycode == RIGHT)
        data->player_angle += 0.1;
    if (keycode == UP)
    {
        double new_x = data->player_x + cos(data->player_angle) * 0.5;
        double new_y = data->player_y + sin(data->player_angle) * 0.5;
        if (can_move(new_x, new_y, data))
        {
            data->player_x = new_x;
            data->player_y = new_y;
        }
    }
    if (keycode == DOWN)
    {
        double new_x = data->player_x - cos(data->player_angle) * 0.5;
        double new_y = data->player_y - sin(data->player_angle) * 0.5;
        if (can_move(new_x, new_y, data))
        {
            data->player_x = new_x;
            data->player_y = new_y;
        }
    }
    render(data);
    return (0);
}

void init_player(t_data *data)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while (y < data->map_height)
    {
        x = 0;
        while(x < data->map_width)
        {
            if (data->map[y][x] == '0')
            {
                data->player_x = x + 0.5;
                data->player_y = y + 0.5;
                data->player_angle = PI / 4;
                return;
            }
            x++;
        }
        y++;
    }
}

void map_size(t_data *data)
{
    data->map_height = 0;
    data->map_width = 0;

    while (data->map[data->map_height])
    {
        int current_width = ft_strlen(data->map[data->map_height]);
        if (current_width > data->map_width)
            data->map_width = current_width;
        data->map_height++;
    }
}

void read_map(t_data *data, char *filename)
{
    int fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        perror("Check file");
        exit(1);
    }
    char buf[1000000];
    int len = read(fd, buf, 999999);
    if (len == -1) {
        perror("Check file");
        close(fd);
        exit(1);
    }
    buf[len] = '\0';
    close(fd);
    data->map = ft_split(buf, '\n');
    if (!data->map)
    {
        printf(stderr, "Check map\n");
        exit(1);
    }
}

void load_img(t_data *data, t_img *img, char *path)
{
    img->img = mlx_xpm_file_to_image(data->mlx, path, &img->width, &img->height);
    if (!img->img)
    {
        printf(RED"Error : Check images%s\n"RESET, path);
        exit(1);
    }
    img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len, &img->endian);
}

void init_img(t_data *data)
{
    load_img(data, &data->img[0], "north.xpm"); 
    load_img(data, &data->img[1], "south.xpm");
    load_img(data, &data->img[2], "east.xpm");
    load_img(data, &data->img[3], "west.xpm");
}