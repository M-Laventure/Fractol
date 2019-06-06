#include "../includes/fractol.h"

int key_hook2(int keycode, t_env *fractol)
{
	if (keycode == 14)
	{
		ft_putendl("hre");
		printf("%d\n", fractol->psych_mod);
		fractol->psych_mod = -fractol->psych_mod;
	}
	if (keycode == 15)
		fractol->color = 0x990000;
	else if (keycode == 5)
	{
		ft_putendl("hre");
		fractol->color = 0x009e00;
	}
	else if (keycode == 11)
		fractol->color = 0x000096;
	else if (keycode == 35) //put the julia constant in pause
		fractol->mouse = !fractol->mouse;
	else if (keycode == 34)
		fractol->show_text = !fractol->show_text;
	return (0);
}

int		key_hook(int keycode, t_env *fractol)
{
	if (keycode == 53)
		exit(1);
	else if (keycode == 69)
		fractol->iter_max += 50;
	else if (keycode == 78)
		fractol->iter_max -= 50;
	else if (keycode == 123) // left
		fractol->x1 += 30 / fractol->zoom;
	else if (keycode == 124) //right
		fractol->x1 -= 30 / fractol->zoom;
	else if (keycode == 125) // up 
		fractol->y1 -= 30 / fractol->zoom;
	else if (keycode == 126) // down
		fractol->y1 += 30 / fractol->zoom;
	else if (keycode == 49) // space bar : reset
		init_fractol(fractol, fractol->argv);
	key_hook2(keycode, fractol);
//	fract_calc(fractol);	
	void	(*make_fractale[3])(t_env *) = {make_julia, make_mandelbrot, make_burningship};
	make_fractale[fractol->id_fractale](fractol);
	return (0);
}

void	ft_zoom(int x, int y, t_env *fractol)
{
	fractol->x1 = (x / fractol->zoom + fractol->x1) - (x / (fractol->zoom * 1.3));
	fractol->y1 = (y / fractol->zoom + fractol->y1) - (y / (fractol->zoom * 1.3));
	fractol->zoom *= 1.3;
	fractol->iter_max++;
}

void	ft_dezoom(int x, int y, t_env *fractol)
{
	fractol->x1 = (x / fractol->zoom + fractol->x1)  - (x / (fractol->zoom / 1.3));
	fractol->y1 = (y / fractol->zoom + fractol->y1) - (y / (fractol->zoom / 1.3));
	fractol->zoom /= 1.3;
	fractol->iter_max--;
}

int		mouse_hook(int mousecode, int x, int y, t_env *fractol)
{
	if (mousecode == 4 || mousecode == 1)
		ft_zoom(x, y, fractol);
	else if (mousecode == 5 || mousecode == 2)
		ft_dezoom(x, y, fractol);
	void	(*make_fractale[3])(t_env *) = {make_julia, make_mandelbrot, make_burningship};
	make_fractale[fractol->id_fractale](fractol);
	//fract_calc(fractol);
	return (0);
}

void	handle_events(t_env *fractol)
{
	mlx_hook(fractol->win_ptr, 6, 1L << 6, julia_mouse, fractol);
	mlx_hook(fractol->win_ptr, 17, 0L, close, fractol);
	mlx_key_hook(fractol->win_ptr, key_hook, fractol);
	mlx_mouse_hook(fractol->win_ptr, mouse_hook, fractol);
}


