#include <stdio.h>
#include <string.h>

#define LOOP_LIMIT 1024
#define FLAG_DESCRIPTIONS_LENGTH 12
#define PADDED_BUFFER_SIZE 24

#define CAT_PATH "/usr/bin/cat"

typedef struct Description{
    char *firstColumn;
    char *secondColumn;
    char description[128];
} Description;

const Description FLAG_DESCRIPTIONS[] = {
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
        {NULL, "--help", "display this help and exit"},
        {NULL, "--version",  "output version information and exit"}
};


const Description EXAMPLES_DESCRIPTIONS[] = {
        {CAT_PATH, "f - g", "Output f's contents, then standard input, then g's contents."},
	{CAT_PATH, NULL, "Copy standard input to standard output."}
};

const char USAGE_DESCRIPTION[] = "Usage: /usr/bin/cat [OPTION]... [FILE]...";
const char PROGRAM_DESCRIPTION[] = "Concatenate FILE(s) to standard input";
const char FALLBACK_DESCRIPTIONS[] = "With no FILE, or when FILE is -, read standard input.";

void show_flag_descriptions(const Description flagDescriptions[]){
    char buffer[PADDED_BUFFER_SIZE] = "";
    buffer[PADDED_BUFFER_SIZE-1] = '\0';
//    int buffer_fill = 1;
    for(size_t i = 0; i < FLAG_DESCRIPTIONS_LENGTH; i++){
        if(flagDescriptions[i].firstColumn != NULL){
            printf_s("  %s", flagDescriptions[i]);
        }
        if(flagDescriptions[i].secondColumn != NULL){
            strncpy(buffer, ", ", 3);
            strncpy(buffer+2, flagDescriptions[i].secondColumn, sizeof(buffer) / sizeof(buffer[0]) - 2);
        }
        size_t bufferLength = strnlen_s(buffer, PADDED_BUFFER_SIZE);
        for (; bufferLength < PADDED_BUFFER_SIZE; bufferLength++) {
            buffer[bufferLength] = ' ';
        }
        printf_s("%s%s\n", buffer, flagDescriptions[i].description);
    }
}

void show_help(
        const char * const usageDescription,
        const char * const programDescription,
        const char * const fallbackDescription,
        const Description flagDescriptions[]
        )
{
    printf_s("%s\n", usageDescription);
    printf_s("%s\n", programDescription);
    printf_s("\n");
    printf_s("%s\n", fallbackDescription);
    printf_s("\n");
    show_flag_descriptions(flagDescriptions);
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
        show_help(
                USAGE_DESCRIPTION,
                PROGRAM_DESCRIPTION,
                FALLBACK_DESCRIPTIONS,
                FLAG_DESCRIPTIONS);
        return 0;
    }
    FILE *file = NULL;
    char buffer[512];
    buffer[511] = '\0';
    for (int i = 0; i < argc-1; ++i) {
        if(strncmp(argv[i+1], "-", 2) == 0){
            file = stdin;
        }
        else{
            fopen_s(&file, argv[i+1], "r");
        }
        print_file_content(file, buffer, sizeof(buffer)/sizeof(buffer[0]));
    }
    return 0;
}
