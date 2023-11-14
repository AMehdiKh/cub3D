void	ft_draw_pixels(t_mlx *mlx, int xc, int yc, int x, int y, int color)
{
	mlx_put_pixel(mlx->img, xc + x, yc + y, color);
	mlx_put_pixel(mlx->img, xc - x, yc + y, color);
	mlx_put_pixel(mlx->img, xc + x, yc - y, color);
	mlx_put_pixel(mlx->img, xc - x, yc - y, color);
	mlx_put_pixel(mlx->img, xc + y, yc + x, color);
	mlx_put_pixel(mlx->img, xc - y, yc + x, color);
	mlx_put_pixel(mlx->img, xc + y, yc - x, color);
	mlx_put_pixel(mlx->img, xc - y, yc - x, color);
}

void	ft_bresenham_circle(t_mlx *mlx, int xc, int yc, int r, int color)
{
	int	x;
	int	y;
	int	d;

	x = 0;
	y = r;
	d = 3 - (2 * r);
	while (x < y)
	{
		ft_draw_pixels(mlx, xc, yc, x, y, color);
		if (d <= 0) 
			d = d + (4 * x) + 6;
		else
		{
			d = d + (4 * (x - y)) + 10;
			y -= 1;
		}
		++x;
	}
}