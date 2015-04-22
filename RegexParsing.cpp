// Copyright Kim Douglas 2015
// based on: 
//      demo regex code
//      Copyright (C) 2015 Fred Martin, fredm@cs.uml.edu for 91.204 Computing IV
//      Thu Apr 16 11:08:45 2015

#include <boost/regex.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include <iostream>
#include <string>
#include "Regex.hpp"

using std::string;
using std::cin;
using std::cout;
using std::endl;
using namespace boost::posix_time;
using namespace boost::gregorian;

const int DATE_TIME = 1;
const int MILLI = 4;
const int BOOT_STARTED = 6;
const int BOOT_ENDED = 7;

int main(int argc, char* argv[]) {
    string line_str, regex_str;
    boost::regex re;
    int line_num = 1;
    bool is_booting = false;

    cout << "If you get errors when constructing the regex, see:\n";
    cout << "http://www.boost.org/doc/libs/1_58_0/";
    cout << "boost/regex/v4/error_type.hpp\n" << endl;

    regex_str =                    //   line           [0]
        "([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2})"        
                                   //   date/time      [1]
                                   // subgroup ----------- [2]
        "((: )|"                   //   empty          [3]
        ".([0-9]{3}))"             //   mil            [4]
                                   // subgroup ------------[5]
        "((.*log.c.166.*)|"        //   boot start     [6]
        "(.*oejs.Abstr.*))";       //   boot end       [7]

    try {
        re = boost::regex(regex_str); 
        cout << "mark_count() is: " << re.mark_count() << endl;
    } catch (boost::regex_error& exc) {
        cout << "Regex constructor failed with code " << exc.code() << endl;
        exit(1);
    }

    while (getline(cin, line_str)) {
        line_num++;
        
        boost::smatch matches;
        boost::regex_match(line_str, matches, re); 
        ptime t1, t2;

        if (matches[0].matched) {
            string time_str = matches[DATE_TIME] + "." + matches[MILLI];
            cout << time_str;
            ptime t(time_from_string(time_str));

            // check for an incomplete boot
            if (matches[BOOT_STARTED] != "" && (is_booting ==true || EOF))
                cout << "*** Incomplete boot ***" << endl;            

            // "log.c.166" was found - means boot has started
            if (matches[BOOT_STARTED] != "" ) {
                is_booting = true;   
                t1 = t;
                cout << endl << "=== Device boot ===" << endl;              
                cout << line_num << "(device-log): " << t1;
                cout << " Boot started" << endl;
            }
            
            // "oejs.Abstr" was found - means boot has ended
            if (matches[BOOT_ENDED] != "") { 
                is_booting = false;
                t2 = t;
                cout << line_num << "(device-log): " << t2;
                cout << " Boot completed" << endl;
            }
/*
            cout << "Line number is: " << line_num << endl;
            cout << "the matches are: " << endl;
            for (unsigned i = 0; i < matches.size(); i++) {
                cout << endl << "index = " << i << "[" << matches[i] << "] ";
            }
            cout << endl << endl;
*/      }
    }

    return 0;
}



















