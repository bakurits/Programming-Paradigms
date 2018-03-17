#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>


#define ERROR_MAX_LEN 10000
#define LINE_MAX_LEN 10000
#define END_OF_REPL "(exit)"
#define EVAL_WITHOUT_FUNCTION 1
#define FUNCTION_NOT_DEFINED 2
#define EVAL_OF_EMPTY_LIST 3
#define SUCCESS 0

void welcome_message() {
    printf("Hello to scheme interpreter\n");
    printf("Copyright Bakur Tsutskhashvili\n");
}

int eval(const list_t* ls, elem_t* ans) {
    if (ls == NULL) return EVAL_OF_EMPTY_LIST;

    elem_t first = ls->val;
    if (first.type != String) return EVAL_WITHOUT_FUNCTION;
    if (strcmp(first.val_ptr, "+") != 0) return FUNCTION_NOT_DEFINED;
    if (ls->next == NULL) return EVAL_OF_EMPTY_LIST;

    list_t* cur_list = ls->next;
    list_t argument_list;
    list_t* cur_argumet;
    list_init(&argument_list);
    cur_argumet = &argument_list;
    while (1) {
        if (cur_list == NULL) break;
        switch (cur_list->val.type) {
            case List:
                break;
            case Float:
            case Integer:
            case String:
                
                break;
        }
    }

    return SUCCESS;

}

void error_message(int err) {
    switch (err){
        case 1:
            printf("%s\n", "syntax error");
            break;

    }
}

int check_errors(char* ln) {

}

int main(){
    welcome_message();

    char st[LINE_MAX_LEN];
    char* buf;
    while ((buf = readline(">>>> ")) != NULL) {
        if (strlen(buf) > 0) {
            
            char* token = strtok(buf, " ");
            int err = check_errors(buf);
            if (err > 0) {
                error_message(err);
            }
            add_history(buf);
        } else {
            free(buf);
            break;
        }
    }

}