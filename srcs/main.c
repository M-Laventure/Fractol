/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malavent <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 08:29:19 by malavent          #+#    #+#             */
/*   Updated: 2019/06/06 10:58:32 by malavent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	t_env *fractol;

	if (argc != 2 && argc != 4)
	{
		ft_putendl(USAGE);
		exit(-1);
	}
	if (!(fractol = (t_env *)malloc(sizeof(t_env))))
		return (-1);
	if (argc == 4)
	{
		fractol->width = ft_atoi(argv[2]);
		fractol->height = ft_atoi(argv[3]);
	}
	init_win(fractol);
	init_fractol(fractol, argv);
	void	(*make_fractale[3])(t_env *) = {make_julia, make_mandelbrot, make_burningship};
	printf("id_frac : %d\n", fractol->id_fractale);
	make_fractale[fractol->id_fractale](fractol);
	handle_events(fractol);
	mlx_loop(fractol->mlx_ptr);
	return (0);
}

