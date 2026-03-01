*This project has been created as part of the 42 curriculum by `shannema.`* 

# Description
**get_next_line** 

TO BE EDITED

ft_printf is a reimplementation of the standard C printf function and serves to display a formatted string on the screen, which we do with format specifiers.

ft_printf is a custom reimplementation of the standard C `printf` function.  
It handles basic format specifiers and reproduces formatted output using variadic arguments and the `write` system call.

The goal of this project is to understand:
- Variadic functions (`stdarg.h`)
- Format string parsing
- Base conversion
- Low-level output handling

Prototype:

int ft_printf(const char *format, ...);

---

**Format Specifiers**

| Character | Description |
|-----------|-------------|
| `%` | Prints a `%` character. |
| `d`, `i` | Print an `int` as a signed integer. `%d` and `%i` are synonymous for output, but differ with `scanf`: `%i` interprets numbers as hexadecimal if preceded by `0x`, and octal if preceded by `0`. |
| `u` | Print a decimal `unsigned int`. |
| `x`, `X` | Print an `unsigned int` as a hexadecimal number. `x` uses lowercase letters; `X` uses uppercase letters. |
| `s` | Print a null-terminated (`\0`) string. |
| `c` | Print a single character (`char`). |
| `p` | Print the address of a pointer (or any variable) in hexadecimal format. Used for `void *` data type. |



# Instructions

## How ft_printf is used

**⚙️ Implementation Overview**

ft_printf uses a linear parsing algorithm:

Iterate through the format string.

Print regular characters directly.

When % is found, dispatch to a specific conversion function.

Count and return the total number of printed characters.

---


**Algorithm Choice**

Single-pass parsing → O(n) complexity.

Number conversions use recursive or iterative base division.

No dynamic memory allocation required.

Modular structure (one function per conversion).

This approach keeps the implementation simple, efficient, and norm-compliant.

---

**🚀 Installation**

git clone

https://github.com/Stephonetic/ft_printf.git

make

---

### 1. Include the Header File

The header file (`ft_printf.h`) contains function prototypes and data structure definitions.
Including it allows the compiler to know how to correctly call the library functions.


#include "ft_printf.h"
This inclusion is required in every source file that uses functions from ft_printf.

### 2. Build Rules & Project Requirements

The **ft_printf** project is written in **C** and strictly follows the **42 Norm**.  

The provided `Makefile` includes the required rules:

- `$(NAME)` / `all`
- `clean`
- `fclean`
- `re`

Memory safety is a core requirement:
- Functions must not crash unexpectedly (segmentation fault, double free, etc.)
- All heap-allocated memory must be properly freed
- Memory leaks are not tolerated

The resulting static library (`ft_printf.h`) is designed to be reused in other projects by
copying the library sources and Makefile into a dedicated `ft_printf.h/` directory and compiling
it through its own Makefile.

### 3. Execution

All source files compile with the flags `-Wall -Wextra -Werror`, and the library is built
using `cc` and `ar` without unnecessary relinking.
After successful compilation and linking, the resulting executable can be run as is mentioned in the 42 subjects which is as follows:

`make`

### 4. Test Program

The test main is using the prorgramm for ft_printf and can be compiled as follows:
`make test`

# Resources

- Peer to peer teaching, tips and implementation of suggestions

- Written in C, following the 42 Norm.

- No external libraries are used.

- Memory allocation is carefully managed to avoid leaks.

- man 3 printf

- man 3 stdarg

- https://42-cursus.gitbook.io/guide/1-rank-01/ft_printf

