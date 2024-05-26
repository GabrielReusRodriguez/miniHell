/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: greus-ro <greus-ro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 23:10:08 by gabriel           #+#    #+#             */
/*   Updated: 2024/05/25 16:13:30 by greus-ro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "tokens.h"
#include "cmd.h"
#include "debug.h"
#include "redirect.h"

void	cmd_debug(t_cmd cmd)
{
	t_list		*node;
	t_token		*token;
	t_redirect	*redirect;

	if (DEBUG_MODE)
	{
		printf("CMD***********************\n");
		node = cmd.redir_in;
		while (node != NULL)
		{
			redirect = (t_redirect *)node->content;
			if (redirect->type->type == TOKEN_TYPE_RED_INPUT)
			{
				printf("\tRedirection input  +  ");
				if (redirect->target->value != NULL)
					printf("file : %s", redirect->target->value);
				printf("\n");
			}
			if (redirect->type->type == TOKEN_TYPE_RED_HERE_DOC)
			{
				printf("\tRedirection input here_doc + ");
				if (redirect->target->value != NULL)
					printf("lim : %s", redirect->target->value);
				printf("\n");
			}
			node = node->next;
		}
		if (cmd.redir_in != NULL)
		{
			printf("\t here_doc read: _%s_\n", cmd.here_doc);
		}
		if (cmd.exec != NULL)
		{
			printf("\tExec: %s\n", cmd.exec->value);
		}
		if (cmd.args != NULL)
		{
			printf("\tARGs :\n");
			node = cmd.args;
			while (node != NULL)
			{
				token = (t_token *)node->content;
				printf("\t\t %s \n", token->value);
				node = node->next;
			}
			printf("\tEND ARGs :\n");
		}
		while (cmd.redir_out != NULL)
		{
			redirect = (t_redirect *)cmd.redir_out->content;
			if (redirect->type->type == TOKEN_TYPE_RED_APPEND)
			{
				printf("\tRedirection output APPEND  +  ");
				if (redirect->target->value != NULL)
					printf("target : %s", redirect->target->value);
				printf("\n");
			}
			if (redirect->type->type == TOKEN_TYPE_RED_TRUNCATE)
			{
				printf("\tRedirection output TRUNCATE + ");
				if (redirect->target->value != NULL)
					printf("file : %s", redirect->target->value);
				printf("\n");
			}
			cmd.redir_out = cmd.redir_out->next;
		}
		printf("END CMD*******************\n");
	}
}

/*
void	cmd_debug(t_cmd cmd)
{
	t_list	*node;
	t_token	*token;

	if (DEBUG_MODE)
	{
		printf("CMD***********************\n");
		if (cmd.red_in != NULL)
		{
			if (cmd.red_in->type == TOKEN_TYPE_RED_INPUT)
			{
				printf("\tRedirection input  +  ");
				if (cmd.red_in_origin != NULL)
					printf("file : %s", cmd.red_in_origin->value);
				printf("\n");
			}
			if (cmd.red_in->type == TOKEN_TYPE_RED_HERE_DOC)
			{
				printf("\tRedirection input here_doc + ");
				if (cmd.red_in_origin != NULL)
					printf("lim : %s", cmd.red_in_origin->value);
				printf("\n");
			}
		}
		if (cmd.exec != NULL)
		{
			printf("\tExec: %s\n", cmd.exec->value);
		}
		if (cmd.args != NULL)
		{
			printf("\tARGs :\n");
			node = cmd.args;
			while (node != NULL)
			{
				token = (t_token *)node->content;
				printf("\t\t %s \n", token->value);
				node = node->next;
			}
			printf("\tEND ARGs :\n");
		}
		if (cmd.red_out != NULL)
		{
			if (cmd.red_out->type == TOKEN_TYPE_RED_APPEND)
			{
				printf("\tRedirection APPEND  +  ");
				if (cmd.red_out_dest != NULL)
					printf("file : %s", cmd.red_out_dest->value);
				printf("\n");
			}
			if (cmd.red_out->type == TOKEN_TYPE_RED_TRUNCATE)
			{
				printf("\tRedirection TRUNCATE + ");
				if (cmd.red_out_dest != NULL)
					printf("file : %s", cmd.red_out_dest->value);
				printf("\n");
			}
		}
		printf("END CMD*******************\n");
	}
}
*/