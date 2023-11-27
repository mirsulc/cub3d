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
		cleaning(data);
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
	mlx_image_t	*img;

	data_init(data);
	setting_starting_angle(data);
	data->mlx = mlx_init(WIDTH, HEIGHT, "cube3D", 0);
	if (!data->mlx)
	{
		puts(mlx_strerror(mlx_errno));
		return (EXIT_FAILURE);
	}
	data->n_t = mlx_load_png(data->mapa.n_id);
	data->e_t = mlx_load_png(data->mapa.e_id);
	data->s_t = mlx_load_png(data->mapa.s_id);
	data->w_t = mlx_load_png(data->mapa.w_id);
	if (!data->n_t || !data->e_t || !data->s_t || !data->w_t)
		error_function(1);
	img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	game_start_ext(data, img);
	mlx_image_to_window(data->mlx, img, 0, 0);
	move_forward(data);
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_close_hook(data->mlx, closeit, data);
	mlx_loop(data->mlx);
	return (EXIT_SUCCESS);
}

void	game_start_ext(t_data *data, mlx_image_t *img)
{
	int	x;
	int	i;

	x = 0;
	while (x < HEIGHT / 2)
	{
		i = 0;
		while (i < WIDTH)
		{
			mlx_put_pixel(img, i, x, data->ceiling);
			i++;
		}
		x++;
	}
	while (x < HEIGHT)
	{
		i = 0;
		while (i < WIDTH)
		{
			mlx_put_pixel(img, i, x, data->floor);
			i++;
		}
		x++;
	}
}

void	data_init(t_data *data)
{
	data->obr = NULL;
	data->floor = convert_colors(data->mapa.f_id);
	data->ceiling = convert_colors(data->mapa.c_id);
	data->rot_speed = M_PI / 24;
	data->init_angle = 0;
	data->ray_angle = 0;
	data->actual_angle = 0;
	data->move_speed = 0.2;
	data->init_pos_x = data->mapa.char_pos_y;
	data->init_pos_y = data->mapa.char_pos_x;
	data->pos_x = (double)data->init_pos_x + 0.5;
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

void	setting_starting_angle(t_data *data)
{
	if (data->mapa.starting_angle == 'N')
		data->init_angle = 0;
	else if (data->mapa.starting_angle == 'E')
		data->init_angle = M_PI * 1.5;
	else if (data->mapa.starting_angle == 'S')
		data->init_angle = M_PI;
	else if (data->mapa.starting_angle == 'W')
		data->init_angle = M_PI / 2;
	data->actual_angle = data->init_angle;
}
