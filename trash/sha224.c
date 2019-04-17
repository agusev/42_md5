/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha224.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agusev <agusev@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 23:36:03 by agusev            #+#    #+#             */
/*   Updated: 2019/04/16 15:18:11 by agusev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ssl.h"

const uint32_t g_k3[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

int		sha224_init(char *init_msg, size_t len, t_gen *g)
{
	int i;

	g->h0 = 0xc1059ed8;
	g->h1 = 0x367cd507;
	g->h2 = 0x3070dd17;
	g->h3 = 0xf70e5939;
	g->h4 = 0xffc00b31;
	g->h5 = 0x68581511;
	g->h6 = 0x64f98fa7;
	g->h7 = 0xbefa4fa4;
	g->length = len * 8;
	g->padded = 1 + ((g->length + 16 + 64) / 512);
	if (!(g->msg_32 = malloc(16 * g->padded * 4)))
		return (-1);
	ft_bzero(g->msg_32, 16 * g->padded * 4);
	ft_memcpy((char *)g->msg_32, init_msg, ft_strlen(init_msg));
	((char*)g->msg_32)[ft_strlen(init_msg)] = 0x80;
	i = 0;
	while (i < (g->padded * 16) - 1)
	{
		g->msg_32[i] = revers_uint32(g->msg_32[i]);
		i++;
	}
	g->msg_32[((g->padded * 512 - 64) / 32) + 1] = g->length;
	return (0);
}

void	sha224_process(t_gen *g, int i)
{
	int j;

	g->w = malloc(512);
	ft_bzero(g->w, 512);
	ft_memcpy(g->w, &g->msg_32[i * 16], 16 * 32);
	j = 16;
	while (j < 64)
	{
		g->tmp4 = ror(g->w[j - 15], 7) ^
		ror(g->w[j - 15], 18) ^ (g->w[j - 15] >> 3);
		g->tmp = ror(g->w[j - 2], 17) ^
		ror(g->w[j - 2], 19) ^ (g->w[j - 2] >> 10);
		g->w[j] = g->w[j - 16] + g->tmp4 + g->w[j - 7] + g->tmp;
		j++;
	}
	g->a = g->h0;
	g->b = g->h1;
	g->c = g->h2;
	g->d = g->h3;
	g->e = g->h4;
	g->f = g->h5;
	g->g = g->h6;
	g->h = g->h7;
}

void	sha224_algorithm(t_gen *g, int j)
{
	g->tmp = ror(g->e, 6) ^ ror(g->e, 11) ^ ror(g->e, 25);
	g->tmp2 = (g->e & g->f) ^ ((~g->e) & g->g);
	g->tmp3 = g->h + g->tmp + g->tmp2 + g_k3[j] + g->w[j];
	g->tmp4 = ror(g->a, 2) ^ ror(g->a, 13) ^ ror(g->a, 22);
	g->tmp5 = (g->a & g->b) ^ (g->a & g->c) ^ (g->b & g->c);
	g->tmp6 = g->tmp4 + g->tmp5;
	g->h = g->g;
	g->g = g->f;
	g->f = g->e;
	g->e = g->d + g->tmp3;
	g->d = g->c;
	g->c = g->b;
	g->b = g->a;
	g->a = g->tmp3 + g->tmp6;
}

int		sha224(char *init_msg, size_t len, t_gen *g)
{
	int i;
	int j;

	sha224_init(init_msg, len, g);
	i = 0;
	while (i < g->padded)
	{
		sha224_process(g, i);
		j = -1;
		while (++j < 64)
			sha224_algorithm(g, j);
		g->h0 += g->a;
		g->h1 += g->b;
		g->h2 += g->c;
		g->h3 += g->d;
		g->h4 += g->e;
		g->h5 += g->f;
		g->h6 += g->g;
		g->h7 += g->h;
		free(g->w);
		i++;
	}
	free(g->msg_32);
	return (0);
}
