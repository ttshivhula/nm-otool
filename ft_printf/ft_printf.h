/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/31 10:41:16 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 12:29:22 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <inttypes.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>
# include "libft/libft.h"

typedef struct		s_vars
{
	char				*s;
	char				c;
	wchar_t				wc;
	wchar_t				*ws;
	long long			i;
	unsigned			ui;
	long				l;
	long long			ll;
	int					len;
	int					df;
	int					init;
}					t_vars;

typedef struct		s_bools
{
	int				sp;
	int				h;
	int				special;
	int				s;
	int				after;
	int				n;
}					t_bools;

typedef struct		s_fmt
{
	int				hash;
	int				zero;
	int				space;
	int				sign;
	int				left;
	int				l;
	int				ll;
	int				h;
	int				hh;
	int				j;
	int				z;
	int				prec;
	int				width;
	int				wide;
}					t_fmt;

void				clean(t_fmt *f);
void				boolclean(t_bools *b);
int					handle_d(t_vars v, va_list ap, t_fmt *f);
int					handle_s(t_vars v, va_list ap, t_fmt *f);
int					handle_o(t_vars v, va_list ap, t_fmt *f);
int					handle_c(t_vars v, va_list ap, t_fmt *f);
int					handle_wc(t_vars v, va_list ap, t_fmt *f);
int					handle_p(t_vars v, va_list ap, t_fmt *f);
int					lenbase(long long value, int base);
void				set_format(t_fmt *f, char **fmt, va_list ap);
int					ft_printf(const char *format, ...);
void				ft_puthhnbr(signed char nbr);
int					ft_wlen(wchar_t wc);
int					ft_wstrlen(wchar_t *ws);
int					ft_putwstr(wchar_t *ws);
int					percent(t_vars v, t_fmt *f);
int					handle_hex(t_vars v, va_list ap, t_fmt *f);
int					unsigned_d(t_vars v, va_list ap, t_fmt *f);
int					set_color(char **fmt);
int					handle_ws(t_vars v, va_list ap, t_fmt *f);
void				asteric(t_fmt *f, char **fmt, va_list ap, int pos);
void				ft_cn(char c, int n);
void				neg_line_kill(t_fmt *f, t_vars *v, t_bools *b);
int					binary(t_vars v, va_list ap, t_fmt *f);
int					ft_putfloat(va_list ap, t_fmt *f);

#endif
