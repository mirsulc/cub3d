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

void	map_consistence_control_6(t_map *map, int y)	//kontroluje uzavreni mapy zac. sloupcu		
{
	int	i;
	int	x;
	char	**cont;
	
	cont = map_corrector(map, y); //ytvarime ctvercovou verzi mapy pro snazsi kontrolu hranic
	i = 0;
	while(i < map->lenght)
	{
		x= 0;
		while(x < map->height)
		{
			if(cont[x][i] > 32)
			{
				if(cont[x][i] != '1')
					error_function(4);
				break;
			}
			x++;
		}
		i++;
	}
	map_consistence_control_7(map, cont);
}

void	map_consistence_control_7(t_map *map, char **cont) //kontroluje mapu od koncu sloupcu
{
	int	i;
	int	x;
	
	i = 0;
	while(i <  map->lenght)
	{
		x = map->height - 1;
		while(x > 0)
		{
			if(cont[x][i] > 32)
			{
				if(cont[x][i] != '1')
					error_function(4);
				break;
			}
			x--;
		}
		i++;		
	}
	semi_cleaning(map, cont);	//prohazujeme puvodni a novou(ctvercovou) verzi mapy
	ft_printf("map file seems to be OK\n\n");
	filling_spces_by_ones(map);
	i = -1;
	while(++i < map->height)
		ft_printf(": %s.\n", map->grid[i]);
	get_starting_position(map);
	ft_printf("x pozice: %d, y pozice: %d, smer: %c\n", map->char_pos_x, map->char_pos_y, map->starting_angle);
//	game_start(map);
//	map_cleaning(map);
}

char	**map_corrector(t_map *map, int y)	//vytvari novou verzi mapy, ktera bude ctvercova
{
	int	i;
	int	x;
	char	**new_map;
	
	
	new_map = malloc(map->height * sizeof(char*));		//alokace pameti pro pointery na mapu
	if(!new_map)
		return(NULL);
	i = -1;
	while(++i < map->height)
	{
		new_map[i] = malloc(sizeof (char) * (map->lenght + 1));	//alokace pro radky
		if(!new_map[i])
			return(NULL);
		new_map[i][map->lenght] = '\0';
	}
	new_map = new_map_fill(map, new_map, y);	//plneni nove mapy mezerami
	i = 0;

	ft_printf("nejdelsi radek mapy: %d\n", map->lenght);
	ft_printf("pocet radku v nove mape: %d\n", map->height);
	return(new_map);
}

char	**new_map_fill(t_map *map, char **new_map, int y)	//plnime novou mapu mezerami
{
	int	i;
	int	x;
	
	i = 0;
	while(i < map->height)
	{
		x = 0;
		while(x < map->lenght)
		{
			new_map[i][x] = ' ';
			x++;
		}
		i++;
	}
	new_map = new_map_fill_2(map, new_map, y);	//plneni nowe mapy starou mapou
	return(new_map);
}

char	**new_map_fill_2(t_map *map, char **new_map, int y)	//plnime starou mapu do nove
{
	int	i;
	int	x;
	int	y2 = y;
	
	i = 0;
	while(map->grid[y])
	{
		x = 0;
		while(map->grid[y][x] != '\0')
		{
			new_map[i][x] = map->grid[y][x];
			x++;
		}
		y++;
		i++;
	}
	return (new_map);
}

void	filling_spces_by_ones(t_map *map)	//nahrazujeme mezery v nove mape jednickami
{
	int	i;
	int	y;
	
	y = 0;
	while(y < map->height)
	{
		i = 0;
		while(map->grid[y][i])
		{
			if(map->grid[y][i] == ' ' || map->grid[y][i] == '	')
				map->grid[y][i] = '1';
			i++;
		}
		y++;
	}
}

void	get_starting_position(t_map *map)	//ziskavame smer hrace v mape
{
	int	x;
	int	y;
	
	x = 0;
	while(map->grid[x])
	{
		y = 0;
		while(map->grid[x][y])
		{
			if(map->grid[x][y] == 'E' || map->grid[x][y] == 'N'
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



