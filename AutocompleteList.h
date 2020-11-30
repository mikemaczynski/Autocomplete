//
//  AutocompleteList.h
//
//  Mike Maczynski
//  CS251 - Fall 2020
//
//  This is the AutocompleteList.h file, where
//  the bulk of the project was written. It holds
//  all the public/private functions & variables and
//  contains all the code that makes the application.cpp
//  file work correctly.
//

#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

struct Term {
    string query;
    long long int weight;
    // need this for autograding
    bool operator==(const Term& term) const {
        return (query == term.query && weight == term.weight);
    }
};

//
// AutocompleteList
//
class AutocompleteList {
 private:
    //
    // Private member variables for the abstraction.
    // This implementation uses a low-level C array, terms, to store a list of
    // Terms.  As a result, you must also keep track of the number of elements
    // stored (size).
    //
    Term* terms;  // pointer to a C-style array
    int size;  // number of elements in the array
    string sortType;  // records how list is sorted

    //
    // Private member function.
    // Returns the index of the first word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //

    int firstIndexOf(string prefix) {
        int low = 0, high = getSize(), value = -1, prefixLength = 0;
        prefixLength = prefix.length();

        while (low <= high) {
            int middle = (low + high) / 2;

            if (terms[middle].query.substr
               (0, prefixLength).compare(prefix) > 0) {
                high = middle - 1;
            } else if (terms[middle].query.substr
                      (0, prefixLength).compare(prefix) < 0) {
                low = middle + 1;
            } else {
                value = middle;
                high = middle - 1;
            }
        }
        return value;
    }

    //
    // Private member function.
    // Returns the index of the last word in terms[] that contains the prefix,
    // or -1 if there are no words containing the prefix. This search should be
    // implemented using a variation of the binary search algorithm.
    // Performance requirement: O(logn), n is size.
    //
    int lastIndexOf(string prefix) {
        int low = 0, high = getSize(), value = -1, prefixLength = 0;
        prefixLength = prefix.length();

        while (low <= high) {
            int middle = (low + high) / 2;

            if (terms[middle].query.substr
               (0, prefixLength).compare(prefix) > 0) {
                high = middle - 1;
            } else if (terms[middle].query.substr
                      (0, prefixLength).compare(prefix) < 0) {
                low = middle + 1;
            } else {
                value = middle;
                low = middle + 1;
            }
        }
        return value;
    }

    //
    // Private member function.
    // This function sorts the terms array by lexicographic order of the query
    // string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByLexOrder() {
        sortType = "lex";

        // c++ sort function modified to sort the query results lexographically
        sort(terms, terms + size, [&](const Term &first, const Term &second) {
            return first.query < second.query;
        });
    }
    
    //
    // Private member function.
    // This function sorts the terms array by decreasing weight order.
    // Set the sortType to "weight".
    // Performance requirement: O(nlogn), n is size.
    //
    void sortByWeightOrder() {
        sortType = "weight";
        
        // c++ sort function modified to sort the
        // weight results in descending order.
        sort(terms, terms + size, [&](const Term &first, const Term &second) {
            return first.weight > second.weight;
        });
    }

 public:
    //
    // default constructor:
    //
    // Called automatically by C++ to create a AutocompleteList.
    // When this is called, intialize terms to a nullptr and set size to 0.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList() {
        terms = nullptr;
        size = 0;
        sortType = "none";
    }

    //
    // a second constructor:
    //
    // Parameter passed in determines size of terms.
    // When this is called, allocate memory for n Terms and
    // set size accordingly.
    // Set sortType to "none".
    // Performance requirement: O(1)
    //
    AutocompleteList(int n) {
        sortType = "none";
        size = n;
        terms = new Term[n];
    }

    //
    // a third constructor:
    //
    // Parameter passed in is name of file to read in.
    // This constructor will build Autocomplete list from file.
    // Assume file format is:
    // line 1: "<size>"
    // lines 2 thru size+1: "weight query"
    // The list should be sorted lexicographic order by the query string.
    // Set sortType to "lex".
    // Performance requirement: O(nlogn), n is size.
    //
    AutocompleteList(string filename) {
        ifstream infile(filename);

        sortType = "lex";
        int fileLength = 0, counter = -1;
        string line = "";

        infile >> fileLength;
        size = fileLength;
        terms = new Term[size+1];

        while (!infile.eof()) {
            getline(infile, line);
            if (counter >= 0 && counter < fileLength) {
                stringstream str(line);
                string tempQuery = "";

                str >> terms[counter].weight >> tempQuery;
                tempQuery = line.substr(line.find(tempQuery));
                terms[counter].query = tempQuery;
            }
            counter++;
        }
        counter--;
        sortByLexOrder();
    }

    //
    // copy constructor:
    //
    // Called automatically by C++ to create an AutocompleteList that contains
    // a copy of an existing AutocompleteList.  Example: this occurs when
    // passing AutocompleteList as a parameter by value.
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList(const AutocompleteList& other) {
        // allocate memory for the new object and set each
        // of the private data variables to match the
        // ones of the object thats being copied.
        this->terms = new Term[other.size + 1];
        this->size = other.size;
        this->sortType = other.sortType;
        
        // copy over each element to the new object
        for (int x = 0; x < other.size; x++) {
            this->terms[x] = other.terms[x];
        }
    }

    //
    // copy operator=
    //
    // Called when you assign one AutocompleteList into another,
    // i.e. this = other;
    // Performance requirement: O(n), n is size.
    //
    AutocompleteList& operator=(const AutocompleteList& other) {
        // check if you're trying to copy an element onto itself.
        if (this == &other) {
            return *this;
        }
        // if the terms has data in it, delete that data to prepare
        // it for receiving new data.
        if (terms != nullptr) {
            delete[] terms;
        }

        // allocate memory for the new object and set each
        // of the private data variables to match the
        // ones of the object thats being copied.
        this->terms = new Term[other.size + 1];
        this->size = other.size;
        this->sortType = other.sortType;

        for (int x = 0; x < other.size; x++) {
            this->terms[x] = other.terms[x];
        }
        return *this;
    }

    //
    // destructor:
    //
    // Called automatically by C++ to free the memory associated by the Term.
    //
    virtual ~AutocompleteList() {
        if (terms != nullptr) {
            delete[] terms;
        }
    }

    //
    // Public member function.
    // Returns the size of the AutocompleteList.
    // Performance requirement: O(1).
    //
    int getSize() {
        return size;
    }

    //
    // Public member function.
    // Returns Term element in AutocompleteList.
    // This gives public access to Terms stored in the AutocompleteList.
    // If i is out of bounds, throw an out_of_range error message:
    // "AutocompleteList: i out of bounds"
    // Note:  This public function does not necessarily fit the design of this
    // abstraction but we are having you write it for testing purposes.
    // Performance requirement: O(1).
    //
    Term& operator[](int i) {
        if (i < 0 || i >= getSize()) {
          throw out_of_range("AutocompleteList: i out of bounds");
        }
        return terms[i];
    }

    // Public member function.
    // Returns an AutocompleteList which stores a list of all Terms that
    // start with the prefix.  The AutocompleteList returned should be sorted
    // in descending order by weight.  Set the returned AutocompleteList's
    // sortType to "weight".
    // If prefix is empty string, return an empty AutocompleteList;
    // If there are no words in the list the start with the prefix, return an
    // empty AutocompleteList.
    // If *this* AutocompleteList's sortType does not equal "lex", then return
    // an empty AutocompleteList.  In other words, allMatches should only be
    // called on an AutocompleteList that is sorted in lexicographic order by
    // the query string.
    // Performance requirement: O(mlogm+logn), n is size and
    // where m is the number of matching terms.
    //
    AutocompleteList allMatches(string prefix) {
        int firstIndex = -1, lastIndex = -1, numMatches = 0, counter = 0;
        numMatches = numberOfMatches(prefix);

        AutocompleteList result(numMatches);
        firstIndex = firstIndexOf(prefix);
        lastIndex = lastIndexOf(prefix);

        if (prefix == "")  {
            return AutocompleteList();
        } else if (numMatches == 0) {
            return AutocompleteList();
        } else if (sortType != "lex") {
            return AutocompleteList();
        } else {
            for (int x = firstIndex; x <= lastIndex; x++) {
                if (counter < numMatches) {
                    result.terms[counter] = terms[x];
                    counter++;
                }
            }
            result.sortByWeightOrder();
        }
        return result;
    }

    // Public member function.
    // Returns the number of Terms that start with the given prefix.
    // If prefix is empty, return 0.
    // If *this* AutocompleteList's sortType does not equal "lex",
    // then return 0.
    // Performance requirement: O(logn), n is size.
    //
    int numberOfMatches(string prefix) {
        int firstIndex = -1, lastIndex = -1;
        firstIndex = firstIndexOf(prefix);
        lastIndex = lastIndexOf(prefix);
        if ((sortType != "lex") || (prefix == "")) {
            // either the sortType is not set to "lex"
            // or the prefix was left blank.
            return 0;
        } else if ((firstIndex >= 0) && (lastIndex >= 0)) {
            return ((lastIndex - firstIndex) + 1);
        } else {
            // no instances of the prefix were found
            return 0;
        }
    }
    //
    // Public member function.
    // Prints the AutocompleteList.
    // Pad the front of the print with 8 spaces for nicely formatted search:
    // print: "        query, weight".
    // NOTE:  This is also useful for debugging purposes.
    // Performance requirement: O(n), n is size
    //
    void print() {
        for (int x = 0; x < size; x++) {
            cout << "        " << terms[x].query
                 << ", " << terms[x].weight << endl;
        }
    }
    
    //
    // Public member function.
    // Prints the AutocompleteList based on the users choice in creativeSearch.
    // Takes in the number of results as a parameter, and then displays
    // that number of elements to the user in a nicely formatted way.
    //
    void printCreative(int numResults) {
        int numToPrint = 0;
        if (size > numResults) {
            numToPrint = numResults;
        } else {
            numToPrint = size;
        }
        for (int x = 0; x < numToPrint; x++) {
            cout << "            | " << terms[x].query << endl;
        }
    }
};
