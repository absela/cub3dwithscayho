/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abelahce <abelahce@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 00:05:13 by abelahce          #+#    #+#             */
/*   Updated: 2023/04/03 01:38:19 by abelahce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

int	main(int ac, char **av)
{
	t_cub	*data;

	if (ac != 2 || ft_strlen(av[1]) < 5 || \
		ft_strncmp((av[1] + ft_strlen(av[1]) - 4), ".cub", 4))
		ft_error("arguments error !\n", NULL);
	data = malloc(sizeof(t_cub));
	if (!data)
		ft_error("unable to allocate !", data);
	data->map_name = ft_strdup(av[1]);
	parse(data);
	free_data(data);
}
	// atexit(check_leaks);
	// system("leaks cub3d");
	// while (1);
