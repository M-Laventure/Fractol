#include "../includes/fractol.h"
#include <stdio.h>

int	ft_close(void)
{
	exit(1);
	return (0);
}
void	fill_pxl(t_env *fractol, int x, int y, int color)
{
	if (fractol->x < WIDTH && fractol->y < WIDTH)
	{
		color = mlx_get_color_value(fractol->mlx_ptr, color);
		ft_memcpy(fractol->img_data + 4 * WIDTH * y + x * 4, &color, sizeof(int));
	}

}

void	init_win(t_env *fractol)
{
	fractol->mlx_ptr = mlx_init();
	fractol->win_ptr = mlx_new_window(fractol->mlx_ptr, WIDTH, WIDTH, "Fractol");
	fractol->img = mlx_new_image(fractol->mlx_ptr, WIDTH, WIDTH);
	fractol->img_data = mlx_get_data_addr(fractol->img, &fractol->bpp, &fractol->size_line, &fractol->endian);
}

void init_fractol(t_env *fractol, char **argv)
{
	init_win(fractol);
	if (ft_strcmp(argv[1], "julia") == 0)
		init_julia(fractol);
	if (ft_strcmp(argv[1], "burningship") == 0)
		init_burn(fractol);	
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
		init_mandel(fractol);
}


