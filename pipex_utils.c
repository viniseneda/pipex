/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:05:14 by vvarussa          #+#    #+#             */
/*   Updated: 2021/11/05 16:17:24 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_error(int i)
{
	if (i < 0)
	{
		perror("error: ");
		exit(errno);
	}
	return (i);
}

int	check_space(char *str)
{
	while (*str)
	{
		if (*str == ' ' || *str == '	')
		{
			return (1);
		}
		str = str + 1;
	}
	return (0);
}

void	print_arg_vector(char **argv)
{
	int	n;

	n = 0;
	while (argv[n] != NULL)
	{
		ft_putstr_fd(argv[n], 1);
		ft_putchar_fd('\n', 1);
		n++;
	}
}

void	check_args(int argc, char **argv)
{
	if (argc < 4)
	{
		ft_putstr_fd("error: lacking arguments\n", 1);
		exit(1);
	}
	if (check_space(argv[1]))
	{
		ft_putstr_fd("error: lacking infile\n", 1);
		exit(1);
	}
	if (check_space(argv[argc - 1]))
	{
		ft_putstr_fd("error: lacking outfile\n", 1);
		exit(1);
	}
}
