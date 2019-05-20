#include "../includes/fractol.h"

void	fill_pxl(t_env *fractol, int x, int y, int color)
{
	if	(x < fractol->width && y < fractol->height && x >= 0 && y >= 0)
		fractol->img_data[y * WIDTH + x] = color;
}

void	init_win(t_env *fractol, char **argv)
{
	fractol->mlx_ptr = mlx_init();
	fractol->width = ft_atoi(argv[2]);
	fractol->height = ft_atoi(argv[3]);
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, fractol->width, fractol->height, "Fractol");
	fractol->img_ptr = mlx_new_image(fractol->mlx_ptr, fractol->width, fractol->height);
	fractol->img_data = (int *)mlx_get_data_addr(fractol->mlx_ptr, &fractol->bpp, &fractol->size_line, &fractol->endian);
}

void init_fractol(t_env *fractol, char **argv)
{
	//ft_bzero(fractol, sizeof(t_env *));
	init_win(fractol, argv);
	if (ft_strcmp(argv[1], "julia"))
		fractol->id_fractale = julia;
	if (ft_strcmp(argv[1], "burningship"))
		fractol->id_fractale = burningship;
	if (ft_strcmp(argv[1], "mandelbrot"))
		fractol->id_fractale = mandelbrot;
}


