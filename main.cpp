#include "Functions.h"


int main()
{
    short nr{}; //Nu este unsigned, fiindca daca va fi introdus un numar negativ in consola obtinem underflow
    short optiune{};
    unsigned short index_i{}, index_j{}; //Vor pastra locatia comorii
    bool nr_nepotrivit = false;

    std::vector<std::vector<int>> bombe_index; //Pastreaza locatiile bombelor
    std::vector<std::vector<int>> matrice; //Declaram o matrice nr x nr

    std::string optiuni_intrare{ R"(
			1.Incepe jocul 
			2.Iesire 
	)" };

    std::string optiuni_rulare{ R"(
		1   Ghiceste coordonatele comorii (rand si coloana)
		2   Activare vederea ROENTGEN pentru a vedea locatia comorii? 
		3   Incepi o joaca noua? 
		4   Iesire din joc
    )" };


    std::cout << std::endl;
    std::cout << YELLOW << "\t\t\t***********CAUTAREA COMORII***********" << RESET << std::endl;
    std::cout << "\n\tOptiuni (inscrie numarul din dreptul optiunii necesare): " << std::endl;
    std::cout << optiuni_intrare << std::endl;
    std::cout << "\tOptiunea introdusa: ";

    optiune = verificare_stream_1_input(); //Verificam daca este valida informatia introdusa in consola pentru tipul short


    if (optiune != 1 && optiune != 2) {
        std::cerr << RED << "\tOptiune incorecta!" << std::endl;
        std::cerr << "\tIn mod implicit este aplicata optiunea 1." << RESET << std::endl;
        optiune = 1;
    }



    switch (optiune)
    {
    case 1:
    {
        std::cout << std::endl << "\tIntrodu marimea hartii (nr linii): ";
        nr = verificare_stream_1_input();

        if (nr < 2 || nr > 300) {
            nr = 5;
            nr_nepotrivit = true;
        }



        generarea_hartii(nr, matrice, index_i, index_j, bombe_index);
        afisare_matrice(matrice, nr);


        if (nr_nepotrivit) {
            std::cout << RED;
            std::cerr << "\tNumar nepotrivit!!!" << std::endl; 
            std::cerr << "\tIn mod implict este aplicat nr = 5." << std::endl;
            std::cout << RESET;
            nr_nepotrivit = false;
        }


        bool sfarsit_joaca = false;
        bool comoara_gasita = false;
        bool bomba_activata = false;

        while (!sfarsit_joaca)
        {
            if (!comoara_gasita && !bomba_activata)
            {
                std::cout << std::endl << "\tOptiuni (inscrie numarul din dreptul optiunii necesare): " << std::endl;
                std::cout << optiuni_rulare << std::endl;
                std::cout << "\tOptiunea introdusa: ";

                optiune = verificare_stream_1_input();

                if (optiune < 1 || optiune > 4) {
                    std::cerr << RED << "\tOptiune incorecta!" << std::endl;
                    continue;
                }
            }
            else
            {
                std::cout << std::endl << "\t1.Incepi o joaca noua?" << std::endl;
                std::cout << "\t2.Iesire din joaca" << std::endl;
                std::cout << "\tOptiune: ";

                optiune = verificare_stream_1_input();

                if (optiune != 1 && optiune != 2) {
                    std::cerr << RED << "\tOptiune incorecta!" << std::endl;
                    continue;
                }
                else if (optiune == 1)
                {
                    optiune = 3;
                    comoara_gasita = false;
                }
                else
                {
                    optiune = 4;
                }
            }


            switch (optiune)
            {
            case 1:
            {
                std::cout << std::endl << "\tIntrodu indicii casutei: ";

                unsigned short index_i_input{}, index_j_input{};

                verificare_stream_2_input(index_i_input, index_j_input);

                //Verificam daca indicii introdusi nu depasesc limitele matricei
                if (index_i_input > nr - 1 || index_j_input > nr - 1)
                {
                    afisare_matrice(matrice, nr);
                    std::cout << RED << "\tIncearca indici mai mici!" << RESET << std::endl;
                    break;
                }

                //Verificam daca indicii introdusi sunt identici cu cei setati pentru comoara
                if (index_i_input == index_i && index_j_input == index_j)
                {
                    matrice[index_i][index_j] = 1;
                    afisare_matrice(matrice, nr);
                    comoara_gasita = true;

                    std::cout << YELLOW << "\tFelicitari, ai gasit comoara!!!" << RESET << std::endl;


                }
                else if (matrice[index_i_input][index_j_input] == 2)
                {
                    afisare_matrice(matrice, nr);

                    std::cout << RED << "\tAici ai cautat deja si nimic nu ai gasi!" << RESET << std::endl;
                }
                else if (compararea_perechi_indici(bombe_index, index_i_input, index_j_input)) //Verificam daca nu am gasit o bomba
                {
                    matrice[index_i_input][index_j_input] = 3;
                    afisare_matrice(matrice, nr);

                    std::cout << RED << "\tAi calcat pe o bomba si ai explodat :(" << std::endl;
                    std::cout << "\tIncearca o joaca noua!" << RESET << std::endl;
                    bomba_activata = true;
                }
                else
                {
                    matrice[index_i_input][index_j_input] = 2; //Insemnam casuta verificata
                    afisare_matrice(matrice, nr);

                    std::cout << RED << "\tSe pare ca aici nu este nimic :( Incearca alta casuta!" << RESET << std::endl;
                }

            }break;

            case 2:
            {
                matrice[index_i][index_j] = 1;

                for (size_t i{}; i < bombe_index.size(); i++)
                {
                    matrice[bombe_index[i][0]][bombe_index[i][1]] = 3;
                }

                afisare_matrice(matrice, nr);
                std::cout << YELLOW << "\tAi activat vederea ROENTGEN si pot vedea direct locatia comorii." << std::endl;
                std::cout << "\tPoti introduce indicii comorii pentru a o obtine sau poti incepe o joaca noua." << std::endl;
                std::cout << RESET;


            }break;

            case 3:
            {
                std::cout << std::endl << "\tIntrodu marimea hartii (nr linii): ";
                nr = verificare_stream_1_input();

                if (nr < 2 || nr > 300) {
                    nr = 5;
                    nr_nepotrivit = true;
                }

                comoara_gasita = false;
                bomba_activata = false;

                generarea_hartii(nr, matrice, index_i, index_j, bombe_index);
                afisare_matrice(matrice, nr);

                if (nr_nepotrivit) {
                    std::cout << RED;
                    std::cerr << "\tNumar nepotrivit!!!" << std::endl;
                    std::cerr << "\tIn mod implict este aplicat nr = 5." << std::endl;
                    std::cout << RESET;
                    nr_nepotrivit = false;
                }

            }break;

            case 4:
            {
                sfarsit_joaca = true;
            }break;

            default:
            {
                afisare_matrice(matrice, nr);
                std::cout << RED;
                std::cout << "\tOptiune incorecta, incercati din nou!" << std::endl;
                std::cout << RESET;
            }
            }
        }

    }break;

    case 2:
        std::cout << CYAN << "\tO zi frumoasa in continuare!" << RESET << std::endl;
        return 0;
    }

    std::cout << CYAN << "\tO zi frumoasa in continuare!" << RESET << std::endl;

    return 0;
}























//Bucati din care este construit tabloul final:
// 
//std::string bucata_0{ R"(       1     2     3     4     5 )" };
//std::string bucata_1{ R"(    ┌─────┬─────┬─────┬─────┬─────┐)" };
//std::string bucata_2{ R"(    ├─────┼─────┼─────┼─────┼─────┤)" };
//std::string bucata_3{ R"(    └─────┴─────┴─────┴─────┴─────┘)" };

  //     1     2     3     4     5 
  //  ┌─────┬─────┬─────┬─────┬─────┐
  //1 │  X  │  X  │  X  │  X  │  X  │
  //  ├─────┼─────┼─────┼─────┼─────┤
  //2 │     │     │     │     │     │
  //  ├─────┼─────┼─────┼─────┼─────┤
  //3 │     │     │     │     │     │
  //  ├─────┼─────┼─────┼─────┼─────┤
  //4 │     │     │     │     │     │
  //  ├─────┼─────┼─────┼─────┼─────┤
  //5 │     │     │     │     │     │
  //  └─────┴─────┴─────┴─────┴─────┘



