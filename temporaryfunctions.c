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