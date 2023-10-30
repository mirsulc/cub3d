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
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_up(data);
/*	if (keydata.key == MLX_KEY_S && keydata.action == MLX_PRESS)
		move_down(game);
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		move_left(game);
	if (keydata.key == MLX_KEY_D && keydata.action == MLX_PRESS)
		move_right(game);*/
}

uint32_t	convert_colors(char *str)
{
	char	**rgb;
	uint32_t		res;

	rgb = ft_split(str, ',');

	res += ft_atoi(rgb[0]) << 24;
	res += ft_atoi(rgb[1]) << 16;
	res += ft_atoi(rgb[2]) << 8;
	res += 255;

	free_arrays(rgb);
	return (res);
}

void	free_arrays(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array[i]);
	free(array);
}


int	game_start(t_map *map)	
{
	int	x = 0;
	int	i = 0;
	t_data	data;
	t_raycast	ray;
	mlx_image_t	*img;

	data.mapa = map;
	raycast_init(&ray, map);
//	data.ray = ray;
	data_init(&data);
	setting_starting_angle(map, &ray);	//prirazujeme startovni pozici vychozi uhel
	printf("ray.init_angle: %f\n", ray.init_angle);
	data.mlx = mlx_init(WIDTH, HEIGHT, "cube3D", 0);
	if (!data.mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	data.img_t = mlx_load_png("include/head.png");
	data.img2 = mlx_texture_to_image(data.mlx, data.img_t);

	mlx_delete_texture(data.img_t);
	img = mlx_new_image(data.mlx, 400, 300);
//	data.img2 = mlx_new_image(data.mlx, WIDTH, HEIGHT);
//	memset(img->pixels, 255, img->width * img->height * sizeof(int32_t));
//	data->address = (int *)mlx_get_data_addr(data->img, &game->bits_per_pixel,
//			&game->line_length, &game->endian);
	mlx_resize_image(img, WIDTH, HEIGHT);
//	data.img2 = mlx_new_image(data.mlx, 0, 0);
	mlx_resize_image(data.img2, 300, 300);
//	data.ceiling = ml_color_at(data.img2, 200, 200);
//	ft_printf("barva z textury: %d\n", data.ceiling);
	ft_printf("barvvaaaaa: %d\n", data.floor);
	while(x < HEIGHT/2)
	{
		i = 0;
		
		while(i < (WIDTH - (x*2)))
		{
			mlx_put_pixel(img, i, x, data.ceiling);
			i += 1;
		}
		x += 1;
	}
	while(x < HEIGHT)
	{
		i = 0;
		
		while(i < (WIDTH))
		{
			mlx_put_pixel(img, i, x, data.floor);
			i += 1;
		}
		x += 1;
	}
	mlx_image_to_window(data.mlx, data.img2, 0, 0);
	mlx_image_to_window(data.mlx, img, 100, 20);
	mlx_key_hook(data.mlx, &key_hook, &data);
	mlx_loop(data.mlx);
	mlx_terminate(data.mlx);
//	data_init(data);
//	ft_printf("         pokus: %d\n", data.mapa->lenght);
	return (EXIT_SUCCESS);
}

void	data_init(t_data *data)
{
	data->floor = convert_colors(data->mapa->F_id);
//	data->cok = NULL;
	ft_printf("                barva stropu: %d\n", data->floor);
	data->ceiling = convert_colors(data->mapa->C_id);
	
}

void	raycast_init(t_raycast *ray, t_map *map)
{
	ray->rot_speed = M_PI / 6;
	ray->init_angle = 0;
	ray->actual_angle = 0;
	ray->move_speed = 0.5;
	ray->init_pos_x = 0;
	ray->init_pos_y = 0;
	ray->pos_x = 0;
	ray->pos_y = 0;
}

void	setting_starting_angle(t_map *map, t_raycast *ray) //urcujeme vychozi uhel pohledu hrace
{
	ft_printf("map->starting_angle: %c\n", map->starting_angle);
	if(map->starting_angle == 'N')
		ray->init_angle = 0;
	else if(map->starting_angle == 'E')
		ray->init_angle = M_PI / 2;
	else if(map->starting_angle == 'S')
		ray->init_angle = M_PI;
	else if(map->starting_angle == 'W')
		ray->init_angle = M_PI * 1.5;
	printf("ray->init_angle    1    : %f\n", ray->init_angle);
	printf("sinus ray->init_angle: %f\n", sin(ray->init_angle));
}
		
