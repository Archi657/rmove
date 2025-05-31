#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

// Struct to hold all CLI options
typedef struct {
    const char* path;      // Default to current directory
    bool force;
    bool rollback;
    bool history;
    bool help;
} CLIOptions;

// Function to parse command-line arguments
CLIOptions parseArguments(int argc, char** argv);

#endif // CLI_H
