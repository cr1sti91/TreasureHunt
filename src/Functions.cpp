#include "Functions.h"

//Am utilizata referinte pentru a evita copiile inutile
void afisare_rand_cu_cifre(const short line, const std::vector<std::vector<int>> matrice, const short& nr)
{
    if (line < 10 && line >= 0) {
        std::cout << deplasare << "   " << CYAN << line << " ";
    }
    else if (line > 9) {
        std::cout << deplasare << "  " << CYAN << line << " ";
    }

    for (size_t i{}; i < nr; i++)
    {
        std::cout << GREEN << linie_v << "  " << YELLOW;
        if (matrice[line][i] == 0)
        {
            std::cout << "   ";
        }
        else if (matrice[line][i] == 2)
        {
            std::cout << RED << "X  " << RESET;
        }
        else if (matrice[line][i] == 3)
        {
            std::cout << RED << bomba << "  " << RESET;
        }
        else
        {
            std::cout << "!  ";
        }
    }
    std::cout << GREEN << linie_v << std::endl;;
}

void afisare_matrice(const std::vector<std::vector<int>>& matrice, const short& nr)
{
    system("CLS"); //Inainte de fiecare afisare curatim consola


    //----------------------------Setam bucata_0-------------------------------
    //"       1     2     3     4     5 " - bucata_0 pentru nr = 5

    std::string bucata_0{ "   " };
    for (size_t i{}; i < nr; i++)
    {
        if (i < 10) {
            bucata_0 += "     ";
            bucata_0 += std::to_string(i);
        }
        else {
            bucata_0 += "    ";
            bucata_0 += std::to_string(i);
        }
    }




    //Setam linia centrala
    std::string centru{ "" };
    centru.append(5, static_cast<char>(205));

    //----------------------------Setam bucata_1-------------------------------
    //"    ┌─────┬─────┬─────┬─────┬─────┐" - bucata_1 pentru nr = 5

    std::string bucata_1{ "     " };
    bucata_1 += static_cast<char>(201);

    for (size_t i{}; i < nr - 1; i++)
    {
        bucata_1 += (centru + static_cast<char>(203));
    }
    bucata_1 += (centru + static_cast<char>(187));

    //----------------------------Setam bucata_2-------------------------------
    //"    ├─────┼─────┼─────┼─────┼─────┤" - bucata_2 pentru nr = 5

    std::string bucata_2{ "     " };
    bucata_2 += static_cast<char>(186);
    for (size_t i{}; i < nr - 1; i++)
    {
        bucata_2 += (centru + static_cast<char>(206));
    }
    bucata_2 += (centru + static_cast<char>(185));

    //----------------------------Setam bucata_3-------------------------------
    //"    └─────┴─────┴─────┴─────┴─────┘" - bucata_3 pentru nr = 5

    std::string bucata_3{ "     " };
    bucata_3 += static_cast<char>(200);
    for (size_t i{}; i < nr - 1; i++)
    {
        bucata_3 += (centru + static_cast<char>(202));
    }
    bucata_3 += (centru + static_cast<char>(188));


    //_________________________Afisarea matricei______________________________
    std::cout << CYAN << deplasare << bucata_0 << RESET << std::endl;
    std::cout << GREEN << deplasare << bucata_1 << RESET << std::endl;
    for (size_t i{}; i < nr - 1; i++)
    {
        afisare_rand_cu_cifre(i, matrice, nr);
        std::cout << deplasare << GREEN << bucata_2 << RESET << std::endl;
    }
    afisare_rand_cu_cifre(nr - 1, matrice, nr);
    std::cout << deplasare << GREEN << bucata_3 << RESET << std::endl;
}


short verificare_stream_1_input()
{
    short optiune{};

    while (!(std::cin >> optiune))
    {
        //Daca sunt introduse alte caracter care nu se potrivesc pentru variabilele de intrare, fluxul cin 
        //cade in stare de eroare.
        std::cin.clear(); //Curata starea de eroare
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Toate caracterele din buffer sunt sterse pana la ultimul newline
        //ultimul newline
        std::cout << RED << "\tAi introdus caractere gresite! Incerca din nou: " << RESET;
    }

    return optiune;
}



void verificare_stream_2_input(unsigned short& index_i, unsigned short& index_j)
{
    while (!(std::cin >> index_i >> index_j))
    {
        //Daca sunt introduse alte caracter care nu se potrivesc pentru variabilele de intrare, fluxul cin 
        //cade in stare de eroare.
        std::cin.clear(); //Curata starea de eroare
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Toate caracterele din buffer sunt sterse pana la ultimul newline
        //ultimul newline
        std::cout << RED << "\tAi introdus caractere gresite! Incerca din nou: " << RESET;
    }
}


bool compararea_perechi_indici(const std::vector<std::vector<int>>& index_bombe, int a, int b) {

    for (size_t i{}; i < index_bombe.size(); i++) {
        if (index_bombe[i][0] == a && index_bombe[i][1] == b) {
            return true;
        }
    }
    return false;
}


void generarea_hartii(const short& nr, std::vector<std::vector<int>>& matrice, unsigned short& index_i,
    unsigned short& index_j, std::vector<std::vector<int>>& bombe_index)
{
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, nr - 1);
    index_i = dist(rd);
    index_j = dist(rd);

    std::vector<std::vector<int>> nrxnr(nr, std::vector<int>(nr)); //Toate elementele sunt initializate cu 0
    matrice = nrxnr; //Setam matrice sa fie de marimea nr x nr

    bombe_index.clear();


    //Setam nr bombe :D
    int limita = nr; //Putem avea nevoia de a mari limita
    for (size_t i{}; i < limita; i++)
    {
        int a = dist(rd);
        int b = dist(rd);

        if (a != index_i || b != index_j) //Cel putin unul din indicii a sau b trebuie sa fie diferit de index_i sau index_j
        {
            if (!compararea_perechi_indici(bombe_index, a, b))
            {
                bombe_index.push_back({ a, b });
            }
            else
            {
                limita++;
            }
        }
        else
        {
            limita++;
        }
    }
}

