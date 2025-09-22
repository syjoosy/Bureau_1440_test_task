#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdbool.h>
#include "md5/md5.h"

void list_files_recursive(const char *path) {
    DIR *dir;
    struct dirent *entry;

    if ((dir = opendir(path)) == NULL) {
        perror("Failed to open directory");
        return;
    }

    printf("Current directory: %s\n", path);

    bool has_bin = false;
    bool has_md5 = false;
    char *hashCalculated = NULL;
    char *hashReaded = NULL;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[4096];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (stat(fullpath, &st) == -1) {
            perror("stat error");
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            // Recurse into subdirectory
            list_files_recursive(fullpath);
            continue;
        }

        // Check for BIN file
        if (strstr(entry->d_name, ".bin")) {
            has_bin = true;
            printf("Found BIN: %s\n", fullpath);

            FILE *f = fopen(fullpath, "r");
            if (f) {
                char *text = malloc(10000);
                if (text) {
                    if (!readFile(text, f)) {
                        printf("Error reading file!\n");
                    }
                    int length = strLen(text);
                    Blocks *blocks = makeBlocks(text, length);
                    hashCalculated = md5(blocks);
                    free(text);
                }
                fclose(f);
            }
        }

        // Check for MD5 file
        if (strstr(entry->d_name, ".md5")) {
            has_md5 = true;
            printf("Found MD5: %s\n", fullpath);

            FILE *f = fopen(fullpath, "r");
            if (f) {
                hashReaded = malloc(33);
                if (hashReaded) {
                    if (fscanf(f, "%32s", hashReaded) != 1) {
                        fprintf(stderr, "Failed to read hash from file\n");
                        free(hashReaded);
                        hashReaded = NULL;
                    }
                }
                fclose(f);
            }
        }
    }

    // After scanning all files in the directory, check if a pair exists
    if (has_bin && has_md5) {
        printf("Pair found in directory %s\n", path);
        printf("Hash read: '%s'\n", hashReaded);
        printf("Hash calculated: '%s'\n", hashCalculated);

        if (hashReaded && hashCalculated && strcmp(hashReaded, hashCalculated) == 0) {
            printf("Hashes match!\n\n\n");
        } else {
            printf("Hashes not match!\n\n\n");
        }
    } else {
        printf("Pair not found in directory %s\n\n", path);
    }

    free(hashReaded);
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Error: No directory provided!\n");
        return 1;
    } else {
        fprintf(stderr, "Using directory '%s' to calculate hashes!\n\n", argv[1]);
        list_files_recursive(argv[1]);
    }
    return 0;
}
