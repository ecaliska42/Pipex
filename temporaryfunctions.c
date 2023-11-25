// int	execute(char** path, char* command)
// {
// 	int i = 0;
// 	while (execve(path[i], &command, NULL) == -1 && path[i])
// 	{
// 		printf("%d\n", i);
// 		i++;
// 	}
// 	if (execve(path[i], &command, NULL) != -1)
// 		return 1;
// 	return -1;
// }

/* OLD MAIN
{
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
		close(fd[0]);
		//dup2(fd[1], file);
		dup2( fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[1]);
		wait(NULL);
		execve(paths2[j], command2, envp);
		//printf("paths = %s and command = %s%s\n", paths[i], command[0], command[1]);
	}
	else //child
	{
		close(fd[1]);
		//char *line = get_next_line(fd[0]);
		//dup2(fd[0], file);
		dup2(fd[0], STDIN_FILENO);
		//close(file);
		close(fd[0]);
		execve(paths[i], command, envp);
		//printf("paths2 = %s and command2 = %s %s\n", paths2[j], command2[0], command2[1]);
		//wre(paths[i])
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
		close(fd[0]);
		//dup2(fd[1], file);
		dup2( fd[1], STDOUT_FILENO);
		close(fd[1]);
		close(fd[1]);
		wait(NULL);
		execve(paths2[j], command2, envp);
		//printf("paths = %s and command = %s%s\n", paths[i], command[0], command[1]);
	}
	else //child
	{
		close(fd[1]);
		//char *line = get_next_line(fd[0]);
		//dup2(fd[0], file);
		dup2(fd[0], STDIN_FILENO);
		//close(file);
		close(fd[0]);
		execve(paths[i], command, envp);
		//printf("paths2 = %s and command2 = %s %s\n", paths2[j], command2[0], command2[1]);
		//write(STDOUT_FILENO, "HELLO\n", 6);
	}
}ite(STDOUT_FILENO, "HELLO\n", 6);
	}
}*/

/*

{
	// if (ac < 4)
	// 	return -1;
	//av[1] file in
	//av[2] command for file
	//av[3] child command
	//av[4] output file (result)
	//(void)ac;
	int	fd[2];
	int com_count = ac;
	char ***all_commands = get_comms(com_count, av, envp);
	char ***all_paths = get_paths(com_count, av);
	//testprintcommands(all_commands);
	// if (pipe(fd) == -1)
	// {
	// 	perror("There was an error with your pipe\n");
	// 	return -1;
	// }
	char **command = ft_split(av[2], ' ');
	char **command2 = ft_split(av[3], ' ');
	char **paths = get_commands(envp, command[0]);
	char **paths2 = get_commands(envp, command2[0]);
	int infile = open(av[1], O_RDONLY);
	if (infile == -1)
	{
		perror("infile error");
		return -1;
	}
	int outfile = open(av[4], O_WRONLY | O_CREAT | O_TRUNC, 0666);
	{
		perror("outfile error");
		return -1;
	}
	int i = 0;
	int j = 0;
	int count = 2;
	int x;
	while (all_commands[i])
	{
		j = 0;
		while(all_commands[i][j])
		{
			if (access(all_commands[i][j], 0) != -1)
				break;
			j++;
		}
		if (pipe(fd) == -1)
		{
			perror("pipeerror");
			return -1;
		}
		pid_t id = fork();
		if (id == 0)
		{
			close (fd[0]);
			dup2(infile, STDIN_FILENO);
			dup2(fd[1], STDOUT_FILENO);
			execve(all_commands[i][j], all_paths[i], envp);
			perror("Failed with execute");
			return -1;
		}
		else
		{
			close(fd[1]);
			dup2(infile, fd[0]);
			wait(NULL);
			//infile = fd[0];
		}
		i++;
		count++;
	}
	x = 0;
	char *gnl = get_next_line(infile);
	while(gnl[x++])
		write(outfile, gnl, 1);
	close(infile);
	close(outfile);
	return 0;
}
*/