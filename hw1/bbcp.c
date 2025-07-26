/*
CS631 -- Advanced Programming in the UNIX Environment - HW#1
HW#1: trivially copy a file

Summary

The objective of this assignment is for you to write your first
program and get comfortable developing a tool from a given specification.

Problem assignment

Write a simple program to copy a file following the
specification in the accompanying manual page.
*/

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "bool.h"

#ifndef BUFFSIZE
#define BUFFSIZE 32768
#endif
#ifndef MAXPATHLEN
#define MAXPATHLEN 1024
#endif

/*
    I belive stat(2) will replace the below 2 functions, but I wanted to 
    use only materials covered up to this point as per the assignment.
*/
BOOL file_exists(char* path) {
    int fd  = open(path, O_RDONLY);
    (void)close(fd);
    return fd != -1;
}

BOOL is_dir(char* path) {
    int fd  = open(path, O_DIRECTORY);
    (void)close(fd);
    return fd != -1;
}

long get_max_path_length() {
    long max_path = pathconf("/", _PC_PATH_MAX);
    return max_path == -1 ? MAXPATHLEN : max_path;
}

BOOL copy_file_to_file(char* path_source, char* path_dest) {
    // Check we can open path_source for reading
    int fd_from;
    if( (fd_from = open(path_source, O_RDONLY)) < 0) {
        fprintf(stderr, "Unable to open [ %s ] for reading: %s\n",
            path_source, strerror(errno));
        exit(EXIT_FAILURE);
    } 

    // Check we can open path_dest for writing
    int fd_to;
    const int flags = O_WRONLY | O_CREAT;
    // TODO: Copy with same permissions as source file ?
    const int perms = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
    if( (fd_to = open(path_dest, flags, perms)) < 0) {
        fprintf(stderr, "Unable to open [ %s ] for writing: %s\n",
                path_dest, strerror(errno));
        exit(EXIT_FAILURE);
    } 

    // Read fd_from and write fd_to
    int n;
    char buf[BUFFSIZE];
    while ((n = read(fd_from, buf, BUFFSIZE)) > 0) {
        if (write(fd_to, buf, n) != n) {
            fprintf(stderr, "Unable to write to [ %s ]: %s\n", path_dest,
                    strerror(errno));
            return FALSE;
        }
    }

    if (n < 0) {
        fprintf(stderr, "Unable to read [ %s ]: %s\n", path_source,
                strerror(errno));
            return FALSE;
    }

    (void)close(fd_from);
    (void)close(fd_to);

    return TRUE;
}


/*
   The bbcp utility copies the contents of the source to the target.  If target
   is a directory, bbcp will copy source into this directory.
*/
int main(int argc, char **argv) {
    // Check number of arguments
    if (argc != 3) {
        fprintf(stderr, "Invalid number of arguments.\nUsage: bbcp <from> <to>");
        exit(EXIT_FAILURE);
    }

    // read args after the first (program name)
    // char* program_name = argv[0];
    char* path_source = argv[1];
    char* path_dest = argv[2];

    if ( ! file_exists(path_source)){
        fprintf(stderr, "[ %s ] does not exist.\n", path_source);
        exit(EXIT_FAILURE);
    }

    if (file_exists(path_dest)){
        fprintf(stderr, "[ %s ] EXISTS...\n", path_dest);

        if (is_dir(path_dest)) {
            fprintf(stderr, "[ %s ] is a directory.\n", path_dest);
            // append base name of FROM onto the directory path of TO
            const long maxpathlen = get_max_path_length();
            char path_dest_new[maxpathlen];
            char* filename = strrchr(path_source, '/');
            filename = filename ? filename + 1 : path_source;
            snprintf(path_dest_new, sizeof(path_dest_new), "%s/%s", path_dest, filename);

            if (!copy_file_to_file(path_source, path_dest_new)) {
                exit(EXIT_FAILURE);
            }
        } else {
            fprintf(stderr, "[ %s ] is a regular file.\n", path_dest);

            fprintf(stderr, "Do you want to overwrite [ %s ]?\n", path_dest);
            fprintf(stderr, ">  TODO: accept input with fgets or whatnot.\n");
            BOOL overwrite = TRUE;

            if (overwrite) {
                fprintf(stderr, "Overwriting [ %s ] ...\n", path_dest);
                if (!copy_file_to_file(path_source, path_dest)) {
                    exit(EXIT_FAILURE);
                }
            } else {
                fprintf(stderr, "Unable to copy [ %s ] to [ %s ]!\n",
                        path_source, path_dest);
                exit(EXIT_FAILURE);
            }
        }
    } else {
        fprintf(stderr, "[ %s ] does not exist.\n", path_dest);
        if (!copy_file_to_file(path_source, path_dest)) {
            exit(EXIT_FAILURE);
        }
    }

    return(EXIT_SUCCESS);
}
