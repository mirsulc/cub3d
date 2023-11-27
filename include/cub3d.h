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
	int		total_char;
	int		nbr_of_lines;
	int		line_index;
	int		lenght;
	int		flag;
	int		height;
	int		consistence;
	char	*s_id;
	char	*n_id;
	char	*e_id;
	char	*w_id;
	char	*c_id;
	char	*f_id;
	char	**grid;
	int		char_pos_x;
	int		char_pos_y;
	char	starting_angle;
}	t_map;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*obr;
	mlx_texture_t	*n_t;
	mlx_texture_t	*s_t;
	mlx_texture_t	*e_t;
	mlx_texture_t	*w_t;
	void			*mlx_win;
	double			rot_speed;
	double			init_angle;
	double			actual_angle;
	double			ray_angle;
	double			move_speed;
	int				init_pos_x;
	int				init_pos_y;
	double			pos_x;
	double			pos_y;
	double			lo_x;
	double			lo_y;
	double			hi_x;
	double			hi_y;
	int				quadrant;
	int				wall;
	char			x_or_y;
	int				map_x;
	int				map_y;
	double			sidedist_x;
	double			sidedist_y;
	double			deltadist_x;
	double			deltadist_y;
	int				direction_x;
	int				direction_y;
	double			distance_to_wall;
	int				line_height;
	int				drawstart;
	int				drawend;
	int				ceiling;
	int				floor;
	int				texture_y;
	int				texture_x;
	double			texture_start;
	double			texture_end;
	double			texture_range;
	double			tex_point_ratio;
	mlx_texture_t	*actual_texture;
	int				i;
	t_map			mapa;
}	t_data;

mlx_texture_t	*choose_texture(t_data *data);
uint32_t		convert_colors_2(mlx_texture_t *img, int x, int y);
uint32_t		convert_colors(char *str);
uint32_t		color(t_data *data);
void			error_function(int i);
int				suffix_check(char *filename);
void			map_textures(char *map_line, t_map *map, int index);
char			*texture_extractor(t_map *map, char *map_line);
char			*texture_extractor_2(t_map *map, char *map_line);
void			data_initializer(t_data *data);
void			cleaning(t_data *data);
void			map_cleaning(t_map *map);
void			semi_cleaning(t_map *map, char **cont);
void			map_check(char *filename, t_data *data);
void			map_init(t_map *map);
int				map_line_counter(int fd);
void			map_consistence_control(t_map *map, char *filename);
int				map_consistence_ext(t_map *map);
void			map_consistence_control_2(t_map *map, int y);
void			map_consistence_control_3(t_map *map, int y);
void			map_consistence_control_4(t_map *map, int y);
void			map_consistence_control_5(t_map *map, int y);
void			map_consistence_control_6(t_map *map, int y);
void			map_consistence_control_7(t_map *map, char **cont);
char			**map_corrector(t_map *map, int y);
char			**new_map_fill(t_map *map, char **new_map, int y);
char			**new_map_fill_2(t_map *map, char **new_map, int y);
void			filling_spces_by_ones(t_map *map);
void			get_starting_position(t_map *map);
void			setting_starting_angle(t_data *data);
char			*ft_strdup_cub(const char *s);
void			closeit(void *data);
void			texture_control(t_map *map);
void			map_textures_ext(char *map_line, t_map *map, int index, int i);
void			map_check_ext(int nbr_of_lines, int i, t_map *map, int fd);

int				game_start(t_data *data);
void			data_init(t_data *data);
void			game_start_ext(t_data *data, mlx_image_t *img);

COLOR			ml_color_at(mlx_texture_t *img, int x, int y);
void			free_arrays(char **array);

void			move_forward(t_data *data);
void			move_back(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			turn_right(t_data *data);
void			turn_left(t_data *data);
void			new_obraz_ext(t_data *data, int x);

void			new_obraz(t_data *data);

void			count_lo_hi(t_data *data);
void			count_quadrant(t_data *data);
void			calculate_sidedist(t_data *data);
void			looking_for_wals(t_data *data);
void			calculate_height(t_data *data);
void			count_texture_coordinates(t_data *data, int temp);
int				count_x_of_texture(t_data *data);
int				count_x_1(t_data *data);
int				count_x_2(t_data *data);

#endif
