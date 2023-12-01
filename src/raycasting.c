/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:14:13 by msulc             #+#    #+#             */
/*   Updated: 2023/11/02 11:14:14 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	count_lo_hi(t_data *data)//pocita vydalenosti od polohy hrace ke stenam policka, osovou
{
	data->lo_x = data->pos_x - floor(data->pos_x);
	data->lo_y = data->pos_y - floor(data->pos_y);
	data->hi_x = ceil(data->pos_x) - data->pos_x;
	data->hi_y = ceil(data->pos_y) - data->pos_y;
}

void	count_quadrant(t_data *data)//zjistuje do jakeho kvadrantu se diva paprsek
{
	if ((data->ray_angle <= 0 && data->ray_angle > (-M_PI / 2))
		|| (data->ray_angle > (M_PI * 1.5) && data->ray_angle <= (M_PI * 2)))
		data->quadrant = 1;
	else if ((data->ray_angle <= (-M_PI / 2) && data->ray_angle > (-M_PI))
		|| (data->ray_angle > M_PI && data->ray_angle <= (M_PI * 1.5)))
		data->quadrant = 2;
	else if ((data->ray_angle <= (-M_PI) && data->ray_angle > (M_PI * -1.5))
		|| (data->ray_angle > (M_PI / 2) && data->ray_angle <= M_PI))
		data->quadrant = 3;
	else if ((data->ray_angle <= (M_PI * -1.5) && data->ray_angle > (M_PI * -2))
		|| (data->ray_angle > 0 && data->ray_angle <= (M_PI / 2)))
		data->quadrant = 4;
}

void	looking_for_wals(t_data *data)//hleda nejblizsi zed ve smeru kazdeho papsku
{
	data->wall = 0;
	data->map_x = (int)data->pos_x;
	data->map_y = (int)data->pos_y;
	while (data->wall == 0)
	{
		if (data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->direction_x;
			data->x_or_y = 'x';//zed je x-ova
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->direction_y;
			data->x_or_y = 'y';//zed je y-ova
		}
		if (data->mapa.grid[data->map_x][data->map_y] == '1')
			data->wall = 1;//narazili jsme na zed
	}
	if (data->x_or_y == 'x')
		data->distance_to_wall = data->sidedist_x - data->deltadist_x;
	else
		data->distance_to_wall = data->sidedist_y - data->deltadist_y;
}

void	calculate_height(t_data *data)//pocitame vysku kazdeho zobrazovaneho sloupce 
{
	int	temp;

	data->line_height = (int)(HEIGHT / (data->distance_to_wall
				* cos((data->actual_angle) - data->ray_angle)));
	temp = data->line_height;
	if (data->line_height > HEIGHT)
		data->line_height = HEIGHT;
	count_texture_coordinates(data, temp);//pocitame souradnice pixelu textury ktery cteme
	data->drawstart = -data->line_height / 2 + HEIGHT / 2;
	data->drawend = data->line_height / 2 + HEIGHT / 2;
	if (data->drawstart < 0)
		data->drawstart = 0;
	if (data->drawend < 0 || data->drawend >= HEIGHT)
		data->drawend = HEIGHT - 1;
}

void	calculate_sidedist(t_data *data)//pocita vzdalenost ke stenam policka ve smeru paprsku
{
	data->deltadist_x = 1 / fabs(cos(fabs(data->ray_angle)));
	data->deltadist_y = 1 / fabs(sin(fabs(data->ray_angle)));
	if (data->quadrant == 1 || data->quadrant == 4)
	{
		data->direction_x = -1;
		data->sidedist_x = fabs(data->lo_x / cos(fabs(data->ray_angle)));
	}
	else if (data->quadrant == 2 || data->quadrant == 3)
	{
		data->sidedist_x = fabs(data->hi_x / cos(fabs(data->ray_angle)));
		data->direction_x = 1;
	}
	if (data->quadrant == 4 || data->quadrant == 3)
	{
		data->sidedist_y = fabs(data->lo_y / sin(fabs(data->ray_angle)));
		data->direction_y = -1;
	}
	else if (data->quadrant == 1 || data->quadrant == 2)
	{
		data->sidedist_y = fabs(data->hi_y / sin(fabs(data->ray_angle)));
		data->direction_y = 1;
	}
}
