/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 11:19:07 by msulc             #+#    #+#             */
/*   Updated: 2023/11/27 11:19:09 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**map_corrector(t_map *map, int y)
{
	int		i;
	int		x;
	char	**new_map;

	new_map = malloc(map->height * sizeof(char *));//alokace pameti pro radky nove mapy - 
	if (!new_map)
		return (NULL);
	i = -1;
	while (++i < map->height)
	{
		new_map[i] = malloc(sizeof (char) * (map->lenght + 1));//alokace pro vsechny znaky
		if (!new_map[i])
			return (NULL);
		new_map[i][map->lenght] = '\0';
	}
	new_map = new_map_fill(map, new_map, y);
	i = 0;
	return (new_map);
}

char	**new_map_fill(t_map *map, char **new_map, int y) //nove alokovanou pamet mapy plnim mezerami
{
	int	i;
	int	x;

	i = 0;
	while (i < map->height)
	{
		x = 0;
		while (x < map->lenght)
		{
			new_map[i][x] = ' ';
			x++;
		}
		i++;
	}
	new_map = new_map_fill_2(map, new_map, y);
	return (new_map);
}

char	**new_map_fill_2(t_map *map, char **new_map, int y)//do nove alokovane mapy kopiruju starou
{
	int	i;
	int	x;
	int	y2;

	i = 0;
	y2 = y;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x] != '\0')
		{
			new_map[i][x] = map->grid[y][x];
			x++;
		}
		y++;
		i++;
	}
	return (new_map);
}

void	filling_spces_by_ones(t_map *map)//zbyle mezery plnim jednickami
{
	int	i;
	int	y;

	y = 0;
	while (y < map->height)
	{
		i = 0;
		while (map->grid[y][i])
		{
			if (map->grid[y][i] == ' ' || map->grid[y][i] == '	')
				map->grid[y][i] = '1';
			i++;
		}
		y++;
	}
}

void	get_starting_position(t_map *map)
{
	int	x;
	int	y;

	x = 0;
	while (map->grid[x])
	{
		y = 0;
		while (map->grid[x][y])
		{
			if (map->grid[x][y] == 'E' || map->grid[x][y] == 'N'
				|| map->grid[x][y] == 'W' || map->grid[x][y] == 'S')
			{
				map->char_pos_x = y;
				map->char_pos_y = x;
				map->starting_angle = map->grid[x][y];
				map->grid[x][y] = '0';
			}
			y++;
		}
		x++;
	}
}
