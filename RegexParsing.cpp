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

const int YEAR = 1;
const int MONTH = 2;
const int DAY = 3;
const int HOUR = 4;
const int MIN = 5;
const int SEC = 6;
const int MILLI = 9;
const int BOOT_STARTED = 11;
const int BOOT_ENDED = 12;

int main(int argc, char* argv[]) {
    std::string line_str, regex_str;
    boost::regex re;
    int line_num = 1;
    bool is_booting = false;

    cout << "If you get errors when constructing the regex, see:\n";
    cout << "http://www.boost.org/doc/libs/1_58_0/";
    cout << "boost/regex/v4/error_type.hpp\n" << endl;

    regex_str = 
        "([0-9]{4})-"          // year  [1]
        "([0-9]{2})-"          // month [2]
        "([0-9]{2}) "          // day   [3]
        "([0-9]{2}):"          // hour  [4]
        "([0-9]{2}):"          // min   [5]
        "([0-9]{2})"           // sec   [6]   
                               // ========== subgroup [7]
        "((: )|"               // empty [8]
        ".([0-9]{3}))"         // milli [9]
                               // ========== subgroup [10]
        "((.*log.c.166.*)|"    // start [11]
        "(.*oejs.Abstr.*))";   // ended [12]

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
            // get the date
            string date_iso = matches[YEAR] + matches[MONTH] + matches[DAY];
            date d(from_undelimited_string(date_iso));
            
            // get the time
            string time_iso = date_iso + "T" + 
                         matches[HOUR] + matches[MIN] + matches[DAY];
            ptime t(from_iso_string(time_iso));

            // "log.c.166" was found - means boot has started
            if (matches[BOOT_STARTED] != "") {
                is_booting = true;
                t1 = t;
                cout << endl << line_num << "(device-example-log): " << t;
                cout << " Boot Start" << endl; 
            
            }

            // "oejs.Abstr" was found - means boot has ended
            if (matches[BOOT_ENDED] != "") {
                is_booting = false;
                t2 = t;
                cout << line_num << "(device-example-log): " << t;
                cout << " Boot Completed" << endl; 
            

            }


/*

            cout << "Line number is: " << line_num << endl;
            cout << "the matches are: " << endl;
            for (unsigned i = 0; i < matches.size(); i++) {
                cout << endl << "index = " << i << "[" << matches[i] << "] ";
            }
            cout << endl << endl;
*/
        }
    }

    return 0;
}



















