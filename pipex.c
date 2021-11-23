/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvarussa <vvarussa@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 16:04:24 by vvarussa          #+#    #+#             */
/*   Updated: 2021/11/05 16:10:11 by vvarussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_split(char **vector)
{
	int	n;

	n = 0;
	while (vector[n] != NULL)
	{
		free(vector[n]);
		n++;
	}
	free(vector);
}

void	exec_command(t_program_info pi, int fd_in, int fd_out)
{
	int	id;

	if (pi.program_path == NULL)
	{
		ft_putstr_fd(pi.program_arguments[0], 1);
		ft_putstr_fd(" command not found\n", 1);
		check_error(close(fd_in));
		check_error(close(fd_out));
		return ;
	}
	id = check_error(fork());
	if (id == 0)
	{
		check_error(dup2(fd_in, 0));
		check_error(dup2(fd_out, 1));
		check_error(execve(pi.program_path, pi.program_arguments, pi.envp));
	}
	check_error(close(fd_in));
	check_error(close(fd_out));
	waitpid(1, NULL, WUNTRACED);
}

char	*check_path(char *command)
{
	char	**pathv;
	char	*program_path;
	int		n;

	n = 0;
	pathv = ft_split(PATH, ':');
	while (pathv[n] != NULL)
	{
		program_path = ft_strjoin(pathv[n], command);
		if (!access(program_path, F_OK))
		{
			free_split(pathv);
			return (program_path);
		}
		free(program_path);
		n++;
	}
	free_split(pathv);
	return (NULL);
}

void	run_commands(t_program_info pi)
{
	int		pipe1[2];
	int		pipe2[2];

	while (pi.i < pi.argc - 1)
	{
		pipe2[0] = pipe1[0];
		pipe2[1] = pipe1[1];
		check_error(pipe(pipe1));
		pi.program_arguments = ft_split_colons(pi.argv[pi.i], ' ');
		pi.program_path = check_path(pi.program_arguments[0]);
		if (pi.argc == 4)
			exec_command(pi, pi.infile_fd, pi.outfile_fd);
		else if (pi.i == 2)
			exec_command(pi, pi.infile_fd, pipe1[1]);
		else if (pi.i == pi.argc - 2)
			exec_command(pi, pipe2[0], pi.outfile_fd);
		else
			exec_command(pi, pipe2[0], pipe1[1]);
		free_split(pi.program_arguments);
		free(pi.program_path);
		pi.n++;
		pi.i++;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_program_info	pi;

	check_args(argc, argv);
	pi.envp = envp;
	pi.argc = argc;
	pi.argv = argv;
	pi.infile_fd = check_error(open(argv[1], O_RDONLY | O_CREAT, 0777));
	pi.outfile_fd = check_error(open(argv[argc - 1], O_WRONLY | O_CREAT
				| O_TRUNC, 0777));
	pi.i = 2;
	pi.n = 0;
	run_commands(pi);
}
