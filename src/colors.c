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
