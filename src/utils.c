/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 14:20:32 by msulc             #+#    #+#             */
/*   Updated: 2023/11/27 14:20:34 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	suffix_check(char *filename)//kontroluje priponu mapoveho souboru
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

void	error_function(int i)//chybova hlaseni 
{
	if (i == 1)
		ft_printf("Error:\nwrong map file format\n");
	else if (i == 2)
		ft_printf("Error:\nwrong file descriptor\n");
	else if (i == 3)
		ft_printf("Error:\nempty or demaged map file\n");
	else if (i == 4)
		ft_printf("Error:\nmap is not valid or is not surrounded by borders\n");
	else if (i == 5)
		ft_printf("Error:\ninvallid characters in the map file\n");
	else if (i == 6)
		ft_printf("Error:\nmap or textures or colors are not ok\n");
	exit(1);
}

char	*texture_extractor(t_map *map, char *map_line)//prirazuje adresu textury do struktury mapy
{
	char	*dest;

	if (!map_line)
		return (NULL);
	while (*map_line != 'i')
		map_line++;
	dest = ft_strdup_cub(map_line);
	return (dest);
}

char	*texture_extractor_2(t_map *map, char *map_line)
{
	char	*dest;

	if (!map_line)
		return (NULL);
	while (*map_line < '0' || *map_line > '9')
		map_line++;
	dest = ft_strdup(map_line);
	return (dest);
}
