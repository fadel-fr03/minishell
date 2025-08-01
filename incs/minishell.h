#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <ctype.h>
# include <curses.h>
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>

# define HEREDOC_BUFFER_SIZE 1024

extern volatile sig_atomic_t	g_signal_atomic;

typedef struct s_shell_state
{
	char				**envp;
	char				*current_dir;
	int					last_status;
}						t_shell_state;

typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
	TOKEN_EOF
}						t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
}						t_token;

typedef enum e_node_type
{
	NODE_COMMAND,
	NODE_PIPE,
	NODE_REDIRECT_IN,
	NODE_REDIRECT_OUT,
	NODE_APPEND,
	NODE_HEREDOC,
	NODE_SEQUENCE
}						t_node_type;

typedef struct s_ast_node
{
	t_node_type			type;
	char				**argv;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}						t_ast_node;

typedef struct s_env
{
	char				*value;
	bool				exported;
	struct s_env		*next;
}						t_env;

typedef struct s_history_node
{
	char					*cmd;
	struct s_history_node	*next;
}				t_history_node;

typedef struct s_data
{
	t_env				*env;
	int					exit;
	int					exit_status;
	int					exit_parsing;
	t_token				*tokens;
	int					history_count;
	t_history_node		*history_head;
	t_history_node		*history_tail;
}						t_data;

typedef struct s_pipe_params
{
	t_ast_node	*node;
	t_env		*env;
	t_data		*data;
	int			pipefd[2];
}				t_pipe_params;

typedef struct s_exec_params
{
	t_ast_node	*node;
	t_env		*env;
	t_data		*data;
	int			in_fd;
	int			out_fd;
}				t_exec_params;

typedef struct s_expander_state
{
	char				*expanded;
	size_t				i;
	size_t				j;
	int					in_single_quotes;
	int					in_double_quotes;
	const char			*exit_status_str;
	char				*home;
	t_data				*data;
}						t_expander_state;

typedef struct s_cmd_args
{
	char				**argv;
	int					argc;
}						t_cmd_args;

typedef struct s_arg_node
{
	char				*value;
	struct s_arg_node	*next;
}				t_arg_node;

typedef struct s_arg_list
{
	t_arg_node	*head;
	t_arg_node	*tail;
	int			count;
}				t_arg_list;

// Debugging functions
void					print_tokens(t_token *tokens);
void					print_ast(t_ast_node *node, int level);
void					print_env_list(t_env *env);

// Tokenization
t_token					*tokenize(const char *input, t_data *data);
void					remove_leading_empty_tokens(t_token **tokens);
// t_token *expand_variables(t_token *tokens, t_data *data);
// char						*expand_variable(const char *input, t_env *env);
char					*expand_variable(const char *input, t_data *data);
void					expand_tokens(t_token **tokens, t_data *data);
char					*process_variable_expansion(const char *input,
							t_expander_state *state);
int						check_quotes(char c, t_expander_state *state);
size_t					handle_dollar_sign(const char *input,
							t_expander_state *state);
size_t					expand_variable_name(const char *input,
							t_expander_state *state);
int						should_expand_tilde(const char *input, size_t i);
size_t					expand_tilde(t_expander_state *state);
int						handle_expanded_value(t_token **current,
							t_token **previous, char *expanded_value,
							t_token **tokens);
size_t					compute_expanded_length(const char *input,
							t_data *data);
void					remove_empty_token(t_token **current,
							t_token **previous, t_token **tokens);

void					free_tokens(t_token *tokens);
void					free_ast(t_ast_node *node);
t_node_type				get_redirection_type(t_token *token);
t_ast_node				*create_ast_node(t_node_type type, char **argv);
t_ast_node				*create_command_node(char **argv);
t_ast_node				*parse_input(t_token *tokens, t_data *data);
t_ast_node				*attach_command_node(t_ast_node *command_node,
							t_ast_node *cmd_node);
int						add_argument(char ***argv, int *argc, char *value);
t_ast_node				*handle_redirection(t_token **tokens,
							t_ast_node *command_node, t_data *data);
t_node_type				get_redirection_type(t_token *token);
int						is_redirection_token(t_token *token);
t_ast_node				*parse_pipeline(t_token **tokens, t_data *data);
int						handle_heredoc(const char *delimiter, t_data *data);
// int execute_ast(t_ast_node *node);
// int							execute_ast(t_ast_node *node, char **envp);
char					**envp_to_array(t_env *env);
void					free_envp_array(char **envp);
int						read_heredoc_lines(int write_fd, const char *delimiter,
							t_data *data);
int						handle_heredoc(const char *delimiter, t_data *data);
int						open_redirection_fd(t_ast_node *node, t_data *data);
int						handle_redirection_node(t_ast_node *node,
							int *in_fd, int *out_fd, t_data *data);
t_ast_node				*parse_command(t_token **tokens, t_data *data);
int						process_redirections(t_ast_node *node,
							int *in_fd, int *out_fd, t_data *data);
t_ast_node				*get_command_node(t_ast_node *node);
int						command_not_found(t_ast_node *cmd_node);
int						handle_execve_error(char *full_path, char **new_envp);
void					check_command_node(t_ast_node *cmd_node);
void					check_if_directory(t_ast_node *cmd_node);
int						execute_external_command(t_ast_node *cmd_node,
							t_env *env);
void					execute_command_node(t_ast_node *node, t_env *env,
							t_data *data);
int						execute_simple_command(t_ast_node *node, t_env *env,
							t_data *data);
int						execute_pipe(t_ast_node *node, t_env *env,
							t_data *data);
int						execute_ast(t_ast_node *node, t_env *env, t_data *data);
int						execute_builtin(t_ast_node *node, t_env *env,
							t_data *data);
// char						*find_full_path(const char *command, char **envp);
char					*find_full_path(const char *command, t_env *env);
t_ast_node				*parse_redirection(t_token **tokens,
							t_ast_node *command_node, t_data *data);
int						is_builtin(t_ast_node *node);
void					handle_assignment(const char **ptr, t_token **tokens,
							const char *start, t_data *data);
void					handle_non_assignment(const char **ptr,
							t_token **tokens, const char *start);
void					add_token(t_token **tokens, t_token_type type,
							const char *value);
void					handle_single_quote(const char **ptr, t_token **tokens,
							t_data *data);
void					handle_double_quote(const char **ptr, t_token **tokens,
							t_data *data);
void					handle_less_than(const char **ptr, t_token **tokens);
void					handle_greater_than(const char **ptr, t_token **tokens);
char					*collect_quoted_segment(const char **ptr, char quote,
							t_data *data);
char					*str_append(char *original, const char *to_append);
char					*collect_unquoted_word(const char **ptr);

// String utils
char					*ft_strndup(const char *s, size_t n);
char					*ft_strcpy(char *dest, const char *src);
const char				*skip_whitespace(const char *str);
int						str_num(char *str);
int						ft_isspace(char c);
int						ft_strcmp(const char *s1, const char *s2);
char					*ft_strsub(char const *s, unsigned int start,
							size_t len);

// Built-ins
int						builtin_echo(char **args);
// int builtin_echo(char **args, t_env *env, t_data *data);
int						builtin_pwd(char **args);
int						builtin_env(t_env *env);
void					builtin_exit(char **args, t_data *data);
void					silent_builtin_exit(char **args, t_data *data);
int						builtin_cd(char **args, t_data *data);
int						builtin_unset(char **args, t_data *data);
int						builtin_export(char **args, t_data *data);

// Built-ins utils
int						update_pwd(t_env **env);
int						is_directory(const char *path);
char					*remove_plus_char(char *str);
void					add_concatenated_env(char *plus, t_env **env);
int						is_not_exported(char *arg, t_env *env);
void					replace_env(char *value, t_env **env);

// Env utils
int						add_env(char *str, t_env **env);
int						find_and_update_env(t_env *env, char *str);
void					get_env_name(char *str1, char *str2);
int						valid_env(char *str);
void					print_sorted_env(t_env *env);
void					printer(char *str, int j);
int						found_in_env(char *arg, t_env *env);
int						free_env(t_env *env, t_env *node);
char					*get_env_value(char *str, t_env *env);
void					increment_shlvl(t_env *env);
int						has_pipe(t_data *data);

// Initialize t_data struct
int						init_data(t_data *data, char **envp);
t_env					*init_env_list(char **envp);

void					handle_signal(int signo);
size_t					handle_dollar_digit(const char *input,
							t_expander_state *state);
size_t					handle_dollar_var(const char *input,
							t_expander_state *state);

int						handle_input(char *input, t_data *data);
int						process_input(t_data *data);
void					*ft_realloc(void *ptr, size_t size);
int						add_history_entry(t_data *data, const char *cmd);
int						builtin_history(char **args, t_data *data);
void					free_history(t_data *data);

#endif
