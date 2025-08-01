# minishell

![Language](https://img.shields.io/badge/language-C-blue)  ![Status](https://img.shields.io/badge/build-passing-brightgreen)

**minishell** is a fully functional, Unix-like command interpreter built in C for the 42 School curriculum. This mandatory-only implementation recreates core features of Bash, exercising deep understanding of process control, I/O redirection, parsing, and signal handling—all under strict Norm constraints.

Unix-like command interpreter built in C for the 42 School curriculum. This mandatory-only implementation recreates core features of Bash, exercising deep understanding of process control, I/O redirection, parsing, and signal handling—all under strict Norm constraints.

---

## 📌 Table of Contents

* [🎯 Project Overview](#-project-overview)
* [🚀 Features](#-features)
* [🔧 Prerequisites](#-prerequisites)
* [📥 Installation & Build](#-installation--build)
* [🖥️ Usage Examples](#️-usage-examples)
* [📂 Project Structure](#-project-structure)
* [🏛️ Shell Grammar & Parsing](#-shell-grammar--parsing)
* [⚙️ Core Components](#️-core-components)

  * [Lexer](#lexer)
  * [Parser](#parser)
  * [Expander](#expander)
  * [Executor](#executor)
  * [Builtins](#builtins)
  * [Signal Handling](#signal-handling)
  * [Memory Management](#memory-management)
* [🧩 Code Snippets](#-code-snippets)
* [🧪 Testing & Examples](#-testing--examples)
* [🐛 Error Handling](#-error-handling)
* [⚖️ Norm & Compliance](#️-norm--compliance)
* [📖 Learnings & Challenges](#-learnings--challenges)
* [📜 License & Credits](#-license--credits)

---

## 🎯 Project Overview

This project implements a simplified shell that supports:

* Interactive command prompt with line editing and history (`readline`).
* Tokenization of user input into words, operators, and quoted strings.
* Parsing tokens into commands, arguments, redirections, and pipelines.
* Environment variable expansion (`$VARIABLE`, `$?`).
* Input/output redirections: `<`, `>`, `>>`, and here-documents (`<<`).
* Pipelines connecting multiple commands (`cmd1 | cmd2 | cmd3`).
* Builtin commands executed internally (`echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`).
* Proper handling of Unix signals (`SIGINT`, `SIGQUIT`).
* Strict adherence to 42 Norm: no global variables (except one for signal code), memory-safe, Norm compliant formatting.

This large-scale project integrates multiple subsystems—lexer, parser, expander, executor—providing hands-on experience with systems programming and Unix internals.

---

## 🚀 Features

1. **Interactive Prompt**

   * Customizable prompt: `minishell$ `
   * Line editing and history via GNU Readline

2. **Comprehensive Parsing**

   * Tokens: words, pipes (`|`), redirections (`<`, `>`, `>>`, `<<`), and quotes.
   * Handles single quotes (literal), double quotes (allow expansion), and escape characters.

3. **Environment Management**

   * Fetches and stores environment variables at startup.
   * `export` and `unset` to modify environment.
   * Expansion of `$VAR` and special `$?` (last exit code).

4. **Redirection Support**

   * `cmd < file`: redirect stdin
   * `cmd > file`: redirect stdout (truncate)
   * `cmd >> file`: redirect stdout (append)
   * `cmd << DELIM`: here-document, reading until `DELIM` line

5. **Pipelines**

   * Support for multiple chained commands with `|`.
   * Manages file descriptors and child processes.

6. **Builtins**

   * `echo [-n] [args...]`
   * `cd [directory]` (updates PWD and OLDPWD)
   * `pwd` (prints current working directory)
   * `export KEY[=VALUE]` (sets environment)
   * `unset KEY` (removes environment variable)
   * `env` (lists environment variables)
   * `exit [n]` (exits shell with status `n`)

7. **Signal Handling**

   * `SIGINT` (Ctrl-C): interrupts current input or child process
   * `SIGQUIT` (Ctrl-): ignored in interactive mode

8. **Robust Error Handling**

   * Graceful messages on syntax errors and system call failures.
   * Returns meaningful exit codes.

9. **Memory Safety**

   * All dynamic allocations freed.
   * Tested with Valgrind for no leaks or invalid access.

---

## 🔧 Prerequisites

* POSIX-compliant system (Linux, macOS).
* `cc` compiler supporting C99.
* GNU Readline library installed (`libreadline-dev`).
* Make.

---

## 📥 Installation & Build

```bash
# Clone repository
git clone https://github.com/fal-frou/minishell.git
cd minishell

# Build the shell
make

# Run
./minishell
```

Makefile targets:

* `all` (default): build `minishell`
* `clean`: remove object files
* `fclean`: remove object files and binary
* `re`: `fclean` + `all`

---

## 🖥️ Usage Examples

```bash
$ ./minishell
minishell$ echo "Hello, $USER"
Hello, fal-frou
minishell$ export TEST=42
minishell$ echo $TEST
42
minishell$ ls | grep minishell | wc -l
1
minishell$ cat << EOF > here.txt
> line1
> line2
> EOF
minishell$ cat here.txt
line1
line2
minishell$ cd ..
minishell$ pwd
/home/fal-frou
minishell$ exit 0
```

---

## 📂 Project Structure

```
minishell/
├── incs/
│   └── minishell.h                # Header with structs and prototypes
├── libft/                         # Custom libc functions
│   ├── Makefile
│   └── *.c, *.h (ft_*.c/h)
├── ft_printf/                     # Custom printf implementation
│   ├── ft_printf.c
│   ├── ft_fprintf.c
│   ├── ft_print_*.c
│   └── ft_sprintf_helpers.c
├── srcs/                          # Source files
│   ├── AST.c, AST1.c, AST2.c, AST3.c
│   ├── builtin_cd.c
│   ├── builtin_cd_utils.c
│   ├── builtin_echo.c
│   ├── builtin_env.c
│   ├── builtin_exit.c
│   ├── builtin_export.c
│   ├── builtin_export_utils.c
│   ├── builtin_history.c
│   ├── builtin_pwd.c
│   ├── builtin_unset.c
│   ├── char_utils.c
│   ├── debugging.c
│   ├── env_utils.c
│   ├── env_utils2.c
│   ├── execution1.c
│   ├── execution2.c
│   ├── execution3.c
│   ├── execution4.c
│   ├── execution5.c
│   ├── execution6.c
│   ├── execution_helpers.c
│   ├── expand_vars.c
│   ├── expand_vars2.c
│   ├── expand_vars3.c
│   ├── expand_vars4.c
│   ├── find_command.c
│   ├── ft_realloc.c
│   ├── history.c
│   ├── increment_lvl.c
│   ├── init_data.c
│   ├── main.c
│   ├── main_helper.c
│   ├── redirect_builtin.c
│   ├── sort_env.c
│   ├── str_utils.c
│   ├── str_utils2.c
│   ├── tokenization.c
│   ├── tokenization1.c
│   ├── tokenization2.c
│   ├── tokenization3.c
│   └── tokens_utils.c
├── Makefile                       # Build script
└── README.md                      # Project README
```

---

## 🏛️ Shell Grammar & Parsing

1. **Tokenization**:

   * Separators: spaces, tabs, newline
   * Tokens: WORD, PIPE (`|`), REDIR\_IN (`<`), REDIR\_OUT (`>`), APPEND (`>>`), HEREDOC (`<<`)
   * Quotes: `'single'` and `"double"`

2. **Parsing**:

   * Sequentially reads tokens
   * Builds a list of `t_command` structs:

     * `argv[]` array
     * `infile` / `outfile` descriptors
     * `append` or `truncate` flags
     * `here_doc` content buffer
   * Validates syntax (e.g., no two pipes in a row, redir with missing target)

---

## ⚙️ Core Components

### Lexer

* Reads input string.
* Extracts tokens with proper handling of quotes and escapes.
* Populates linked list of tokens.

### Parser

* Consumes token list.
* Groups tokens into commands and redirections.
* Allocates and initializes `t_command` for each pipeline segment.

### Expander

* Performs environment variable replacement inside words:

  * `$VAR` → value from `environ`
  * `$?` → last command exit code
* Removes quotes after expansion.

### Executor

* Determines if command is builtin or external.
* For external commands:

  * Sets up pipes (if part of pipeline).
  * Forks child processes.
  * Uses `dup2()` for redirections.
  * Calls `execve()` with full `envp` array.
* For builtins:

  * Executes function in the parent process (no fork).

### Builtins

* **echo**: supports `-n` (no newline)
* **cd**: updates PWD and OLDPWD, handles `cd -`
* **pwd**: prints current working directory
* **export**: adds/updates `KEY=VALUE`
* **unset**: removes variable
* **env**: lists variables
* **exit**: exits shell with status

### Signal Handling

* `SIGINT` (Ctrl-C):

  * In main prompt: prints newline + prompt
  * In child: interrupts command
* `SIGQUIT` (Ctrl-): ignored in interactive
* Single global `g_last_signal` captures status for `$?`.

### Memory Management

* All allocations tracked and freed at exit.
* No leaks (Valgrind tested).
* Helpers in `utils.c` wrap `malloc`/`free`.

---

## 🧩 Code Snippets

### Token Creation (`srcs/tokenization.c`)

```c
// create_token: allocate and initialize a new token
t_token *create_token(t_token_type type, const char *value)
{
    t_token *token = malloc(sizeof(t_token));
    if (!token)
        return (NULL);
    token->type = type;
    token->value = value ? ft_strdup(value) : NULL;
    token->next = NULL;
    return (token);
}

// add_token: append a new token to the list
void add_token(t_token **tokens, t_token_type type, const char *value)
{
    t_token *new_token = create_token(type, value);
    if (!new_token)
        perror_exit("Failed to create token");
    if (!*tokens)
        *tokens = new_token;
    else {
        t_token *tmp = *tokens;
        while (tmp->next)
            tmp = tmp->next;
        tmp->next = new_token;
    }
}
```

### Here-Document Reader (`srcs/execution1.c`)

```c
// Handle SIGINT during heredoc
void sigint_handler(int sig)
{
    (void)sig;
    write(1, "
", 1);
    exit(130);
}

// read_heredoc_lines: read lines until delimiter, writing to pipe
int read_heredoc_lines(int write_fd, const char *delimiter, t_data *data)
{
    signal(SIGINT, sigint_handler);
    char *expanded;
    while ((expanded = get_expanded_line(delimiter, data))) {
        write(write_fd, expanded, ft_strlen(expanded));
        write(write_fd, "
", 1);
        free(expanded);
    }
    signal(SIGINT, SIG_IGN);
    return (0);
}
```

### Simple Command Execution (`srcs/execution4.c`)

```c
int execute_simple_command(t_ast_node *node, t_env *env, t_data *data)
{
    t_exec_params params = {node, env, data, STDIN_FILENO, STDOUT_FILENO};
    int pid, status;

    if (process_redirections(node, &params.in_fd, &params.out_fd, data))
        return (1);
    signal(SIGINT, SIG_IGN);
    pid = fork();
    if (pid == 0)
        handle_child_process(&params);
    status = 0;
    waitpid(pid, &status, 0);
    signal(SIGINT, handle_signal);
    return (WIFEXITED(status) ? WEXITSTATUS(status) : 128 + WTERMSIG(status));
}
```

---

## 🧪 Testing & Examples

1. **Basic Commands**

   ```bash
   $ ls -l
   $ pwd
   $ echo "Hello, World"
   ```
2. **Redirections & Pipelines**

   ```bash
   $ grep minishell < README.md > out.txt
   $ cat out.txt | wc -l
   ```
3. **Heredoc**

   ```bash
   $ cat << END
     line1
     line2
   END
   line1
   line2
   ```
4. **Environment**

   ```bash
   $ export MYVAR=123
   $ echo $MYVAR
   123
   $ unset MYVAR
   ```
5. **Error Scenarios**

   ```bash
   $ | ls          # Syntax error
   $ cat <        # Missing filename
   ```

---

## 🐛 Error Handling

* **Syntax errors**: prints `minishell: syntax error near unexpected token`
* **Command not found**: `minishell: cmd: command not found`
* **Redirection errors**: uses `perror()` to show underlying errno
* **Builtin errors**: custom messages (e.g., `cd: no such file or directory`)

---

## ⚖️ Norm & Compliance

* No global variables except `int g_last_signal`.
* All code formatted to 42 Norm with `norminette`.
* No memory leaks; validated with Valgrind.
* No forbidden functions.

---

## 📖 Learnings & Challenges

* Designing a multi-stage parser for a shell grammar.
* Managing inter-process communication and I/O redirection.
* Handling asynchronous signals and maintaining shell state.
* Balancing simplicity with correctness under Norm constraints.

---

## 📜 License & Credits

This project is part of the 42 School curriculum. Educational use only.

**Credits (Github usernames):**

* fadel-fr03
* Nixential

---
