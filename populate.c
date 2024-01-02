#include "defs.h"

/*
    *Function to initialize A Dynamic Array to hold the Pokemons
*/

void initialize_pokemon_array (PokemonArray* pokemonArray){
    pokemonArray->cap = INIT;
    pokemonArray->size = 0;
    pokemonArray->data = (Pokemon*)malloc (pokemonArray->cap * sizeof (Pokemon));
    if (pokemonArray->data == NULL){
        printf("Error: Initializing the Pokemon Array\n");
        return;
    }
}

/*
    *Function to resize our Dynamic Array   
    *utility function 
*/

void resiz_array (PokemonArray* array, int new_cap){
    //*Error Checking
    if (new_cap < array->size){
        printf("Error: New Capacity is Less than the Size\n");
        return;
    }

    //*Resizing The Array and updating new capacity
    Pokemon* new_pokemon = (Pokemon*)malloc(new_cap * sizeof(Pokemon));

    for (int i = 0; i < array->size; i++){
        new_pokemon[i] = array->data[i];
    }

    //* Freeing old Pokemon Data
    free(array->data);
    array->data = new_pokemon;
    array->cap = new_cap; 
}

/*
    *Function to Add a Pokemon to a Dynamic Array
    *This function use the resize function and it will take care of the resizing for us when growing/shrinking the array
*/

void add_pokemon_to_array (PokemonArray* array, Pokemon pokemon){
    if (array->size >= array->cap){
        int new_cap = array->cap * 2; //*this doubles the current capacity
        resiz_array(array, new_cap);
    }

    //*Adding Pokemon to Array
    array->data[array->size++] = pokemon;
}

