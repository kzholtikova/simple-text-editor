#include <cstdio>
#include "../include/additional_commands.h"

void clearConsole() {
    printf("\e[1;1H\e[2J"); // RegEx using ANSI escape codes
}
