/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/07 08:37:24 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 08:47:35 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_putstr_n(char *s, int len)
{
	int i;

	i = 0;
	while (i < len)
		write(1, &s[i++], 1);
}

static int		init_s(t_vars *v, va_list ap, t_fmt *f)
{
	int l;

	l = 0;
	v->s = va_arg(ap, char *);
	if (!v->s)
	{
		ft_putstr("(null)");
		return (1);
	}
	if (f->prec)
		l = f->prec;
	v->len = ft_strlen(v->s);
	if (l && v->len)
		v->len = (l < v->len) ? l : v->len;
	return (0);
}

int				handle_s(t_vars v, va_list ap, t_fmt *f)
{
	if (init_s(&v, ap, f) == 1)
		return (6);
	v.df = 0;
	if ((f->width > v.len) && !f->left)
	{
		v.df = f->width - v.len;
		(f->zero) ? ft_putnchar('0', v.df) : ft_putnchar(' ', v.df);
	}
	ft_putstr_n(v.s, v.len);
	if ((f->width > v.len) && f->left)
	{
		v.df = f->width - v.len;
		ft_putnchar(' ', v.df);
	}
	if (v.df)
		return (f->width);
	return (v.len);
}

int				percent(t_vars v, t_fmt *f)
{
	v.s = "%";
	v.len = 1;
	v.df = 0;
	if ((f->width > v.len || f->prec > v.len) && !f->left)
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		(f->prec || f->zero) ? ft_putnchar('0', v.df) : ft_putnchar(' ', v.df);
	}
	ft_putstr(v.s);
	if (f->width > v.len && f->left)
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		ft_putnchar(' ', v.df);
	}
	if (v.df)
		return (f->width ? f->width : f->prec);
	return (v.len);
}

int				handle_c(t_vars v, va_list ap, t_fmt *f)
{
	v.c = (char)va_arg(ap, int);
	v.len = 1;
	v.df = 0;
	if (((f->width > v.len || f->prec > v.len) && !f->left))
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		(f->zero) ? ft_putnchar('0', v.df) : ft_putnchar(' ', v.df);
	}
	ft_putchar(v.c);
	if ((v.c >= 0) && (f->width > v.len && f->left))
	{
		v.df = (f->width) ? f->width - v.len : f->prec - v.len;
		ft_putnchar(' ', v.df);
	}
	if (v.df)
		return (f->width ? f->width : f->prec);
	return (v.len);
}
