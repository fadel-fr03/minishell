#include "../incs/minishell.h"

/*
 * Attaches the command node to the AST.
 */
t_ast_node	*attach_cmd_node(t_ast_node *command_node, t_ast_node *cmd_node)
{
	command_node = attach_command_node(command_node, cmd_node);
	return (command_node);
}

/*
 * Parses redirections and attaches them to the command node.
 */

t_ast_node	*process_single_redirection(t_token **tokens,
				t_ast_node *command_node, t_data *data)
{
	command_node = handle_redirection(tokens, command_node, data);
	if (!command_node)
		return (NULL);
	return (command_node);
}

t_ast_node	*parse_redirection(t_token **tokens, t_ast_node *command_node,
				t_data *data)
{
	while (*tokens && is_redirection_token(*tokens))
	{
		command_node = process_single_redirection(tokens, command_node, data);
		if (!command_node)
			return (NULL);
	}
	return (command_node);
}

/*
 * Processes command tokens by handling redirections and adding arguments.
 * Returns 1 on success, 0 on failure.
 */
int	process_command_tokens(t_token **tokens, t_cmd_args *cmd_args,
			t_ast_node **command_node, t_data *data)
{
	t_token	*curr;

	curr = *tokens;
	while (curr && (curr->type == TOKEN_WORD || is_redirection_token(curr)))
	{
		if (is_redirection_token(curr))
		{
			*command_node = handle_redirection(&curr, *command_node, data);
			if (!*command_node)
				return (0);
		}
		else if (curr->type == TOKEN_WORD)
		{
			if (!add_argument(&cmd_args->argv, &cmd_args->argc, curr->value))
				return (0);
			curr = curr->next;
		}
	}
	*tokens = curr;
	return (1);
}

/*
 * Parses a simple command (command with its arguments and redirections).
 */
t_ast_node	*parse_command(t_token **tokens, t_data *data)
{
	t_ast_node	*command_node;
	t_cmd_args	cmd_args;
	t_ast_node	*cmd_node;

	command_node = NULL;
	cmd_args.argv = NULL;
	cmd_args.argc = 0;
	if (!process_command_tokens(tokens, &cmd_args, &command_node, data))
		return (NULL);
	if (cmd_args.argc > 0)
	{
		cmd_node = create_command_node(cmd_args.argv);
		if (!cmd_node)
			return (NULL);
		command_node = attach_cmd_node(command_node, cmd_node);
	}
	return (command_node);
}
