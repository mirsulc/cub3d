/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 09:50:39 by msulc             #+#    #+#             */
/*   Updated: 2023/10/18 09:50:42 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_consistence_control(t_map *map, char *filename)
{
	int		fd;
	int		control;
	char	buf[4096];
	int		y;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_function(2);
	control = read(fd, buf, 4095);
	buf[control] = '\0';
	map->grid = ft_split(buf, '\n');
	y = map_consistence_ext(map);
	map_consistence_control_2(map, y);
}

int	map_consistence_ext(t_map *map)
{
	int	y;
	int	i;

	y = 0;
	while (map->grid[y] && map->flag < 6)
	{
		i = 0;
		while (map->grid[y][i])
		{
			if (map->grid[y][i] > 32)
			{
				map->flag++;
				break ;
			}
			i++;
		}
		y++;
	}
	return (y);
}

void	map_consistence_control_2(t_map *map, int y)
{
	int	i;
	int	con;

	map->height = map->nbr_of_lines - map->line_index;
	con = y;
	while (map->grid[con])
	{
		i = 0;
		while (map->grid[con][i])
		{
			if (map->grid[con][i] != ' ' && map->grid[con][i] != '1'
				&& map->grid[con][i] != '0' && map->grid[con][i] != 'W'
				&& map->grid[con][i] != 'E' && map->grid[con][i] != 'N'
				&& map->grid[con][i] != '\n' && map->grid[con][i] != 'S'
				&& map->grid[con][i] != '	')
				error_function(5);
			i++;
		}
		if (i > map->lenght)
			map->lenght = i;
		con++;
	}
	map_consistence_control_3(map, y);
}

void	map_consistence_control_3(t_map *map, int y)
{
	int	i;
	int	con;
	int	characters;

	characters = 0;
	con = y;
	while (map->grid[con])
	{
		i = 0;
		while (map->grid[con][i])
		{
			if (map->grid[con][i] == 'W' || map->grid[con][i] == 'E'
				|| map->grid[con][i] == 'N' || map->grid[con][i] == 'S')
				characters++;
			i++;
		}
		con++;
	}
	if (characters != 1)
		error_function(6);
	map_consistence_control_4(map, y);
}

void	map_consistence_control_4(t_map *map, int y)
{
	int	i;
	int	con;

	con = y;
	while (map->grid[con])
	{
		i = 0;
		while (map->grid[con][i])
		{
			if (map->grid[con][i] > 32)
			{
				if (map->grid[con][i] != '1')
					error_function(4);
				break ;
			}
			i++;
		}
		con++;
	}
	map_consistence_control_5(map, y);
}
