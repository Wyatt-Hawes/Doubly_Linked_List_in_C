#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include <string.h>


int main(int argc, char* argv[]){

    if (argc != 3){
        fprintf(stderr, "Please enter 2 arguments.\n Ex: Lex <input file> <output file>\n");
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");

    if (input == NULL){

        fprintf(stderr, "Input file does not exist.\n");
        return 1;
    }

    int lines = 0;

    char c = getc(input);

    while(c != EOF){
        
        if(c == '\n'){
            lines++;
        }
        c = getc(input);
    }
    //fprintf(output, "%d lines.\n", lines);

    fclose(input);
    input = fopen(argv[1], "r");


    char** string_arr = calloc(lines, sizeof(char*));

    char* currentLine = malloc(300 * sizeof(char));


    for(int i = 0; i < lines; i++){
        fgets(currentLine, 300, input);
        //fprintf(output, "%s", currentLine);
        
        int length = strlen(currentLine);
        currentLine[length -1] = '\0';
        //printf("-%s-", currentLine);
        //fprintf(output, "%s", currentLine);

        string_arr[i] = malloc((length) * sizeof(char));
        //printf("Length:%d  %s\n", length,currentLine);
        memcpy(string_arr[i],currentLine, sizeof(char) * (length));
    }

    free(currentLine);
    
    List L = newList();

    int arr_pos = 0;
    //printf("L:%d\n", lines);
    //printf("loop\n");
    while(length(L) < lines){
        char* word = string_arr[arr_pos];
        moveFront(L);
        //printf("\n-----------\nw:%s ", word);
        //printList(stdout,L);
        while (true){
            //printf("Curs:%d\n", index(L));
            if (index(L) == length(L) || index(L) == -1){
                //printf("append:%s\n", word);
                append(L, arr_pos);
                break;
            }
            if (strcmp(word, string_arr[get(L)]) > 0){
                
                moveNext(L);
                continue;
            }

            //printf("Insert:%s\n", word);
            insertBefore(L, arr_pos);
            //printf("insert\n");
            break;
        }
        
       // printf("\n------------------------\n");
       // printList(stdout,L);
       // printf("------------------------\n");
        arr_pos++;
    }

    //printList(stdout, L);
    moveFront(L);
    while (index(L) != -1){
        //printf("Curs:%d\n", index(L));
        fprintf(output, "%s\n", string_arr[get(L)]);
        moveNext(L);

    }
    //printf("bottom\n");

    for(int i = 0; i < lines; i++){
        free(string_arr[i]);
    }
    free(string_arr);
    freeList(&L);
    fclose(input);
    fclose(output);
}