/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 10:37:13 by msulc             #+#    #+#             */
/*   Updated: 2023/10/20 10:37:14 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

static void	key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = param;

	
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(1);
	if (keydata.key == MLX_KEY_W && keydata.action == MLX_PRESS)
		move_forward(data);
	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_back(data);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_left(data);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_right(data);
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
		turn_left(data);
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
		turn_right(data);
}



int	game_start(t_data *data)	
{
	
	int	x = 0;
	int	i = 0;
//	t_data	data;

	mlx_image_t	*img;


	data_init(data);
//	ft_printf("kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk\n");
	setting_starting_angle(data);	//prirazujeme startovni pozici vychozi uhel
//	printf("data->init_angle 55555: %f\n", data->init_angle);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cube3D", 0);
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	data->img_t = mlx_load_png("include/head.png");
	data->img2 = mlx_texture_to_image(data->mlx, data->img_t);

	mlx_delete_texture(data->img_t);
	img = mlx_new_image(data->mlx, 400, 300);
//	data.img2 = mlx_new_image(data.mlx, WIDTH, HEIGHT);
//	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
//	data->address = (int *)mlx_get_data_addr(data->img, &game->bits_per_pixel,
//			&game->line_length, &game->endian);
	mlx_resize_image(img, WIDTH, HEIGHT);
//	data.img2 = mlx_new_image(data.mlx, 0, 0);
	mlx_resize_image(data->img2, WIDTH, HEIGHT / 2);
//	data.ceiling = ml_color_at(data.img2, 200, 200);
//	ft_printf("barva z textury: %d\n", data.ceiling);
	while(x < HEIGHT/2)
	{
		i = 0;
		
		while(i < WIDTH)
		{
			mlx_put_pixel(img, i, x, data->ceiling);
			i++;
		}
		x++;
	}
	while(x < HEIGHT)
	{
		i = 0;
		
		while(i < WIDTH)
		{
			mlx_put_pixel(img, i, x, data->floor);
			i++;
		}
		x++;
	}
	mlx_image_to_window(data->mlx, img, 0, 0);
	mlx_image_to_window(data->mlx, data->img2, 0, 0);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
//	data_init(data);
//	ft_printf("         pokus: %d\n", data.mapa->lenght);
	return (EXIT_SUCCESS);
}

void	data_init(t_data *data)
{
	data->floor = convert_colors(data->mapa.F_id);
	data->ceiling = convert_colors(data->mapa.C_id);
	data->rot_speed = M_PI / 24;
	data->init_angle = 0;
	data->ray_angle = 0;
	data->actual_angle = 0;
	data->move_speed = 0.2;
	data->init_pos_x = data->mapa.char_pos_y;
//	ft_printf("kontrola z init  mapa.char_pos_y: %d\n", data->mapa.char_pos_y);
	data->init_pos_y = data->mapa.char_pos_x;
	data->pos_x = (double)data->init_pos_x + 0.5;
//	printf("kontrola z init  pos_x: %f\n", data->pos_x);
	data->pos_y = (double)data->init_pos_y + 0.5;
	data->lo_x = data->pos_x - (double)floor(data->pos_x);
	data->lo_y = data->pos_y - (double)floor(data->pos_y);
	data->hi_x = (double)ceil(data->pos_x) - data->pos_x;
	data->hi_y = (double)ceil(data->pos_y) - data->pos_y;
	data->quadrant = 0;
	data->wall = 0;
	data->x_or_y = 'n';
	data->map_y = 0;
	data->map_x = 0;
	data->i = 0;
	data->line_height = 0;
	data->drawstart = 0;
	data->drawend = 0;
}



void	setting_starting_angle(t_data *data) //urcujeme vychozi uhel pohledu hrace
{
	if(data->mapa.starting_angle == 'N')
		data->init_angle = 0;
	else if(data->mapa.starting_angle == 'E')
		data->init_angle = M_PI * 1.5;
	else if(data->mapa.starting_angle == 'S')
		data->init_angle = M_PI;
	else if(data->mapa.starting_angle == 'W')
		data->init_angle = M_PI / 2;
	printf("data->ray.init_angle: %f\n", data->init_angle);
	printf("sinus data->ray.init_angle: %f\n", sin(data->init_angle));
	data->actual_angle = data->init_angle;
}
		
