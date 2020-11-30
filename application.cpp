//
//  application.cpp
//  Mike Maczynski
//  CS 251 - Fall 2020
//
//  This program replicates the function of a typical search box
//  in which the user is shown several popular search results for
//  the prefix they have typed in so far. This program has two search
//  functions- the default search and my custom search that has added
//  functionality.
//

#include <iostream>
#include "AutocompleteList.h"

using namespace std;

int main() {
    string fileName = "", prefix = "";
    int numResults = 0;
    char userInput;

    cout << "Enter filename: ";
    cin >> fileName;
    cout << "Enter s-search or c-creative search: ";
    cin >> userInput;
    cin.ignore();

    if (userInput == 's') {
        AutocompleteList list(fileName);

        cout << "Welcome!" << endl;
        cout << "Type your search below, press enter for autocomplete (# to stop)." << endl;
        while (prefix != "#") {
            cout << "Search: ";
            getline(cin, prefix);

            if (prefix == "#") {
                return(0);
            }
            AutocompleteList result = list;
            result = result.allMatches(prefix);
            result.print();
        }
    }
    
    //
    // To run my creative search, type 'c' when prompted for your search type
    // and then follow the prompts on the screen. It will first ask you for
    // the number of search terms you'd like to see displayed on the screen,
    // and then it'll prompt you to enter a search term (similarly to the
    // original search function above), at which point it'll display those
    // to you. If you enter a search term that isn't in the file, it'll
    // display an error message and prompt you to enter another search term.
    //
    if (userInput == 'c') {
        AutocompleteList creativeList(fileName);
        cout << "--------------------------------" << endl;
        cout << " Welcome to my creative search!" << endl;
        cout << "--------------------------------" << endl;
        cout << "How many results would you like to see? (Default is 10)." << endl;
        cout << "Number of results: ";
        cin >> numResults;
        cin.ignore();
        cout << "\nType your search term below, then press enter to see the top results. (Enter # to stop).";
        while (prefix != "#") {
            cout << "\nEnter search: ";
            getline(cin, prefix);

            if (prefix == "#") {
                return(0);
            }
            AutocompleteList creativeResult = creativeList;
            if (creativeResult.numberOfMatches(prefix) == 0) {
                cout << "No matches found, please try again." << endl;
            } else {
                creativeResult = creativeResult.allMatches(prefix);
                creativeResult.printCreative(numResults);
            }
        }
    }
    return 0;
}
