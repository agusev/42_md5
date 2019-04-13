/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusev <agusev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:18:29 by agusev            #+#    #+#             */
/*   Updated: 2019/04/12 20:20:54 by agusev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

void		pars_entre(t_gen *g, int argc, char **argv)
{
	g->i = 2;
	g->f_p = 0;
	g->f_q = 0;
	g->f_r = 0;
	g->f_s = 0;
	while (g->i < argc)
	{
		if (ft_strcmp("-p", argv[g->i]) == 0)
			g->f_p = 1;
		else if (ft_strcmp("-q", argv[g->i]) == 0)
			g->f_q = 1;
		else if (ft_strcmp("-r", argv[g->i]) == 0)
			g->f_r = 1;
		else if (ft_strcmp("-s", argv[g->i]) == 0)
		{
			g->i++;
			g->f_s++;
		}
		else
			break ;
		g->i++;
	}
	g->nb_file = g->i - argc;
}

void		no_ro_s(t_gen *g, char **argv)
{
	if (!g->f_q)
	{
		if (ft_strcmp(argv[1], "sha256") == 0)
			ft_putstr("SHA256 (\"");
		else if (ft_strcmp(argv[1], "sha256") == 0)
			ft_putstr("SHA256 (\"");
		else
			ft_putstr("MD5 (\"");
		ft_putstr(argv[g->pars]);
		ft_putstr("\") = ");
	}
	if (ft_strcmp(argv[1], "sha256") == 0)
		go_sha256(argv[g->pars], g);
	else if (ft_strcmp(argv[1], "sha256") == 0)
		go_sha256(argv[g->pars], g);
	else
		go_md5(argv[g->pars], g);
	ft_putchar('\n');
}

void		rotate_s(t_gen *g, char **argv)
{
	if (ft_strcmp(argv[1], "sha256") == 0)
		go_sha256(argv[g->pars], g);
	else if (ft_strcmp(argv[1], "sha256") == 0)
		go_sha256(argv[g->pars], g);
	else
	{
		ft_printf("MD5 (\"%s\") = ", argv[g->pars]);
		go_md5(argv[g->pars], g);
	}
	if (!g->f_q)
		ft_printf(" \"%s\"\n", argv[g->pars]);
	else
		ft_putstr("\n");
}

int			print_s(t_gen *g, char **argv, int argc)
{
	if (ft_strcmp("-p", argv[g->pars]) == 0)
		g->f_p = 1;
	else if (ft_strcmp("-q", argv[g->pars]) == 0)
		g->f_q = 1;
	else if (ft_strcmp("-r", argv[g->pars]) == 0)
		g->f_r = 1;
	else if (ft_strcmp("-s", argv[g->pars]) == 0)
	{
		g->pars++;
		if (g->pars < argc)
		{
			if (!g->f_r)
				no_ro_s(g, argv);
			else
				rotate_s(g, argv);
		}
	}
	else
		return (-1);
	g->pars++;
	return (0);
}

int			no_such_file(t_gen *g, char **argv)
{
	if ((g->fd = open(argv[g->pars], O_RDWR)) < 0)
	{
		if (ft_strcmp(argv[1], "sha256") == 0)
			ft_putstr("ssl: sha256: ");
		if (ft_strcmp(argv[1], "sha256") == 0)
			ft_putstr("ssl: sha256: ");
		else
			ft_putstr("ssl: md5: ");
		ft_putstr(argv[g->pars]);
		ft_putstr(": No such file or directory\n");
		g->pars++;
		return (-1);
	}
	return (0);
}