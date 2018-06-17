/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cwu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:02:19 by cwu               #+#    #+#             */
/*   Updated: 2018/06/06 17:02:22 by cwu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void			check_for_shadow(t_vars *vp, t_pt p, int i)
{
	t_pt	v;
	int		n;
	bool	b;
	float	tmp;

	((unsigned int*)vp->str)[i] = 0;
	vp->c_l = 0;
	while (vp->c_l < vp->n_l)
	{
		v = vector(p, vp->li[vp->c_l]);
		n = -1;
		b = 1;
		while (++n < vp->n_ob)
			if (vp->obj + n != vp->c_ob && 0 <
				(tmp = vp->obj[n].intersect(vp->obj[n], p, v)) && tmp < 1)
				b = 0;
		if (b)
			((unsigned int*)vp->str)[i] =
				add_color(vp->c_ob->light(vp, p), ((unsigned int*)vp->str)[i]);
		vp->c_l++;
	}
}

unsigned int	sphere_light(t_vars *vp, t_pt p)
{
	t_pt			l;
	t_pt			normal;
	t_pt			n;
	float			dot;
	unsigned int	ob_color;

	l = vector(p, vp->li[vp->c_l]);
	l = v_scale(l, (float)1.0 / norm(l));
	normal = translate(p, vp->c_ob->c);
	n = v_scale(normal, (float)1.0 / norm(normal));
	dot = l.x * n.x + l.y * n.y + l.z * n.z;
	if (dot < 0)
		return (0);
	ob_color = div_color(vp->n_l, t_color(dot, 0, vp->c_ob->color));
	if (vp->mode == 1 && dot > 0.96)
		ob_color = (t_color((cos(PI *
			pow((25 * (1 - dot)), 0.3)) + 1) / 2, ob_color, 0xffffff));
	else if (vp->mode == 2)
		ob_color = (t_color((cos(PI * pow(((1 - dot)), 0.3)) + 1) / 2,
			ob_color, vp->li[vp->c_l].sx));
	return (ob_color);
}

unsigned int	plane_light(t_vars *vp, t_pt p)
{
	t_pt			l;
	t_pt			n;
	float			dot;
	float			ll;
	unsigned int	ob_color;

	l = vector(p, vp->li[vp->c_l]);
	ll = norm(l);
	l = v_scale(l, (float)1.0 / ll);
	n = v_scale(vp->c_ob->normal, (float)1.0 / norm(vp->c_ob->normal));
	dot = l.x * n.x + l.y * n.y + l.z * n.z;
	if (dot < 0)
		return (0);
	ob_color = div_color(vp->n_l, t_color(dot, 0, vp->c_ob->color));
	if (vp->mode == 1 && dot > 0.96)
		ob_color = (t_color((cos(PI *
			pow((25 * (1 - dot)), 0.3)) + 1) / 2, ob_color, 0xffffff));
	else if (vp->mode == 2)
		ob_color = (t_color((cos(PI * pow(((1 - dot)), 0.3)) + 1) / 2,
			ob_color, vp->li[vp->c_l].sx));
	return (ob_color);
}

unsigned int	cylinder_light(t_vars *vp, t_pt p)
{
	t_pt			l;
	t_pt			n;
	float			dot;
	t_pt			normal;
	unsigned int	ob_color;

	l = cy_rot(*(vp->c_ob), vector(p, vp->li[vp->c_l]));
	l = v_scale(l, (float)1.0 / norm(l));
	normal.x = cy_rot(*(vp->c_ob), translate(p, vp->c_ob->c)).x;
	normal.z = cy_rot(*(vp->c_ob), translate(p, vp->c_ob->c)).z;
	normal.y = 0;
	n = v_scale(normal, (float)1.0 / norm(normal));
	dot = l.x * n.x + l.y * n.y + l.z * n.z;
	if (dot < 0)
		return (0);
	ob_color = div_color(vp->n_l, t_color(dot, 0, vp->c_ob->color));
	if (vp->mode == 1 && dot > 0.96)
		ob_color = (t_color((cos(PI *
			pow((25 * (1 - dot)), 0.3)) + 1) / 2, ob_color, 0xffffff));
	else if (vp->mode == 2)
		ob_color = (t_color((cos(PI * pow(((1 - dot)), 0.3)) + 1) / 2,
			ob_color, vp->li[vp->c_l].sx));
	return (ob_color);
}

unsigned int	cone_light(t_vars *vp, t_pt p)
{
	t_pt			l;
	t_pt			n;
	float			dot;
	t_pt			normal;
	unsigned int	ob_color;

	l = cy_rot(*(vp->c_ob), vector(p, vp->li[vp->c_l]));
	l = v_scale(l, (float)1.0 / norm(l));
	p = cy_rot(*(vp->c_ob), translate(p, vp->c_ob->c));
	normal.x = p.x;
	normal.z = p.z;
	normal.y = -copysign(pow(pow(normal.x, 2) +
		pow(normal.z, 2), 0.5) * vp->c_ob->r / 100, p.y);
	n = v_scale(normal, (float)1.0 / norm(normal));
	dot = l.x * n.x + l.y * n.y + l.z * n.z;
	if (dot < 0)
		return (0);
	ob_color = div_color(vp->n_l, t_color(dot, 0, vp->c_ob->color));
	if (vp->mode == 1 && dot > 0.96)
		ob_color = (t_color((cos(PI *
			pow((25 * (1 - dot)), 0.3)) + 1) / 2, ob_color, 0xffffff));
	else if (vp->mode == 2)
		ob_color = (t_color((cos(PI * pow(((1 - dot)), 0.3)) + 1) / 2,
			ob_color, vp->li[vp->c_l].sx));
	return (ob_color);
}
