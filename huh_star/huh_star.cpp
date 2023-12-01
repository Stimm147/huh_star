#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>

using namespace std;

int const wym2 = 9;
int const wym1 = 9;

struct wektor {
    int x;
    int y;
    double heuryst_value;
    double identifier;
    int koszt_ruchu;
    bool czy_obliczony_koszt = false;
};

//wektor odwiedzone[wym1 * wym2];
wektor nie_odwiedzone[wym1 * wym2];
vector<wektor> odwiedzone;
vector<wektor> do_odwiedzenia;

double zaokragl_do_dwoch_miejsc(double liczba) {
    return round(liczba * 100.0) / 100.0;
}

double heurystyka(int x, int y, int cel_x, int cel_y) {
    return zaokragl_do_dwoch_miejsc(sqrt(pow((x - cel_x), 2) + pow((y - cel_y), 2)));
}

bool czy_w_liscie(vector<wektor> lista, wektor element) {
    for (auto & uuh : lista) {
        if((uuh.x == element.x) && (uuh.y == element.y))
            return true;
    }
    return false;
}

int Oblicz_koszt_ruchu(wektor G[][wym1],wektor element) {

    vector<wektor> lista;

    for (int i = 1; i < 5; i++) {
        if ((i == 1) && G[element.x][element.y + 1].czy_obliczony_koszt == true && (element.y + 1 <= wym2 - 1) && (G[element.x][element.y + 1].identifier != 5)) { // w górę
            lista.push_back(G[element.x][element.y + 1]);
        }
        i++;
        if ((i == 2) && G[element.x + 1][element.y].czy_obliczony_koszt == true && (element.x + 1 <= wym1 - 1) && (G[element.x + 1][element.y].identifier != 5)) { // w prawo
            lista.push_back(G[element.x + 1][element.y]);
        }
        i++;
        if ((i == 3) && G[element.x][element.y - 1].czy_obliczony_koszt == true && (element.y - 1 >= 0) && (G[element.x][element.y - 1].identifier != 5)) { // w dół
            lista.push_back(G[element.x][element.y - 1]);
        }
        i++;
        if ((i == 4) && G[element.x - 1][element.y].czy_obliczony_koszt == true && (element.x - 1 >= 0) && (G[element.x - 1][element.y].identifier != 5)) { // w lewo
            lista.push_back(G[element.x - 1][element.y]);
        }
        i++;
    }

    int naj = lista[0].koszt_ruchu;

    for (auto& uuh : lista) {
        if (uuh.koszt_ruchu < naj) {
            naj = uuh.koszt_ruchu;
        }
    }
    lista.clear();
    return naj + 1;

}

void A_star(wektor G[][wym1],int x,int y,int cel_x,int cel_y) {

    int start_x = x;
    int start_y = y;

    odwiedzone.push_back(G[x][y]);

    G[x][y].koszt_ruchu = 0;
    G[x][y].czy_obliczony_koszt = true;

    while ((x != cel_x) || (y != cel_y)) {

        int point = 1; // to jest tylko wpisywanie wartosci do gridu, po tym trzeba jeszcze wybrać najmniejsza heurystyke 

        /*G[x][y].identifier = 3;*/

        for(int i = 1; i < 5; i++){ 
            if ((i == 1) && (y + 1 <= wym2 - 1) && (G[x][y + 1].identifier != 5) && czy_w_liscie(odwiedzone, G[x][y + 1]) == false) { // w górę
                if (G[x][y + 1].czy_obliczony_koszt == false) {
                    G[x][y + 1].koszt_ruchu = Oblicz_koszt_ruchu(G, G[x][y + 1]);
                    G[x][y + 1].czy_obliczony_koszt = true;
                    G[x][y + 1].heuryst_value = heurystyka(x, y + 1, cel_x, cel_y);
                    G[x][y + 1].heuryst_value = G[x][y + 1].heuryst_value + G[x][y + 1].koszt_ruchu;

                }
                do_odwiedzenia.push_back(G[x][y + 1]);
            }
            i++;
            if ((i == 2) && (x + 1 <= wym1 - 1) && (G[x + 1][y].identifier != 5) && czy_w_liscie(odwiedzone, G[x + 1][y]) == false) { // w prawo
                if (G[x + 1][y].czy_obliczony_koszt == false) {
                    G[x + 1][y].koszt_ruchu = Oblicz_koszt_ruchu(G, G[x + 1][y]);
                    G[x + 1][y].czy_obliczony_koszt = true;
                    G[x + 1][y].heuryst_value = heurystyka(x + 1, y, cel_x, cel_y);
                    G[x + 1][y].heuryst_value = G[x + 1][y].heuryst_value + G[x + 1][y].koszt_ruchu;

                }
                do_odwiedzenia.push_back(G[x + 1][y]);
            }
            i++;
            if ((i == 3) && (y - 1 >= 0) && (G[x][y - 1].identifier != 5) && czy_w_liscie(odwiedzone, G[x][y - 1]) == false) { // w dół
                if (G[x][y - 1].czy_obliczony_koszt == false) {
                    G[x][y - 1].koszt_ruchu = Oblicz_koszt_ruchu(G, G[x][y - 1]);
                    G[x][y - 1].czy_obliczony_koszt = true;
                    G[x][y - 1].heuryst_value = heurystyka(x, y - 1, cel_x, cel_y);
                    G[x][y - 1].heuryst_value = G[x][y - 1].heuryst_value + G[x][y - 1].koszt_ruchu;
                }
                do_odwiedzenia.push_back(G[x][y - 1]);
            }
            i++;
            if ((i == 4) && (x - 1 >= 0) && (G[x - 1][y].identifier != 5) && czy_w_liscie(odwiedzone, G[x - 1][y]) == false) { // w lewo
                if (G[x - 1][y].czy_obliczony_koszt == false) {
                    G[x - 1][y].koszt_ruchu = Oblicz_koszt_ruchu(G, G[x - 1][y]);
                    G[x - 1][y].czy_obliczony_koszt = true;
                    G[x - 1][y].heuryst_value = heurystyka(x - 1, y, cel_x, cel_y);
                    G[x - 1][y].heuryst_value = G[x - 1][y].heuryst_value + G[x - 1][y].koszt_ruchu;
                }
                do_odwiedzenia.push_back(G[x - 1][y]);
            }
            i++;
        }
        int pozycja = 0;
        wektor naj = do_odwiedzenia[0];
        double najnaj = naj.heuryst_value;
        for (auto & uuh : do_odwiedzenia) {
            if ((uuh.heuryst_value <= najnaj)) {
                najnaj = uuh.heuryst_value;
                naj = uuh;
            }
        }
        for (auto& uuh2 : do_odwiedzenia) {
            if (uuh2.x == naj.x && uuh2.y == naj.y) {
                break;
            }
            pozycja++;
        }
        
        x = naj.x;
        y = naj.y;

        odwiedzone.push_back(G[x][y]);
        do_odwiedzenia.erase(do_odwiedzenia.begin()+pozycja);
    }
    /*G[x][y].identifier = 3; */

    x = cel_x;
    y = cel_y;

    odwiedzone.clear();
    do_odwiedzenia.clear();

    odwiedzone.push_back(G[cel_x][cel_y]);

    while ((x != start_x) || (y != start_y)) {

        G[x][y].identifier = 3;

        for (int i = 1; i < 5; i++) {
            if ((i == 1) && (y + 1 <= wym2 - 1) && (G[x][y + 1].identifier != 5) && G[x][y + 1].czy_obliczony_koszt == true && czy_w_liscie(odwiedzone, G[x][y + 1]) == false) { // w górę
                do_odwiedzenia.push_back(G[x][y + 1]);
            }
            i++;
            if ((i == 2) && (x + 1 <= wym1 - 1) && (G[x + 1][y].identifier != 5) && G[x + 1][y].czy_obliczony_koszt == true && czy_w_liscie(odwiedzone, G[x + 1][y]) == false) { // w prawo
                do_odwiedzenia.push_back(G[x + 1][y]);
            }
            i++;
            if ((i == 3) && (y - 1 >= 0) && (G[x][y - 1].identifier != 5) && G[x][y - 1].czy_obliczony_koszt == true && czy_w_liscie(odwiedzone, G[x][y - 1]) == false) { // w dół
                do_odwiedzenia.push_back(G[x][y - 1]);
            }
            i++;
            if ((i == 4) && (x - 1 >= 0) && (G[x - 1][y].identifier != 5) && G[x - 1][y].czy_obliczony_koszt == true && czy_w_liscie(odwiedzone, G[x - 1][y]) == false) { // w lewo
                do_odwiedzenia.push_back(G[x - 1][y]);
            }
            i++;
        }

        int pozycja = 0;
        wektor naj = do_odwiedzenia[0];
        double najnaj = naj.heuryst_value;
        for (auto& uuh : do_odwiedzenia) {
            if ((uuh.heuryst_value < najnaj)) {
                najnaj = uuh.heuryst_value;
                naj = uuh;
            }
        }
        for (auto& uuh2 : do_odwiedzenia) {
            if (uuh2.x == naj.x && uuh2.y == naj.y) {
                break;
            }
            pozycja++;
        }

        x = naj.x;
        y = naj.y;

        odwiedzone.clear();

        odwiedzone.push_back(G[x][y]);

        do_odwiedzenia.erase(do_odwiedzenia.begin() + pozycja);
    }
    G[x][y].identifier = 3;
}   

void wypisz(wektor G[][wym1]) {
    cout << "\nWypisujemy na ekran\n\n";
    for (int i = 0; i < wym2; i++)
    {
        for (int j = 0; j < wym1; j++)
        {
            cout << " " << G[j][wym1 - i - 1].identifier;

        }cout << "\n";
    }
}



int main(void) {

    cout << "Wczytywanie danych z pliku\n";

    string nazwap = "grid.txt";

    double G[wym1][wym1];
    wektor grid_ale_lepszy[wym1][wym1];

    std::ifstream plik(nazwap.c_str());

    for (unsigned int i = 0; i < wym2; i++)
    {
        for (unsigned int j = 0; j < wym1; j++)
        {
            plik >> grid_ale_lepszy[j][wym2 - i - 1].identifier;
            grid_ale_lepszy[j][wym2 - i - 1].x = j;
            grid_ale_lepszy[j][wym2 - i - 1].y = wym2 - i - 1;
        }
    }
    plik.close();

    wypisz(grid_ale_lepszy);

    int start_x = 0;
    int start_y = 7;
    //grid_ale_lepszy[start_x][start_y].identifier = 9;
    int cel_x = 6;
    int cel_y = 8;
    //grid_ale_lepszy[cel_x][cel_y].identifier = 8;

    A_star(grid_ale_lepszy, start_x, start_y, cel_x, cel_y);

    wypisz(grid_ale_lepszy);


    return 0;
}

