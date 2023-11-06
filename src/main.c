/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 09:16:34 by msulc             #+#    #+#             */
/*   Updated: 2023/10/17 09:16:35 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	error_function(int i)
{
	if (i == 1)
		ft_printf("Error:\nwrong map file format\n");
	else if (i == 2)
		ft_printf("Error:\nwrong file descriptor\n");
	else if (i == 3)
		ft_printf("Error:\nempty map file\n");
	else if (i == 4)
		ft_printf("Error:\nmap is not valid or is not surrounded by borders\n");
	else if (i == 5)
		ft_printf("Error:\ninvallid characters\n");
	else if (i == 6)
		ft_printf("Error:\ninvalid number of characters\n");
	else if (i == 7)
		ft_printf("Error:\nsome collectibles or the exit are not accessible\n");
	exit(1);
}

int	suffix_check(char *filename)
{
	int	i;

	i = 0;
	while (filename[i] != '\0')
		i++;
	if (filename[i - 4] != '.' || filename[i - 3] != 'c'
		|| filename[i - 2] != 'u' || filename[i - 1] != 'b')
		error_function(1);
	return (0);
}

int	map_check(char *filename, t_data *data)
{
	int		fd ;
	int		i;
	char	*b = NULL;
	t_map	map = data->mapa;
	
	i = 0;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		error_function(2);
	map.nbr_of_lines = map_line_counter(fd);	//pocita pocet radek v souboru mapy
	fd = open(filename, O_RDONLY);		//bylo potreba znovu otevrit fd
	while(i < map.nbr_of_lines)
	{
		b = get_next_line(fd);
		map_textures(b, &map, i + 1);		//hleda v souboru mapy textury na zed
		i++;
		free(b);
	}
	if(!map.W_id || !map.S_id || !map.E_id || !map.N_id || !map.C_id || !map.F_id)
		ft_printf("			se to nejak posralo\n");
	ft_printf("nbr_of_lines: %d\n", map.nbr_of_lines);
	ft_printf("kontrola identifieru textury map.N_id: %s\n", map.N_id);
	ft_printf("kontrola identifieru textury map.S_id: %s\n", map.S_id);
	ft_printf("kontrola identifieru textury map.E_id: %s\n", map.E_id);
	ft_printf("kontrola identifieru textury map.W_id: %s\n", map.W_id);
	ft_printf("kontrola identifieru textury map.F_id: %s\n", map.F_id);
	ft_printf("kontrola identifieru textury map.C_id: %s\n", map.C_id);
	ft_printf("line_index: %d\n", map.line_index);
	close(fd);
	map_consistence_control(&map, filename);
	data->mapa = map;
//	ft_printf("kontrola barvy yyyyyyyyy %s\n", data->mapa.C_id);
	game_start(data);
//	ft_printf("x pozice: %d, y pozice: %d, uhel: %c\n", map.char_pos_x, map.char_pos_y, map.starting_angle);


//	game_start(&map, buf);					!!!!!!!!!!
}


int	main(int argc, char **argv)
{	
	t_data	data;
	
	if (argc != 2)
	{
		ft_printf("wrong number of arguments\n");
		return (1);
	}
//	data_initializer(&data);		asi blbost...
	map_init(&data.mapa);
	suffix_check(argv[1]);
	map_check(argv[1], &data);
//	cleaning(&data);
	return (0);
}

int	map_textures(char *map_line, t_map *map, int index)
{
	int	i = -1;
	
	if(!map_line)
		return(1);
	while(map_line[++i])
	{
		if(map_line[i] == 'N' && map_line[i + 1] == 'O')
		{
			map->N_id = texture_extractor(map, map_line);
			if(index > map->line_index)
				map->line_index = index;
		}
		else if(map_line[i] == 'E' && map_line[i + 1] == 'A')
		{
			map->E_id = texture_extractor(map, map_line);
			if(index > map->line_index)
				map->line_index = index;
		}
		else if(map_line[i] == 'S' && map_line[i + 1] == 'O')
		{
			map->S_id = texture_extractor(map, map_line);
			if(index > map->line_index)
				map->line_index = index;
		}
		else if(map_line[i] == 'W' && map_line[i + 1] == 'E')
		{
			map->W_id = texture_extractor(map, map_line);
			if(index > map->line_index)
				map->line_index = index;
		}
		else if(map_line[i] == 'C')
		{
			map->C_id = texture_extractor_2(map, map_line);
			if(index > map->line_index)
				map->line_index = index;
		}
		else if(map_line[i] == 'F')
		{
			map->F_id = texture_extractor_2(map, map_line);
			if(index > map->line_index)
				map->line_index = index;
		}
	}
	return (0);
}

char	*texture_extractor(t_map *map, char *map_line)
{
	char	*dest;
	
	if(!map_line)
		return(NULL);
	ft_printf("texture line:%s\n", map_line);
	while(*map_line != '.')
		map_line++;
	dest = ft_strdup(map_line);
	return(dest);
}
char	*texture_extractor_2(t_map *map, char *map_line)
{
	char	*dest;
	
	if(!map_line)
		return(NULL);
	ft_printf("texture 2 line:%s\n", map_line);
	while(*map_line < '0' || *map_line > '9')
		map_line++;
	dest = ft_strdup(map_line);
	return(dest);
}

/*					asi blbost....
void	data_initializer(t_data *data)
{
	data->mapa = (t_map*)malloc(sizeof(t_map));
	if(!data->mapa)
		exit(1);
}*/

void	map_init(t_map *map)
{
	map->total_char = 0;
	map->nbr_of_lines = 0;
	map->line_index = 0;
	map->lenght = 0;
	map->flag = 0;
	map->height = 0;
	map->consistence = 0;
	map->S_id = NULL;
	map->N_id = NULL;
	map->E_id = NULL;
	map->W_id = NULL;
	map->C_id = NULL;
	map->F_id = NULL;
	map->grid = NULL;
	map->char_pos_x = 0;
	map->char_pos_y = 0;
	map->starting_angle = 0;
}

int	map_line_counter(int fd)
{
	int	line;
	int	control;
	int	i;
	char	buf[4096];
	
	line = 0;
	i = 0;
	control = read(fd, buf, 4095);
//	ft_printf("control:%d", control);
	buf[control] = '\0';
	while(i < control)
	{
		if(buf[i] == '\n')
			line++;
		i++;
	}
//	ft_printf("line:%d", line);
	close(fd);
	return(line);
}
