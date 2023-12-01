/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:14:33 by msulc             #+#    #+#             */
/*   Updated: 2023/10/26 14:14:35 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

COLOR	ml_color_at(mlx_texture_t *img, int x, int y)
{
	COLOR	*pixel;

	if (x >= img->width)
		x = img->width - 1;
	if (y >= img->height)
		y = img->height - 1;
	pixel = (COLOR *)&img->pixels[(x + y * img->width) * sizeof(COLOR)];
	return (*pixel);
}

uint32_t	convert_colors(char *str)//prevadi barvy podlahy a stropu ze souboru mapy
{
	char		**rgb;
	uint32_t	res;

	rgb = ft_split(str, ',');
	res = 0;
	res += ft_atoi(rgb[0]) << 24;
	res += ft_atoi(rgb[1]) << 16;
	res += ft_atoi(rgb[2]) << 8;
	res += 255;
	free_arrays(rgb);
	return (res);
}

uint32_t	convert_colors_2(mlx_texture_t *img, int x, int y)//prevadi barvu z pixelu textury
{
	COLOR		*pixel;
	uint32_t	res;

	pixel = (COLOR *)(img->pixels + (x + y * img->width) * 4);
	res = 0;
	res += pixel[0] << 24;
	res += pixel[1] << 16;
	res += pixel[2] << 8;
	res += pixel[3];
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

uint32_t	color(t_data *data)//vola funkci, ktera prevadi barvy z textury podle smeru pohledu 
{
	if ((data->quadrant == 1 || data->quadrant == 4) && data->x_or_y == 'x')
		return (convert_colors_2(data->n_t, data->texture_x, data->texture_y));
	else if ((data->quadrant == 1
			|| data->quadrant == 2) && data->x_or_y == 'y')
		return (convert_colors_2(data->s_t, data->texture_x, data->texture_y));
	else if ((data->quadrant == 2
			|| data->quadrant == 3) && data->x_or_y == 'x')
		return (convert_colors_2(data->e_t, data->texture_x, data->texture_y));
	else if ((data->quadrant == 3
			|| data->quadrant == 4) && data->x_or_y == 'y')
		return (convert_colors_2(data->w_t, data->texture_x, data->texture_y));
}
