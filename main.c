#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h> 
#include "defs.h"

int main() {
    char* csv_data = NULL;
    // *Initializing The Array
    PokemonArray array;
    initialize_pokemon_array(&array);

    // Prompt the user to enter the name of the file containing the Pokemon descriptions
    char filename[INIT];
    printf("Enter the name of the file containing the Pokemon descriptions:\n");
    scanf("%s", filename);

    // Try to read the CSV file
    csv_data = readCSV(filename);
    while (csv_data == NULL) {
        // If the file is not found, prompt the user to enter the name again or exit the program
        printf("\nPokemon file is not found\n\n");
        printf("Please enter the name of the file again");
        sleep(1);
        printf("or type 'exit' to exit the program.\n");
        scanf("%s", filename);
        if (strcmp(filename, "exit") == 0) {
            printf("Exiting The Prg...");
            return 1; // Exit the program
        }
        csv_data = readCSV(filename);
    }

    // * Mutex For Synchronization
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    
    char option;
    int active_search_threads = 0;
    while (true) {
        display_menu();
        scanf(" %c", &option);
        clear_input_buffer();

        switch (option) {

            case 'a': 

                printf("Please enter the Type1 property to search: ");
                char type_to_search[INIT];
                scanf("%s", type_to_search);
                clear_input_buffer();

                char* args[5] = { csv_data, strdup(type_to_search), (char*)&array,
                (char*)&active_search_threads, (char*)&mutex };
                pthread_t search_thread;
                pthread_create(&search_thread, NULL, search_pokemon_threaded, (void*)args);

                break;
            
            case 'b':
            // Save the results
                printf("Please enter the name of the file to save the results: ");
                char save_filename[INIT];
                scanf("%s", save_filename);
                clear_input_buffer();

                void* save_args[3] = { save_filename, (void*)&array, (void*)&mutex };
                pthread_t save_thread;
                pthread_create(&save_thread, NULL, save_results_threaded, (void*)save_args);
                pthread_detach(save_thread); // Detach the saving thread to let it run in the background

                break;


            case 'c':
                // Exit the program
                printf("Exiting the program...\n");
                sleep(1);
                printf("Number of Pokemon found: %d\n", array.size);
                sleep(1);
                printf("GOOD BYE!\n");
                free(csv_data);
                free(array.data);
                exit(0);

            default:
                printf("Invalid option. Please try again.\n");
                sleep(1);
                break;
        }
    }

    //*Free 
    free(csv_data);

    // Don't forget to free the CSV data as well
    pthread_mutex_destroy(&mutex);
    return 0;
}
