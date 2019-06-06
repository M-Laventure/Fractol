#include "../includes/fractol.h"
#include <stdio.h>

int	ft_close(void)
{
	exit(1);
	return (0);
}
void	fill_pxl(t_env *fractol, int x, int y, int color)
{
	if (fractol->x < fractol->width && fractol->y < fractol->height)
		fractol->img_data[y * fractol->height + x] = color;
}

void	init_win(t_env *fractol)
{
	fractol->mlx_ptr = mlx_init();
	if (!fractol->width || !fractol->height || fractol->width > 2560 || fractol->height > 1440)
	{
		ft_putendl("Incorrect value for window's size, setting to default size");
		fractol->width = WIDTH;
		fractol->height = HEIGHT;
	}
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, fractol->width, fractol->height, "Fractol");
	fractol->img = mlx_new_image(fractol->mlx_ptr, fractol->width , fractol->height);
	fractol->img_data = (unsigned int *)mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
}

void init_fractol(t_env *fractol, char **argv)
{
	if (ft_strcmp(argv[1], "julia") == 0)
		init_julia(fractol);
	if (ft_strcmp(argv[1], "burningship") == 0)
		init_burn(fractol);	
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		init_mandel(fractol);
	fractol->psych_mod = -1;
}


