#include "../incs/minishell.h"

void	print_tokens(t_token *tokens)
{
	while (tokens)
	{
		printf("Token: Type = %d, Value = %s\n",
			tokens->type, tokens->value);
		tokens = tokens->next;
	}
}

const char	*node_type_to_string(t_node_type type)
{
	if (type == NODE_COMMAND)
		return ("COMMAND");
	else if (type == NODE_PIPE)
		return ("PIPE");
	else if (type == NODE_REDIRECT_IN)
		return ("REDIRECT_IN");
	else if (type == NODE_REDIRECT_OUT)
		return ("REDIRECT_OUT");
	else if (type == NODE_APPEND)
		return ("APPEND");
	else if (type == NODE_HEREDOC)
		return ("HEREDOC");
	else if (type == NODE_SEQUENCE)
		return ("SEQUENCE");
	else
		return ("UNKNOWN");
}

void	print_ast_node_args(char **argv)
{
	int	i;

	i = 0;
	printf(" [");
	while (argv[i])
	{
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(", ");
		i++;
	}
	printf("]");
}

void	print_ast(t_ast_node *node, int level)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	while (i < level)
	{
		printf("  ");
		i++;
	}
	printf("%s", node_type_to_string(node->type));
	if ((node->type == NODE_COMMAND || node->type == NODE_REDIRECT_IN
			|| node->type == NODE_REDIRECT_OUT || node->type == NODE_APPEND
			|| node->type == NODE_HEREDOC) && node->argv)
		print_ast_node_args(node->argv);
	printf("\n");
	if (node->left)
		print_ast(node->left, level + 1);
	if (node->right)
		print_ast(node->right, level + 1);
}

void	print_env_list(t_env *env)
{
	while (env)
	{
		if (env->value)
			printf("%s\n", env->value);
		env = env->next;
	}
}
