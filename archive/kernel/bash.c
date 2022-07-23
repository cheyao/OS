#include "bash.h"
#include "functions.h"

char parameters[256];
char command[32];

void run(char input[]) {
    int i = 0;
    for (; input[i] != ' ' && input[i] != 0; i++) append(command, input[i]);
    i++;
    for (; input[i] != 0; i++) append(parameters, input[i]);

    if (strcasecmp(command, "echo")) {
        kprint(parameters);
        kprint("\n");
    }

    kprint("usr $ ");  // Gets reddy for a next session
    memset(command, 0, sizeof command);       // Clear lists
    memset(parameters, 0, sizeof parameters);
    UNUSED(input);
}
