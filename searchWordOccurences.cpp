#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int naiveWordSearch(string line, string searchWord) {
    int total = 0;
    int wordLen = searchWord.length();
    vector<size_t> vect;

    size_t pos = line.find(searchWord, 0);
    while (pos != string::npos) {
        vect.push_back(pos);
        pos = line.find(searchWord, pos+1);
    }
    return vect.size();
}

int main(int argc, char** argv) {
    string line;
    ifstream myfile ( argv[1] );
    int totalOccurences = 0;
    string wordToSearch;
    cout << "Enter word you want to search: ";
    cin >> wordToSearch;

    if (myfile.is_open())
    {
        while ( getline (myfile, line))
        {
            totalOccurences += naiveWordSearch(line, wordToSearch);
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    cout << "Total # of occurences of " << wordToSearch << " is " << totalOccurences << ".";
    return 0;
}