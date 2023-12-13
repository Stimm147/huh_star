#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

const int wym1 = 20;
const int wym2 = 20;

struct wektor {
    int x{};
    int y{};
    double heuryst_value{};
    double identifier{};
    int koszt_ruchu{};
    bool czy_obliczony_koszt = false;
    bool czy_odwiedzone = false;
    bool czy_odwiedzone_back = false;
};

struct CompareHeuristic {
    bool operator()(const wektor& lhs, const wektor& rhs) const {
        return lhs.heuryst_value > rhs.heuryst_value;
    }
};

double heurystyka(int x, int y, int cel_x, int cel_y) {
    return sqrt(pow((x - cel_x), 2) + pow((y - cel_y), 2));
}

int A_star(wektor G[][wym1], int start_x, int start_y, int cel_x, int cel_y) {
    priority_queue<wektor, vector<wektor>, CompareHeuristic> do_odwiedzenia;

    if (start_x >= wym1 || start_y >= wym1 || start_x < 0 || start_y < 0 || cel_x >= wym1 || cel_y >= wym1 || cel_x < 0 || cel_y < 0) {
        return 3;
    }
    if (G[start_x][start_y].identifier == 5 || G[cel_x][cel_y].identifier == 5) {
        return 2;
    }

    int x_check;
    int y_check;

    G[start_x][start_y].koszt_ruchu = 0;
    G[start_x][start_y].heuryst_value = heurystyka(start_x, start_y, cel_x, cel_y);
    do_odwiedzenia.push(G[start_x][start_y]);

    while (!do_odwiedzenia.empty()) {
        wektor current = do_odwiedzenia.top();
        do_odwiedzenia.pop();

        if (current.x == cel_x && current.y == cel_y) {
            // Destination reached
            break;
        }

        for (int i = 1; i <= 4; ++i) {
            int new_x = current.x;
            int new_y = current.y;


            switch (i) {
            case 1: // Down
                new_y -= 1;
                break;
            case 2: // Left
                new_x -= 1;
                break;
            case 3: // Up
                new_y += 1;
                break;
            case 4: // Right
                new_x += 1;
                break;
            }

            if (new_x >= 0 && new_x < wym1 && new_y >= 0 && new_y < wym2 &&
                G[new_x][new_y].identifier != 5 && !G[new_x][new_y].czy_odwiedzone) {

                int new_cost = current.koszt_ruchu + 1;

                if (!G[new_x][new_y].czy_obliczony_koszt || new_cost < G[new_x][new_y].koszt_ruchu) {
                    G[new_x][new_y].koszt_ruchu = new_cost;
                    G[new_x][new_y].czy_obliczony_koszt = true;
                    G[new_x][new_y].heuryst_value = heurystyka(new_x, new_y, cel_x, cel_y) + new_cost;
                    do_odwiedzenia.push(G[new_x][new_y]);
                }
            }
        }
        //G[current.x][current.y].identifier = G[current.x][current.y].heuryst_value;
        G[current.x][current.y].czy_odwiedzone = true;
        x_check = current.x;
        y_check = current.y;

    }

    if (do_odwiedzenia.empty() && !(x_check == cel_x && y_check == cel_y)) {
        return 1;
    }

    vector<wektor> do_odwiedzenia2;

    do_odwiedzenia2.push_back(G[cel_x][cel_y]);
    //G[cel_x][cel_y].czy_odwiedzone_back = true;

    while (!do_odwiedzenia2.empty()) {

        int pozycja = 0;
        wektor naj = do_odwiedzenia2[0];
        double najnaj = naj.heuryst_value;
        for (auto& uuh : do_odwiedzenia2) {
            if ((uuh.heuryst_value <= najnaj)) {
                najnaj = uuh.heuryst_value;
                naj = uuh;
            }
        }
        for (auto& uuh2 : do_odwiedzenia2) {
            if (uuh2.x == naj.x && uuh2.y == naj.y) {
                break;
            }
            pozycja++;
        }

        wektor current = do_odwiedzenia2[pozycja];
        do_odwiedzenia2.clear();

        if (current.x == start_x && current.y == start_y) {
            // Destination reached
            break;
        }

        for (int i = 1; i <= 4; ++i) {
            int new_x = current.x;
            int new_y = current.y;


            switch (i) {
            case 1: // Down
                new_y -= 1;
                break;
            case 2: // Left
                new_x -= 1;
                break;
            case 3: // Up
                new_y += 1;
                break;
            case 4: // Right
                new_x += 1;
                break;
            }

            if (new_x >= 0 && new_x < wym1 && new_y >= 0 && new_y < wym2 &&
                G[new_x][new_y].identifier != 5 && !G[new_x][new_y].czy_odwiedzone_back && G[new_x][new_y].czy_odwiedzone) {
                    
                do_odwiedzenia2.push_back(G[new_x][new_y]);
            }
        }
        G[current.x][current.y].czy_odwiedzone_back = true;
        G[current.x][current.y].identifier = 3;

    }
    G[start_x][start_y].identifier = 3;
    return 0;
}


void wypisz(wektor G[][wym1]) {
    cout << "\nWypisujemy na ekran\n\n";
    for (int i = 0; i < wym2; i++) {
        for (int j = 0; j < wym1; j++) {
            cout << " " << G[j][wym1 - i - 1].identifier;
        }
        cout << "\n";
    }
}

int main() {
    cout << "Wczytywanie danych z pliku\n";

    string nazwap = "grid.txt";

    wektor grid_ale_lepszy[wym1][wym1];

    ifstream plik(nazwap.c_str());

    for (unsigned int i = 0; i < wym2; i++) {
        for (unsigned int j = 0; j < wym1; j++) {
            plik >> grid_ale_lepszy[j][wym2 - i - 1].identifier;
            grid_ale_lepszy[j][wym2 - i - 1].x = j;
            grid_ale_lepszy[j][wym2 - i - 1].y = wym2 - i - 1;
        }
    }
    plik.close();

    wypisz(grid_ale_lepszy);

    int start_x = 7;
    int start_y = 0;
    int cel_x = 4;
    int cel_y = 4;

    int wynik = A_star(grid_ale_lepszy, start_x, start_y, cel_x, cel_y);

    if (wynik == 0) {
        printf("\nPomyślnie znaleziono droge!\n");
        wypisz(grid_ale_lepszy);
    }
    else if (wynik == 1) {
        printf("\nNie udalo sie znalezc drogi - miejsce startowe odciete od celu\n");
    }
    else if (wynik == 2) {
        printf("\nCel lub miejsce startowe nie moze znajdowac sie na scianie\n");
    }
    else if (wynik == 3) {
        printf("\nCel lub miejsce startowe nie moze znajdowac sie poza mapa\n");
    }

    return 0;
}