/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaning.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:57:39 by msulc             #+#    #+#             */
/*   Updated: 2023/10/19 13:57:41 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	semi_cleaning(t_map *map, char **cont)
{
	int	i;

	i = 0;
	while (i < map->height)
	{
		free(map->grid[i]);
		i++;
	}
	i = -1;
	while (++i < map->height)
		map->grid[i] = strdup(cont[i]);
	i = -1;
	while (++i < map->height)
		free(cont[i]);
	free(cont);
}

void	map_cleaning(t_map *map)
{
	int	i;	

	i = -1;
	free((char *)map->s_id);
	free((char *)map->w_id);
	free((char *)map->n_id);
	free((char *)map->e_id);
	free((char *)map->c_id);
	free((char *)map->f_id);
	while (++i < map->height)
		free(map->grid[i]);
	free(map->grid);
}

void	cleaning(t_data *data)
{
	mlx_delete_texture(data->s_t);
	mlx_delete_texture(data->n_t);
	mlx_delete_texture(data->w_t);
	mlx_delete_texture(data->e_t);
	mlx_delete_image(data->mlx, data->obr);
	mlx_terminate(data->mlx);
	exit(0);
}

char	*ft_strdup_cub(const char *s)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	dst = (char *)malloc((i + 1) * sizeof(char));
	if (!dst)
		return (0);
	j = 0;
	while (j < i)
	{
		dst[j] = s[j];
		j++;
	}
	dst[j] = '\0';
	return (dst);
}

void	closeit(void *data)
{
	t_data	*d;
	mlx_t	*mlx;

	d = data;
	mlx = d->mlx;
	cleaning(d);
}
