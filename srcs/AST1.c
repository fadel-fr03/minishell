#include "../incs/minishell.h"

/*
 * Adds an argument to the argv array, reallocating memory as needed.
 * Returns 1 on success, 0 on failure.
 */
int	add_argument(char ***argv, int *argc, char *value)
{
	char	**new_argv;
	int		i;

	new_argv = malloc(sizeof(char *) * (*argc + 2));
	if (!new_argv)
		return (0);
	i = 0;
	while (i < *argc)
	{
		new_argv[i] = (*argv)[i];
		i++;
	}
	new_argv[*argc] = ft_strdup(value);
	if (!new_argv[*argc])
	{
		free(new_argv);
		return (0);
	}
	new_argv[*argc + 1] = NULL;
	free(*argv);
	*argv = new_argv;
	(*argc)++;
	return (1);
}

/*
 * Creates a redirection node with the given type, tokens, and command node.
 */
t_ast_node	*create_redirection_node(t_node_type type, t_token **tokens,
		t_ast_node *command_node, t_data *data)
{
	char		**argv;
	t_ast_node	*redirect_node;

	if (!*tokens || (*tokens)->type != TOKEN_WORD)
	{
		printf("Error: Expected a file name after redirection\n");
		data->exit_parsing = 2;
		return (NULL);
	}
	argv = malloc(sizeof(char *) * 2);
	if (!argv)
		return (NULL);
	argv[0] = ft_strdup((*tokens)->value);
	if (!argv[0])
	{
		free(argv);
		return (NULL);
	}
	argv[1] = NULL;
	redirect_node = create_ast_node(type, argv);
	redirect_node->left = command_node;
	*tokens = (*tokens)->next;
	return (redirect_node);
}

/*
 * Handles the redirection by creating a redirection node and attaching it.
 */
t_ast_node	*handle_redirection(t_token **tokens, t_ast_node *command_node,
				t_data *data)
{
	t_node_type	type;
	t_ast_node	*redir_node;

	type = get_redirection_type(*tokens);
	*tokens = (*tokens)->next;
	redir_node = create_redirection_node(type, tokens, command_node, data);
	return (redir_node);
}

/*
 * Attaches the command node to the leftmost part of the existing AST.
 */
t_ast_node	*attach_command_node(t_ast_node *command_node, t_ast_node *cmd_node)
{
	t_ast_node	*temp;

	if (command_node)
	{
		temp = command_node;
		while (temp->left)
			temp = temp->left;
		temp->left = cmd_node;
	}
	else
	{
		command_node = cmd_node;
	}
	return (command_node);
}

/*
 * Creates a command node from argv.
 */
t_ast_node	*create_command_node(char **argv)
{
	t_ast_node	*cmd_node;

	cmd_node = create_ast_node(NODE_COMMAND, argv);
	return (cmd_node);
}
