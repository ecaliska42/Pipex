/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:45 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/28 21:07:34 by ecaliska         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <fcntl.h>
#include <unistd.h> //open, close, read, write, dup, dup2, execve, fork, pipe, unlink
#include <stdlib.h> //malloc, free, exit
#include <stdio.h> //perror
#include <string.h> //strerror
#include <sys/wait.h> //wait, waitpid
#include "libft/libft.h"
#include "ft_printf/ft_printf.h"
#include "ft_fd_printf/ft_fd_printf.h"

typedef struct p_list
{
    char **commands;
    char **paths;
    struct list *next;
}com_list;


#endif