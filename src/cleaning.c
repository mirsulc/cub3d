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

	
void	semi_cleaning(t_map *map, char **cont)	//zahazujeme puvodni verzi mapy a ukazujeme na novou
{
	int	i;
	
	i = 0;
	while(i < map->height)		//osvobozujeme puvodni verzi mapy
	{
        	free(map->grid[i]);
                i++;
        }
	i = -1;
	while(++i < map->height)
		map->grid[i] = strdup(cont[i]);	//ukazujeme na nowou verzi mapy
	i = -1;
	while(++i < map->height)	//osvobozujeme starou verzi nove mapy
		free(cont[i]);
	free(cont);
}
	
void	map_cleaning(t_map *map)
{
	int	i;	
	
	i = -1;
	free(map->S_id);
	free(map->W_id);
	free(map->N_id);
	free(map->E_id);
	free(map->C_id);
	free(map->F_id);
	while(++i < map->height)
		free(map->grid[i]);
	free(map->grid);
	
}

void	cleaning(t_data *data)
{
//	free(data->mapa->S_id);
//	data->mapa->S_id = NULL;
//	free(data->mapa);
}


