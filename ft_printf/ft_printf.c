/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 10:44:58 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/14 09:32:53 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		cut1(char **s, t_fmt *f, va_list ap, t_vars v)
{
	if (*(*s) == 'd' || *(*s) == 'i' || *(*s) == 'D')
	{
		if (*(*s) == 'D')
			f->wide = 1;
		++(*s);
		return (handle_d(v, ap, f));
	}
	if (*(*s) == 'u' || *(*s) == 'U')
	{
		if (*(*s) == 'U')
			f->wide = 1;
		++(*s);
		return (unsigned_d(v, ap, f));
	}
	if (*(*s) == 'x' || *(*s) == 'X')
	{
		if (*(*s) == 'X')
			f->wide = 1;
		++(*s);
		return (handle_hex(v, ap, f));
	}
	return (0);
}

static int		cut2(char **s, t_fmt *f, va_list ap, t_vars v)
{
	if (*(*s) == 'p')
	{
		++(*s);
		return (handle_p(v, ap, f));
	}
	if (*(*s) == 's')
	{
		++(*s);
		return (handle_s(v, ap, f));
	}
	if (*(*s) == 'S')
	{
		++(*s);
		return (handle_ws(v, ap, f));
	}
	if (*(*s) == 'o' || *(*s) == 'O')
	{
		f->wide = (*(*s) == 'O') ? 1 : 0;
		++(*s);
		return (handle_o(v, ap, f));
	}
	++(*s);
	return (percent(v, f));
}

static int		cut3(va_list ap, t_fmt *f, char **s)
{
	++(*s);
	return (ft_putfloat(ap, f));
}

static int		processor(char **s, t_fmt *f, va_list ap)
{
	t_vars		v;

	v.init = 14;
	set_format(f, s, ap);
	if (*(*s) == 'd' || *(*s) == 'i' || *(*s) == 'D' || *(*s) == 'X' ||
			*(*s) == 'x' || *(*s) == 'u' || *(*s) == 'U')
		return (cut1(s, f, ap, v));
	if (*(*s) == '%' || *(*s) == 'O' || *(*s) == 'o' || *(*s) == 'S' ||
			*(*s) == 's' || *(*s) == 'p')
		return (cut2(s, f, ap, v));
	if (*(*s) == 'c' || *(*s) == 'b')
	{
		f->wide = (*(*s) == 'b') ? 1 : 0;
		++(*s);
		return (f->wide ? binary(v, ap, f) : handle_c(v, ap, f));
	}
	if (*(*s) == 'C')
	{
		++(*s);
		return (handle_wc(v, ap, f));
	}
	if (*(*s) == 'f' || *(*s) == 'F')
		return (cut3(ap, f, s));
	return (0);
}

/*
** Looks for the formating character % and calls the processor which then calls
** other functions that does all the printfing, keeping a record of number of
** characters written but if we dont find the formating character we just print
** and move the pointer to the next cell...
*/

int				ft_printf(const char *format, ...)
{
	int		printed;
	char	*s;
	t_fmt	f;
	va_list	ap;

	va_start(ap, format);
	printed = 0;
	s = (char *)format;
	while (*s)
	{
		if (*s == '%')
		{
			clean(&f);
			printed += processor(&s, &f, ap);
		}
		else if (*s == '{')
			printed += set_color(&s);
		else
		{
			printed += write(1, s, 1);
			s++;
		}
	}
	va_end(ap);
	return (printed);
}
