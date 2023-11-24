/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/24 16:37:21 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


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


int main(int ac, char **av, char **envp)
{
	// if (ac < 4)
	// 	return -1;
	//av[1] file in
	//av[2] command for file
	//av[3] child command
	//av[4] output file (result)
	(void)ac;
	int	fd[2];
	if (pipe(fd) == -1)
	{
		perror("There was an error with your pipe\n");
		return -1;
	}
	char **command = ft_split(av[2], ' ');
	char **command2 = ft_split(av[3], ' ');
	char **paths = get_commands(envp, command[0]);
	char **paths2 = get_commands(envp, command2[0]);
	int i = 0;
	while(paths[i])
	{
		if (access(paths[i], 0) != -1)
			break;
		i++;
	}
	if (access(paths[i], 0) == -1)
	{
		perror("command of av[2] not found\n");
		return -1;
	}
	//execve(paths[i], command, envp);
	int j = 0;
	while(paths2[j])
	{
		if (access(paths2[j], 0) != -1)
			break;
		j++;
	}
	if (access(paths2[j], 0) == -1)
	{
		perror("command of av[3] not found\n");
		return -1;
	}
	pid_t id = fork();
	if (id != 0) //parent
	{
		close(fd[1]);
		wait(NULL);
		int file = open(av[4], O_WRONLY | O_CREAT | O_TRUNC);
		dup2(file, fd[0]);
		//close(file);
		close(fd[0]);
		execve(paths2[j], command2, envp);
		//printf("paths = %s and command = %s%s\n", paths[i], command[0], command[1]);
	}
	else //child
	{
		close(fd[0]);
		int file = open(av[1], O_RDONLY);
		dup2(file, fd[1]);
		//close(file);
		close(fd[1]);
		execve(paths[i], command, envp);
		//printf("paths2 = %s and command2 = %s %s\n", paths2[j], command2[0], command2[1]);
		//write(STDOUT_FILENO, "HELLO\n", 6);
	}
	close(fd[0]);
	close(fd[1]);
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