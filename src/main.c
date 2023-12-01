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

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
	{
		ft_printf("wrong number of arguments\n");
		return (1);
	}
	map_init(&data.mapa);	
	suffix_check(argv[1]);
	map_check(argv[1], &data);	//kontrola mapy a nasledne spusteni programu
	return (0);
}

void	map_init(t_map *map)//inicializace promennych ve strukture mapy
{
	map->total_char = 0;
	map->nbr_of_lines = 0;
	map->line_index = 0;
	map->lenght = 0;
	map->flag = 0;
	map->height = 0;
	map->consistence = 0;
	map->s_id = NULL;
	map->n_id = NULL;
	map->e_id = NULL;
	map->w_id = NULL;
	map->c_id = NULL;
	map->f_id = NULL;
	map->grid = NULL;
	map->char_pos_x = 0;
	map->char_pos_y = 0;
	map->starting_angle = 0;
}

int	map_line_counter(int fd)
{
	int		line;
	int		control;
	int		i;
	char	buf[4096];

	i = -1;
	while (++i < 4096)
		buf[i] = '0';
	line = 0;
	i = 0;
	control = read(fd, buf, 4095);
	buf[control] = '\0';
	while (i < control)
	{
		if (buf[i] == '\n')
			line++;
		i++;
	}
	close(fd);
	return (line);
}
