/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/22 20:08:20 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf/ft_printf.h"
#include "libft/libft.h"
#include <fcntl.h>
#include <unistd.h>

void	printlist(t_list **head)
{
	t_list *temp;
	temp = *head;
	while(temp)
	{
		ft_printf("node = %s\n", temp->content);
		temp = temp->next;
	}
}


char	**get_commands(char **envp)
{
	int i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	//ft_printf("enviroment = %s\n", envp[i]);
	char **paths = ft_split(envp[i], ':');
	int j = 0;
	while(paths[j])
	{
		paths[j] = ft_strtrim(paths[j], "PATH=");
		paths[j] = ft_strjoin(paths[j], "/");
		ft_printf("%s\n", paths[j]);
		j++;
	}
	j = 0;
	t_list *cmds = NULL;
	ft_printf("printing nodes\n\n\n");
	while(paths[j])
	{
		ft_lstadd_back(&cmds, ft_lstnew(paths[j]));
		j++;
	}
	printlist(&cmds);
	return paths;
}

void	execute(char* path, char* command)
{
	
}

void	child(int *filedescriptor)
{
	
}

void	parent(int *filedescriptor,char *file, char *command)
{
	close(filedescriptor[1]);
	dup2(2, 1);
	int fd = open(file, O_RDONLY);
	if (fd == -1)
		exit(ft_printf("ERROR with FD in Parent\n"));
	
}

int main(int ac, char **av, char **envp)
{
	// if (ac < 4)
	// 	return -1;
	char **commands = get_commands(envp);
	
	int	fd[2];
	if (pipe(fd) == -1)
	{
		perror("There was an error with your pipe\n");
		return -1;
	}
	pid_t id = fork();
	if (id != 0)
	{
		parent(fd, av[1], av[2]);
		wait(NULL);
	}
	else
	{
		child(fd);
	}
}


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