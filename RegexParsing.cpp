// Copyright Kim Douglas 2015
// based on: 
//      demo regex code
//      Copyright (C) 2015 Fred Martin, fredm@cs.uml.edu for 91.204 Computing IV
//      Thu Apr 16 11:08:45 2015

#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include "Regex.hpp"

using std::cin;
using std::cout;
using std::endl;

int main(int argc, char* argv[]) {
    std::string s, rs;
    boost::regex re;

    cout << "If you get errors when constructing the regex, see:\n";
    cout << "http://www.boost.org/doc/libs/1_58_0/";
    cout << "boost/regex/v4/error_type.hpp\n" << endl;

//    cout << "Enter regex > ";
//    getline(cin, rs);

    rs = ".*log.c.166.*";


    try {
        re = boost::regex(rs);  // regex object is created with 
        cout << "mark_count() is " << re.mark_count() << endl;
    } catch (boost::regex_error& exc) {
        cout << "Regex constructor failed with code " << exc.code() << endl;
        exit(1);
    }

//    cout << "Enter line > ";

    while (getline(cin, s)) {
//      cout << endl;

        boost::smatch matches;  // gets populated with results
        boost::regex_match(s, matches, re); 

//        cout << "matches[0].matched is ";
//        cout << (matches[0].matched ? "true" : "false") << endl;

        if (matches[0].matched) {
            cout << "the matches were: ";
            for (unsigned i = 0; i < matches.size(); i++) {
                cout << "index = " << i << "[" << matches[i] << "] " << endl;
            }
        }

//        cout << endl << "Enter line > ";
    }

    return 0;
}
