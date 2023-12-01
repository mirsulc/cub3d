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

# define WIDTH 1400
# define HEIGHT 1000

# define COLOR uint8_t

typedef struct s_map
{
	int	total_char;
	int	nbr_of_lines;		//pocet radku v mape
	int	line_index;		//cislo radku na kterem je posledni informace pred mapou
	int	lenght;			//nejdelsi radek mapy
	int	flag;			//pomocne, pro vypocet radku, ktere zabiraji textury
	int	height;
	int	consistence;
	char	*s_id;			//adresa pozadi zdi Jih
	char	*n_id;			//adresa pozadi zdi Sever
	char	*e_id;			//adresa pozadi zdi Vychod
	char	*w_id;			//adresa pozadi zdi Zapad
	char	*c_id;			//barva stropu
	char	*f_id;			//barva podlahy
	char	**grid;
	int	char_pos_x;		//X pozice hrace 
	int	char_pos_y;		//Y pozice hrace
	char	starting_angle;		//E/S/W/N na zacatku hry
}	t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*obr;
	mlx_texture_t	*n_t;
	mlx_texture_t	*s_t;
	mlx_texture_t	*e_t;
	mlx_texture_t	*w_t;
	void		*mlx_win;
	double		rot_speed;	//rychlost otaceni
	double		init_angle;	//uvodni uhel (sever = 0, ...)
	double		actual_angle;	//aktualni uhel
	double		ray_angle;	//uhel paprsku, kterym hledame zdi
	double		move_speed;	//rychlost pohybu vpred i do stran
	int		init_pos_x;	//uvodni pozice x
	int		init_pos_y;	//uvodni pozice y
	double		pos_x;		//aktualni pozice x
	double		pos_y;		//aktualni pozice y
	double		lo_x;		//rozdil mezi pos_x a nejnizsim celym cislem
	double		lo_y;		//rozdil mezi pos_y a nejnizsim celym cislem
	double		hi_x;		//rozdil mezi pos_x a nejvyssim celym cislem
	double		hi_y;		//rozdil mezi pos_y a nejvyssim celym cislem
	int		quadrant;	//urcuje kvadrant to ktereho smeruje paprsek
	int		wall;		//hodnota 0 nebo 1 podle toho, jestli jsme narazili na zed
	char		x_or_y;		//urcuje, jestli je zed za osou X nebo Y
	int		map_x;		//souradnice pro kontrolu zdi pri raycastingu
	int		map_y;		//souradnice pro kontrolu zdi pri raycastingu
	double		sidedist_x;	//delka k nejblizsi ose X pri raycastingu
	double		sidedist_y;	//delka k nejblizsi ose Y pri raycastingu
	double		deltadist_x;	//delka mezi osami X pri raycastingu
	double		deltadist_y;	//delka mezi osami Y pri raycastingu
	int		direction_x;	//hodnota 1 nebo -1 podle toho jestli jdeme nahoru nebo dolu
	int		direction_y;	//hodnota 1 nebo -1 podle toho, jetsli doleva nebo doprava
	double		distance_to_wall;	//vydalenost ke zdi pri raycastingu
	int		line_height;	//vyska steny, kterou vykreslujeme
	int		drawstart;	//pocatecni bod vykreslovani sloupce
	int		drawend;	//nenizsi bod vykreslovani sloupce
	int		ceiling;	//barva stropu
	int		floor;		//barva podlahy
	int		texture_y;	//y pozice pixelu textury, ktery vykreslujeme na stenu
	int		texture_x;	//x pozice pixelu textury, ktery vykreslujeme na stenu
	double		texture_start;	//prvni pixel textury, ktery vykreslujeme v danem sloupci
	double		texture_end;	//posledni pixel textury, ktery vykreslujeme v danem sloupci
	double		texture_range;	//rozsah mezi texture_end a texture_start
	double		tex_point_ratio;//kolik bodu na jeden pixel textury
	mlx_texture_t	*actual_texture;	//textura pro aktualni sloupec, ktery vykreslujeme
	int		i;
	t_map		mapa;
}	t_data;

//main.c
void			map_init(t_map *map);
int			map_line_counter(int fd);
//map_control.c
void			map_consistence_control(t_map *map, char *filename);
int			map_consistence_ext(t_map *map);
void			map_consistence_control_2(t_map *map, int y);
void			map_consistence_control_3(t_map *map, int y);
void			map_consistence_control_4(t_map *map, int y);
//map_control_2.c
void			map_consistence_control_5(t_map *map, int y);
void			map_consistence_control_6(t_map *map, int y);
void			map_consistence_control_7(t_map *map, char **cont);
//map_control_3.c
char			**map_corrector(t_map *map, int y);
char			**new_map_fill(t_map *map, char **new_map, int y);
char			**new_map_fill_2(t_map *map, char **new_map, int y);
void			filling_spces_by_ones(t_map *map);
void			get_starting_position(t_map *map);
//map_parsing.c
void			map_check(char *filename, t_data *data);
void			map_check_ext(int nbr_of_lines, int i, t_map *map, int fd);
void			map_textures(char *map_line, t_map *map, int index);
void			map_textures_ext(char *map_line, t_map *map, int index, int i);
//game.c
int			game_start(t_data *data);
void			game_start_ext(t_data *data, mlx_image_t *img);
void			data_init(t_data *data);
void			setting_starting_angle(t_data *data);
//colors.c
COLOR			ml_color_at(mlx_texture_t *img, int x, int y);
uint32_t		convert_colors(char *str);
uint32_t		convert_colors_2(mlx_texture_t *img, int x, int y);
void			free_arrays(char **array);
uint32_t		color(t_data *data);
//moves.c
void			move_forward(t_data *data);
void			move_back(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
//moves_2.c
void			turn_right(t_data *data);
void			turn_left(t_data *data);
void			new_obraz(t_data *data);
void			new_obraz_ext(t_data *data, int x);
//raycasting.c
void			count_lo_hi(t_data *data);
void			count_quadrant(t_data *data);
void			looking_for_wals(t_data *data);
void			calculate_height(t_data *data);
void			calculate_sidedist(t_data *data);
//raycasting_2.c
mlx_texture_t		*choose_texture(t_data *data);
void			count_texture_coordinates(t_data *data, int temp);
int			count_x_of_texture(t_data *data);
int			count_x_1(t_data *data);
int			count_x_2(t_data *data);
//utils.c
int			suffix_check(char *filename);
void			error_function(int i);
char			*texture_extractor(t_map *map, char *map_line);
char			*texture_extractor_2(t_map *map, char *map_line);
//cleaning.c
void			semi_cleaning(t_map *map, char **cont);
void			map_cleaning(t_map *map);
void			cleaning(t_data *data);
char			*ft_strdup_cub(const char *s);
void			closeit(void *data);




#endif
