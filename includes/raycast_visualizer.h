/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_visualizer.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/10 15:08:57 by julian            #+#    #+#             */
/*   Updated: 2022/01/02 19:34:32 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_VISUALIZER_H
# define RAYCAST_VISUALIZER_H

# include <stdio.h>
# include <math.h>
# include <errno.h>
# include "../mlx/mlx.h"
# include "../libft/libft.h"

# define screenWidth	1024
# define screenHeight	512
# define mapWidth		8
# define mapHeight		8
# define mapS			mapWidth*mapHeight
# define PI				3.1415926535
# define P2				PI/2
# define P3				3*PI/2
# define DR				0.0174533 //one degree in radian

# define KEY_ANSI_A		(0X00)
# define KEY_ANSI_S		(0X01)
# define KEY_ANSI_D		(0X02)
# define KEY_ANSI_W		(0X0D)
# define KEY_LEFTARROW	(0X7B)
# define KEY_RIGHTARROW	(0X7C)
# define KEY_ESCAPE		(0X35)

typedef struct s_img
{
	void	*img_ptr;
	char	*addr;
	int		bpp;
	int		sl;
	int		endian;
	int		width;
	int		height;
}			t_img;

typedef struct s_data
{
	int		worldMap[mapHeight * mapWidth];
	
	// players position
	float	px;		//x position in map
	float	py;		//x position in map
	float	pdx;	//delta x
	float	pdy;	//delta y
	float	pa;		//angle of player;
	
	void	*mlx_ptr;
	void	*mlx_win;
	t_img	img;
}			t_data;


int		interactive(int key, t_data	*data);
int		create_trgb(int t, int r, int g, int b);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	initialize_map(t_data *data);
void 	drawPlayer(t_data *data);
void 	drawDirection(t_data *data);
void	drawWindowGray(t_data *data);
void 	drawMap(t_data *data);
void	drawRays2D(t_data *data);
float	dist(float ax, float ay, float bx, float by);

#endif