*This project has been created as part of the 42 curriculum by shannema.*

# get_next_line

## Description

`get_next_line` is a project from the 42 school curriculum. Its goal is to implement a C function that reads and returns one line at a time from a file descriptor, allowing repeated calls to iterate through an entire file line by line — similar to how `fgets` works in the standard library, but without using it.

The function has the following prototype:

```c
char *get_next_line(int fd);
```

It must work correctly for any valid file descriptor (regular files, standard input) and for any buffer size, including edge cases such as `BUFFER_SIZE=1` or `BUFFER_SIZE=10000000`. Each call returns the next unread line including its trailing `\n` character (except at end of file if the file does not end with one). It returns `NULL` when there is nothing left to read or if an error occurs.

The project is split across three files:

- `get_next_line.c` — the main function and its helpers
- `get_next_line_utils.c` — utility string functions
- `get_next_line.h` — the header containing prototypes and the `BUFFER_SIZE` macro

**Constraints imposed by the 42 Norm:**
- No more than 5 functions per `.c` file
- No function body longer than 25 lines
- No global variables
- No use of `lseek()` or `libft`
- No use of `while`/`for` loops in utility functions (only in main logic)

---

## Instructions

### Compilation

The project must be compiled with a `-D BUFFER_SIZE=n` flag to define the read buffer size. A default value of 42 is used if not specified.

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

### Testing with a main

To test locally, create a `main.c` file:

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int   fd;
    char  *line;

    fd = open("test.txt", O_RDONLY);
    if (fd < 0)
        return (1);
    line = get_next_line(fd);
    while (line)
    {
        printf("%s", line);
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    return (0);
}
```

Then compile all files together:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 main.c get_next_line.c get_next_line_utils.c
./a.out
```

Test with different buffer sizes:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1    main.c get_next_line.c get_next_line_utils.c && ./a.out
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 main.c get_next_line.c get_next_line_utils.c && ./a.out
```

---

## Algorithm

### The Problem with Naïve Approaches

The most intuitive approach — reading `BUFFER_SIZE` bytes at a time, joining chunks with `strjoin` until a newline is found — leads to **O(N²) performance**. Each `strjoin` call must copy the entire accumulated string into a new allocation. For a line of N characters read one byte at a time (i.e. `BUFFER_SIZE=1`), this means copying 1+2+3+...+N bytes, which is roughly N²/2 total byte operations. On large lines this causes guaranteed timeouts.

A second common mistake is using a stack-allocated `char chunk[BUFFER_SIZE + 1]` inside a recursive function. With `BUFFER_SIZE=10000000`, each stack frame reserves 10MB — far exceeding the typical 8MB stack limit — causing an immediate segfault.

### The Chosen Algorithm: Growing Heap Buffer with Direct Append

The algorithm chosen avoids both of these problems by maintaining a **heap-allocated buffer that grows as needed**, and by reading new data **directly into the end of the buffer** at offset `len` — never copying existing content.

```
buf = malloc(BUFFER_SIZE + 1)
seed buf with any leftover from previous call (carry)
len = strlen(carry)

while no '\n' found in buf:
    if len + BUFFER_SIZE > cap:
        double the buffer capacity (grow_buf)
    read(fd, buf + len, BUFFER_SIZE)   ← appends directly, no copying
    len += bytes_read

extract line from buf
save everything after '\n' into carry for next call
free buf
return line
```

Key properties of this approach:

- **O(N log N) total work** for a line of N bytes: the buffer doubles in capacity at most log₂(N) times, and each doubling copies the current content once. All other reads are direct appends with zero copying of old data.
- **No stack overflow**: `chunk` is eliminated entirely; data is read straight into the heap buffer.
- **No infinite loop on EOF**: `read()` returning 0 exits the loop immediately, and `make_line` returns `NULL` on an empty buffer, correctly signalling end of file to the caller.
- **Leftover handling**: After extracting a line, everything after the `\n` is copied into a fixed `static char carry[BUFFER_SIZE + 1]` array and seeded into the next call's buffer, ensuring no data is lost between calls.

### Function Breakdown

| Function | Role |
|---|---|
| `get_next_line` | Entry point: validates fd, calls helpers, returns line |
| `init_buf` | Allocates initial buffer and seeds it from `carry` |
| `read_into` | Main read loop: appends chunks directly into buffer |
| `grow_buf` | Doubles buffer capacity when needed |
| `make_line` | Extracts the line, saves remainder to `carry` |

---

## Resources

### Documentation & References

- [Linux `read()` man page](https://man7.org/linux/man-pages/man2/read.2.html) — the only I/O function used
- [Linux `open()` man page](https://man7.org/linux/man-pages/man2/open.2.html) — for understanding file descriptors
- [42 Norm v3](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf) — coding standard enforced throughout the project
- [File descriptors explained — GeeksforGeeks](https://www.geeksforgeeks.org/input-output-system-calls-c-create-open-close-read-write/) — background on how fd-based I/O works in C
- [Static variables in C — tutorialspoint](https://www.tutorialspoint.com/static-variables-in-c) — essential concept for persisting state between calls

### Use of AI

AI (Claude, by Anthropic) was used throughout this project as a collaborative debugging and implementation tool. Specifically:

- **Initial scaffolding**: Claude generated a first working version of `get_next_line.c` and `get_next_line_utils.c` based on the project subject.
- **Iterative debugging**: Each compiler error and tester failure was fed back to Claude, which diagnosed the issue and proposed corrections. Errors addressed included implicit function declarations, conflicting types, unused functions, stack overflows from VLA recursion, infinite loops on EOF, O(N²) performance on giant lines, and NULL dereferences on empty files.
- **Constraint enforcement**: Claude enforced 42 Norm rules (max 5 functions per file, max 25 lines per function, no ternaries, no forbidden functions) across all iterations, recounting and restructuring code as constraints were clarified.
- **Conceptual explanation**: Claude explained each error message and fix in plain language, helping build understanding of C memory management, linking, recursion limits, and algorithmic complexity alongside the working code.
