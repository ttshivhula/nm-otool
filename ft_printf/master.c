/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   master.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 10:39:12 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 09:02:43 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
** Lenbase takes the value and the base and return the exact number of chars
** that exist in the particular value...
*/

int				lenbase(long long value, int base)
{
	int len;

	len = 0;
	if (!value)
		return (1);
	if (value < 0)
	{
		value = -value;
		if (base == 10)
			len++;
	}
	len++;
	value /= base;
	while (value)
	{
		value /= base;
		len++;
	}
	return (len);
}

/*
** This function will set  the length when called, & must be called last.
*/

static void		set_lenth(t_fmt *f, char **fmt, va_list ap)
{
	asteric(f, fmt, ap, 0);
	while (*(*fmt) == 'l' || *(*fmt) == 'h' || *(*fmt) == 'j' || *(*fmt) == 'z')
	{
		if (*(*fmt) == 'l' && *((*fmt) + 1) == 'l')
		{
			f->ll = 1;
			(*fmt)++;
		}
		else if (*(*fmt) == 'l')
			f->l = 1;
		if (*(*fmt) == 'h' && *((*fmt) + 1) == 'h')
		{
			(*fmt)++;
			f->hh = 1;
		}
		else if (*(*fmt) == 'h')
			f->h = 1;
		if (*(*fmt) == 'j')
			f->j = 1;
		if (*(*fmt) == 'z')
			f->z = 1;
		(*fmt)++;
	}
}

/*
** This initializes the printf flags and it is supposed to be called first.
*/

static void		prec(t_fmt *f, char **fmt, va_list ap)
{
	if (*(*fmt) == '.')
	{
		f->prec = 1;
		if (*(*fmt + 1) >= '1' && *(*fmt + 1) <= '9')
		{
			(*fmt)++;
			f->prec = ft_atoi(*fmt);
			*fmt += lenbase(f->prec, 10);
		}
		else if (*(*fmt) == '*')
			asteric(f, fmt, ap, 1);
	}
}

static void		set_flags(t_fmt *f, char **fmt, va_list ap)
{
	while (*(*fmt) == '#' || *(*fmt) == '-' || *(*fmt) == '+'
			|| *(*fmt) == '0' || *(*fmt) == ' ' || *(*fmt) == '.')
	{
		if (*(*fmt) == '#')
			f->hash = 1;
		if (*(*fmt) == '-')
			f->left = 1;
		if (*(*fmt) == '+')
			f->sign = 1;
		if (*(*fmt) == ' ')
			f->space = 1;
		if (*(*fmt) == '0')
			f->zero = 1;
		(*fmt)++;
		if (*(*fmt) == '.')
			prec(f, fmt, ap);
	}
	asteric(f, fmt, ap, 0);
}

/*
** This is where all the fucking happens, this modifies the width and calls, the
** rest of this other functions..
*/

void			set_format(t_fmt *f, char **fmt, va_list ap)
{
	(*fmt)++;
	prec(f, fmt, ap);
	set_flags(f, fmt, ap);
	if (*(*fmt) >= '1' && *(*fmt) <= '9')
	{
		f->width = ft_atoi(*fmt);
		*fmt += lenbase(f->width, 10);
	}
	if (*(*fmt) == '.')
	{
		(*fmt)++;
		if (*(*fmt) >= '1' && *(*fmt) <= '9')
		{
			f->prec = ft_atoi(*fmt);
			*fmt += lenbase(f->prec, 10);
		}
		else if (*(*fmt) == '*')
			asteric(f, fmt, ap, 1);
		else if (*(*fmt) == '0')
			(*fmt)++;
	}
	set_lenth(f, fmt, ap);
}
