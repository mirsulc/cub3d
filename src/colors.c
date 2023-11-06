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

COLOR	ml_color_at(mlx_image_t *img, int x, int y)
{
	COLOR	*pixel;

	if (x >= img->width)
		x = img->width - 1;
	if (y >= img->height)
		y = img->height - 1;
	pixel = (COLOR *)(img->pixels + (x + y * img->width) * sizeof(COLOR));
//	ft_printf("barva:, %u\n", pixel);
	return (*pixel);
}

uint32_t	convert_colors(char *str)
{
	char	**rgb;
	uint32_t		res;

	rgb = ft_split(str, ',');

	res = 0;
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
