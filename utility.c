/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:03:36 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:03:42 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

unsigned int	t_color(float t, unsigned int c_st, unsigned int c_ed)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = (unsigned int)((c_st >> 16) * (1 - t) + (c_ed >> 16) * t);
	g = (unsigned int)((c_st >> 8 & 255) * (1 - t) + (c_ed >> 8 & 255) * t);
	b = (unsigned int)((c_st & 255) * (1 - t) + (c_ed & 255) * t);
	return ((unsigned int)((r << 16) + (g << 8) + b));
}

unsigned int	div_color(int div, unsigned int color)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = (unsigned int)((color >> 16) / div);
	g = (unsigned int)((color >> 8 & 255) / div);
	b = (unsigned int)((color & 255) / div);
	return ((unsigned int)((r << 16) + (g << 8) + b));
}

unsigned int	add_color(unsigned int c1, unsigned int c2)
{
	unsigned int r;
	unsigned int g;
	unsigned int b;

	r = (unsigned int)((c1 >> 16) + (c2 >> 16) < 255 ?
	(c1 >> 16) + (c2 >> 16) : 255);
	g = (unsigned int)((c1 >> 8 & 255) + (c2 >> 8 & 255) < 255 ?
	(c1 >> 8 & 255) + (c2 >> 8 & 255) : 255);
	b = (unsigned int)((c1 & 255) + (c2 & 255) < 255 ?
	(c1 & 255) + (c2 & 255) : 255);
	return ((unsigned int)((r << 16) + (g << 8) + b));
}

int				max(int a, int b, int c)
{
	if (abs(a) > abs(b) && abs(a) > abs(c))
		return (abs(a));
	if (abs(b) > abs(c))
		return (abs(b));
	return (abs(c));
}

float			norm(t_pt p)
{
	return (pow(pow(p.x, 2) + pow(p.y, 2) + pow(p.z, 2), 0.5));
}
