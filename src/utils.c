/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:31:10 by julian            #+#    #+#             */
/*   Updated: 2022/01/02 19:35:41 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_visualizer.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

int		create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;
	
	dst = img->addr + (y * img->sl + x * (img->bpp / 8));
	*(unsigned int*)dst = color;
}

void	initialize_map(t_data *data)
{	
	int	i;

	i = -1;
	while (++i < mapHeight * mapWidth)
	{
		if (i < 8 || i >= 56 \
			|| i == 8 || i == 16 || i == 24 || i == 32 || i == 40 || i == 48 \
			|| i == 15 || i == 23 || i == 31 || i == 39 || i == 47 || i == 55 \
			|| i == 2 || i == 10 || i == 18 || i == 45)
			data->worldMap[i] = 1;
		else
			data->worldMap[i] = 0;
	}
	data->px = 300;					//x start position
	data->py = 300;					//y start position
	data->pa = 0;					//angle of player;
	data->pdx = cos(data->pa) * 5;	//initial direction vector
	data->pdy = sin(data->pa) * 5;	//initial direction vector
	
}
