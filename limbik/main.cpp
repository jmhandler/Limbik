//
//  main.cpp
//  limbik
//
//  Created by Josh Handler on 7/23/19.
//  Copyright © 2019 Josh Handler. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;


bool search(int p, vector<int> positions)
{
    vector<int>::iterator it = find(positions.begin(), positions.end(), p);
    if (it == positions.end())
    {
        return false;
    }
    return true;
}

int searchPosition(int p, vector<int> positions)
{
    vector<int>::iterator it = find(positions.begin(), positions.end(), p);
    if (it == positions.end())
    {
        return -1;
    }
    int index = distance(positions.begin(), it);
    return index;
}

void setBoard(vector<int> pawns, int queen)
{
    int boardSpot = 1;
    int i = 0;

    for (int x = 0; x < 8; x++)
    {
        for (int y = 0; y < 8; y++)
        {
            if (pawns[i] == boardSpot)
            {
                cout << "p ";
                i++;
            }
            else if (queen == boardSpot)
            {
                cout << "Q ";
            }
            else
            {
                cout << "- ";
            }
            boardSpot++;
        }
        cout << endl;
    }
}



int main() {
    
    srand(time(0));
    
    int queen = rand() % 64 + 1;
    vector<int> positions;
    positions.push_back(queen);
    vector<int> pawns;
    int numPawns = rand() % 64;
    
    while (numPawns > 0)
    {
        int p = rand() % 64 + 1;
       
        if (!search(p, positions))
        {
            positions.push_back(p);
            pawns.push_back(p);
            numPawns--;
        }
    }
    sort(pawns.begin(), pawns.end());

    setBoard(pawns, queen);
    vector<int> checkedPawns;
    
    int up = queen - 8;
    while (up > 0)
    {
        if (search(up, pawns))
        {
            checkedPawns.push_back(up);
            int dangered = searchPosition(up, pawns);
            pawns.erase(pawns.begin() + dangered);
            up = 0;
        }
        else
        {
            up = up - 8;
        }
    }
    int down = queen + 8;
    while (down < 65)
    {
        if (search(down, pawns))
        {
            checkedPawns.push_back(down);
            int dangered = searchPosition(down, pawns);
            pawns.erase(pawns.begin() + dangered);
            down = 65;
        }
        else
        {
            down = down + 8;
        }
    }
    int upright = queen - 7;
    while (upright > 0 && (upright % 8) != 1)
    {
        if (search(upright, pawns))
        {
            checkedPawns.push_back(upright);
            int dangered = searchPosition(upright, pawns);
            pawns.erase(pawns.begin() + dangered);
            upright = 0;
        }
        else
        {
            upright = upright - 7;
        }
    }
    int upleft = queen - 9;
    while (upleft > 0 && (upleft % 8) != 0)
    {
        if (search(upleft, pawns))
        {
            checkedPawns.push_back(upleft);
            int dangered = searchPosition(upleft, pawns);
            pawns.erase(pawns.begin() + dangered);
            upleft = 0;
        }
        else
        {
            upleft = upleft - 9;
        }
    }
    int downright = queen + 9;
    while (downright < 65 && (downright % 8) != 1)
    {
        if (search(downright, pawns))
        {
            checkedPawns.push_back(downright);
            int dangered = searchPosition(downright, pawns);
            pawns.erase(pawns.begin() + dangered);
            downright = 65;
        }
        else
        {
            downright = downright + 9;
        }
    }
    int downleft = queen + 7;
    while (downleft < 65 && (downleft % 8) != 0)
    {
        if (search(downleft, pawns))
        {
            checkedPawns.push_back(downleft);
            int dangered = searchPosition(downleft, pawns);
            pawns.erase(pawns.begin() + dangered);
            downleft = 65;
        }
        else
        {
            downleft = downleft + 7;
        }
    }
    int left = queen - 1;
    while ((left % 8) != 0)
    {
        if (search(left, pawns))
        {
            checkedPawns.push_back(left);
            int dangered = searchPosition(left, pawns);
            pawns.erase(pawns.begin() + dangered);
            left = 0;
        }
        else
        {
            left = left - 1;
        }
    }
    int right = queen + 1;
    while ((right % 8) != 1)
    {
        if (search(right, pawns))
        {
            checkedPawns.push_back(right);
            int dangered = searchPosition(right, pawns);
            pawns.erase(pawns.begin() + dangered);
            right = 1;
        }
        else
        {
            right = right + 1;
        }
    }
    
    cout << "{" << checkedPawns[0];
    for (int x = 1; x < checkedPawns.size(); x++)
    {
        cout << ", " << checkedPawns[x];
    }
    cout << "}" << endl;
    cout << "^^^ danger ^^^" << endl;
    
    cout << "{" << pawns[0];
    for (int x = 1; x < pawns.size(); x++)
    {
        cout << ", " << pawns[x];
    }
    cout << "}" << endl;
    cout << "^^^ safe ^^^" << endl;

    return 0;
}


