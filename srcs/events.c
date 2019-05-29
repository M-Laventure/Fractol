#include "../includes/fractol.h"

int key_hook2(int keycode, t_env *fractol)
{
	if (keycode == 19)
		fractol->color = 2050;
	else if (keycode == 20)
		fractol->color = 265;
	else if (keycode == 35)
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
		fractol->it_max += 50;
	else if (keycode == 78)
		fractol->it_max -= 50;
	else if (keycode == 123)
		fractol->x1 -= 30 / fractol->zoom;
	else if (keycode == 124)
		fractol->x1 += 30 / fractol->zoom;
	else if (keycode == 125)
		fractol->y1 += 30 / fractol->zoom;
	else if (keycode == 126)
		fractol->y1 -= 30 / fractol->zoom;
	else if (keycode == 49)
		init_fractol(fractol, fractol->argv);
	else if (keycode == 18)
		fractol->color = 1677216;
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
	fractol->it_max++;
}

void	ft_dezoom(int x, int y, t_env *fractol)
{
	fractol->x1 = (x / fractol->zoom + fractol->x1)  - (x / (fractol->zoom / 1.3));
	fractol->y1 = (y / fractol->zoom + fractol->y1) - (y / (fractol->zoom / 1.3));
	fractol->zoom /= 1.3;
	fractol->it_max--;
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
	mlx_hook(fractol->win_ptr, 6, 1L<<6, julia_mouse, fractol);
	mlx_hook(fractol->win_ptr, 17, 0L, close, fractol);
	mlx_key_hook(fractol->win_ptr, key_hook, fractol);
	mlx_mouse_hook(fractol->win_ptr, mouse_hook, fractol);
}


