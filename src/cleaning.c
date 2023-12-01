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

void	semi_cleaning(t_map *map, char **cont)//cisti alokovanou pamet po puvodni mape
{
	int	i;
	int	con;

	con = 0;
	while (map->grid[con])
		con++;
	i = 0;
	while (i < con)
	{
		free(map->grid[i]);
		map->grid[i] = NULL;
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

void	map_cleaning(t_map *map)//cisti polozky, pro ktere jsme alokovali pamet
{
	int	i;	

	i = -1;
	free(map->s_id);
	free(map->w_id);
	free(map->n_id);
	free(map->e_id);
	free(map->c_id);
	free(map->f_id);
	while (++i < map->height)
		free(map->grid[i]);
	free(map->grid);
}

void	cleaning(t_data *data)//odstranuje textury z MLX
{
	mlx_delete_texture(data->s_t);
	mlx_delete_texture(data->n_t);
	mlx_delete_texture(data->w_t);
	mlx_delete_texture(data->e_t);
	mlx_delete_image(data->mlx, data->obr);
	mlx_terminate(data->mlx);
	exit(0);
}

char	*ft_strdup_cub(const char *s)//kopiruje adresy textur ze souboru
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

void	closeit(void *data)//stara se o ukonceni programu krizkem
{
	t_data	*d;
	mlx_t	*mlx;

	d = data;
	mlx = d->mlx;
	cleaning(d);
}
