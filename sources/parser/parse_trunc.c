/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_trunc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cspreafi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 17:59:11 by cspreafi          #+#    #+#             */
/*   Updated: 2024/05/13 17:59:14 by cspreafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

static void	open_outfile_trunc(t_io_fds *io, char *file, char *var_filename)
{
	if (!remove_old_file_ref(io, false))
		return ;
	io->outfile = ft_strdup(file);
	if (io->outfile && io->outfile[0] == '\0')
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	io->fd_out = open(io->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (io->fd_out == -1)
		errmsg_cmd(io->outfile, NULL, strerror(errno), false);
}

void	parse_trunc(t_command **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_command	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	init_io(cmd);
	open_outfile_trunc(cmd->io_fds, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
