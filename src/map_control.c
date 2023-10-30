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
	int	fd;
	int	control;
	char	buf[4096];
	int	i = 0;
	int	y = 0;
	
	fd = open(filename, O_RDONLY);		//bylo potreba znovu otevrit fd
	control = read(fd, buf, 4095);
	buf[control] = '\0';
	map->grid = ft_split(buf, '\n');
	while(map->grid[y] && map->flag < 6)	//kolik radku zabere 6 informaci o texturach?
	{
		i = 0;
		while(map->grid[y][i])
		{
			if(map->grid[y][i] > 32)
			{
				ft_printf("last character: %c\n", map->grid[y][i]);
				map->flag++;
				break;
			}
			i++;
		}
		y++;
	}
	ft_printf("y: %d\n", y);
	ft_printf("flag: %d\n", map->flag);
	ft_printf("i: %d\n", i);
	map_consistence_control_2(map, y);
}

void	map_consistence_control_2(t_map *map, int y)	//kontroluje pritomnost nepripustnych znaku
{
	int	i = 0;
	int	con = y;
	
	map->height = map->nbr_of_lines - map->line_index;	//vypocet poctu radku mapy
	while(map->grid[con])
	{
		i = 0;
		while(map->grid[con][i])
		{
			if(map->grid[con][i] != ' ' && map->grid[con][i] != '1'
				&& map->grid[con][i] != '0' && map->grid[con][i] != 'W'
				&& map->grid[con][i] != 'E' && map->grid[con][i] != 'N'
				&& map->grid[con][i] != '\n' && map->grid[con][i] != 'S'
				&& map->grid[con][i] != '	')
				error_function(5);
			i++;
		}
		if(i > map->lenght)
			map->lenght = i;
		con++;
	}
	map_consistence_control_3(map, y);
}

void	map_consistence_control_3(t_map *map, int y)	//kontroluje pocet "hracu" v mape
{
	int	i = 0;
	int	con = y;
	int	characters = 0;
	
	while(map->grid[con])
	{
		i = 0;
		while(map->grid[con][i])
		{
			if(map->grid[con][i] == 'W' ||  map->grid[con][i] == 'E'
			 	|| map->grid[con][i] == 'N' || map->grid[con][i] == 'S')
				characters++;
			i++;
		}
		con++;
	}
	if(characters != 1)
		error_function(6);
	map_consistence_control_4(map, y);	
}

void	map_consistence_control_4(t_map *map, int y)	//kontroluje uzavreni mapy zacatky radku
{
	int	i = 0;
	int	con = y;
	
	while(map->grid[con])
	{
		i = 0;
		while(map->grid[con][i])
		{
			if(map->grid[con][i] > 32)
			{
				if(map->grid[con][i] != '1')
					error_function(4);
				break;
			}
			i++;
		}
		con++;
	}
	map_consistence_control_5(map, y);
}

void	map_consistence_control_5(t_map *map, int y)	//kontroluje uzavreni mapy konce radku
{
	int	i = 0;
	int	con = y;
	
	while(map->grid[con])
	{
		i = 0;
		while(map->grid[con][i])
			i++;
		while(i > 0)
		{
			if(map->grid[con][i] > 32)
			{
				if(map->grid[con][i] != '1')
					error_function(4);
				break;
			}
			i--;
		}
		con++;
	}
	map_consistence_control_6(map, y);
}
