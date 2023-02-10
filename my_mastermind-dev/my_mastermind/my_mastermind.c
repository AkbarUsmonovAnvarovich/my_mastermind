#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int my_strlen(char* str) {
    int count = 0;
    for (int i = 0; str[i]; i++) {
        count++;
    }
    return count;
}
int my_strchar(char* str , char c){
    for (int i = 0; str[i]; i++) {
        if (str[i] == c) {
            return 0;
        }
    }
    return 1;
}

void print_text_of_game(int param_1) {
    if (param_1 == 0) {
        printf("---\n");
    }
    else if (param_1 == 1) {
        write(1, ">", 1);
        fflush(stdin);
    }

}
char* prompt_input(){
    print_text_of_game(1);
    char temp;
    char newline = '\n';
    char* input = (char*)malloc(sizeof(char) *10);
    int i = 0;
    while (read(0, &temp, 1)) {
        if (temp == newline) {
            return input;
        }
        input[i] = temp;
        i++;
    }
    return "emp_file";
}

int check_letter(char* param_1){
    for (int i = 0; param_1[i]; i++) {
        if (!(param_1[i] > 47 && param_1[i] < 57)) {
            return 1;
        }
    }
    return 0;
}

int bubble_cmp_str(char* str){
    for (int i = 0; i < (my_strlen(str) - 1); i++) {
        for (int in = i + 1; in < my_strlen(str); in++) {
            if (str[i] == str[in]) {
                return 1;
            }
        }
    }
    return 0;
}

int miss_or_in(char* u_input , char* gen_code) {
    int well = 0 , miss = 0;
    for (int i = 0; gen_code[i]; i++) {
        for (int in = 0; u_input[in]; in++) {
            if (gen_code[i] == u_input[in] && i == in) {
                well++;
            }
            else if (gen_code[i] == u_input[in] && i != in) {
                miss++;
            }
        }
    }
    if (well == 4) {
        printf("Congratz! You did it!\n");
        return 1;
    }
    printf("Well placed pieces: %d\nMisplaced pieces: %d\n", well , miss);
    return 0;
}

int check_for_wrong_input(char* u_input , char* gen_code){
    if (my_strlen(u_input) != 4 || check_letter(u_input) || bubble_cmp_str(u_input)) {
        printf("Wrong input!\n");
        return 0;
    }
    if (miss_or_in(u_input, gen_code) == 1) return 5;
    return 1;
}


void game_cmp_main(char* gen_code, int chances) {
    printf("Will you find the secret code?\nPlease enter a valid guess\n");
    int i = 0, temp = 0, result;
    char* input;
    while (i < chances) {
        if (temp == 0){
            print_text_of_game(0); 
            printf("Round %d\n", i);
        }
        input = prompt_input();
        if (strcmp(input, "emp_file") == 0) return;
        if ((result = check_for_wrong_input(input , gen_code)) == 1) {
            i++;
            temp = 0;
        }
        else if (result == 5) return;
        else temp = 1;
    }
}

char* generate_random_code(int length) {
    char* x = (char*)malloc(sizeof(char) *4);
    if (length == 1) {
        time_t code;

        srand(time(&code));
        int i = 0;
        while (my_strlen(x) != 4) {
            char temp = rand() % 9 + '0';
            if (my_strchar(x , temp)) {
                x[i] = temp;
                i++;
            }    
        }
    }    
    return x;       
}

void seperate_options(int ac ,char** av) {
    char* secret_pincode = generate_random_code(ac);
    int rounds_value = 10;
    if (ac > 1) {
        for (int i = 1; i < ac; i++) {
            if (!(strcmp(av[i], "-c"))) {
            secret_pincode = av[i += 1]; 
            }
            else if (!(strcmp(av[i], "-t"))) {
                rounds_value = atoi(av[i += 1]);
            }
        }
    }
    game_cmp_main(secret_pincode, rounds_value);
}

int main(int ac, char** av) {
    seperate_options(ac, av);
    return 0;
}