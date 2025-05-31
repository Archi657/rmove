#include "../include/colors.h"
#include <dirent.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "../include/definitions.h"

char **files_in_path(const char *path) {
    FILE *fptr;
    struct dirent *entry;
    int i = 0;

    char **files = malloc(sizeof(char*) * (MAX_FILES + 1));
    if (!files) {
        fprintf(stderr, RED "Error: Cannot initialize files in %s\n" RESET, path);
        perror("malloc");
        return NULL;
    }

    DIR *dir = opendir(path);
    if (!dir) {
        fprintf(stderr, RED "Error: Cannot open directory %s\n" RESET, path);
        perror("opendir");
        free(files);
        return NULL;
    }

    fptr = fopen("/var/log/re.log", "a");
    if (!fptr) {
        perror("Unable to open /var/log/re.log");
        closedir(dir);
        free(files);
        return NULL;
    }

    while ((entry = readdir(dir)) != NULL) {
        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)) {
            continue;
        }

        if (i >= MAX_FILES) {
            fprintf(stderr, YELLOW "Warning: Reached file limit of %d. Some files will be ignored.\n" RESET, MAX_FILES);
            break;
        }

        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        char timestamp[32];
        strftime(timestamp, sizeof(timestamp), "[%Y-%m-%d %H:%M:%S]", t);

        fprintf(fptr, "%s File found %s in %s\n", timestamp, entry->d_name, path);

        char filePath[PATH_MAX];
        snprintf(filePath, sizeof(filePath), "%s/%s", path, entry->d_name);
        files[i] = strdup(filePath);
        i++;
    }

    files[i] = NULL;

    closedir(dir);
    fclose(fptr);

    return files;
}
