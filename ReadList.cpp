#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "time.h"
#include <windows.h>
#include <algorithm>

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

    // cout << "Enter name of list with recommendations in format {Title,Author,Pages,RecommendedBy}: ";
    // cin >> listName;

    ifstream fin(listName.c_str(), ios::in);

    string tmp;

    while (!fin.eof())
    {
        recommendation rec;

        for (string line; getline(fin, line);)
        {
            stringstream ss(line);
            string word;

            if (!line.empty())
            {
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
}

void outputList()
{
    cout << "\n\t\tLIST OF SELECTED BOOKS\n"
         << endl;

    for (int i = 0; i < recList.size(); i++)
    {
        cout << "\t\t------";
        cout << "#" << i + 1;
        cout << "------" << endl;

        cout << "\t\tBook Title: " << recList.at(i).bookTitle << endl;
        cout << "\t\tAuthor: " << recList.at(i).author << endl;
        cout << "\t\tPage Count: " << recList.at(i).pages << endl;
        cout << "\t\tRecommended By: " << recList.at(i).recommendedBy << endl;
        cout << "\t\tCount: " << recList.at(i).count << endl;
        cout << endl;
    }
}

void sortList(vector<recommendation> &rList)
{
    int n = rList.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (rList.at(j).count < rList.at(j + 1).count)
            {
                iter_swap(rList.begin() + j, rList.begin() + (j + 1));
            }
        }
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

    sortList(recList);
    outputList();
}

int main()
{
    readList();
    scramble();
}
