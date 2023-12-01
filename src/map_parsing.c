/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 13:36:34 by msulc             #+#    #+#             */
/*   Updated: 2023/11/27 13:36:35 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_check(char *filename, t_data *data)
{
	int		fd ;
	int		i;
	char	*b;
	t_map	map;

	b = NULL;
	map = data->mapa;
	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_function(2);
	map.nbr_of_lines = map_line_counter(fd);//pocitame pocet radek v souboru mapy
	fd = open(filename, O_RDONLY);
	map_check_ext(map.nbr_of_lines, i, &map, fd);//hledame adresy textur na pozadi 
	if (!map.w_id || !map.s_id || !map.e_id
		|| !map.n_id || !map.c_id || !map.f_id)
		error_function(6);
	close(fd);
	map_consistence_control(&map, filename);//kontroluje samotnou mapu
	data->mapa = map;
	game_start(data);//spousti program, pokud kontrola mapy probehla v poradku
}

void	map_check_ext(int nbr_of_lines, int i, t_map *map, int fd)//hleda adresy textur v souboru mapy
{
	char	*b;

	b = NULL;
	while (i < nbr_of_lines)
	{
		b = get_next_line(fd);
		map_textures(b, map, i + 1);//pridava adresy textur do struktury map
		i++;
		free(b);
	}
}

void	map_textures(char *map_line, t_map *map, int index)//adresy textur pridava do struktury 
{
	int	i;

	if (!map_line)
		error_function(3);
	i = -1;
	while (map_line[++i])
	{
		if (map_line[i] == 'N' && map_line[i + 1] == 'O'
			&& map_line[i + 2] == ' ')
		{
			map->n_id = texture_extractor(map, map_line);
			if (index > map->line_index)
				map->line_index = index;
		}
		else if (map_line[i] == 'E' && map_line[i + 1] == 'A'
			&& map_line[i + 2] == ' ')
		{
			map->e_id = texture_extractor(map, map_line);
			if (index > map->line_index)
				map->line_index = index;
		}
		map_textures_ext(map_line, map, index, i);
	}
}

void	map_textures_ext(char *map_line, t_map *map, int index, int i)//pokraovani funkce vyse
{
	if (map_line[i] == 'S' && map_line[i + 1] == 'O' && map_line[i + 2] == ' ')
	{
		map->s_id = texture_extractor(map, map_line);
		if (index > map->line_index)
			map->line_index = index;
	}
	else if (map_line[i] == 'W' && map_line[i + 1] == 'E'
		&& map_line[i + 2] == ' ')
	{
		map->w_id = texture_extractor(map, map_line);
		if (index > map->line_index)
			map->line_index = index;
	}
	else if (map_line[i] == 'C' && map_line[i + 1] == ' ')
	{
		map->c_id = texture_extractor_2(map, map_line);
		if (index > map->line_index)
			map->line_index = index;
	}
	else if (map_line[i] == 'F' && map_line[i + 1] == ' ')
	{
		map->f_id = texture_extractor_2(map, map_line);
		if (index > map->line_index)
			map->line_index = index;
	}
}
