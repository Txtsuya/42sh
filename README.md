# 42sh - Advanced Unix Shell

<div align="center">

</div>

## 📋 Overview

42sh is a projected made to replicate in C programming language the Unix shell TCSH. 
The project is carried out by 5 members

## 🚀 Usage

### Basic Usage
```bash
./42sh
```

Launch the shell and start executing commands interactively.

### Bonus Features
```bash
make bonus
./42sh
```

The bonus version includes additional features:
- **Custom prompt colors**: Configurable via `.42shrc`
- **Enhanced alias system**: Pre-configured aliases from `.42shrc`
- **Color customization**: Use `setcolor` command to modify prompt colors

Example `.42shrc` configuration:
```bash
alias "lsl=ls -la"
alias "c=clear"
color "YELLOW WHITE BLUE BRIGHT_CYAN"
```

## ✨ Some Implemented Features

### Basic Features
- **Command execution** with PATH resolution
- **Built-in commands**: `cd`, `env`, `setenv`, `unsetenv`, `exit`, `echo`
- **Command separators**: `;` for sequential execution
- **Pipes**: Multiple pipe chaining (`|`)
- **Redirections**: `>`, `>>`, `<`, `<<` (heredoc)
- **Error handling**: Command not found, permission denied, etc.

### Advanced Features
- **Globbing**: Wildcard expansion (`*.c`, `?.txt`, `[abc].c`)
- **Job control**: Background execution (`&`), `jobs`, `fg`, `bg`
- **Aliases**: Define and use command aliases
- **History**: Command history with `!` syntax
- **Local variables**: `set` and `unset` commands
- **Logical operators**: `&&` and `||` (partial support)
- **Backticks**: Command substitution
- **Special commands**: `where`, `which`, `repeat`
- **Parentheses**: Command grouping
- **Custom getline**: Arrow key navigation, history search

### Special Variables
- `$cwd` - Current working directory
- `$cwdcmd` - Hook executed on directory change
- `$precmd` - Hook executed before each prompt
- `$ignoreeof` - Prevent Ctrl-D from exiting
- `$term` - Terminal type

### Inhibitors & Quoting
- Single quotes `'...'` - Literal strings
- Double quotes `"..."` - Variable expansion allowed
- Backslash `\` - Escape character

## 🧪 Testing

### Run the automated test suite:
```bash
make tester
# or
./tester.sh
```

### Run unit tests:
```bash
make tests_run
```

### Test Results

| Category                         | Percentage | Tests Passed |
|----------------------------------|:----------:|:------------:|
| basic tests                      |    100%    |     4/4      |
| path handling                    |    80%     |     4/5      |
| setenv and unsetenv              |    100%    |     2/2      |
| builtin cd                       |    100%    |     3/3      |
| line formatting (space and tabs) |    100%    |     8/8      |
| error handling                   |    100%    |     6/6      |
| separator                        |    100%    |     1/1      |
| simple pipes                     |    100%    |     3/3      |
| advanced pipes                   |    100%    |     6/6      |
| redirections                     |    100%    |     5/5      |
| advanced manipulations           |    100%    |     3/3      |
| && and \|\| tests                |    100%    |     3/3      |
| globbing                         |    100%    |     1/1      |
| var interpreter                  |    100%    |     3/3      |
| inhibitor                        |    100%    |     2/2      |
| command substitution (magic quotes) |    100%    |     3/3      |
| alias                            |    75%     |     3/4      |
| scripting                        |     0%     |     0/1      |
| foreach                          |     0%     |     0/1      |
| which                            |    100%    |     2/2      |
| where                            |     100%   |     2/2      |
| if                               |     0%     |     0/2      |
| repeat                           |    100%    |     1/1      |
| parenthesis                      |     0%     |     0/1      |
| **Overall Results**              | **91.7%**  |  **65/72**   |

### 📚 Keynote result
We got the **best 42sh** of **our class**.

Project Mark :
```
Mark : 25
Automatic tests (11 / 14) :

History (3 / 3.5) :

Job control (2.5 / 2.5) :
Tout les jobs controls
Dynamic command line (0.5 / 2.5) :
pas d'autocomplete

Bonus (5 / 10) :
AST
bashrc
unit test
Questions fun (3 / 5) :

```

Oral Mark :
```
Mark : 4444
Testing Policy (4 / 4) :
Tests unitaires, tests fonctionnels

Methodology and Organisation (40 / 40) :
Agilité, github project, pull requests

Involvment (400 / 400) :
Globbings, inhibiteurs, scripting, edit de ligne, système de priorité AST
variable locale, alias
personnalisation, couleurs

Oral Presentation (4000 / 4000) :
Belle uniformité, belle tenue + 1
Attention avec le pointage du doigt
"Merci enzo"
Vous êtes devant la télé mais ça s'est arrangé
Rétrospection
alors attention github n'a pas inventé les branches, c'est git.
Politiques de tests
C'est très fluide.
```


## 🔨 Compilation

### Standard compilation:
```bash
make
```

### Bonus compilation:
```bash
make bonus
```

### Clean build files:
```bash
make clean      # Remove object files
make fclean     # Remove object files and binary
make re         # Rebuild from scratch
```

### Debug compilation:
```bash
make val        # Compile with debug symbols
make runval     # Run with valgrind
make runvalcheck # Run with full memory leak check
```

### Other useful commands:
```bash
make run        # Compile and run
make echorun ARG="ls -l" # Test with specific command
```

## 💡 Examples

### Basic Commands
```bash
42sh> ls -l
42sh> cd /tmp
42sh> pwd
```

### Pipes and Redirections
```bash
42sh> ls -l | grep .c | wc -l
42sh> cat file.txt > output.txt
42sh> echo "Hello" >> output.txt
42sh> cat < input.txt
```

### Job Control
```bash
42sh> sleep 10 &
[1] 12345
42sh> jobs
[1] Running    sleep 10
42sh> fg %1
```

### Aliases
```bash
42sh> alias ll ls -la
42sh> ll
42sh> unalias ll
```

### Variables
```bash
42sh> set myvar=hello
42sh> echo $myvar
hello
42sh> unset myvar
```

### History
```bash
42sh> ls -l
42sh> !-1        # Repeat last command
42sh> !ls        # Repeat last command starting with 'ls'
```

### Special Commands
```bash
42sh> which ls
/bin/ls
42sh> where ls cd
cd is a shell built-in
/bin/ls
42sh> repeat 3 echo "Hello"
Hello
Hello
Hello
```

## 🐛 Known Issues

- `if` statements have implementation issues. It has been deactivated in the code for the keynote as it caused crashes

## 👥 Contributors

- [Aryan](https://github.com/Txtsuya)
- [Enzo](https://github.com/enzo-bazin)
- [Antony](https://github.com/antothP)
- [Simon](https://github.com/Simon-du06)
- [Jeremy](https://github.com/JeremyAlbertini)
