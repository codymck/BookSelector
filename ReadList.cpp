#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "time.h"
#include <windows.h>

using namespace std;

struct recommendation
{
    string bookTitle;     // name of book
    string author;        // other of book
    string recommendedBy; // who recommended the book
    int pages;            // number of pages

    int count; // number of times book selected
};

vector<recommendation> recList;

void readList()
{
    string listName = "list.txt";

    ifstream fin(listName.c_str(), ios::in);

    string tmp;

    while (!fin.eof())
    {
        recommendation rec;

        for (string line; getline(fin, line);)
        {
            stringstream ss(line);
            string word;

            while (!ss.eof())
            {
                getline(ss, word, ',');
                rec.bookTitle = word;

                getline(ss, word, ',');
                rec.author = word;

                getline(ss, word, ',');
                rec.pages = stoi(word);

                getline(ss, word, ',');
                rec.recommendedBy = word;

                recList.push_back(rec);
            }
        }
    }
}

void outputList()
{
    cout << "LIST OF SELECTED BOOKS\n"
         << endl;

    for (int i = 0; i < recList.size(); i++)
    {
        cout << "Book Title: " << recList.at(i).bookTitle << endl;
        cout << "Author: " << recList.at(i).author << endl;
        cout << "Page Count: " << recList.at(i).pages << endl;
        cout << "Recommended By: " << recList.at(i).recommendedBy << endl;
        cout << "Count: " << recList.at(i).count << endl;
        cout << endl;
    }
}

void scramble()
{
    time_t current_time = time(NULL);

    srand((unsigned)time(NULL));

    for (int i = 0; i < 100; i++)
    {
        int random = rand() % recList.size();
        int value = rand() % 300;
        recList.at(random).count += value;
    }

    outputList();
}

int main()
{
    readList();
    scramble();
}
