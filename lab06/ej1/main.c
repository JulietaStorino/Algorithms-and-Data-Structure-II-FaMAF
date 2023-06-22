/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

static void opciones(abb tree){
    unsigned int operation = 0u;
    
    while (operation != 7) {
        printf("Choose one of the following options:\n 1 ........ Show tree on screen \n");
        printf(" 2 ........ Add an item \n 3 ........ Delete an item \n");
        printf(" 4 ........ Check element existence \n 5 ........ Show tree length \n");
        printf(" 6 ........ Show root, maximum and minimum of the tree \n 7 ........ Exit\n\n");
        
        scanf("%u", &operation);

        if(operation == 1) {
            abb_dump(tree);
            if(abb_is_empty(tree)){
                printf("Empty tree.");
            }
        } else if(operation == 2) {
            abb_elem e;
            printf("Enter the item to add:\n");
            scanf("%d", &e);
            tree = abb_add(tree, e);
        } else if(operation == 3) {
            abb_elem e;
            printf("Enter the item to delete:\n");
            scanf("%d", &e);
            tree = abb_remove(tree, e);
        } else if(operation == 4) {
            abb_elem e;
            printf("Enter the item to find:\n");
            scanf("%d", &e);
            bool exists = abb_exists(tree, e);
            printf("The item %s.\n", exists?"exists":"does not exist");
        } else if(operation == 5) {
            printf("Length: %u\n", abb_length(tree));
        } else if(operation == 6) {
            printf("Root: %d\n minimum: %d\n maximum: %d", abb_root(tree), abb_min(tree), abb_max(tree));
        } else if(operation == 7) {
            tree = abb_destroy(tree);
        }

        printf("\n\n");
        
    }
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /* show the options and execute them */
    opciones(tree);
    
    return (EXIT_SUCCESS);
}
