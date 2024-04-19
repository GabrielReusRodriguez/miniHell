#include <stdio.h>
#include "minishell.h"

void	ft_token_debug(t_token_set tokens)
{
	t_list	*node;
	t_token	*token;
	
	printf("INICIO DEBUG Tokens: \n");
	node = tokens.tokens;
	while (node != NULL)
	{
		token = (t_token *)node->content;
		printf("\t NODE value : _%s_\n", token->value);
		printf("\t NODE type : _%d_ ", token->type);
		if (token->type == TOKEN_TYPE_AND)
			printf("AND");
		if (token->type == TOKEN_TYPE_EMPTY)
			printf("EMPTY");
		if (token->type == TOKEN_TYPE_OR)
			printf("OR");
		if (token->type == TOKEN_TYPE_FILE)
			printf("FILE");
		if (token->type == TOKEN_TYPE_PAR_CLOSE)
			printf("PATENTHESIS CLOSE");
		if (token->type == TOKEN_TYPE_PAR_OPEN)
			printf("PARENTHESIS OPEN");
		if (token->type == TOKEN_TYPE_PIPE)
			printf("PIPE");
		if (token->type == TOKEN_TYPE_RED_APPEND)
			printf("REDIRECTION OUT APPEND");
		if (token->type == TOKEN_TYPE_RED_INPUT)
			printf("REDIRECTION IN");
		if (token->type == TOKEN_TYPE_RED_HERE_DOC)
			printf("REDIRECTION IN HEREDOC");
		if (token->type == TOKEN_TYPE_RED_TRUNCATE)
			printf("REDIRECTION OUT TRUNCATE");
		if (token->type == TOKEN_TYPE_SEMICOLON)
			printf("SEMICOLON");
		if (token->type == TOKEN_TYPE_UNKNOWN)
			printf("UNKNOWN");
		if (token->type == TOKEN_TYPE_WORD)
			printf("WORD");
		if (token->type == TOKEN_TYPE_WORD_SQUOTE)
			printf("WORD SQUOTE");
		if (token->type == TOKEN_TYPE_WORD_DQUOTE)
			printf("WORD DQUOTE");

		printf("\n");	
		node = node->next;
	}
	printf("FIN DEBUG Tokens \n");
}