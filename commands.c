#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "header.h"

void commands() {
    printf("=== Commands Supported by Your Minimal Shell ===\n\n");

    printf("Built-in command:\n");
    printf("  cd                - change directory\n\n");

    printf("External commands (anything in your system PATH):\n");
    printf("  ls                - list files\n");
    printf("  pwd               - print working directory\n");
    printf("  cat <file>        - show file contents\n");
    printf("  echo <text>       - print text\n");
    printf("  touch <file>      - create file\n");
    printf("  rm <file>         - remove file\n");
    printf("  mkdir <dir>       - create directory\n");
    printf("  rmdir <dir>       - remove directory\n");
    printf("  cp <src> <dst>    - copy file\n");
    printf("  mv <src> <dst>    - move/rename file\n");
    printf("  date              - show date/time\n");
    printf("  uname -a          - system information\n");
    printf("  ps                - process list\n");
    printf("  whoami            - current user\n");
    printf("  gcc <file.c> -o a.out   - compile C programs\n");
    printf("  ./program         - run your own binaries\n\n");

    printf("Notes:\n");
    printf("  Your shell currently does NOT support pipes (|), redirection (> <),\n");
    printf("  background jobs (&), variables ($HOME), or wildcards (*).\\n");
}
