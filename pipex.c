/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/27 13:15:27 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

char	**get_commands(char **envp, char *first)
{
	int i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	char **paths = ft_split(envp[i], ':');
	int j = 0;
	while(paths[j])
	{
		paths[j] = ft_strtrim(paths[j], "PATH=");
		paths[j] = ft_strjoin(paths[j], "/");
		paths[j] = ft_strjoin(paths[j], first);
		j++;
	}
	return paths;
}

char	***get_comms(int command_count, char **commands, char **envp)
{
	int i = 2;
	int j = 0;
	char ***allcoms = malloc(sizeof(char **) * command_count);
	while(i < command_count - 1)
	{
		char **command = ft_split(commands[i], ' ');
		allcoms[j] = get_commands(envp, command[0]);
		j++;
		i++;
	}
	return allcoms;
}

char ***get_paths(int command_count, char **commands)
{
	int i = 2;
	int j = 0;
	char ***allpaths = malloc(sizeof(char **) * command_count);
	while (i < command_count - 1)
	{
		allpaths[j] = ft_split(commands[i], ' ');
		j++;
		i++;
	}
	return allpaths;
}

int main(int ac, char **av, char **envp)
{
	if (ac < 5)
		return -1;
	char ***all_commands = get_comms(ac, av, envp);
	char ***all_paths = get_paths(ac, av);
	int infile = open(av[1], O_RDONLY);
	int outfile = open(av[ac-1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int	fd[2];
	int j = 0;
	int x = 0;

	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	while(all_commands[0][j])
	{
		if (access(all_commands[0][j], 0) != -1)
			break;
		j++;
	}
	while(all_commands[1][x])
	{
		if (access(all_commands[1][x], 0) != -1)
			break;
		x++;
	}
	pipe(fd);
	pid_t id = fork();
	if (id == -1)
	{
		perror("Error");
		exit(-1);
	}
	if (id == 0)//child
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		execve(all_commands[0][j], all_paths[0], NULL);
	}
	else //parent
	{
		close(fd[1]);
		wait(NULL);
		dup2(fd[0], STDIN_FILENO);
		execve(all_commands[1][x], all_paths[1], NULL);
		close(fd[0]);
	}
	close(infile);
	close(outfile);
	return 0;
}



//./pipex input "grep aa" "wc -l" output

/*
open		is used to open a file for reading, writing, or both. It can also create the file if it does not exist
close		is used to close a file descriptor, effectively destroying the file table entry referenced by it
read		reads a specified amount of bytes from a file into a memory area
perror		is used to print a descriptive error message to the standard error output
strerror	is used to map an error number to a string that describes the error
access		is used to check the accessibility of a file
dup			is used to duplicate a file descriptor
dup2		is similar to dup, but it allows you to specify the new file descriptor
execve		is used to execute a program
pipe		is used to create a pipe, which is a mechanism for inter-process communication
unlink		is used to delete a name and possibly the file it refers to
wait		is used to make a parent process wait until one of its child processes exits
waitpid		is similar to wait, but it allows you to wait for a specific child process
*/