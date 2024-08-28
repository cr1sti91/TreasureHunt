#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>
#include <random>
#include <vector>

const char linie_v = 186; //linie verticala (codul ASCII)
const char bomba = 'B';

const std::string deplasare = "\t\t\t\t";


//Constante de preprocesor - Cod de control ANSI pentru modificarea culorilor in terminal
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define CYAN    "\033[36m"


//Functii
void afisare_matrice(const std::vector<std::vector<int>>& matrice, const short& nr);

short verificare_stream_1_input(); //Verifica daca informatia introdusa in consola este valida pentru tipul de date short
void verificare_stream_2_input(unsigned short& index_i, unsigned short& index_j); //La fel ca precedenta, insa pentru doua variabile


void generarea_hartii(const short& nr, std::vector<std::vector<int>>& matrice, unsigned short& index_i,
    unsigned short& index_j, std::vector<std::vector<int>>& bombe_index);

//Verifica daca avem perechi de indici identici - {a, b} este comparat cu index_bombe.at(index)
bool compararea_perechi_indici(const std::vector<std::vector<int>>& index_bombe, int a, int b);

#endif //FUNCTIONS_H