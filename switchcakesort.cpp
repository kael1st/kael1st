#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

struct Plate
{
    vector<int> cakes = {0, 0, 0, 0, 0, 0};
};

vector<Plate> table[5][4];

void printPlate(const Plate &plate)
{
    cout << "[ ";
    for (int cake : plate.cakes)
    {
        cout << cake << " ";
    }
    cout << "]";
}

void printTable()
{
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            cout << "{(" << i << "," << j << ") ";
            if (table[i][j].empty())
            {
                cout << "[]";
            }
            else
            {
                for (int k = 0; k < table[i][j].size(); ++k)
                {
                    printPlate(table[i][j][k]);
                }
            }
            cout << "} ";
        }
        cout << endl; // Newline at the end of each row
    }
}

Plate GeneratePlate()
{
    Plate plate;
    int count = 0;
    while (count < 3)
    {
        int cake = rand() % 6 + 1; // generate non-zero cakes
        plate.cakes[count] = cake;
        ++count;
    }
    sort(plate.cakes.begin(), plate.cakes.end(), greater<int>()); // Sort cakes in descending order
    return plate;
}

void transferCakes(Plate &source, Plate &destination)
{
    for (int i = 0; i < source.cakes.size(); ++i)
    {
        if (source.cakes[i] != 0)
        {
            for (int j = 0; j < destination.cakes.size(); ++j)
            {
                if (destination.cakes[j] == 0)
                {
                    destination.cakes[j] = source.cakes[i];
                    source.cakes[i] = 0;
                    break;
                }
            }
        }
    }
}

void trySwitch(int row, int col, Plate &currentPlate)
{
    if (col > 0 && !table[row][col - 1].empty())
    {
        Plate &adjacentPlate = table[row][col - 1].back();
        for (int i = 0; i < 6; ++i)
        {
            if (currentPlate.cakes[i] != 0 && currentPlate.cakes[i] == adjacentPlate.cakes[i])
            {
                transferCakes(currentPlate, adjacentPlate);
            }
        }
    }
    if (col < 3 && !table[row][col + 1].empty())
    {
        Plate &adjacentPlate = table[row][col + 1].back();
        for (int i = 0; i < 6; ++i)
        {
            if (currentPlate.cakes[i] != 0 && currentPlate.cakes[i] == adjacentPlate.cakes[i])
            {
                transferCakes(currentPlate, adjacentPlate);
            }
        }
    }
    if (row > 0 && !table[row - 1][col].empty())
    {
        Plate &adjacentPlate = table[row - 1][col].back();
        for (int i = 0; i < 6; ++i)
        {
            if (currentPlate.cakes[i] != 0 && currentPlate.cakes[i] == adjacentPlate.cakes[i])
            {
                transferCakes(currentPlate, adjacentPlate);
            }
        }
    }
    if (row < 4 && !table[row + 1][col].empty())
    {
        Plate &adjacentPlate = table[row + 1][col].back();
        for (int i = 0; i < 6; ++i)
        {
            if (currentPlate.cakes[i] != 0 && currentPlate.cakes[i] == adjacentPlate.cakes[i])
            {
                transferCakes(currentPlate, adjacentPlate);
            }
        }
    }
}

int main()
{
    srand(time(0));
    while (true)
    {
        system("cls");
        int row, col;
        printTable();
        Plate currentPlate = GeneratePlate();
        cout << "Current Cake : ";
        printPlate(currentPlate);
        cout << endl;

        cout << "Insert to Table";
        cout << "\n\n";
        cout << "Row : ";
        cin >> row;
        cout << "\nCol : ";
        cin >> col;

        trySwitch(row, col, currentPlate);
        if (table[row][col].size() >= 6)
        {
            table[row][col].erase(table[row][col].begin()); // Remove the oldest plate if the cell is full
        }
        table[row][col].push_back(currentPlate);
    }

    return 0;
}
