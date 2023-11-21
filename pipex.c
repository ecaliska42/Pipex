/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/21 18:47:32 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "ft_printf/ft_printf.h"
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>

void	child()
{
	
}

void	parent()
{
	
}

int main(int ac, char **av, char **envp)
{
	int	fd[2];
	if (pipe(fd) == -1)
	{
		ft_printf("There was an error with your pipe\n");
		return -1;
	}
	int id = fork();
	if (id != 0)
	{
		parent();
	}
	else
	{
		child();
	}
	if (id != 0)
	{
		wait(NULL);
	}
}


/*
open		is used to open a file for reading, writing, or both. It can also create the file if it does not exist
close		is used to close a file descriptor, effectively destroying the file table entry referenced by it
read		reads a specified amount of bytes from a file into a memory area
write		writes a specified amount of bytes from a memory area into a file
malloc		is used to dynamically allocate a specified number of bytes of memory
free		is used to deallocate memory that was previously allocated by malloc
perror		is used to print a descriptive error message to the standard error output
strerror	is used to map an error number to a string that describes the error
access		is used to check the accessibility of a file
dup			is used to duplicate a file descriptor
dup2		is similar to dup, but it allows you to specify the new file descriptor
execve		is used to execute a program
exit		is used to terminate the current process
fork		is used to create a new process by duplicating the existing process
pipe		is used to create a pipe, which is a mechanism for inter-process communication
unlink		is used to delete a name and possibly the file it refers to
wait		is used to make a parent process wait until one of its child processes exits
waitpid		is similar to wait, but it allows you to wait for a specific child process
*/