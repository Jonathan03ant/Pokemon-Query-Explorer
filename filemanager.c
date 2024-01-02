#include "defs.h"

/*
    *A function to Load the CSV file into Memory
    *Returns Character Pointer (Pokemons)

*/

char* readCSV(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Unable to open the file.\n");
        return NULL;
    }

    char* pokemonData = NULL;
    size_t buffer_size = 0;
    int line_length = 0;
    size_t total_size = 0;

    /*
        *Total Number of Pokemon
    */
    while ((line_length = getline(&pokemonData, &buffer_size, file)) != -1) {
        total_size += line_length;
    }

    //*Move file pointer back to the beginning
    fseek(file, 0, SEEK_SET);

    //*Allocate memory for pokemonData
    pokemonData = (char*)malloc(total_size + 1);
    if (pokemonData == NULL) {
        printf("ERROR: Memory Allocation failed\n");
        fclose(file);
        return NULL;
    }

    //*Read the entire file into pokemonData to store the content
    ssize_t bytes_read = fread(pokemonData, 1, total_size, file);
    if (bytes_read < (ssize_t)total_size) {
        printf("Error: Reading file failed.\n");
        free(pokemonData);
        fclose(file);
        return NULL;
    }

    pokemonData[total_size] = '\0'; // Null-terminate the string
    fclose(file);
    return pokemonData;
}

/*
    *Creates a new Pokemon object
    *Creates (init) the array
    *Add Pokemons to the Array!
    *Uses helper functions
*/

PokemonArray create_pokemon_array(const char* csv_data, const char* type_to_search) {
    PokemonArray result;
    initialize_pokemon_array(&result);
    //*creating a copy
    char* csv_data_copy = strdup(csv_data); 
    char* csv_data_ptr = csv_data_copy;

    //*Skip the title (First Line),
    strtok(csv_data_ptr, "\n");

    while (true) {
        char* line = strtok(NULL, "\n");
        if (line == NULL) {
            break; 
        }

        char* num_str = parse_field(&line);
        if (*num_str == '\0') {
            break; // 
        }

        char* name = parse_field(&line);
        if (*name == '\0') {
            break; //
        }

        char* type1 = parse_field(&line);
        if (*type1 == '\0') {
            break; 
        }

        /*
            *Check if the type1 matches the search_type
            *Also Assigns the searched field to the Array
        */
        if (strcmp(type1, type_to_search) == 0) {
            Pokemon new_pokemon;

            /*
                *I know I should have probably used function to simply my prg here
                *Just overly Exhausted. 
            */
            new_pokemon.name = strdup(name);
            new_pokemon.type1 = strdup(type1);
            new_pokemon.type2 = parse_field(&line);
            new_pokemon.total = atoi(parse_field(&line));
            new_pokemon.hp = atoi(parse_field(&line));
            new_pokemon.attack = atoi(parse_field(&line));
            new_pokemon.defense = atoi(parse_field(&line));
            new_pokemon.special_attack = atoi(parse_field(&line));
            new_pokemon.special_defense = atoi(parse_field(&line));
            new_pokemon.speed = atoi(parse_field(&line));
            new_pokemon.generation = atoi(parse_field(&line));
            new_pokemon.legendary = (strcmp(parse_field(&line), "True") == 0) ? true : false;
            // Add the Pokemon to the array
            add_pokemon_to_array(&result, new_pokemon);
        }
        
    }

    free(csv_data_copy); // Free the temporary copy of the CSV data

    return result;
}



