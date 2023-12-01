/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:48:50 by msulc             #+#    #+#             */
/*   Updated: 2023/10/30 12:48:52 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	move_forward(t_data *data)//pohyb dopredu
{
	double	old_x;
	double	old_y;

	old_x = data->pos_x;//aktualni poloha - souradnice
	old_y = data->pos_y;
	data->pos_x = data->pos_x - (data->move_speed * cos(data->actual_angle));//vypocet nove polohy
	data->pos_y = data->pos_y - (data->move_speed * sin(data->actual_angle));
	if (data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')//neumozni projit zdi
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return ;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';//pole ve kterem jsem byl ma hodnotu 0
	count_lo_hi(data);//prepocita nove vzdalenosti k hranicim policka
	new_obraz(data);//vykresli nove okno
}

void	move_back(t_data *data)
{
	double	old_x;
	double	old_y;

	old_x = data->pos_x;
	old_y = data->pos_y;
	data->pos_x = data->pos_x + (data->move_speed * cos(data->actual_angle));
	data->pos_y = data->pos_y + (data->move_speed * sin(data->actual_angle));
	if (data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return ;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	count_lo_hi(data);
	new_obraz(data);
}

void	move_left(t_data *data)
{
	double	old_x;
	double	old_y;

	old_x = data->pos_x;
	old_y = data->pos_y;
	data->pos_x = data->pos_x + (data->move_speed
			* cos(data->actual_angle - (M_PI / 2)));
	data->pos_y = data->pos_y + (data->move_speed
			* sin(data->actual_angle - (M_PI / 2)));
	if (data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return ;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	count_lo_hi(data);
	new_obraz(data);
}

void	move_right(t_data *data)
{
	double	old_x;
	double	old_y;

	old_x = data->pos_x;
	old_y = data->pos_y;
	data->pos_x = data->pos_x + (data->move_speed
			* cos(data->actual_angle + (M_PI / 2)));
	data->pos_y = data->pos_y + (data->move_speed
			* sin(data->actual_angle + (M_PI / 2)));
	if (data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return ;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	count_lo_hi(data);
	new_obraz(data);
}
