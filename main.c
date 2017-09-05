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

enum MetaCommandResult_t{
    META_COMMAND_SUCCESS,
    META_COMMAND_UNRECOGNIZED_COMMAND
};
typedef enum MetaCommandResult_t MetaCommandResult;

enum PrepareResult_t{
    PREPARE_SUCCESS,
    PREPARE_UNRECOGNIZED_STATEMENTS
};
typedef enum  PrepareResult_t PrepareResult;

enum StatementType_t {
    STATEMENT_INSERT,
    STATEMENT_SELECT
};
typedef enum StatementType_t StatementType;

struct Statement_t{
    StatementType type;
};
typedef struct Statement_t Statement;

MetaCommandResult do_meta_command(InputBuffer *inputBuffer){
    if(strcmp(inputBuffer->buffer, ".exit") == 0){
        exit(EXIT_SUCCESS);
    }else {
        return META_COMMAND_UNRECOGNIZED_COMMAND;
    }
}

PrepareResult prepare_statement(InputBuffer* inputBuffer, Statement* statement){
    if(strncmp(inputBuffer->buffer, "insert", 6) == 0){
        statement->type = STATEMENT_INSERT;
        return PREPARE_SUCCESS;
    }
    if (strcmp(inputBuffer->buffer, "select") == 0) {
       statement->type = STATEMENT_SELECT;
        return PREPARE_SUCCESS;
    }
    return PREPARE_UNRECOGNIZED_STATEMENTS;
}

void execute_statement(Statement* statement){
    switch (statement->type){
        case STATEMENT_INSERT:
            printf("This is where we would do an insert.\n");
            break;
        case STATEMENT_SELECT:
            printf("This is where we would do an select.\n");
            break;
    }
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

        if(inputBuffer->buffer[0] == '.'){
            switch (do_meta_command(inputBuffer)){
                case META_COMMAND_SUCCESS:
                    continue;
                case META_COMMAND_UNRECOGNIZED_COMMAND:
                    printf("Unrecognized command '%s'.\n", inputBuffer->buffer);
                    continue;
            }
        }

        Statement statement;
        switch (prepare_statement(inputBuffer, &statement)){
            case PREPARE_SUCCESS:
                break;
            case PREPARE_UNRECOGNIZED_STATEMENTS:
                printf("Unrecognized keyword at start of '%s'.\n", inputBuffer->buffer);
                continue;
        }
        execute_statement(&statement);
        printf("Execcted!\n");
    }
}



