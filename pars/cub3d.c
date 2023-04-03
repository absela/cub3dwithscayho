/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:05:13 by abelahce          #+#    #+#             */
/*   Updated: 2023/04/03 01:11:23 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_leaks(void)
{
	system("leaks cub3d");
	exit(0);
}

// void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

void	free_table(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i++]);
	}
	if (tab)
		free(tab);
}

void	ft_free(char *str)
{
	if (!str)
		free(str);
	str = NULL;
}

void	free_data(t_cub *data)
{
	free(data->info->c);
	free(data->info->f);
	free(data->info->no);
	free(data->info->we);
	free(data->info->so);
	free(data->info->ea);
	free(data->info);
	free(data->ply);
	ft_free(data->map_name);
	ft_free(data->map);
	free_table(data->map_final);
	free(data);
}

void	ft_error(char *str, t_cub *data)
{
	(void)data;
	ft_putstr_fd(str, 2);
	if (data)
		free_data(data);
	exit(0);
}

void	init_my_data(t_cub *data)
{
	data->info = malloc(sizeof(t_info));
	if (!data->info)
		ft_error("unable to allocate !\n", NULL);
	data->ply = malloc(sizeof(t_ply_info));
	if (!data->ply)
		ft_error("unable to allocate !\n", NULL);
	data->info->floor_color = malloc(sizeof(int *) * 3);
	if (!data->info->floor_color)
		ft_error("unable to allocate !\n", NULL);
	data->info->sky_color = malloc(sizeof(int *) * 3);
	if (!data->info->sky_color)
		ft_error("unable to allocate !\n", NULL);
	data->info->so = NULL;
	data->info->no = NULL;
	data->info->we = NULL;
	data->info->ea = NULL;
	data->info->f = NULL;
	data->info->c = NULL;
}

char	*r_map(char	*str)
{
	int		check;
	int		fd;
	char	*buf;
	char	*map;

	map = ft_strdup("");
	fd = open(str, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("unable to open the map!!\n", 2);
		exit(1);
	}
	buf = malloc(2);
	check = read(fd, buf, 1);
	buf[1] = '\0';
	while (check > 0)
	{
		map = ft_strjoin(map, buf);
		check = read(fd, buf, 1);
		buf[1] = '\0';
	}
	free(buf);
	return (map);
}

int	str_search(char *str, int n)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == n)
			return (i);
		i++;
	}
	return (i);
}

int	store_info3(char *check, t_cub *data)
{
	if (!ft_strncmp(check, "NO ", 3))
	{
		data->info->no = ft_strtrim(ft_substr(check, 2,
					str_search(check + 2, '\n')), " ");
		data->info->flag_no++;
		free(check);
		return (1);
	}
	else if (!ft_strncmp(check, "F ", 2))
	{
		data->info->f = ft_strtrim(ft_substr(check, 1,
					str_search(check + 1, '\n')), " ");
		data->info->flag_f++;
		free(check);
		return (1);
	}
	return (0);
}

int	store_info2(char *check, t_cub *data)
{
	if (!ft_strncmp(check, "WE ", 3))
	{
		data->info->we = ft_strtrim(ft_substr(check, 2,
					str_search(check + 2, '\n')), " ");
		data->info->flag_we++;
		return (free(check), 1);
	}
	else if (!ft_strncmp(check, "EA ", 3))
	{
		data->info->ea = ft_strtrim(ft_substr(check, 2,
					str_search(check + 2, '\n')), " ");
		data->info->flag_ea++;
		return (free(check), 1);
	}
	else if (!ft_strncmp(check, "C ", 2))
	{
		data->info->c = ft_strtrim(ft_substr(check, 1,
					str_search(check + 1, '\n')), " ");
		data->info->flag_c++;
		return (free(check), 1);
	}
	else if (store_info3(check, data))
		return (1);
	return (0);
}

int	store_info(char *check, t_cub *data)
{
	if (!ft_strncmp(check, "SO ", 3))
	{
		data->info->so = ft_strtrim(ft_substr(check, 2,
					str_search(check + 2, '\n')), " ");
		data->info->flag_so++;
		free(check);
		return (1);
	}
	else if (store_info2(check, data))
	{
		return (1);
	}
	else if (check[0] == '\n')
	{
		free(check);
		return (1);
	}
	free(check);
	return (0);
}

void	get_map_info(t_cub *data)
{
	char	*check;
	char	*tmp;

	check = data->map;
	while (1)
	{
		if (data->info->flag_so == 1 && data->info->flag_we == 1 && \
			data->info->flag_ea == 1 && data->info->flag_no == 1 && \
			data->info->flag_f == 1 && data->info->flag_c == 1)
		{
			tmp = ft_strdup(check);
			free(data->map);
			data->map = tmp;
			break ;
		}
		if (store_info(ft_strdup(check), data))
			;
		else
			ft_error("error in the map contents !\n", NULL);
		check = ft_strchr(check, '\n');
		if (!check)
			ft_error("map ended without finding all the compenent  !!\n", NULL);
		check++;
	}
}

void	parse_each_textures(char *str)
{
	int	fd;

	if (!ft_strncmp(str + ft_strlen(str) - 5, ".xpm", 4))
		ft_error("textures error !!\n", NULL);
	fd = open(str, O_RDONLY);
	if (fd == -1)
		ft_error("unable to open the textures file !!\n", NULL);
	close (fd);
}

void	parse_each_color(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i])
	{
		if (str[i] == ',' && str[i + 1] == ',')
			ft_error("invalid information in colors !!\n", NULL);
		if (str[i] == ',')
			flag++;
		else if (!ft_isdigit(str[i]))
			ft_error("invalid information in colors !!\n", NULL);
		i++;
	}
	if (flag != 2)
		ft_error("invalid information in colors !!\n", NULL);
}

void	store_colors(int	*flor, char *str)
{
	char	**tmp;

	tmp = ft_split(str, ',');
	if (!tmp)
		ft_error("unable to split !!\n", NULL);
	if (ft_strlen(tmp[0]) > 3 || ft_atoi(tmp[0]) > 255 || ft_atoi(tmp[0]) < 0)
		ft_error("colors numbers are fals !!\n", NULL);
	flor[0] = ft_atoi(tmp[0]);
	if (ft_strlen(tmp[1]) > 3 || ft_atoi(tmp[1]) > 255 || ft_atoi(tmp[1]) < 0)
		ft_error("colors numbers are fals !!\n", NULL);
	flor[1] = ft_atoi(tmp[1]);
	if (ft_strlen(tmp[2]) > 3 || ft_atoi(tmp[2]) > 255 || ft_atoi(tmp[2]) < 0)
		ft_error("colors numbers are fals !!\n", NULL);
	flor[2] = ft_atoi(tmp[2]);
	free_table(tmp);
}

void	parse_info(t_cub *data)
{
	parse_each_textures(data->info->ea);
	parse_each_textures(data->info->we);
	parse_each_textures(data->info->no);
	parse_each_textures(data->info->so);
	parse_each_color(data->info->c);
	parse_each_color(data->info->f);
	store_colors(data->info->floor_color, data->info->f);
	store_colors(data->info->sky_color, data->info->c);
}

void	store_player_info(t_cub *data, int i, int j)
{
	data->ply->x = ((double)i * TILE) + TILE / 2;
	data->ply->y = ((double)j * TILE) + TILE / 2;
	if ((data->map_final[i][j]) == 'N')
	{
		data->ply->angle = 90;
	}
	else if ((data->map_final[i][j]) == 'E')
	{
		data->ply->angle = 90;
	}
	else if ((data->map_final[i][j]) == 'W')
	{
		data->ply->angle = 90;
	}
	else if ((data->map_final[i][j]) == 'S')
	{
		data->ply->angle = 90;
	}
}

void	get_ply_info(t_cub *data)
{
	int	i;
	int	j;
	int	flag;

	j = 0;
	i = 0;
	flag = 0;
	while (data->map_final[i])
	{
		while ((data->map_final[i][j]))
		{
			if ((data->map_final[i][j]) == 'N' || (data->map_final[i][j]) == 'E'
			|| (data->map_final[i][j]) == 'W' || (data->map_final[i][j]) == 'S')
			{
				flag++;
				store_player_info(data, i, j);
				data->map_final[i][j] = 'P';
			}
			j++;
		}
		i++;
		j = 0;
	}
	if (flag != 1)
		ft_error("player position error !!\n", data);
}

void	re_allocate_map(t_cub *data)
{
	int		i;
	char	*tmp;

	i = 0;
	while (data->map_final[i])
	{
		tmp = data->map_final[i];
		data->map_final[i] = malloc(sizeof(char) * data->map_lines + 1);
		if (!data->map_final[i])
			ft_error("unable to allocate in re_allocate_map_final  !!!\n", data);
		ft_memcpy(data->map_final[i], tmp, ft_strlen(tmp));
		ft_memset(data->map_final[i] + ft_strlen(tmp), ' ', data->map_lines - \
			ft_strlen(tmp));
		data->map_final[i][data->map_lines] = '\0';
		free(tmp);
		i++;
	}
}

void	fill_map(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < data->map_lines - 1)
	{
		while (data->map_final[j])
		{
			if (data->map_final[j][i] != '1' && data->map_final[j][i] != '0' &&
				data->map_final[j][i] != 'P')
				data->map_final[j][i] = '1';
			j++;
		}
		i++;
		j = 0;
	}
}

void	check_map(t_cub *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map_final[i])
	{
		while (data->map_final[i][j])
		{
			if (data->map_final[i][j] == '0' || data->map_final[i][j] == 'P')
			{
				if (data->map_final[i + 1] == NULL || j < 1 || i < 1 || \
				data->map_final[i + 1][j] == ' ' || data->map_final[i - 1][j]
				== ' ' || data->map_final[i][j - 1] == ' ' || \
				data->map_final[i][j + 1] == ' ' || \
				data->map_final[i][j + 1] == '\0')
					ft_error("map is not closed\n", data);
			}
			j++;
		}
		i++;
		j = 0;
	}
}

void	mutate_map(t_cub *data)
{
	int	large_line;
	int	large_collumn;
	int	i;

	large_collumn = 0;
	large_line = 0;
	i = 0;
	while (data->map_final[i])
	{
		if (large_line < (int)ft_strlen(data->map_final[i]))
			large_line = (int)ft_strlen(data->map_final[i]);
		i++;
	}
	data->map_lines = large_line;
	re_allocate_map(data);
	check_map(data);
	fill_map(data);
}

void	parse_map(t_cub *data)
{
	int	i;

	i = 0;
	while (data->map[i] == ' ' || (data->map[i]) == '\n')
		i++;
	while ((data->map[i]) == '1' || (data->map[i]) == '0' || \
		(data->map[i]) == 'N' || (data->map[i]) == 'E' || \
		(data->map[i]) == 'W' || (data->map[i]) == 'S' || \
		(data->map[i]) == '\n' || (data->map[i]) == ' ')
	{
		if (data->map[i] == '\n' && (data->map[i + 1] == '\n' || \
			data->map[i + 1] == '\0'))
			ft_error("empty line inside the map !!\n", data);
		i++;
	}
	if ((data->map[i]) != '\0')
		ft_error("map error !!\n", data);
	data->map_final = ft_split(data->map, '\n');
	if (!data->map_final)
		ft_error("split cant allocate !!\n", data);
	get_ply_info(data);
	mutate_map(data);
}

void	read_map(t_cub *data)
{
	data->map = r_map(data->map_name);
	get_map_info(data);
	parse_info(data);
	parse_map(data);
}

void	parse(t_cub *data)
{
	init_my_data(data);
	read_map(data);
}

int	main(int ac, char **av)
{
	t_cub	*data;

	// atexit(check_leaks);
	if (ac != 2 || ft_strlen(av[1]) < 5 || \
		ft_strncmp((av[1] + ft_strlen(av[1]) - 4), ".cub", 4))
		ft_error("arguments error !\n", NULL);
	data = malloc(sizeof(t_cub));
	if (!data)
		ft_error("unable to allocate !", data);
	data->map_name = ft_strdup(av[1]);
	parse(data);
	free_data(data);
	printf("DONE\n");
	system("leaks cub3d");
}
