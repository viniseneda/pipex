/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_colons.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 12:27:33 by vvarussa          #+#    #+#             */
/*   Updated: 2021/11/05 13:45:10 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char const	*skip_char(char const *s, char c)
{
	while (*s && *s == c)
		s++;
	return (s);
}

const char	*skip_quote_group(char const *s)
{
	if (*s == '\'')
	{
		s++;
		while (*s != '\'' && *s != '\0')
			s++;
		s++;
	}
	else if (*s == '\"')
	{
		s++;
		while (*s != '\"' && *s != '\0')
			s++;
		s++;
	}
	return (s);
}

static int	how_many(char const *s, char c)
{
	size_t		co;
	const char	*s2;

	co = 0;
	s2 = skip_char(s, c);
	if ((*s2 == '\0') || (*s == '\0'))
		return (0);
	if (*s == c)
		co--;
	if (*(s + ft_strlen(s) - 1) == c)
		co--;
	while (*s != '\0')
	{
		s = skip_quote_group(s);
		if (*s == c)
		{
			s = skip_char(s, c);
			s = skip_quote_group(s);
			co++;
		}
		else
			s++;
	}
	return (co + 1);
}

static void	word_maker(char const *s, char c, char **out,
size_t n_of_words)
{
	const char		*walker;
	size_t			beg;
	size_t			end;

	walker = s;
	walker = skip_char(walker, c);
	while (n_of_words--)
	{
		walker = skip_char(walker, c);
		beg = walker - s;
		end = walker - s - beg;
		if (end > ft_strlen(s))
			end = ft_strlen(s);
		while ((*walker != c) && (*walker != '\0'))
		{
			if (*walker == '\'' || *walker == '\"')
				walker = skip_quote_group(walker);
			else
				walker++;
		}
		*out = make_out(s, walker, beg);
		out++;
	}
	*out = NULL;
}

char	**ft_split_colons(char const *s, char c)
{
	char		**out;
	size_t		n_of_words;

	if (s == NULL)
		return (NULL);
	n_of_words = how_many(s, c);
	out = malloc((n_of_words + 1) * sizeof(char **));
	if (out == NULL)
		return (NULL);
	word_maker(s, c, out, n_of_words);
	return (out);
}
