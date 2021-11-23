/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:03:35 by vvarussa          #+#    #+#             */
/*   Updated: 2021/11/05 16:16:36 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>
# define PATH "/usr/local/sbin/::/usr/local/bin/:\
/usr/sbin/:/usr/bin/:/sbin:/bin/:/home/vinicius/Desktop/42/pipex/submit/pipex-tester/assets/"

typedef struct s_program_info
{
	char	*program_path;
	char	**program_arguments;
	char	**envp;
	char	**argv;
	int		n;
	int		i;
	int		argc;
	int		infile_fd;
	int		outfile_fd;
}	t_program_info;

int		check_error(int i);
void	print_arg_vector(char **argv);
void	check_args(int argc, char **argv);
int		check_space(char *str);
#endif
