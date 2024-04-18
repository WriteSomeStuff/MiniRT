// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        ::::::::            */
// /*   cube.c                                             :+:    :+:            */
// /*                                                     +:+                    */
// /*   By: vvan-der <vvan-der@student.codam.nl>         +#+                     */
// /*                                                   +#+                      */
// /*   Created: 2023/11/16 13:25:29 by vvan-der      #+#    #+#                 */
// /*   Updated: 2023/11/17 16:54:54 by cschabra      ########   odam.nl         */
// /*                                                                            */
// /* ************************************************************************** */

// #include "miniRT.h"

// void	rotate_rectangle(t_data *data, t_complex a, t_complex b, \
// t_complex c, t_complex d, int32_t angle)
// {
// 	float theta;

// 	(void)a;
// 	(void)b;
// 	(void)c;
// 	(void)d;
// 	(void)data;
// 	theta = (float)(angle % 360) * PI/180;
// 	a.x = cos(theta) - sin(theta);
// 	a.y = 
// 	b.x = 
// 	b.y = 
// 	c.x = 
// 	c.y = 
// 	d.x = 
// 	d.y = 
// 	printf("Theta: %f\n", theta);
// 	// exit(0);
// }

// void	draw_rectangle(t_data *data, uint32_t wide, uint32_t high, t_complex center)
// {
// 	t_complex a, b, c, d, middle;
// 	float	x;
// 	float	y;

// 	middle.x = WIDTH / 2;
// 	middle.y = HEIGHT / 2;
// 	a.x = middle.x - wide / 2;
// 	a.y = middle.y - high / 2;
// 	b.x = middle.x + wide / 2;
// 	b.y = middle.y - high / 2;
// 	c.x = middle.x - wide / 2;
// 	c.y = middle.y + high / 2;
// 	d.x = middle.x + wide / 2;
// 	d.y = middle.y + high / 2;
// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < HEIGHT)
// 		{
// 			if ((x >= a.x && x <= b.x) && (y == a.y || y == c.y))
// 				mlx_put_pixel(data->scene, x, y, ft_pixel(100, 0, 255, 255));
// 			else if ((x == a.x || x == b.x) && (y >= a.y && y <= c.y))
// 				mlx_put_pixel(data->scene, x, y, ft_pixel(100, 0, 255, 255));
// 			y++;
// 		}
// 		x++;
// 	}
// 	// rotate_rectangle(data, a, b, c, d, 18);
// }

// void	draw_cube(t_data *data, t_complex center)
// {
// 	t_complex	center2;

// 	center2.x = WIDTH / 2 + 10;
// 	center2.x = HEIGHT / 2 + 10;
// 	draw_rectangle(data, 200, 200, center);
// 	draw_rectangle(data, 200, 200, center2);
// 	draw_line(data, )
// }

// void	draw_background(t_data *data)
// {
// 	int	x;
// 	int	y;

// 	x = 0;
// 	while (x < WIDTH)
// 	{
// 		y = 0;
// 		while (y < HEIGHT)
// 		{
// 			mlx_put_pixel(data->scene, x, y, ft_pixel(0, 0, 0, 0xFF));
// 			y++;
// 		}
// 		x++;
// 	}
// }

// void	draw_line(t_data *data, t_complex start, t_complex end)
// {
// 	float	len;
// 	float	angle;
// 	int		dx;
// 	int		dy;

// 	dx = end.x - start.x;
// 	dy = end.y - start.y;
// 	len = (float)sqrt(dx * dx + dy * dy);
// 	angle = atan2(dy, dx);
// 	while (len > 0)
// 	{
// 		mlx_put_pixel(data->scene, (uint32_t)start.x + cos(angle) * len, \
// 		(uint32_t)start.y + sin(angle) * len, ft_pixel(100, 0, 255, 255));
// 		len--;
// 	}
// }