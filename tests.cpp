//
//  tests.cpp
//  Mike Maczynski
//  CS251 - Fall 2020
//
//  This is my testing file, in this file I have 24
//  tests that test each public function in the
//  AutocompleteList.h file and then display the
//  results neatly when the file is run.
//

#include <iostream>
#include "AutocompleteList.h"
#include <algorithm>
#include <string>

using namespace std;

bool size_test1() {
    AutocompleteList  list;  // empty list
    if (list.getSize() == 0) {
        return true;
    }
    return false;
}
bool size_test2() {
    int n = 10;
    AutocompleteList  list(n);  // list of size 10
    if (list.getSize() == 10) {
        return true;
    }
    return false;
}
bool print_test_1() {
    int n = 10;
    int numElemsPrinted = 0;
    AutocompleteList  list(n);  // empty list
    for(int x = 0; x < list.getSize(); x++){
        numElemsPrinted++;
    }
    if(numElemsPrinted == n){
        return true;
    }
    return false;
}
bool file_reading_test_1() {
    AutocompleteList list("tiny.txt");
    if ((list[1].weight == 12) && (list[1].query == "sad")) {
        return true;
    }
    return false;
}
bool copyConstructor_test() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2 = list;
    if (list.getSize() == list2.getSize()) {
        return true;
    }
    return false;
}
bool copyConstructor_test2() {
    AutocompleteList list("wiktionary.txt");
    AutocompleteList list2 = list;
    if (list.getSize() == list2.getSize()) {
        return true;
    }
    return false;
}
bool copyConstructor_test3() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2 = list;
    int lNum = 0, l2Num = 0;
    lNum = list.numberOfMatches("sp");
    l2Num = list2.numberOfMatches("sp");
    if (lNum == l2Num) {
        return true;
    }
    return false;
}
bool copyConstructorAndBracket_test() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2 = list;
    if (list[2].query == list2[2].query) {
        return true;
    }
    return false;
}
bool copyConstructorAndBracket_test2() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2 = list;
    if (list[list.getSize()-1].query == list2[list2.getSize()-1].query) {
        return true;
    }
    return false;
}
bool copyConstructorAndBracket_test3() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2 = list;
    if (list[0].weight == list2[0].weight) {
        return true;
    }
    return false;
}
bool copyConstructorEqualOperator_test() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2(9);
    list2 = list;
    if (list.getSize() == list2.getSize()) {
        return true;
    }
    return false;
}
bool copyConstructorEqualOperator_test2() {
    AutocompleteList list("wiktionary.txt");
    AutocompleteList list2(200);
    list2 = list;
    if (list.getSize() == list2.getSize()) {
        return true;
    }
    return false;
}
bool copyConstructorEqualOperator_test3() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2("wiktionary.txt");
    list2 = list;
    int lNum = 0, l2Num = 0;
    lNum = list.numberOfMatches("sp");
    l2Num = list2.numberOfMatches("sp");
    if (lNum == l2Num) {
        return true;
    }
    return false;
}
bool copyConstructorEqualOperatorAndBracket_test() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2(2);
    list2 = list;
    if (list[2].query == list2[2].query) {
        return true;
    }
    return false;
}
bool copyConstructorEqualOperatorAndBracket_test2() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2(20);
    list2 = list;
    if (list[list.getSize()-1].query == list2[list2.getSize()-1].query) {
        return true;
    }
    return false;
}
bool copyConstructorEqualOperatorAndBracket_test3() {
    AutocompleteList list("tiny.txt");
    AutocompleteList list2("wiktionary.txt");
    list2 = list;
    if (list[0].weight == list2[0].weight) {
        return true;
    }
    return false;
}
bool count_numberOfMatches_for_prefix_test() {
    AutocompleteList list("movies.txt");
    AutocompleteList list2 = list;
    if (list2.numberOfMatches("The Good Woman") == 3) {
        return true;
    }
    return false;
}
bool count_numberOfMatches_for_prefix_test2() {
    AutocompleteList list("wiktionary.txt");
    if (list.numberOfMatches("tr") == 132) {
        return true;
    }
    return false;
}
bool count_numberOfMatches_for_prefix_test3() {
    AutocompleteList list("tiny.txt");
    if (list.numberOfMatches("z") == 0) {
        return true;
    }
    return false;
}
bool count_numberOfMatches_for_prefix_test4() {
    AutocompleteList list("tiny.txt");
    if (list.numberOfMatches("buc") == 1) {
        return true;
    }
    return false;
}
bool count_numberOfMatches_for_prefix_test5() {
    AutocompleteList list("tiny.txt");
    if (list.numberOfMatches("") == 0) {
        return true;
    }
    return false;
}
bool allMatches_for_prefix_test() {
    AutocompleteList list("tiny.txt");
    list = list.allMatches("sp");
    if (list[1].weight == 15) {
        return true;
    }
    return false;
}
bool allMatches_for_prefix_test2() {
    AutocompleteList list("wiktionary.txt");
    list = list.allMatches("thr");
    if (list[3].query == "thrown") {
        return true;
    }
    return false;
}
bool allMatches_for_prefix_test3() {
    AutocompleteList list("wiktionary.txt");
    list = list.allMatches("");
    if (list.getSize() == 0) {
        return true;
    }
    return false;
}





int main() {
    int passed = 0;
    int failed = 0;
    
    // Run tests
    if (size_test1()) {
        passed++;
    } else {
        cout << "size_test1 failed" << endl;
        failed++;
    }
    if (size_test2()) {
        passed++;
    } else {
        cout << "size_test2 failed" << endl;
        failed++;
    }
    if (print_test_1()) {
        passed++;
    } else {
        cout << "print_test_1 failed" << endl;
        failed++;
    }
    if (file_reading_test_1()) {
        passed++;
    } else {
        cout << "file_reading_test_1 failed" << endl;
        failed++;
    }
    if (copyConstructor_test()) {
        passed++;
    } else {
        cout << "copyConstructor_test failed" << endl;
        failed++;
    }
    if (copyConstructor_test2()) {
        passed++;
    } else {
        cout << "copyConstructor_test2 failed" << endl;
        failed++;
    }
    if (copyConstructor_test3()) {
        passed++;
    } else {
        cout << "copyConstructor_test3 failed" << endl;
        failed++;
    }
    if (copyConstructorAndBracket_test()) {
        passed++;
    } else {
        cout << "copyConstructorAndBracket_test failed" << endl;
        failed++;
    }
    if (copyConstructorAndBracket_test2()) {
        passed++;
    } else {
        cout << "copyConstructorAndBracket_test2 failed" << endl;
        failed++;
    }
    if (copyConstructorAndBracket_test3()) {
        passed++;
    } else {
        cout << "copyConstructorAndBracket_test2 failed" << endl;
        failed++;
    }
        if (copyConstructorEqualOperator_test()) {
        passed++;
    } else {
        cout << "copyConstructorEqualOperator_test failed" << endl;
        failed++;
    }
    if (copyConstructorEqualOperator_test2()) {
        passed++;
    } else {
        cout << "copyConstructorEqualOperator_test2 failed" << endl;
        failed++;
    }
    if (copyConstructorEqualOperator_test3()) {
        passed++;
    } else {
        cout << "copyConstructorEqualOperator_test3 failed" << endl;
        failed++;
    }
    if (copyConstructorEqualOperatorAndBracket_test()) {
        passed++;
    } else {
        cout << "copyConstructorEqualOperatorAndBracket_test failed" << endl;
        failed++;
    }
    if (copyConstructorEqualOperatorAndBracket_test2()) {
        passed++;
    } else {
        cout << "copyConstructorEqualOperatorAndBracket_test2 failed" << endl;
        failed++;
    }
    if (copyConstructorEqualOperatorAndBracket_test3()) {
        passed++;
    } else {
        cout << "copyConstructorEqualOperatorAndBracket_test2 failed" << endl;
        failed++;
    }
    if (count_numberOfMatches_for_prefix_test()) {
        passed++;
    } else {
        cout << "count_occurences_of_prefix_test failed" << endl;
        failed++;
    }
    if (count_numberOfMatches_for_prefix_test2()) {
        passed++;
    } else {
        cout << "count_occurences_of_prefix_test2 failed" << endl;
        failed++;
    }
    if (count_numberOfMatches_for_prefix_test3()) {
        passed++;
    } else {
        cout << "count_occurences_of_prefix_test3 failed" << endl;
        failed++;
    }
    if (count_numberOfMatches_for_prefix_test4()) {
        passed++;
    } else {
        cout << "count_occurences_of_prefix_test4 failed" << endl;
        failed++;
    }
    if (count_numberOfMatches_for_prefix_test5()) {
        passed++;
    } else {
        cout << "count_occurences_of_prefix_test5 failed" << endl;
        failed++;
    }
    if (allMatches_for_prefix_test()) {
        passed++;
    } else {
        cout << "allMatches_for_prefix_test failed" << endl;
        failed++;
    }
    if (allMatches_for_prefix_test2()) {
        passed++;
    } else {
        cout << "allMatches_for_prefix_test2 failed" << endl;
        failed++;
    }
    if (allMatches_for_prefix_test3()) {
        passed++;
    } else {
        cout << "allMatches_for_prefix_test3 failed" << endl;
        failed++;
    }

    cout << "----------------" << endl;
    cout << "Tests passed: " << passed << endl;
    cout << "Tests failed: " << failed << endl;
    cout << "----------------" << endl;
    return 0;
}
