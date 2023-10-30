/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msulc <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:28:26 by msulc             #+#    #+#             */
/*   Updated: 2023/10/17 15:28:30 by msulc            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <limits.h>
# include <math.h>
# include <string.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIDTH 800
# define HEIGHT 600

# define COLOR unsigned int

typedef struct	s_raycast
{
	double	rot_speed;	//rychlost otaceni
	double	init_angle;	//uvodni uhel (sever = 0, ...)
	double	actual_angle;	//aktualni uhel
	double	move_speed;	//rychlost pohybu vpred i do stran
	int	init_pos_x;	//uvodni pozice x
	int	init_pos_y;	//uvodni pozice y
	double	pos_x;		//aktualni pozice x
	double	pos_y;		//aktualni pozice y

}	t_raycast;

typedef struct s_map
{
	int	total_char;
	int	nbr_of_lines;		//pocet radku v mape
	int	line_index;		//cislo radku na kterem je posledni informace pred mapou
	int	lenght;			//nejdelsi radek mapy
	int	flag;			//pomocne, pro vypocet radku, ktere zabiraji textury
	int	height;
	int	consistence;
	char	*S_id;			//adresa pozadi zdi Jih
	char	*N_id;			//adresa pozadi zdi Sever
	char	*E_id;			//adresa pozadi zdi Vychod
	char	*W_id;			//adresa pozadi zdi Zapad
	char	*C_id;			//barva stropu
	char	*F_id;			//barva podlahy
	char	**grid;
	int	char_pos_x;		//X pozice hrace 
	int	char_pos_y;		//Y pozice hrace
	char	starting_angle;		//E/S/W/N na zacatku hry
	
	
}	t_map;


typedef struct s_data
{

	mlx_t	*mlx;
	mlx_texture_t	*img_t;
	mlx_image_t	*img2;
	void	*mlx_win;
//	void	*img;
//	t_img	*image;
	int	ceiling;
	int	floor;
	t_map	*mapa;
	t_raycast ray;
	
}	t_data;

void	error_function(int i);
int	suffix_check(char *filename);		//kontroluje priponu souboru mapy
int	map_textures(char *map_line, t_map *map,int index);	//hleda v souboru mapy textury
char	*texture_extractor(t_map *map, char *map_line);		//pridava texturu do struktury mapy
char	*texture_extractor_2(t_map *map, char *map_line);	//pridava barvu stropu a podlahy
void	data_initializer(t_data *data);
void	cleaning(t_data *data);
void	map_cleaning(t_map *map);
void	semi_cleaning(t_map *map, char **cont);
void	map_init(t_map *map);
int	map_line_counter(int fd);		//pocita kolik je v souboru mapy radku
void	map_consistence_control(t_map *map, char *filename);
void	map_consistence_control_2(t_map *map, int y);
void	map_consistence_control_3(t_map *map, int y);
void	map_consistence_control_4(t_map *map, int y);
void	map_consistence_control_5(t_map *map, int y);
void	map_consistence_control_6(t_map *map, int y);
void	map_consistence_control_7(t_map *map, char **cont);
char	**map_corrector(t_map *map, int y);
char	**new_map_fill(t_map *map, char **new_map, int y);
char	**new_map_fill_2(t_map *map, char **new_map, int y);
void	filling_spces_by_ones(t_map *map);
void	get_starting_position(t_map *map);
void	move_up(t_data *data);
void	setting_starting_angle(t_map *map, t_raycast *ray);

//game.c
int	game_start(t_map *map);
void	free_arrays(char **array);
uint32_t	convert_colors(char *str);
void	data_init(t_data *data);
void	raycast_init(t_raycast *ray, t_map *map);

//colors
COLOR	ml_color_at(mlx_image_t *img, int x, int y);


#endif
