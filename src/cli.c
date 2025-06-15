/* rm implementation options
- The idea of this implementation is avoid mistakes while deleting files,
for that reason the iteractive mode is always enabled, and -f/--force will be necessary,
if you want to avoid it.

- Rollback mode will allow you to recover the deleted files.

- This command offers a history mode to see an historical of files removed.
*/

#include "../include/cli.h"
#include <linux/limits.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

CLIOptions parseArguments(int argc, char** argv) {

    CLIOptions options;
    options.path = ".";         // Default path if not specified
    options.force = false;
    options.rollback = false;
    options.history = false;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--force") == 0) {
            options.force = true;
        } else if (strcmp(argv[i], "-rr") == 0 || strcmp(argv[i], "--rollback") == 0) {
            options.rollback = true;
        } else if (strcmp(argv[i], "-hh") == 0 || strcmp(argv[i], "--history") == 0) {
            options.history = true;
        } else if (strcmp(argv[i], "-h") == 0 || strcmp(argv[i], "--help") == 0) {
            options.help = true;
        // Convert path to absolute path
        } else {
            char cwd[PATH_MAX];
            if(strcmp(argv[i], ".") == 0){
                if(getcwd(cwd, sizeof(cwd)) == NULL){
                    perror("Error getting the directory specified");
                }
            }else{
                strncpy(cwd, argv[i], PATH_MAX-1);
                cwd[PATH_MAX - 1] = '\0';  // Assume it's a path
            }
            options.path = cwd;
        }
    }

    return options;
}
