/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: absela <absela@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:51:53 by abelahce          #+#    #+#             */
/*   Updated: 2023/04/02 02:21:17 by absela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef CUB3D_H
# define CUB3D_H

// i ------> y
// j ------|> x
// 	90
// 0		180
// 	270

# define WWITH 900.0
# define HHEITH 800
# define TILE 64
# define ROSE 0xFF00FF
# define YOLLOW 0xFFFF00
# define PURPLE 0x8000FF
# define SKY 0x00FFFF
# define PI 3.14159265359
# define MVSPEED 1
# define TUSPEED 0.1
# define FOV 60.0
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "mlx.h"
# include "libft/libft.h"

typedef struct s_ply_info
{
	double x;
	double y;
	double angle;
	int	walk;
	int rotate;
}	t_ply_info;

typedef struct s_info
{
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int	flag_so;
	int	flag_no;
	int	flag_we;
	int	flag_ea;
	int	flag_f;
	int	flag_c;
	int	*floor_color;
	int	*sky_color;
} t_info;

typedef struct s_cub
{
	char *map_name;
	char *map;
	char **map_final;
	int  map_lines;
	int  map_collumn;
	t_info *info;
	t_ply_info *ply;
} t_cub;

// void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	free_table(char **tab);

#endif