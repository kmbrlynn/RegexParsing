// Copyright (C) Kim Douglas 2015
// Based on demo regex code: 
//      Copyright (C) 2015 Fred Martin, fredm@cs.uml.edu for 91.204 Computing IV
//      Thu Apr 16 11:08:45 2015

#include <boost/regex.hpp>
#include "boost/date_time/posix_time/posix_time.hpp"
#include "boost/date_time/gregorian/gregorian.hpp"
#include <exception>
#include <stdexcept>
#include <fstream>
#include <iostream>
#include <string>
#include "Regex.hpp"

using std::cin;
using std::cout;
using std::endl;
using std::string;
using namespace boost::posix_time;
using namespace boost::gregorian;

const int DATE_TIME = 1;
const int MILLI = 4;
const int BOOT_STARTED = 6;
const int BOOT_ENDED = 7;

int main(int argc, char* argv[]) {
    std::string in_filename = argv[1];
    std::string out_filename = in_filename + ".rpt";
    std::ifstream inf;
    std::ofstream outf;

    std::string line_str;
    boost::regex re;
    int line_num = 1;
    bool is_booting = false;

    std::string regex_str =        //   whole line                  [0]
                                   //   date/time                   [1]
        "([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2})"        
                                   // subgroup ---------------------- [2]
        "((: )|"                   //   empty                       [3]
        ".([0-9]{3}))"             //   mil                         [4]
                                   // subgroup ---------------------- [5]
        "((.*log.c.166.*)|"        //   boot start                  [6]
        "(.*oejs.Abstr.*))";       //   boot end                    [7]

    try {
        re = boost::regex(regex_str); 
    } catch (boost::regex_error& exc) {
        cout << "Regex constructor failed with code " << exc.code() << endl;
        exit(1);
    }

    outf.open(out_filename);
    if (!outf.is_open()) {
        std::string outf_err = "Unable to create file: " + out_filename;
        throw std::runtime_error(outf_err);
    }

    inf.open(in_filename);
    if (inf.is_open()) {
        // holds boot start & end times
        ptime t1, t2;

        while (getline(inf, line_str)) { 
            boost::smatch matches;
            boost::regex_match(line_str, matches, re); 

            if (matches[0].matched) {
                // for additional time precision, uncomment the rest of line:
                string time_str = matches[DATE_TIME]/*+ "." + matches[MILLI]*/;
                ptime t(time_from_string(time_str));

                // check for an incomplete boot
                if (matches[BOOT_STARTED] != "" && is_booting)
                    outf << "*** Incomplete boot ***" << endl;            

                // "log.c.166" was found - means boot has started
                if (matches[BOOT_STARTED] != "" ) {
                    is_booting = true;   
                    t1 = t;
                    outf << endl << "=== Device boot ===" << endl;              
                    outf << line_num << "(" << in_filename << "): " << time_str;
                    outf << " Boot Start" << endl;
                }
            
                // "oejs.Abstr" was found - means boot has ended
                if (matches[BOOT_ENDED] != "") { 
                    is_booting = false;
                    t2 = t;
                    outf << line_num << "(" << in_filename << "): " << time_str;
                    outf << " Boot Completed" << endl;
 
                    time_duration td;
                    td = t2 - t1;
                    outf << "\tBoot time: " << td.total_milliseconds() << "ms";
                    outf << endl;
                }
            }

            line_num++;
        }

        inf.close();
        outf.close();
    
    } else {
        std::string inf_err = "Unable to open file: " + in_filename;
        throw std::runtime_error(inf_err);
    }

    return 0;
}

