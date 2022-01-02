/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: julian <julian@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 15:28:29 by julian            #+#    #+#             */
/*   Updated: 2022/01/02 19:55:04 by julian           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/raycast_visualizer.h"

int	interactive(int key, t_data	*data)
{	
	if (key == KEY_ESCAPE)				//exit visualizer
		exit(0);
	else if (key == KEY_ANSI_A)			//rotate to the left
	{
		data->pa -= 0.1;
		if (data->pa < 0)
			data->pa += 2 * M_PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else if (key == KEY_ANSI_D)			//rotate to the right
	{
		data->pa += 0.1;
		if (data->pa > 2 * M_PI)
			data->pa -= 2 * M_PI;
		data->pdx = cos(data->pa) * 5;
		data->pdy = sin(data->pa) * 5;
	}
	else if (key == KEY_ANSI_W)			//move forward
	{
		data->px += data->pdx;
		data->py += data->pdy;
	}	
	else if (key == KEY_ANSI_S)			//move backwards
	{
		data->px -= data->pdx;
		data->py -= data->pdy;
	}
	return (0);
}