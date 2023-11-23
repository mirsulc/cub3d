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

void	count_lo_hi(t_data *data)	//prepocitava koordinaty/presnou pozici v poli aktualni pozice
{
	data->lo_x = data->pos_x - floor(data->pos_x);
	data->lo_y = data->pos_y - floor(data->pos_y);
	data->hi_x = ceil(data->pos_x) - data->pos_x;
	data->hi_y = ceil(data->pos_y) - data->pos_y;
}

void	count_quadrant(t_data *data)	//pocita do jakeho kvadrantu se diva kazdy paprsek 
{
//	data->ray_angle = data->actual_angle;		//odstranit po zprovozneni raycastingu 
	if((data->ray_angle <= 0 && data->ray_angle > (-M_PI / 2))
		|| (data->ray_angle > (M_PI * 1.5) && data->ray_angle <= (M_PI * 2)))
		data->quadrant = 1;
	else if((data->ray_angle <= (-M_PI / 2) && data->ray_angle > (-M_PI))
		|| (data->ray_angle > M_PI && data->ray_angle <= (M_PI * 1.5)))
		data->quadrant = 2;
	else if((data->ray_angle <= (-M_PI) && data->ray_angle > (M_PI * -1.5))
		|| (data->ray_angle > (M_PI / 2) && data->ray_angle <= M_PI))
		data->quadrant = 3;
	else if((data->ray_angle <= (M_PI * -1.5) && data->ray_angle > (M_PI * -2))
		|| (data->ray_angle > 0 && data->ray_angle <= (M_PI / 2)))
		data->quadrant = 4;
}

void	looking_for_wals(t_data *data)	//hledame zed a znacime, jestli je na X nebo Y hranici
{
	data->wall = 0;
	data->map_x = (int)data->pos_x;
	data->map_y = (int)data->pos_y;
	while(data->wall == 0)
	{
		if(data->sidedist_x < data->sidedist_y)
		{
			data->sidedist_x += data->deltadist_x;
			data->map_x += data->direction_x;
			data->x_or_y = 'x';
		}
		else
		{
			data->sidedist_y += data->deltadist_y;
			data->map_y += data->direction_y;
			data->x_or_y = 'y';
		}
		if(data->mapa.grid[data->map_x][data->map_y] == '1')
			data->wall = 1;
	}
	if(data->x_or_y == 'x')
		data->distance_to_wall = data->sidedist_x - data->deltadist_x;
	else
		data->distance_to_wall = data->sidedist_y - data->deltadist_y;
}

void	calculate_height(t_data *data)	//pocitame vysku vykresleneho sloupce a 1.a posledni bod 
{

	int	temp;
//	printf("data->distance_to_wall: %f, data->x_or_y: %c\n", data->distance_to_wall, data->x_or_y);
	data->line_height = (int)(HEIGHT / (data->distance_to_wall * cos((data->actual_angle) - data->ray_angle)));
//	ft_printf("data->line_height: %d\n", data->line_height);
	temp = data->line_height;
	if(data->line_height > HEIGHT)
		data->line_height = HEIGHT;
	count_texture_coordinates(data, temp);
	data->drawstart = -data->line_height / 2 + HEIGHT / 2;
	data->drawend = data->line_height / 2 + HEIGHT /2;
	if(data->drawstart < 0)
		data->drawstart = 0;
	if(data->drawend < 0 || data->drawend >= HEIGHT)
		data->drawend = HEIGHT - 1;
//	ft_printf("vyska sloupce: %d,  drawstart: %d, drawend: %d\n", data->line_height, data->drawstart, data->drawend);
}
		
void	calculate_sidedist(t_data *data)	//pocitame vydalenost paprsku k nejblizsi hranici X/Y
{
	data->deltadist_x = 1 / fabs(cos(fabs(data->ray_angle)));
	data->deltadist_y = 1 / fabs(sin(fabs(data->ray_angle)));
	if(data->quadrant == 1 || data->quadrant == 4)
	{
		data->direction_x = -1;
		data->sidedist_x = fabs(data->lo_x / cos(fabs(data->ray_angle)));
	}
	else if(data->quadrant == 2 || data->quadrant == 3)
	{
		data->sidedist_x = fabs(data->hi_x / cos(fabs(data->ray_angle)));
		data->direction_x = 1;
	}
	if(data->quadrant == 4 || data->quadrant == 3)
	{
		data->sidedist_y = fabs(data->lo_y / sin(fabs(data->ray_angle)));
		data->direction_y = -1;
	}
	else if(data->quadrant == 1 || data->quadrant == 2)
	{
		data->sidedist_y = fabs(data->hi_y / sin(fabs(data->ray_angle)));
		data->direction_y = 1;
	}
//	ft_printf("data->quadrant: %d\n", data->quadrant);
//	printf("data->sidedist_x: %f\n", data->sidedist_x);
//	printf("data->sidedist_y: %f\n", data->sidedist_y);
//	printf("data->deltadist_x: %f\n", data->deltadist_x);
//	printf("data->deltadist_y: %f\n", data->deltadist_y);
}

uint32_t	color(t_data *data)
{
	if((data->quadrant == 1 || data->quadrant == 4) && data->x_or_y == 'x')
		return(convert_colors_2(data->n_t, data->texture_x, data->texture_y));		
	else if((data->quadrant == 1 || data->quadrant == 2) && data->x_or_y == 'y')
		return(convert_colors_2(data->s_t, data->texture_x, data->texture_y));
	else if((data->quadrant == 2 || data->quadrant == 3) && data->x_or_y == 'x')
		return(convert_colors_2(data->e_t, data->texture_x, data->texture_y));
	else if((data->quadrant == 3 || data->quadrant == 4) && data->x_or_y == 'y')
		return(convert_colors_2(data->w_t, data->texture_x, data->texture_y));
}

mlx_texture_t	*choose_texture(t_data *data)	//kterou texturu vykreslujeme
{
	if((data->quadrant == 1 || data->quadrant == 4) && data->x_or_y == 'x')
		return(data->n_t);		
	else if((data->quadrant == 1 || data->quadrant == 2) && data->x_or_y == 'y')
		return(data->s_t);
	else if((data->quadrant == 2 || data->quadrant == 3) && data->x_or_y == 'x')
		return(data->e_t);
	else if((data->quadrant == 3 || data->quadrant == 4) && data->x_or_y == 'y')
		return(data->w_t);
}

void	count_texture_coordinates(t_data *data, int temp)	//pocitame vyskovy rozsah zobrazene texturyy
{
	double	ratio;
	mlx_texture_t	*textura;

	textura = choose_texture(data);
//	printf("jaka textura: %d\n", textura->height);
	if(temp <= HEIGHT)
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
//	printf("data->texture_range: %f\n", data->texture_range);
//	printf("data->texture_range: %f\n", data->texture_range);
	data->tex_point_ratio = data->line_height / data->texture_range;
}

int	count_x_of_texture(t_data *data)	//pocitame ve kterem miste presne narazime na zed
{
	double	temp;
	
	temp = 0;
	if((data->quadrant == 1 || data->quadrant == 2) && data->x_or_y == 'x')
	{
		temp = fabs((sin(fabs(data->ray_angle)) * data->distance_to_wall)) - data->hi_y;
		temp = temp - floor(temp);
		return((int)(data->actual_texture->width * (1 - temp)));
	}
	else if((data->quadrant == 3 || data->quadrant == 4) && data->x_or_y == 'x')
	{
		temp = fabs((sin(fabs(data->ray_angle)) * data->distance_to_wall)) - data->lo_y;
		temp = temp - floor(temp);
		return((int)(data->actual_texture->width * temp));
	}
	else if((data->quadrant == 1 || data->quadrant == 4) && data->x_or_y == 'y')
	{
		temp = fabs((cos(fabs(data->ray_angle)) * data->distance_to_wall)) - data->lo_x;
		temp = temp - floor(temp);
		return((int)(data->actual_texture->width * temp));
	}
	else if((data->quadrant == 2 || data->quadrant == 3) && data->x_or_y == 'y')
	{
		temp = fabs((cos(fabs(data->ray_angle)) * data->distance_to_wall)) - data->hi_x;
		temp = temp - floor(temp);
		return((int)(data->actual_texture->width * (1 - temp)));
	}
	return 0;
}
