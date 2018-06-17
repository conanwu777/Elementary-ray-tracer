/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldehaudt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/06 17:32:39 by ldehaudt          #+#    #+#             */
/*   Updated: 2018/06/06 17:32:42 by ldehaudt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int		ptos(t_pt p)
{
	int c;

	c = (-p.sy + H / 2) * W + (p.sx + W / 2);
	return (c);
}

int		ft_atoi_base(const char *str, int str_base)
{
	char	*hex;
	char	*t;
	int		i;
	int		sign;
	int		sum;

	sum = 0;
	sign = 1;
	hex = "0123456789abcdef";
	t = (char*)str;
	if (*t == '-')
	{
		sign = -1;
		t++;
	}
	while (*t)
	{
		i = -1;
		while (++i < str_base)
			if (*t == hex[i] || (i > 9 && *t == hex[i] + ('A' - 'a')))
				sum = sum * str_base + sign * i;
		t++;
	}
	return (sum);
}

int		num_len(int num)
{
	int length;

	length = 1;
	if (num < 0)
		length++;
	while (num >= 10 || num <= -10)
	{
		num /= 10;
		length++;
	}
	return (length);
}

bool	read_cont(t_vars *vp, int fd, char *line, bool fail)
{
	vp->eye.y = fail ? 0 : ft_atoi(line + 7 + num_len(vp->eye.x));
	vp->eye.z = fail ? 0 : ft_atoi(line + 8 + num_len(vp->eye.x)
	+ num_len(vp->eye.y));
	fail ? 0 : free(line);
	fail = !ft_gnl(fd, &line);
	vp->rot.x = fail ? 0 : ft_atoi(line + 8) * (PI / 180.0);
	vp->rot.y = fail ? 0 : ft_atoi(line + 10 + num_len(vp->rot.x))
	* (PI / 180.0);
	free(line);
	while (!fail && vp->c_ob < vp->obj + vp->n_ob)
	{
		fail = !ft_gnl(fd, &line);
		free(line);
		fail = !ft_gnl(fd, &line);
		fail = (fail == false) ? check_shape(fd, vp, &line) : true;
		free(line);
		while (!fail && ft_gnl(fd, &line) && ft_strcmp(line, "end"))
		{
			fail = check_properties(vp, &line);
			free(line);
		}
		(fail == false) ? free(line) : 0;
		vp->c_ob++;
	}
	return (!(fail || vp->c_l != vp->n_l || get_next(fd, &line, " ") != 0));
}

bool	read_map(t_vars *vp, char *file)
{
	int		fd;
	char	*line;
	bool	fail;

	fail = false;
	fd = open(file, O_RDONLY);
	if (fd == -1 || read(fd, NULL, 0) == -1)
		return (false);
	fail = !ft_gnl(fd, &line);
	vp->n_ob = fail ? 0 : ft_atoi(line + 13);
	fail ? 0 : free(line);
	fail = !ft_gnl(fd, &line);
	vp->n_l = fail ? 0 : ft_atoi(line + 12);
	fail ? 0 : free(line);
	vp->li = fail ? NULL : (t_pt*)malloc(vp->n_l * sizeof(t_pt));
	vp->obj = fail ? NULL : (t_obj*)malloc(vp->n_ob * sizeof(t_obj));
	vp->c_ob = fail ? NULL : vp->obj;
	vp->c_l = 0;
	fail = !ft_gnl(fd, &line);
	fail ? 0 : free(line);
	fail = !ft_gnl(fd, &line);
	fail ? 0 : free(line);
	fail = !ft_gnl(fd, &line);
	vp->eye.x = fail ? 0 : ft_atoi(line + 6);
	return (read_cont(vp, fd, line, fail));
}
