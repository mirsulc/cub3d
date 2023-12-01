/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 10:42:21 by msulc             #+#    #+#             */
/*   Updated: 2023/11/27 10:42:27 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

mlx_texture_t	*choose_texture(t_data *data)//vybirame texturu na kereou paprsek hledi
{
	if ((data->quadrant == 1 || data->quadrant == 4) && data->x_or_y == 'x')
		return (data->n_t);
	else if ((data->quadrant == 1 || data->quadrant == 2)
		&& data->x_or_y == 'y')
		return (data->s_t);
	else if ((data->quadrant == 2 || data->quadrant == 3)
		&& data->x_or_y == 'x')
		return (data->e_t);
	else if ((data->quadrant == 3 || data->quadrant == 4)
		&& data->x_or_y == 'y')
		return (data->w_t);
}

void	count_texture_coordinates(t_data *data, int temp)//pocita podklady pro urceni pixelu textury
{
	double				ratio;
	mlx_texture_t		*textura;

	textura = choose_texture(data);
	if (temp <= HEIGHT)
	{
		data->texture_start = 0;
		data->texture_end = textura->height;
		data->texture_range = data->texture_end - data->texture_start;
	}
	else
	{
		ratio = (double)HEIGHT / (double)temp;
		data->texture_range = textura->height * ratio;
		data->texture_start = (textura->height - data->texture_range) / 2;
		data->texture_end = textura->height - data->texture_start;
	}
	data->tex_point_ratio = data->line_height / data->texture_range;
}

int	count_x_of_texture(t_data *data)//pocita x souradnici pixelu textury
{
	double	temp;

	temp = 0;
	if ((data->quadrant == 1 || data->quadrant == 2) && data->x_or_y == 'x')
		return (count_x_1(data));
	else if ((data->quadrant == 3
			|| data->quadrant == 4) && data->x_or_y == 'x')
		return (count_x_2(data));
	else if ((data->quadrant == 1
			|| data->quadrant == 4) && data->x_or_y == 'y')
	{
		temp = fabs((cos(fabs(data->ray_angle))
					* data->distance_to_wall)) - data->lo_x;
		temp = temp - floor(temp);
		return ((int)(data->actual_texture->width * temp));
	}
	else if ((data->quadrant == 2
			|| data->quadrant == 3) && data->x_or_y == 'y')
	{
		temp = fabs((cos(fabs(data->ray_angle))
					* data->distance_to_wall)) - data->hi_x;
		temp = temp - floor(temp);
		return ((int)(data->actual_texture->width * (1 - temp)));
	}
	return (0);
}

int	count_x_1(t_data *data)//pocita osovou vzdalenost k bodu na kterz hledime a vypocitava zbytek
{
	double	temp;

	temp = 0;
	temp = fabs((sin(fabs(data->ray_angle))
				* data->distance_to_wall)) - data->hi_y;
	temp = temp - floor(temp);
	return ((int)(data->actual_texture->width * (1 - temp)));
}

int	count_x_2(t_data *data)
{
	double	temp;

	temp = 0;
	temp = fabs((sin(fabs(data->ray_angle))
				* data->distance_to_wall)) - data->lo_y;
	temp = temp - floor(temp);
	return ((int)(data->actual_texture->width * temp));
}
