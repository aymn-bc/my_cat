#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <malloc.h>
#include <dirent.h>
#include <errno.h>

int isFile(char *name);

int main(int argc, char **argv){
    FILE *theFile[argc];
    int j = 0;
    int ch;
    char **error = NULL;
    if (argc == 1){
        theFile[argc-1] = stdin;
        while((ch = getc(theFile[argc - 1])) != EOF){
            putc(ch, stdout);
        }  
    }
    else if ( argc >= 2 ){
        error = (char**) malloc ((argc - 1) * sizeof(char*));
        for (int i = 1; i < argc; i++){
            if (!isFile(argv[i])){
                size_t len = strlen("Error: \"\" is a Directory!\n") + strlen(argv[i]) + 1;
                error[j] = (char*) malloc(len);
                if ( error[j] != NULL ) snprintf(error[j], len, "Error: \"%s\" is a Directory!\n", argv[i]);
                j++;
                continue;
            }
            else if (isFile(argv[i]) == -1) {
                size_t len = strlen("Error: No such file or directory named \"\" is not found!\n") + strlen(argv[i]) + 1;
                error[j] = (char*) malloc(len);
                if ( error[j] != NULL ) snprintf(error[j], len, "Error: No such file or directory named \"%s\" is not found!\n", argv[i]);
                j++;
                continue;
            }
            else{
                theFile[i] = fopen(argv[i], "r");
                while ((ch = getc(theFile[i])) != EOF){
                    putc(ch, stdout);
                }
                fclose(theFile[i]);
            }
        }
        if (error != NULL){
            for (int i = 0; i < j; i++){
                printf("%s", error[i]);
                free(error[i]);
            }
            free(error);
        }
    }
}
    


int isFile(char *name){
    DIR *directory = opendir(name);
    if (directory != NULL) {
        printf("\nWorkss\n");
        closedir(directory);
        return 0;
    }else if (errno == ENOENT){
        return -1;
    }
    return 1;
}