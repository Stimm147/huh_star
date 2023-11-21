#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int const wym2 = 6;
int const wym1 = 6;

struct wektor {
    double identifier;
    int koszt_ruchu;
};

wektor odwiedzone[wym1 * wym2];
wektor nie_odwiedzone[wym1 * wym2];



void A_star(wektor G[][6],int start_x,int start_y,int cel_x,int cel_y) {
    int x = start_x;
    int y = start_y;
    while ((start_x != cel_x) || (start_y != cel_y)) {
        int point = 1;
        for(int i = 1; i < 5; i++){
            //if (i == 1) {
            //    if (sprawdz_czy_git(start_x, start_y,G[][6]) {

            //    }
            //}

        
            
        }
    }
}

bool sprawdz_czy_git(int x, int y, wektor node) {
    if (x - 1 < 0 || x + 1 > 5 || y - 1 < 0 || y + 1 > 5 || node.identifier == 5)
        return false;
    return true;
}

double heurystyka(int x, int y, int cel_x, int cel_y) {
    return sqrt(pow((x - cel_x), 2) + pow((y - cel_y), 2));
}

void wypisz(wektor G[][6]) {
    cout << "\nWypisujemy na ekran\n\n";
    for (int i = 0; i < wym2; i++)
    {
        for (int j = 0; j < wym1; j++)
        {
            cout << " " << G[i][j].identifier;
        }cout << "\n";
    }
}



int main(void) {



    cout << "Wczytywanie danych z pliku\n";

    string nazwap = "grid.txt";

    double G[6][6];
    wektor grid_ale_lepszy[6][6];

    std::ifstream plik(nazwap.c_str());

    for (unsigned int i = 0; i < wym2; i++)
    {
        for (unsigned int j = 0; j < wym1; j++)
        {
            plik >> grid_ale_lepszy[i][j].identifier;
        }
    }
    plik.close();

    wypisz(grid_ale_lepszy);

    int start_x = 2;
    int start_y = 1;

    int cel_x = 1;
    int cel_y = 5;

    //cout<<heurystyka(2, 0, 1, 5);



    return 0;
}

