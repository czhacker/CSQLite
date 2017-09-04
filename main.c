//
// Created by chenHiro on 17/9/4.
//

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct InputBuffer_t {
    char* buffer;
    size_t buffer_length;
    ssize_t input_length;
};

typedef struct InputBuffer_t InputBuffer;

InputBuffer* new_input_buffer(){
    InputBuffer* input_buffer = malloc(sizeof(InputBuffer));
    input_buffer->buffer = NULL;
    input_buffer->buffer_length = 0;
    input_buffer->input_length = 0;
    return input_buffer;
}

void print_prompt() {
    printf("db > ");
}

void read_input(InputBuffer* inputBuffer){
    ssize_t bytes_read = getline(&(inputBuffer->buffer), &(inputBuffer->buffer_length), stdin);

    if(bytes_read < 0){
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    inputBuffer->buffer[bytes_read-1] = 0;
    inputBuffer->input_length = bytes_read - 1;
}

int main(int argc, char** args) {
    InputBuffer* inputBuffer = new_input_buffer();
    while(true){
        print_prompt();
        read_input(inputBuffer);

        if(strcmp(inputBuffer->buffer, ".exit") == 0){
            exit(EXIT_SUCCESS);
        }else{
            printf("Unrecognized command '%s'.\n", inputBuffer->buffer);
        }
    }
}



