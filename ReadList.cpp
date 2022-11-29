#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>
#include "time.h"
#include <algorithm>

using namespace std;

/**
 * @brief Simple console application for selecting a book from a list of recommendations, randomizing a score for each book, and sorting by highest score
 *
 * @author Cody McKinney
 */

struct recommendation
{
    string bookTitle;     // name of book
    string author;        // other of book
    string recommendedBy; // who recommended the book
    int pages;            // number of pages

    int score; // number of times book selected
};

// Global variable for recommendation list vector
vector<recommendation> recList;

// read ist and fill out recommendation info to add to recommendation list
void readList()
{
    string listName = "list.txt"; // can hardcode list name

    /* Or uncomment below to set name of text through input */
    // cout << "Enter name of list with recommendations in format {Title,Author,Pages,RecommendedBy}: ";
    // cin >> listName;

    ifstream fin(listName.c_str(), ios::in);

    string tmp;

    while (!fin.eof())
    {
        recommendation rec;

        // for every line in the file input stream
        for (string line; getline(fin, line);)
        {
            // string stream to delimit commas
            stringstream ss(line);
            string word;

            // handle empty lines
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

/* output list of recommendations and their randomized score */
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
        cout << "\t\tScore: " << recList.at(i).score << endl;
        cout << endl;
    }
}

/**
 * @brief bubblesort vector of recommendations based on score
 *
 * @param rList
 */
void sortList(vector<recommendation> &rList)
{
    int n = rList.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (rList.at(j).score < rList.at(j + 1).score)
            {
                iter_swap(rList.begin() + j, rList.begin() + (j + 1));
            }
        }
    }
}

/**
 * @brief scrambles the recommendation list using time
 * loops 100 times selecting random recommendation
 * then adds a random number 0 - 300 to the score
 */
void scramble()
{
    time_t current_time = time(NULL);

    srand((unsigned)time(NULL));

    for (int i = 0; i < 100; i++)
    {
        int random = rand() % recList.size();
        int value = rand() % 300;
        recList.at(random).score += value;
    }

    sortList(recList);
    outputList();
}

int main()
{
    readList();
    scramble();
}
