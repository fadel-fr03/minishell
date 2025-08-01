#include "../incs/minishell.h"

/*
 * Creates a new AST node with the given type and arguments.
 */
t_ast_node	*create_ast_node(t_node_type type, char **argv)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->argv = argv;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

/*
 * Counts the number of command arguments starting from the current token.
 */
int	count_command_args(t_token *curr)
{
	int	argc;

	argc = 0;
	while (curr && curr->type == TOKEN_WORD)
	{
		argc++;
		curr = curr->next;
	}
	return (argc);
}

/*
 * Builds the command arguments array from tokens.
 */
char	**build_command_args(t_token **tokens, int argc)
{
	char	**argv;
	t_token	*curr;
	int		i;

	argv = malloc(sizeof(char *) * (argc + 1));
	if (!argv)
		return (NULL);
	curr = *tokens;
	i = 0;
	while (i < argc)
	{
		argv[i] = ft_strdup(curr->value);
		if (!argv[i])
		{
			while (i > 0)
				free(argv[--i]);
			free(argv);
			return (NULL);
		}
		curr = curr->next;
		i++;
	}
	argv[argc] = NULL;
	*tokens = curr;
	return (argv);
}

/*
 * Determines the type of redirection based on the token.
 */
t_node_type	get_redirection_type(t_token *token)
{
	if (token->type == TOKEN_REDIRECT_IN)
		return (NODE_REDIRECT_IN);
	if (token->type == TOKEN_REDIRECT_OUT)
		return (NODE_REDIRECT_OUT);
	if (token->type == TOKEN_APPEND)
		return (NODE_APPEND);
	if (token->type == TOKEN_HEREDOC)
		return (NODE_HEREDOC);
	return (-1);
}

/*
 * Checks if the token is a redirection token.
 */
int	is_redirection_token(t_token *token)
{
	return (token->type == TOKEN_REDIRECT_IN
		|| token->type == TOKEN_REDIRECT_OUT
		|| token->type == TOKEN_APPEND
		|| token->type == TOKEN_HEREDOC);
}
