# Simple C `grep` Utility

A lightweight, customized C implementation of the standard Unix `grep` pattern-matching tool. It scans files line-by-line for target search keywords with optional support for case-insensitive matching and whole-word filtering.

---

## Features

* **Pattern Matching:** Scans text files line-by-line and reports line numbers where matches occur.
* **Case-Insensitive Search (`-i`):** Normalizes text and patterns to lower-case for case-agnostic lookups.
* **Whole-Word Matching (`-w`):** Uses alphanumeric and underscore delimiter boundaries to isolate standalone word matches.
* **Colored Matches:** Emphasizes matched lines in red using ANSI escape sequences.
* **Length & Buffer Safety:** Enforces bounds checking on keyword lengths and buffers to prevent overflows.

---

## Getting Started

### Prerequisites

* A C compiler (`gcc`, `clang`, etc.)
* Standard C library (`libc`)

### Compilation

Compile the program using `gcc`:

```bash
gcc -Wall -Wextra -O2 grep_2.c -o mygrep
```

---

## Usage

```bash
./mygrep <keyword> <filename> [flags]
```

### Supported Flags

| Flag | Description |
| :--- | :--- |
| `-i` | Ignore case distinctions in patterns and file data |
| `-w` | Match only whole words separated by non-alphanumeric characters |

---

## Examples

* **Basic search:**
  ```bash
  ./mygrep main program.c
  ```

* **Case-insensitive search:**
  ```bash
  ./mygrep error log.txt -i
  ```

* **Whole-word search:**
  ```bash
  ./mygrep cat story.txt -w
  ```
  *(Matches "cat", but ignores "caterpillar" or "scatter")*

* **Combined flags:**
  ```bash
  ./mygrep test log.txt -i -w
  ```

---

## Error Handling

* **Missing arguments:**
  ```text
  Usage: grep <keyword> <filename> [flags]
  ```
* **Oversized keywords:** Prints an error if the keyword exceeds 1023 characters.
* **Missing or unreadable files:**
  ```text
  Could not open file '<filename>'
  ```
* **No matches found:**
  ```text
  Unable to find '<keyword>' inside file '<filename>'
  ```

---

## Disclaimer

I haven't tested this personally, so I dont know if its working or if there are any bugs. This is also why there isn't a .exe file in this repo.

---

## License

This project is open-source and available under the [MIT License](LICENSE).
