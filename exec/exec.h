/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbousaad <bbousaad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 18:12:42 by bbousaad          #+#    #+#             */
/*   Updated: 2024/12/24 13:24:31 by bbousaad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
#define EXEC_H

# define BLACK2   0x000000
# define WHITE2   0xFFFFFF
# define RED2     0xFF0000
# define GREEN2   0x00FF00
# define BLUE2    0x0000FF
# define YELLOW2  0xFFFF00
# define CYAN2    0x00FFFF
# define MAGENTA2 0xFF00FF
# define ORANGE2  0xFFA500
# define PURPLE2  0x800080
# define GREY2    0x808080
# define ESC	  65307
# define UP		  65362
# define LEFT     65361
# define DOWN     65364
# define RIGHT    65363
# define PI		  3.1415926535
# define TURN 0.05
#define ang 360
#define PLAYER_MOVE_SPEED 0.1
#define PLAYER_ROTATE_SPEED 0.05

#define WIN_WIDTH 800
#define WIN_HEIGHT 600
#define MAP_WIDTH 1500
#define MAP_HEIGHT 900
#define FOV 75.0

typedef struct s_img {
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}				t_img;

typedef struct s_data
{
    void    *mlx;
    void    *win;
	int		size;
	int		posy;
	int		posx;
	int		pdx;
	int		pdy;
	int		pa;
	int		playerX;
	int		playerY;
	int		playerAngle;
	int		p_x;
	int		p_y;
	double	dir_x;
	double	dir_y;
	double	dir_a;
	int		map_height;
	int		map_width;
	char	**map;
	char	**mapa;
	t_img	north;
    t_img   south;
    t_img  east;
    t_img   west;
	t_img	floor;
    double player_x;
    double player_y;
    double player_angle;
	t_img   img[4];
}               t_data;

void	ft_exit(t_data *dta, char *mess, int status);
void    ft_error(char *error_msg);
void    open_win(t_data *data);
void	readmap(t_data	*dta, char	**argv);
void	map_size(t_data *dta);
void    init_data(t_data *dta);
void 	draw_line(void *mlx, void *win, int x, int start, int end, int color);
void 	render(t_data *data);
int 	key_press(int keycode, t_data *data);
void 	map_size(t_data *data);
void    pos_player(t_data *dta);
void 	init_player(t_data *data);
void 	read_map(t_data *data, char *filename);
void 	init_img(t_data *data);
void 	load_img(t_data *data, t_img *img, char *path);
#endif