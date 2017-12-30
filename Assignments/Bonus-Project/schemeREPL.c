
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <readline/readline.h>
#include <readline/history.h>


#define ERROR_MAX_LEN 10000
#define LINE_MAX_LEN 10000
#define END_OF_REPL "(exit)"


void welcome_message() {
    printf("Hello to scheme interpreter\n");
    printf("Copyright Bakur Tsutskhashvili\n");
}

int eval(const char* st) {
    
}

void error_message(int err) {
    switch (err){
        case 1:
            printf("%s\n", "syntax error");
            break;

    }
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