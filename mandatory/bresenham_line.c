/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-khel <ael-khel@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:20:10 by ael-khel          #+#    #+#             */
/*   Updated: 2023/11/13 15:53:58 by ael-khel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void dda(t_mlx *mlx, int X0, int Y0, int X1, int Y1) {
//     int dx = X1 - X0;
//     int dy = Y1 - Y0;
//     int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
//     double Xinc = dx / (double) steps;
//     double Yinc = dy / (double) steps;
//     double X = X0;
//     double Y = Y0;

//     for (int i = 0; i <= steps; i++) {
// 		mlx_put_pixel(mlx->img, X, Y, 0X5B305AFF);
//         X += Xinc;
//         Y += Yinc;
//     }
// }

void dda(t_mlx *mlx, int X0, int Y0, int X1, int Y1) {
    int dx = abs(X1 - X0);
    int dy = abs(Y1 - Y0);
    int twoDy = 2 * dy;
    int twoDx = 2 * dx;
    int decisionParameter;

    int slopeSignX = (X1 - X0 > 0) ? 1 : -1;
    int slopeSignY = (Y1 - Y0 > 0) ? 1 : -1;

    int x = X0;
    int y = Y0;

    // Plot the initial point
    mlx_put_pixel(mlx->img, x, y, 0X5B305AFF);


    // For lines with slope between 0 and 1
    if (dy <= dx) {
        decisionParameter = twoDy - dx;

        while (x != X1) {
            x += slopeSignX;
            if (decisionParameter < 0) {
                decisionParameter += twoDy;
            } else {
                decisionParameter += twoDy - twoDx;
                y += slopeSignY;
            }
		mlx_put_pixel(mlx->img, x, y, 0X5B305AFF);

        }
    }
    // For lines with slope greater than 1
    else {
        decisionParameter = twoDx - dy;

        while (y != Y1) {
            y += slopeSignY;
            if (decisionParameter < 0) {
                decisionParameter += twoDx;
            } else {
                decisionParameter += twoDx - twoDy;
                x += slopeSignX;
            }
			mlx_put_pixel(mlx->img, x, y, 0X5B305AFF);

        }
    }
}

void	bresenhams_line(t_mlx *mlx, int x1, int y1, int x2, int y2)
{
	int	diff_x;
	int	diff_y;
	int	slope;
	int	decision_param;
	int	x;
	int	y;

	diff_x = x2 - x1;
	diff_y = y2 - y1;
	slope = diff_y / diff_x;
	if (slope < 1)
	{
		decision_param = (2 * diff_y) - diff_x;
		x = x1;
		y = y1;
		if (diff_x < 0)
		{
			x = x2;
			y = y2;
			x2 = x1;
		}
		mlx_put_pixel(mlx->img, x, y, 0x00FF00);
		while (x < x2)
		{
			if (decision_param >= 0)
			{
				x = x + 1;
				if (diff_y < 0)
					y = y + 1;
				else
					y = y - 1;
				decision_param += ((2 * diff_y) - (2 * diff_x) * (y + 1 - y));
			}
			else
			{
				x = x + 1;
				decision_param += ((2 * diff_y) - (2 * diff_x) * (y - y));
			}
			mlx_put_pixel(mlx->img, x, y, 0x00FF00);
		}
	}
	else if (slope > 1)
	{
		decision_param = (2 * diff_x) - diff_y;
		x = x1;
		y = y1;
		if (diff_y < 0)
		{
			x = x2;
			y = y2;
			y2 = y1;
		}
		mlx_put_pixel(mlx->img, x, y, 0x00FF00);
		while (y < y2)
		{
			if (decision_param >= 0)
			{
				if (diff_x < 0)
					x = x + 1;
				else
					x = x - 1;
				y = y + 1;
				decision_param += ((2 * diff_x) - (2 * diff_y) * (x + 1 - x));
			}
			else
			{
				y = y + 1;
				decision_param += ((2 * diff_x) - (2 * diff_y) * (x - x));
			}
			mlx_put_pixel(mlx->img, x, y, 0x00FF00);
		}
	}
	else if (slope == 1)
	{
		x = x1;
		y = y1;
		if (diff_x < 0)
		{
			x = x2;
			y = y2;
			x2 = x1;
		}
		mlx_put_pixel(mlx->img, x, y, 0x00FF00);
		while (x < x2)
		{
			x = x + 1;
			y = y + 1;
			mlx_put_pixel(mlx->img, x, y, 0x00FF00);
		}
	}
}
