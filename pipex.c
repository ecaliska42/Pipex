/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:19 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/28 18:00:16 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "libft/libft.h"
#include <stdlib.h>

// void	free_dobble(char **head)
// {
	
// }

char	**get_commands(char **envp, char *first)// envp av[0]
{
	int i = 0;
	while(ft_strncmp(envp[i], "PATH=", 5) != 0)
	{
		i++;
	}
	// if (access(first, 0) != -1)
	// 	return (*first);
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

char	***get_comms(int command_count, char **commands, char **envp) //ac av envp
{
	//printf("command count = %d\n\n", command_count-1);
	int i = 2;
	int j = 0;
	char ***allcoms = malloc(sizeof(char **) * command_count);
	while(i < command_count - 1)
	{
		// printf("im here lol \n\n");
		// printf("command in while loop is %s\n\n", commands[i]);
		if (access(commands[i], 0) == 0)
		{
			printf("commands[i] = %s\n\n", commands[i]);
			// allcoms[j] = malloc(sizeof(char *) * command_count);
			allcoms[j][0] = ft_strdup(commands[i]);
			j++;
			i++;
		}
		else
		{
			//printf("else condition\n\n");
			char **command = ft_split(commands[i], ' ');
			allcoms[j] = get_commands(envp, command[0]);
			j++;
			i++;
		}
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

void	free_all_commands(char ***head)
{
	int a = 0;
	int b = 0;
	//int c = 0;
	//printf("\n\nfreeingfunction = %s\n\n", head[a][b]);
	while(head[a])
	{
		b = 0;
		//printf("\n\n [a] head = %s\n\n", *head[a]);
		//printf("\n\nfreeingfunction of [%d] = %s\n\n",b, head[a][b]);
		while(head[a][b])
		{
			free(head[a][b]);
			b++;
		}
		free(head[a]);
		a++;
	}
	free(head);
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
	//exit(1);	
	printf("\n\n\n");
}

int main(int ac, char **av, char **envp)
{
	if (ac < 5)
	{
		write(2, "./pipex file1 cmd1 cmd2 file2", 30);
		return 1;
	}
	int infile = open(av[1], O_RDONLY);
	if (infile < 0)
	{
		perror("Error opening infile");
	}
	int outfile = open(av[ac-1], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	if (outfile < 0)
	{
		perror("Error opening outfile");
		exit(EXIT_FAILURE);
	}
	char ***all_commands = get_comms(ac, av, envp);
	char ***all_paths = get_paths(ac, av);
	int	fd[2];
	int j = 0;
	int x = 0;
	int flag1 = 0;
	int flag2 = 0;

	// dup2(infile, STDIN_FILENO);
	// dup2(outfile, STDOUT_FILENO);
	// close(infile);
	// close(outfile);
	while(all_commands[0][j])
	{
		if (access(all_commands[0][j], 0) != -1)
		{
			flag1 = 1;
			break;
		}
		j++;
	}
	if (access(all_commands[0][j], 0) == -1)
	{
		//printf("im here 1");
		perror("'command not found'");
		// free_all_commands(all_commands);
		// free_all_commands(all_paths);
		//return -1;
	}
	// testprintcommands(all_commands);
	// testprintcommands(all_paths);
	// return 0;
	while(all_commands[1][x])
	{
		if (access(all_commands[1][x], 0) == 0)
		{
			flag2 = 1;
			break;
		}
		x++;
	}
	if (access(all_commands[1][x], 0) == -1)
	{
		//perror("'command not found'");
		//write(2, "im here", 7);
		write(2, "command not found\n", 19);
		// free_all_commands(all_commands);
		// free_all_commands(all_paths);
		//return -1;
	}
	pipe(fd);
	pid_t id = fork();
	if (id == -1)
	{
		perror("Error");
		exit(-1);
	}
	if (id == 0 && flag1 == 1)//child
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		// if (execve(all_commands[0][j], all_paths[0], NULL) == -1)
		// 	write(2, "'command not found'", 20);
		int ret = execve(all_commands[0][j], all_paths[0], NULL);
		if (ret == -1)
			perror("not executing");
	}
	else if (id > 0 && flag2 == 1) //parent
	{
		close(fd[1]);
		waitpid(id, NULL, WNOHANG | WUNTRACED);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		// if(execve(all_commands[1][x], all_paths[1], NULL) == -1)
		// {
		// 	write(2, "'command not found'", 20);
		// 	// freeall(&all_commands);
		// 	// freeall(&all_paths);
		// 	// return 1;
		// }
		int ret = execve(all_commands[1][x], all_paths[1], NULL);
		if (ret == -1)
		{
			perror("execve error");
			free_all_commands(all_commands);
			free_all_commands(all_paths);
			return 1;
		}
	}
	free_all_commands(all_commands);
	free_all_commands(all_paths);
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