#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h> 
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define INIT 50

typedef struct Pokemon {
    char *name;
    char *type1;
    char *type2;
    int total;
    int hp;
    int attack;
    int defense;
    int special_attack;
    int special_defense;
    int speed;
    int generation;
    bool legendary;
} Pokemon;

typedef struct PokemonArray {
    Pokemon *data;
    int cap;
    int size;
} PokemonArray;


char* readCSV(const char* );
PokemonArray create_pokemon_array(const char* pokemonData, const char* search_type);

void initialize_pokemon_array (PokemonArray*);
void add_pokemon_to_array(PokemonArray*, Pokemon);
void resize_array(PokemonArray*, int);


char* parse_field(char**);
PokemonArray search_pokemon (const char*, const char*, PokemonArray*);


void* search_pokemon_threaded (void*);
void* save_results_threaded(void* args);




void print_pokemon_array(const PokemonArray*);
void display_menu ();
void clear_input_buffer();

