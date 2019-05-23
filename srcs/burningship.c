#include "../includes/fractol.h"

void	burningship_calc(t_fractol *fractol)
{
	fractol->c_r = fractol->x / fractol->zoom + fractol->x1;
	fractol->c_i = fractol->y / fractol->zoom + fractol->y1;
	fractol->z_r = 0;
	fractol->z_i = 0;
	fractol->it = 0;
	while (fractol->z_r * fractol->z_r + fractol->z_i * fractol->z_i < 4
			&& fractol->it < fractol->it_max)
	{
		fractol->tmp = fractol->z_r * fractol->z_r - fractol->z_i * fractol->z_i + fractol->c_r;
		fractol->z_i = fabs(2 * fractol->z_r * fractol->z_i) + fractol->c_i;
		fractol->z_r = fractol->tmp;
		fractol->it++;
	}
	if (fractol->it == fractol->it_max)
		put_pxl_to_img(fractol, fractol->x, fractol->y, 0x000000);
	else
		put_pxl_to_img(fractol, fractol->x, fractol->y, (fractol->color * fractol->it));
}

