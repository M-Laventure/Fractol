#include "../includes/fractol.h"

int	julia_mouse(int x, int y, t_env *fractol)
{
	if (fractol->fract == 1 && fractol->mouse == 1)
	{
		fractol->c_r = x * 2;
		fractol->c_i = y * 2 - 800;
		make_fractale[fractol->id_fractale - 1](fractol);
	}
	return (0);
}

void	*julia(void *fractol)
{
	int		tmp;
	t_fractol	*data;

	data = (t_fractol *)fractol;
	data->x = 0;
	tmp = data->y;
	while (data->x < WIDTH)
	{
		data->y = tmp;
		while (data->y < data->y_max)
		{
			julia_calc(data);
			data->y++;
		}
		data->x++;
	}
	return (fractol);
}


void	julia_calc(t_fractol *data)
{
	data->z_r = data->x / data->zoom + data->x1;
	data->z_i = data->y / data->zoom + data->y1;
	data->it = 0;
	while (data->z_r * data->z_r + data->z_i
			* data->z_i < 4 && data->it < data->it_max)
	{
		data->tmp = data->z_r;
		data->z_r = data->z_r * data->z_r -
			data->z_i * data->z_i - 0.8 + (data->c_r / WIDTH);
		data->z_i = 2 * data->z_i * data->tmp + data->c_i / WIDTH;
		data->it++;
	}
	if (data->it == data->it_max)
		put_pxl_to_img(data, data->x, data->y, 0x000000);
	else
		put_pxl_to_img(data, data->x, data->y, (data->color * data->it));
}

