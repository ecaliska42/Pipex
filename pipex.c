/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/26 16:39:13 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "gnl/get_next_line.h"
#include "gnl/get_next_line_bonus.h"
#include "libft/libft.h"
#include <fcntl.h>
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

void	testprintcommands(char ***all_commands)
{
	int i = 0;
	int x = 0;
	while (all_commands[i])
	{
		x = 0;
		printf("commands in all_commands[%d] are:\n", i);
		while (all_commands[i][x])
		{
			printf("\t%s\n", all_commands[i][x]);
			x++;
		}
		i++;
	}
	exit(1);	
}

void	printpaths(char ***allpaths, int i)
{
	int j = 0;
	while (allpaths[i])
	{
		j = 0;
		printf("\tfor path %s\n", *allpaths[i]);
		while(allpaths[i][j])
		{
			printf("\t\t%s\n", allpaths[i][j]);
			j++;
		}
		i++;
	}
}

int main(int ac, char **av, char **envp)
{
	int	fd[2];
	char ***all_commands = get_comms(ac, av, envp);
	char ***all_paths = get_paths(ac, av);
	//testprintcommands(all_commands);
	int infile = open(av[1], O_RDONLY);
	int outfile = open(av[ac-1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int tempfile = open("temp.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
	int i = 0;
	int j = 0;
	int x;
	char *temp;
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	while (all_commands[i])
	{
		j = 0;
		while(all_commands[i][j])
		{
			if (access(all_commands[i][j], 0) != -1)
				break;
			j++;
		}
		//printf("command is %s\n", all_commands[i][j]);
		pipe(fd);
		pid_t id = fork();
		if (id == 0)//child
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			execve(all_commands[i][j], all_paths[i], NULL);
			// printf("paths are :\n");
			// printpaths(all_paths, i);
		}
		else //parent
		{
			//dup2(tempfile, fd[1]);
			close(fd[1]);
			wait(NULL);
			dup2(fd[0], STDIN_FILENO);
			temp = get_next_line(fd[1]);
			//dup2(fd[0], STDIN_FILENO);
			//dup2(tempfile, STDIN_FILENO);
			//dup2(int fd, int fd2)
			close(fd[0]);
			execve(all_commands[i+1][j], all_paths[i+1], NULL);
			int p = 0;
			while (temp[p])
			{
				write(outfile, &temp[p], 1);
				p++;
			}
			//printf("temp is %s\n", temp);
			//close(tempfile);
		}
		close(infile);
		close(tempfile);
		close(outfile);
		i++;
	}
	// x = 0;
	// char *gnl = get_next_line(infile);
	// while(gnl[x++])
	// 	write(outfile, gnl, 1);
	// close(infile);
	// close(outfile);
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