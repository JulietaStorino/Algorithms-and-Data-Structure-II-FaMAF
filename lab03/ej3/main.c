#include <stdlib.h>
#include <stdio.h>

#define MAX_SIZE 1000

char *parse_filepath(int argc, char *argv[]) {
    char *result = NULL;

    if (argc != 2) {
        printf("Expected argument: <input file path>.\n");
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int
data_from_file(const char *path,
               unsigned int indexes[],
               char letters[],
               unsigned int max_size){

    unsigned int index, length=0;
    char letter;
    FILE *file = fopen(path, "r");
    if(file == NULL){
        printf("Invalid path: %s\n.", path);
        fclose(file);
        exit(EXIT_FAILURE);
    }
    while (!feof(file) && length < max_size){
        int errorvalue = fscanf(file, "%u -> *%c*\n", &index, &letter);
        if(errorvalue == EOF || index>=max_size){
            printf("Invalid file.\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
        indexes[length] = index;
        letters[length] = letter;
        length++;
    }
    return length;
}

static void sort(char sorted[], 
                 unsigned int indexes[],
                 char letters[],
                 unsigned int length) {
    
    for (unsigned int j=0u; j < length; j++) {
        unsigned int index = indexes[j];
        sorted[index] = letters[j];
    }
}

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

int main(int argc, char *argv[]) {
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    char *path = parse_filepath(argc, argv);
    length = data_from_file(path, indexes, letters, MAX_SIZE);

    sort(sorted, indexes, letters, length);
    dump(sorted, length);

    return EXIT_SUCCESS;
}

