// Copyright Kim Douglas 2015
// based on: 
//      demo regex code
//      Copyright (C) 2015 Fred Martin, fredm@cs.uml.edu for 91.204 Computing IV
//      Thu Apr 16 11:08:45 2015

#include <boost/regex.hpp>
#include <iostream>
#include <string>
#include "Regex.hpp"

//using std::cout;
//using std::cin;
//using std::endl;

int main(int argc, char* argv[]) {
    std::string s, rs;
    boost::regex re;

    std::cout << "If you get errors when constructing the regex, see:\n";
    std::cout << "http://www.boost.org/doc/libs/1_58_0/";
    std::cout << "boost/regex/v4/error_type.hpp\n";
    std::cout << std::endl;

    std::cout << "Enter regex > ";
    getline(std::cin, rs);

    try {
        re = boost::regex(rs);  // regex object is created with 
        std::cout << "mark_count() is " << re.mark_count() << std::endl;
    } catch (boost::regex_error& exc) {
        std::cout << "Regex constructor failed with code " << exc.code() << std::endl;
        exit(1);
    }

    std::cout << "Enter line > ";

    while (getline(std::cin, s)) {
        std::cout << std::endl;

        boost::smatch matches;  // gets populated with results
        boost::regex_match(s, matches, re); 

        std::cout << "matches[0].matched is ";
        std::cout << (matches[0].matched ? "true" : "false") << std::endl;

        if (matches[0].matched) {
            std::cout << "the matches were: ";
            for (unsigned i = 0; i < matches.size(); i++) {
                std::cout << "index = " << i << " [";
                std::cout << matches[i] << "] " << std::endl;
            }
        }

        std::cout << std::endl;
        std::cout << "Enter line > ";
    }

    return 0;
}
