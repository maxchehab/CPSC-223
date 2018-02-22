// Inserting items (integers) into a dictionary (hash table)
// Maxwell Chehab
// Hashprogram.cpp

#include <iostream>

using namespace std;

const int MAXSIZE = 7;

void input(int hashTable[]);
int hashFunction(int item);
void print(int hashTable[]);

void input(int hashTable[])
{
    int item;
    for (int i = 0; i < 3; i++)
    {
        cout << "Enter an integer -> ";
        cin >> item;
        hashTable[hashFunction(item)];
    }
}

int hashFunction(int item)
{
    return item % MAXSIZE;
}

void print(int hashTable[])
{
    for (int i = 0; i < MAXSIZE; i++)
    {
        cout << i << " : " << hashTable[i] << endl;
    }
}

int main()
{
    int hashTable[MAXSIZE];

    return 0;
}
