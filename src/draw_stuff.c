/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_stuff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:43:50 by julian            #+#    #+#             */
/*   Updated: 2022/01/02 19:35:49 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_visualizer.h"

void	drawRays2D(t_data *data)
{
	int	r, mx, my, mp, dof;
	float rx, ry, ra, xo, yo, disT;
	float disH, disV, hx, hy, vx, vy;
	int dx, dy, sx, sy, err, e2;
	
	float lineH, lineStartX, lineStartY, ca; //for drawing 3D walls
	int		x, y;

	int		color;
	int		x0;
	int		y0;
	int		x1;
	int		y1;

	ra = data->pa - DR * 30;
	r = -1;
	while (++r < 60)
	{
		// check horizontal lines
		dof = 0;
		disH = 1000000;
		hx = data->px;
		hy = data->py;
		float aTan = -1 / tan(ra);
		if (ra > PI)	//looking up
		{
			ry = (((int)data->py / 64) * 64) - 0.0001;
			rx = (data->py - ry) * aTan + data->px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)	//looking down
		{
			ry = (((int)data->py / 64) * 64) + 64;
			rx = (data->py - ry) * aTan + data->px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) //looking straight left or right
		{
			rx = data->px;
			ry = data->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx / 64;
			my = (int)ry / 64;
			mp = my * mapWidth + mx;
			if (mp > 0 && mp < mapWidth * mapHeight && data->worldMap[mp] == 1)
			{
				hx = rx;
				hy = ry;
				disH = dist(data->px, data->py, hx, hy);
				dof = 8; //hit wall
			}
			else //next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}

		//check vertical lines
		dof = 0;
		disV = 1000000;
		vx = data->px;
		vy = data->py;
		float nTan = -tan(ra);
		if (ra > P2 && ra < P3)	//looking left
		{
			rx = (((int)data->px / 64) * 64) - 0.0001;
			ry = (data->px - rx) * nTan + data->py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)	//looking right
		{
			rx = (((int)data->px / 64) * 64) + 64;
			ry = (data->px - rx) * nTan + data->py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI) //looking straight up or down
		{
			rx = data->px;
			ry = data->py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)rx / 64;
			my = (int)ry / 64;
			mp = my * mapWidth + mx;
			if (mp > 0 && mp < mapWidth * mapHeight && data->worldMap[mp] == 1)
			{
				vx = rx;
				vy = ry;
				disV = dist(data->px, data->py, vx, vy);
				dof = 8; //hit wall
			}
			else //next line
			{
				rx += xo;
				ry += yo;
				dof += 1;
			}
		}
		if (disV < disH)	//vertical wall hit
		{
			rx = vx;
			ry = vy;
			disT = disV;
			color = create_trgb(0, 255, 0, 0);
		}
		if (disH < disV)	//horizontal wall hit
		{
			rx = hx;
			ry = hy;
			disT = disH;
			color = create_trgb(0, 200, 0, 0) / 2;
		}
		x0 = data->px + 4;
		y0 = data->py + 4;
		x1 = rx;
		y1 = ry;
		dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
		dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
		err = dx + dy;
		while (1)
		{
			my_mlx_pixel_put(&data->img, x0, y0, color);
			if (x0 == x1 && y0 == y1) 
				break;
			e2 = 2 * err;
			if (e2 > dy) 
			{ 
				err += dy;
				x0 += sx; 
			}
			if (e2 < dx)
			{
				err += dx;
				y0 += sy; 
			}
		}
	
		//Draw 3D Walls
		ca = data->pa - ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		disT = disT * cos(ca); 			//fix fisheye
		lineH = (mapS * 320) / disT;	//line height
		if (lineH > 320)
			lineH = 320;
		lineStartX = screenWidth / 2 + 16 + (r * 8);
		lineStartY = screenHeight / 2 - lineH / 2;
		y = lineStartY - 1;
		while (++y < lineStartY + lineH)
		{
			x = lineStartX - 1;
			while (++x < lineStartX + 8)
				my_mlx_pixel_put(&data->img, x, y, color);
		}
		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra -= 2 * PI;
	}
}


void 	drawDirection(t_data *data)
{
	int		color;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
	
	color = create_trgb(0, 255, 255, 0);
	x0 = data->px + 4;
	y0 = data->py + 4;
	x1 = x0 + 30 * cos(data->pa);
	y1 = y0 + 30 * sin(data->pa);

	int dx =  abs(x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs(y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2;
	while (1)
	{
		my_mlx_pixel_put(&data->img, x0, y0, color);
		if (x0 == x1 && y0 == y1) 
			break;
		e2 = 2 * err;
		if (e2 > dy) 
		{ 
			err += dy;
			x0 += sx; 
		}
		if (e2 < dx)
		{ 
			err += dx;
			y0 += sy; 
		}
	}
}

void 	drawPlayer(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 255, 255, 0);
	i = data->px - 1;
	while (++i < data->px + 9)
	{
		j = data->py - 1;
		while (++j < data->py + 9)
			my_mlx_pixel_put(&data->img, i, j, color);
	}
}

void	drawMap(t_data *data)
{
	int		x;
	int		y;
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 255, 255, 255);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.sl, &data->img.endian);
	y = -1;
	while (++y < mapHeight)
	{
		x = -1;
		while (++x < mapWidth)
		{
			if (data->worldMap[y * mapWidth + x] == 1)
			{
				i = 0;
				while (++i < 63)
				{
					j = 0;
					while (++j < 63)
						my_mlx_pixel_put(&data->img, (x * 64) + i, (y * 64) + j, color);
				}
			}
		}
	}
}

void	drawWindowGray(t_data *data)
{
	int		i;
	int		j;
	int		color;

	color = create_trgb(0, 128, 128, 128);
	data->img.addr = mlx_get_data_addr(data->img.img_ptr, &data->img.bpp, &data->img.sl, &data->img.endian);
	i = screenWidth / 2 - 1;
	while (++i < screenWidth)
	{
		j = -1;
		while (++j < screenHeight)
			my_mlx_pixel_put(&data->img, i, j, color);
	}
}
