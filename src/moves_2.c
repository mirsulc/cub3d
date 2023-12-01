/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:19:06 by msulc             #+#    #+#             */
/*   Updated: 2023/11/27 13:19:08 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	turn_right(t_data *data)
{
	data->actual_angle = data->actual_angle - data->rot_speed;//prepocita uhel pohledu
	if (data->actual_angle <= (-2 * M_PI))//zajistuje uhel v hranicich 0 - 2M_PI(pi)
		data->actual_angle = data->actual_angle + (2 * M_PI);
	new_obraz(data);
}

void	turn_left(t_data *data)
{
	data->actual_angle = data->actual_angle + data->rot_speed;
	if (data->actual_angle >= (2 * M_PI))
		data->actual_angle = data->actual_angle - (2 * M_PI);
	new_obraz(data);
}

void	new_obraz(t_data *data)//vykresluje nove okno po kazdem pohybu
{
	int	i;
	int	x;

	mlx_delete_image(data->mlx, data->obr);
	data->obr = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	i = 0;
	x = 0;
	while (x < WIDTH)
	{
		new_obraz_ext(data, x);//x oznacuje kazdy sloupec v obraze
		i = data->drawstart;
		while (i <= data->drawend)//urcuje odkud vykreslujeme texturu a vklada pixely do okna
		{
			data->texture_y = (int)(data->texture_start
					+ ((i - data->drawstart) / data->tex_point_ratio));
			if (data->texture_y >= data->actual_texture->height)
				data->texture_y = data->actual_texture->height - 1;
			mlx_put_pixel(data->obr, x, i, color(data));
			i++;
		}
		x++;
	}
	mlx_image_to_window(data->mlx, data->obr, 0, 0);
}

void	new_obraz_ext(t_data *data, int x)//pocitame potrebne udaje pro kazdy sloupec 
{
	data->ray_angle = data->actual_angle
		- (M_PI / 6) + ((M_PI / 3) / WIDTH * x);
	if (data->ray_angle >= (2 * M_PI))
		data->ray_angle = data->ray_angle - (2 * M_PI);
	else if (data->ray_angle <= (-2 * M_PI))
		data->ray_angle = data->ray_angle + (2 * M_PI);
	count_quadrant(data);//do ktereho kvadrantu se divame
	calculate_sidedist(data);//vzdalenost k nejblizsim osam/hranicim pole ve kterem jsme 
	looking_for_wals(data);//jak daleko je to k nejblizsi zdi a jaka je to zed(x/y)
	calculate_height(data);//pocitame vysku kazdeho 
	data->actual_texture = choose_texture(data);
	data->texture_x = count_x_of_texture(data);
}
