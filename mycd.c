 /**
Author: Yufei Pan
How to compile: use "gcc mycd.c -o mycd"
How to run: use "mycd"
**/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h> 
#include <unistd.h>
#include <ctype.h>

int strIsAlnum(char * token){
    int i = 0;
    while (token[i] != '\0') {
        if (!isalnum(token[i])){
            return 0;
        }
        i++;
    }
    return 1;
}

// This will take in a string location and format it to output a valid address to the console
void printDir(char * dirName){

    // using c's string tokenize liburary to split the string
    const char seperator[2] = "/";
    char *token;
    // creating a full static array as this whole array is not very memory intensive
    // for bigger project a dynamic array (linked) will be preferable 
    char tokens [1024][1024];
    int tokenPtr = 0;
    //get the first address
    token = strtok(dirName, seperator);
   
    //loop through all the addresses until null
    while( token != NULL ) {
        //printf( " %s\n", token );
        if (strcmp(token, ".") == 0){
             // This means this directory, not adding anything
        }else if (strcmp(token, "..") == 0){
            // This means previous directory, going back if possible.
            if (tokenPtr > 0){
                tokenPtr--;
            }
        }else if (strIsAlnum(token)){
            // store this token for reconstructing later
            strcpy(tokens[tokenPtr],token);
            tokenPtr++;
        }else{
            printf("%s : No such file or directory\n",token);
            printf("Note: directory name can only contain alphanumeric characters.\n");
            return;
        }
        //get the next token
        token = strtok(NULL, seperator);
    }

    // print the new dir address

    int ptr = 0;
    if (tokenPtr == 0){
        printf("/");
    }
    while (ptr < tokenPtr){
        printf("/");
        printf("%s",tokens[ptr]);
        ptr++;
    }
    printf("\n");
}


void resolveDir(char * baseDir,char * cdPath){
    //printf("%s,%s\n",baseDir,cdPath);
    if (cdPath[0] == ('/')){
        strcpy(baseDir,cdPath);
    }
    else{
        //printf("yeah\n");
        strcat(baseDir, "/");
        strcat(baseDir, cdPath);
        //printf("%s\n",baseDir);
    }
}



int main( int argc, char *argv[] )  {

    if( argc == 2 ) {
        char cache1 [1024];
        strcpy(cache1,argv[1]);
        // One arguments had been passed in. Dereference it and print out the output directly
        printDir(cache1);
    }
    else if( argc > 2 ) {
        // At least two arguments had been passed in. We are only interested in the first two.
        char cache1 [1024];
        strcpy(cache1,argv[1]);
        resolveDir(cache1,argv[2]);
        //printf("%s\n",targetDir);
        //printf("%s\n",cache1);
        printDir(cache1);
    }
    else {
        printf("MyCD takes two arguments: \n");
        printf("The first path is a current directory. The second path is a new directory.\n");
        printf("MyCD will decode and print out the final directory.\n");
        printf("Note: directory name can only contain alphanumeric characters.\n");
    }

}