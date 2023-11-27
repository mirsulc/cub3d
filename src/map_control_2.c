/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 13:55:03 by msulc             #+#    #+#             */
/*   Updated: 2023/10/19 13:55:04 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_consistence_control_5(t_map *map, int y)
{
	int	i;
	int	con;

	con = y;
	while (map->grid[con])
	{
		i = 0;
		while (map->grid[con][i])
			i++;
		while (i > 0)
		{
			if (map->grid[con][i] > 32)
			{
				if (map->grid[con][i] != '1')
					error_function(4);
				break ;
			}
			i--;
		}
		con++;
	}
	map_consistence_control_6(map, y);
}

void	map_consistence_control_6(t_map *map, int y)
{
	int		i;
	int		x;
	char	**cont;

	cont = map_corrector(map, y);
	i = 0;
	while (i < map->lenght)
	{
		x = 0;
		while (x < map->height)
		{
			if (cont[x][i] > 32)
			{
				if (cont[x][i] != '1')
					error_function(4);
				break ;
			}
			x++;
		}
		i++;
	}
	map_consistence_control_7(map, cont);
}

void	map_consistence_control_7(t_map *map, char **cont)
{
	int	i;
	int	x;

	i = 0;
	while (i < map->lenght)
	{
		x = map->height - 1;
		while (x > 0)
		{
			if (cont[x][i] > 32)
			{
				if (cont[x][i] != '1')
					error_function(4);
				break ;
			}
			x--;
		}
		i++;
	}
	semi_cleaning(map, cont);
	filling_spces_by_ones(map);
	get_starting_position(map);
}
