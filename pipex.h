/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaliska <ecaliska@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/19 15:27:45 by ecaliska          #+#    #+#             */
/*   Updated: 2023/11/24 16:34:23 by ecaliska         ###   ########.fr       */
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

// typedef struct list
// {
//     char *commands;
//     struct s_list *next;
// }p_list;


#endif