#include "defs.h"
/*
    *Helper function1
    *pharases a given ptr (which is a pointer to pokemon Datas)
*/

char* parse_field(char** ptr) {
    char* start = *ptr;
    char* end = strchr(*ptr, ',');
    if (end) {
        *end = '\0';
        *ptr = end + 1;
    } else {
        // The field is empty or reached the end of the line
        *ptr = start + strlen(start); // Move the pointer to the end of the line
    }
    return start;
}

/* 
    *Helper function2
    *to clear the input buffer
*/ 

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

/*
    *Thread Search function
    *Sync with Mutext and Arguments
*/

void* search_pokemon_threaded(void* args) {
    char** arguments = (char**)args;
    char* csv_data = arguments[0];
    char* type_to_search = arguments[1];
    PokemonArray* array = (PokemonArray*)arguments[2];

    //* To cross check active threads
    int* active_search_threads = (int*)arguments[3];
    pthread_mutex_t* mutex = (pthread_mutex_t*)arguments[4];

    //* Lockinh, appending, unloacking search threads
    pthread_mutex_lock(mutex);
    (*active_search_threads)++;
    pthread_mutex_unlock(mutex);

    //*Temp Array
    PokemonArray temp_array = create_pokemon_array(csv_data, type_to_search);

    //*Acquire the mutex before accessing the main array
    pthread_mutex_lock(mutex);

    //*Update the main array by appending the new search results
    int total_size = array->size + temp_array.size;
    array->data = realloc(array->data, total_size * sizeof(Pokemon));
    memcpy(array->data + array->size, temp_array.data, temp_array.size * sizeof(Pokemon));
    array->size = total_size;

    //* Unloacking so it can be accessed later
    pthread_mutex_unlock(mutex);

    //* Freeing the Temporary Array ptr
    free(temp_array.data);

    //*Exiting
    pthread_exit(NULL);
}

/*
    *Thread Save Function
    *Sync with mutex and arguments
*/

void* save_results_threaded(void* args) {
    void** arguments = (void**)args;
    char* filename = (char*)arguments[0];
    PokemonArray* array = (PokemonArray*)arguments[1];
    pthread_mutex_t* mutex = (pthread_mutex_t*)arguments[2];

    //* we only need to work with mutex here!
    pthread_mutex_lock(mutex);

    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Unable to create the new file. Please enter the name of the file again.\n");
        pthread_mutex_unlock(mutex);
        return NULL;
    }

    //* Assigning Datas Correctly

    for (int i = 0; i < array->size; i++) {
    fprintf(file, "%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%s\n",
        array->data[i].name,array->data[i].type1,array->data[i].type2,
        array->data[i].total,array->data[i].hp,array->data[i].attack,
        array->data[i].defense,array->data[i].special_attack,array->data[i].special_defense,
        array->data[i].speed,array->data[i].generation,array->data[i].legendary ? "True" : "False");
}

    fclose(file);
    printf("Results saved to %s\n", filename);

    //*Unlocking for next Operation.
    pthread_mutex_unlock(mutex);
    return NULL;
}


/*
    *This function performs searching/performing the results!
    *another helper fucntion
*/

PokemonArray search_pokemon (const char* csv_data, const char* type_to_search, PokemonArray* array){
   
    *array = create_pokemon_array(csv_data, type_to_search);

    //* return the Updated Array
    return *array;
}

/*
    * Print Function for Debugging purpose
    * Not reqquired!
*/

void print_pokemon_array(const PokemonArray* array) {
    for (int i = 0; i < array->size; i++) {
        printf("Name: %s, Type 1: %s, Type 2: %s, HP: %d\n, Defense: %d\n, Speed: %d, Generation: %d, Legendary: %s\n",
            array->data[i].name,
            array->data[i].type1,
            array->data[i].type2,
            array->data[i].hp,
            array->data[i].defense, 
            array->data[i].speed,
            array->data[i].generation,
            array->data[i].legendary ? "True" : "False");
    }
}

/*
    *Display Menu Function.
*/

void display_menu (){
    printf("\nMenu Options:\n");
    printf("a. Type search\n");
    sleep(1);
    printf("b. Save results\n");
    sleep(1);
    printf("c. Exit the program\n");
    sleep(1);
    printf("Enter your choice: ");
}