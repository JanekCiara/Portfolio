#include <iostream>
#include <vector>
using namespace std;
void wypiszPlansze(vector<vector<char>> plansza)
{
    for (int i = 0; i < plansza.size(); i++)
    {
        for (int j = 0; j < plansza[i].size(); j++)
        {
            cout << plansza[i][j] << ' ';
        }
        cout << '\n';
    }
}
bool czyWygral(vector<vector<char>> plansza, char znak)
{
    int licznik = 0;
    for (int i = 1; i < plansza.size(); i++) // sprawdzam poziom
    {
        if (plansza[i][1] == znak && plansza[i][2] == znak && plansza[i][3] == znak)
        {
            return true;
        }
    }
    for (int i = 1; i < plansza.size(); i++) // sprawdzam pion
    {
        if (plansza[1][i] == znak && plansza[2][i] == znak && plansza[3][i] == znak)
        {
            return true;
        }
    }
    if (plansza[1][1] == znak && plansza[2][2] == znak && plansza[3][3] == znak) // sprawdzam dwa przypadki ukos
    {
        return true;
    }
    if (plansza[1][3] == znak && plansza[2][2] == znak && plansza[3][1] == znak)
    {
        return true;
    }
    return false;
}
vector<vector<char>> wybierz_miejsce(vector<vector<char>> plansza, char znak)
{
    char poz1, poz2;
    cout << "Podaj gdzie postawić " << znak << " : " << '\n';
    cin >> poz1 >> poz2;
    while (poz1 < 'A' || poz1 > 'C' || poz2 < '1' || poz2 > '3')
    {
        cout << "Nie ma takiego miejsca, wybierz inne: " << '\n';
        cin >> poz1 >> poz2;
    }
    while (plansza[poz2 - '0'][poz1 - 'A' + 1] != '-')
    {
        cout << "To miejsce jest zajete, wybierz inne: " << '\n';
        cin >> poz1 >> poz2;
    }
    plansza[poz2 - '0'][poz1 - 'A' + 1] = znak;
    return plansza;
}
bool czyRemis(vector<vector<char>> plansza)
{
    for (int i = 1; i < plansza.size(); i++)
    {
        for (int j = 1; j < plansza[i].size(); j++)
        {
            if (plansza[i][j] == '-')
                return false;
        }
    }
    return true;
}
int minimax(vector<vector<char>> plansza, char znak)
{
    char przeciwny;
    if (znak == 'X')
        przeciwny = 'O';
    else
        przeciwny = 'X';
    if (czyWygral(plansza, znak))
        return 1;
    if (czyWygral(plansza, przeciwny))
        return -1;
    if (czyRemis(plansza))
        return 0;

    int score, bestScore = INT_MIN;
    for (int i = 1; i < plansza.size(); i++)
    {
        for (int j = 1; j < plansza[i].size(); j++)
        {
            if (plansza[i][j] != '-')
            {
                continue;
            }
            plansza[i][j] = znak;
            score = -minimax(plansza, przeciwny);
            plansza[i][j] = '-';
            bestScore = max(score, bestScore);
        }
    }
    return bestScore;
}
vector<vector<char>> bestMove(vector<vector<char>> plansza, char znak)
{
    char przeciwny;
    if (znak == 'X')
        przeciwny = 'O';
    else
        przeciwny = 'X';
    int score = INT_MIN, bestScore = INT_MIN;
    pair<int, int> bestMove;
    for (int i = 1; i < plansza.size(); i++)
    {
        for (int j = 1; j < plansza[i].size(); j++)
        {
            if (plansza[i][j] != '-')
            {
                continue;
            }
            plansza[i][j] = znak;
            score = -minimax(plansza, przeciwny);
            plansza[i][j] = '-';
            if (score > bestScore)
            {
                bestScore = score;
                bestMove = { i, j };
            }
        }
    }
    plansza[bestMove.first][bestMove.second] = znak;
    return plansza;
}

int main()
{
    bool end = false;
    pair<char, char> pozX, pozO;
    vector<vector<char>> plansza = { {' ', 'A', 'B', 'C'},
                                    {'1', '-', '-', '-'},
                                    {'2', '-', '-', '-'},
                                    {'3', '-', '-', '-'} };
    wypiszPlansze(plansza);
    while (!end)
    {
        plansza = wybierz_miejsce(plansza, 'X');
        wypiszPlansze(plansza);

        if (czyWygral(plansza, 'X'))
        {
            cout << "Wygral X" << '\n';
            break;
        }
        if (czyRemis(plansza))
        {
            cout << "Remis!" << '\n';
            break;
        }
        plansza = bestMove(plansza, 'O');
        wypiszPlansze(plansza);

        if (czyWygral(plansza, 'O'))
        {
            cout << "Wygral O" << '\n';
            break;
        }
        if (czyRemis(plansza))
        {
            cout << "Remis!" << '\n';
            break;
        }
    }
}
