#include <stdio.h>
#include <string.h>

#define LOOP_LIMIT 1024
#define FLAG_DESCRIPTIONS_LENGTH 12
#define PADDED_BUFFER_SIZE 24

char *flagDescriptions[FLAG_DESCRIPTIONS_LENGTH][3] = {
        {"-A", "--show-all", "equivalent to -vET"},
        {"-b," "--number-nonblank", "number nonempty output lines, overrides -n"},
        {"-e", NULL, "equivalent to -vE"},
        {"-E", "--show-ends", "display $ at end of each line"},
        {"-n", "--number", "number all output lines"},
        {"-s", "--squeeze-blank", "suppress repeated empty output lines"},
        {"-t", NULL, "equivalent to -vT"},
        {"-T", "--show-tabs", "display TAB characters as ^I"},
        {"-u", NULL, "(ignored)"},
        {"-v", "--show-nonprinting", "use ^ and M- notation, except for LFD and TAB"},
        {NULL, "--help"     ,"display this help and exit"},
        {NULL, "--version",  "output version information and exit"}
};

const char usageString[] = "Usage: /usr/bin/cat [OPTION]... [FILE]...";
const char descriptionString[] = "Concatenate FILE(s) to standard input";
const char fallbackDescription[] = "With no FILE, or when FILE is -, read standard input.";

void show_flag_descriptions(void){
    char buffer[PADDED_BUFFER_SIZE] = "";
    buffer[PADDED_BUFFER_SIZE-1] = '\0';
//    int buffer_fill = 1;
    for(size_t i = 0; i < FLAG_DESCRIPTIONS_LENGTH; i++){
        if(flagDescriptions[i][0] != NULL){
            printf_s("  %s", flagDescriptions[i]);
        }
        if(flagDescriptions[i][1] != NULL){
            strncpy(buffer, ", ", 3);
            strncpy(buffer+2, flagDescriptions[i][1],sizeof(buffer)/sizeof(buffer[0]) - 2);
        }
        size_t bufferLength = strnlen_s(buffer, PADDED_BUFFER_SIZE);
        for (; bufferLength < PADDED_BUFFER_SIZE; bufferLength++) {
            buffer[bufferLength] = ' ';
        }
        printf_s("%s%s\n", buffer, flagDescriptions[i][2]);
    }
}

int show_help(){
    int out = 0;
    out += printf_s("%s\n", usageString);
    out += printf_s("%s\n", descriptionString);
    out += printf_s("\n");
    out += printf_s("%s\n", fallbackDescription);
    printf_s("\n");
    show_flag_descriptions();
    return out;
}

void print_file_content(FILE *file, char *buffer, size_t bufferSize){
    if(file == NULL) {
        return;
    }
    for(int i = 0; i < LOOP_LIMIT && fgets(buffer, (int)bufferSize, file) != NULL; i++){
        printf_s("%s", buffer);
        if(feof(file)){
            return;
        }
    }
}

int main(int argc, char *argv[]){
//    printf("Kek");
    if(argc == 1){
        show_help();
        return 0;
    }
//    errno_t err = 0;
    FILE *file = NULL;
    char buffer[512];
    buffer[511] = '\0';
    for (int i = 0; i < argc-1; ++i) {
//        err =
        fopen_s(&file, argv[i+1], "r");
        print_file_content(file, buffer, sizeof(buffer)/sizeof(buffer[0]));
    }
    return 0;
}
