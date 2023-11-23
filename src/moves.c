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

void	move_forward(t_data *data)
{
//	printf("pocatecni pozice x: %f y: %f\n", data->pos_x, data->pos_y);
	double	old_x;
	double	old_y;
	
	old_x = data->pos_x;
	old_y = data->pos_y;
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	data->pos_x = data->pos_x - (data->move_speed * cos(data->actual_angle));
	data->pos_y = data->pos_y - (data->move_speed * sin(data->actual_angle));
//	printf("po pohybu pozice x: %f y: %f\n", data->pos_x, data->pos_y);
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	if(data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	data->mapa.grid[(int)data->pos_x][(int)data->pos_y] = 'X';	//odstranit
//	prekresli_mapu(data);
	count_lo_hi(data);
	new_obraz(data);
//	printf("lo_x: %f, lo_y: %f, hi_x: %f, hi_y:%f\n", data->lo_x, data->lo_y, data->hi_x, data->hi_y);
}

void	move_back(t_data *data)
{
//	printf("pocatecni pozice x: %f y: %f\n", data->pos_x, data->pos_y);
	double	old_x;
	double	old_y;
	
	old_x = data->pos_x;
	old_y = data->pos_y;
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	data->pos_x = data->pos_x + (data->move_speed * cos(data->actual_angle));
	data->pos_y = data->pos_y + (data->move_speed * sin(data->actual_angle));
//	printf("po pohybu pozice x: %f y: %f\n", data->pos_x, data->pos_y);
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	if(data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	data->mapa.grid[(int)data->pos_x][(int)data->pos_y] = 'X';
//	prekresli_mapu(data);
	count_lo_hi(data);
	new_obraz(data);
}
void	move_left(t_data *data)
{
//	printf("pocatecni pozice x: %f y: %f\n", data->pos_x, data->pos_y);
	double	old_x;
	double	old_y;
	
	old_x = data->pos_x;
	old_y = data->pos_y;
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	data->pos_x = data->pos_x + (data->move_speed * cos(data->actual_angle - (M_PI / 2)));
	data->pos_y = data->pos_y + (data->move_speed * sin(data->actual_angle - (M_PI / 2)));
//	printf("po pohybu pozice x: %f y: %f\n", data->pos_x, data->pos_y);
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	if(data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	data->mapa.grid[(int)data->pos_x][(int)data->pos_y] = 'X';
//	prekresli_mapu(data);
	count_lo_hi(data);
	new_obraz(data);
}
void	move_right(t_data *data)
{
//	printf("pocatecni pozice x: %f y: %f\n", data->pos_x, data->pos_y);
	double	old_x;
	double	old_y;
	
	old_x = data->pos_x;
	old_y = data->pos_y;
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
	data->pos_x = data->pos_x + (data->move_speed * cos(data->actual_angle + (M_PI / 2)));
	data->pos_y = data->pos_y + (data->move_speed * sin(data->actual_angle + (M_PI / 2)));
//	printf("po pohybu pozice x: %f y: %f\n", data->pos_x, data->pos_y);
//	ft_printf("policko v gridu: %c\n", data->mapa.grid[(int)data->pos_x][(int)data->pos_y]);
//	double	pokus = ceil(data->pos_x);
//	printf("pokus zaokrouhleny data->pos_x: %f\n", pokus);
	if(data->mapa.grid[(int)data->pos_x][(int)data->pos_y] == '1')
	{
		data->pos_x = old_x;
		data->pos_y = old_y;
		return;
	}
	data->mapa.grid[(int)old_x][(int)old_y] = '0';
	data->mapa.grid[(int)data->pos_x][(int)data->pos_y] = 'X';
//	prekresli_mapu(data);
	count_lo_hi(data);
	new_obraz(data);
}
void	turn_right(t_data *data)
{
//	printf("uhel pred otocenim %f\n", data->actual_angle);
	data->actual_angle = data->actual_angle - data->rot_speed;
	if(data->actual_angle <= (-2 * M_PI))
		data->actual_angle = data->actual_angle + (2 * M_PI);
//	printf("uhel po otoceni %f\n", data->actual_angle);
	new_obraz(data);
}
void	turn_left(t_data *data)
{
//	printf("uhel pred otocenim %f\n", data->actual_angle);
	data->actual_angle = data->actual_angle + data->rot_speed;
	if(data->actual_angle >= (2 * M_PI))
		data->actual_angle = data->actual_angle - (2 * M_PI);
//	printf("uhel po otoceni %f\n", data->actual_angle);
	new_obraz(data);
}

void	new_obraz(t_data *data)
{
	int	i = 0;
	int	x = 0;
	mlx_delete_image(data->mlx, data->obr);
		data->obr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	while(x < WIDTH)
	{
		data->ray_angle = data->actual_angle - (M_PI / 4) + ((M_PI / 2) / WIDTH * x);
//		printf("data->ray_angle: %f\n", data->ray_angle);
		if(data->ray_angle >= (2 * M_PI))
			data->ray_angle = data->ray_angle - (2 * M_PI);
		else if(data->ray_angle <= (-2 * M_PI))
			data->ray_angle = data->ray_angle + (2 * M_PI);
		count_quadrant(data);
		calculate_sidedist(data);
		looking_for_wals(data);
		calculate_height(data);
		i = data->drawstart;
		data->actual_texture = choose_texture(data);
		data->texture_x = count_x_of_texture(data);
//		ft_printf("data->texture_x: %d\n", data->texture_x);
//		ft_printf("data->line_height: %d\n", data->line_height);
//		ft_printf("data->texture_x: %d\n", data->texture_x);
		while(i <= data->drawend )
		{
//			if(i % 100 == 0)
//				printf("data->tex_point_ratio: %f\n", data->tex_point_ratio);
			data->texture_y = (int)(data->texture_start + ((i - data->drawstart) / data->tex_point_ratio));
//			ft_printf("data->texture_y: %d\n", data->texture_y);
			if(data->texture_y >= data->actual_texture->height)
				data->texture_y = data->actual_texture->height - 1;
//			printf("data->texture_start: %f\n", data->texture_start);
//			if(i % 100 == 0)
//			{
//				printf("data->texture_start: %f\n", data->texture_start);
//				printf("data->tex_point_ratio: %f\n", data->tex_point_ratio);
//				ft_printf("i: %d\n", i);
//				ft_printf("data->drawend: %d\n", data->drawend);
//				ft_printf("data->texture_y: %d\n", data->texture_y);
//			}
			mlx_put_pixel(data->obr, x, i, color(data));
			i++;
		}
		x++;
	}
	mlx_image_to_window(data->mlx, data->obr, 0, 0);
}
	


void	prekresli_mapu(t_data *data)
{
	int	i = 0;
	int	y = 0;
	
	while(i < data->mapa.height)
	{
		ft_printf("%s\n", data->mapa.grid[i]);
		i++;
	}
}
	
