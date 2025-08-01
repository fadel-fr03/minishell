#include "../incs/minishell.h"

/*
 * Frees the memory allocated for the AST.
 */
void	free_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	if (node->argv)
	{
		i = 0;
		while (node->argv[i])
		{
			free(node->argv[i]);
			i++;
		}
		free(node->argv);
	}
	free_ast(node->left);
	free_ast(node->right);
	free(node);
}

static int	handle_pipe_error(t_data *data)
{
	printf("minishell: syntax error near unexpected token `|`\n");
	data->exit_parsing = 2;
	return (1);
}

static t_ast_node	*create_pipe_node(t_ast_node *left, t_ast_node *right)
{
	t_ast_node	*new_node;

	new_node = create_ast_node(NODE_PIPE, NULL);
	if (!new_node)
		return (NULL);
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_ast_node	*parse_pipeline(t_token **tokens, t_data *data)
{
	t_ast_node	*left;
	t_ast_node	*right;

	if (!*tokens || (*tokens)->type == TOKEN_PIPE)
		return (handle_pipe_error(data), NULL);
	left = parse_command(tokens, data);
	if (!left)
		return (NULL);
	while (*tokens && (*tokens)->type == TOKEN_PIPE)
	{
		*tokens = (*tokens)->next;
		if (!*tokens || (*tokens)->type == TOKEN_PIPE)
			return (handle_pipe_error(data), NULL);
		right = parse_command(tokens, data);
		if (!right)
			return (NULL);
		left = create_pipe_node(left, right);
		if (!left)
			return (NULL);
	}
	return (left);
}
