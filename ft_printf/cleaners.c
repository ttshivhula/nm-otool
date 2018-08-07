/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttshivhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/13 11:05:15 by ttshivhu          #+#    #+#             */
/*   Updated: 2017/08/13 11:26:13 by ttshivhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void			clean(t_fmt *f)
{
	f->hash = 0;
	f->left = 0;
	f->sign = 0;
	f->space = 0;
	f->zero = 0;
	f->h = 0;
	f->hh = 0;
	f->l = 0;
	f->ll = 0;
	f->j = 0;
	f->z = 0;
	f->width = 0;
	f->prec = 0;
	f->wide = 0;
}

void			boolclean(t_bools *b)
{
	b->sp = 0;
	b->h = 0;
	b->special = 0;
	b->h = 0;
	b->s = 0;
	b->after = 0;
}
