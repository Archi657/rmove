#include "../include/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>  
#include <string.h>
#include "../include/functions.h"
#include "../include/definitions.h"

const char* get_filename(const char* path) {
    const char* filename = strrchr(path, '/');

    if (filename == NULL) {
        // No '/' found, entire path is the filename
        return path;
    } else {
        // Move pointer past '/'
        return filename + 1;
    }
}

int deleteF(const CLIOptions* options) {
    const char *pathEnd = "/home/archi/Desktop/Projects/rmove/tests/new";
    FILE *fptr;

    // Get current time
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    char timestamp[32];
    strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", t);

    // Create or open file
    fptr = fopen("/var/log/re.log", "a");
    if (!fptr) {
        perror("Unable to open /var/log/re.log");
        return -1;
    }

    // if not -f Output starting process 
    if (!options->force) printf("Detailed log at /var/log/re.log\n");
    if (!options->force) printf("Preparing to 'delete' (move) %s...\n", options->path);

    // Write log starting process
    fprintf(fptr, "%s Executing moving file\n", timestamp);
    fprintf(fptr, "%s Path provided: %s\n", timestamp, options->path);
    fclose(fptr);
    // TODO: Process regex and move files
    char** files = files_in_path(options->path);
    
    if(!files){
        fprintf(stderr, "Failed to get files from path :%s\n", options->path);
        return -1;
    }

    // Move files
   char newPath[MAX_FILES]; 

    for (int i = 0; i < MAX_FILES && files[i] != NULL; i++) {
        // Compose new path by combining pathEnd + "/" + filename
        snprintf(newPath, sizeof(newPath), "%s/%s", pathEnd, get_filename(files[i]));

        int rc = rename(files[i], newPath);
        if (rc != 0) {
            perror("Failed to rename file");
        }

        free(files[i]);
    }
    free(files);


    
    return 0;
}

