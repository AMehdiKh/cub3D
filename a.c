#include <stdio.h>

// Function to draw a pixel
void drawPixel(int x, int y) {
	printf("(%d, %d)\n", x, y);
}

// Bresenham's circle drawing algorithm
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

// Flood fill algorithm
void floodFill(int x, int y, int fillColor, int targetColor) {
	// Assuming implementation of filling logic here
	// This is a basic example and a detailed implementation may be needed for a practical application
	// Recursive calls or a stack-based approach may be used for a real implementation
	printf("Filling the circle at position (%d, %d) with color: %d\n", x, y, fillColor);
}

// Function to draw and fill a circle
void	ft_circle(t_mlx *mlx, int xc, int yc, int r, int color)
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
		if (d < 0) 
			d = d + (4 * x) + 6;
		else
		{
			d = d + (4 * (x - y)) + 10;
			y -= 1;
		}
		++x;
	}
}

// Driver program
int main() {
	int xc = 16, yc = 16, r = 10;
	int fillColor = 1; // Fill color
	int targetColor = 0; // Target color
	drawAndFillCircle(xc, yc, r, fillColor, targetColor);
	return 0;
}



// void	ft_cast_rays(t_mlx	*mlx)
// {
// 	t_player	*player_data;
// 	t_cord		wall_hit[1];
// 	double		ray_angle;
// 	int			i;

// 	player_data = mlx->player_data;
// 	ray_angle = player_data->rotation_angle - (player_data->field_of_view / 2);
// 	i = 0;
// 	while (ray_angle < player_data->rotation_angle + (player_data->field_of_view / 2))
// 	{

// 		// ft_V_intersection();
// 		ft_H_intersection(mlx->map_data->map, player_data);
// 		// wall_hitft_nearest_point();
// 		dda(mlx, player_data->player, wall_hit);
// 		ray_angle += player_data->field_of_view / player_data->num_rays;
// 		++i;
// 	}
// }

// void	ft_H_intersection(char **map, t_cord *player, double ray_angle)
// {
// 	t_cord	intersection[1];
// 	int		x_step;
// 	int		y_step;
// 	int		x_first;
// 	int		y_first;

// 	x_step = TILE_SIZE / tan(ray_angle);
// 	y_step = TILE_SIZE;
// 	y_first = (player->y / TILE_SIZE) * TILE_SIZE;
// 	x_first = player->x + abs(player->y - y_first) / tan(ray_angle);
// 	ft_init_cord(intersection, x_first, y_first);
// 	while (map[intersection->y / TILE_SIZE][intersection->x / TILE_SIZE] != '1')
// 	{
// 		intersection->x += x_step;
// 		intersection->y += y_step;
// 	}
// }
