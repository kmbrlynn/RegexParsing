/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name: Kim Douglas


Hours to complete assignment (optional):


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

 	Yep, I was able to do the whole thing. The boot-start and boot-end
 	lines in my file match the ones in the example file, so it looks ok.

/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/

 	I made one big regex string, separating it into groups, so my 
 	mark_count() is 8. The important ones are: 

 	matches[1] holds a date/time string. ex: 2014-04-23 01:41:30
 	matches[4] holds a milliseconds string, if it exists. ex: 256
 		(see the extra comments section at the bottom for more about this)
 	matches[6] holds a line containing startup indicators
 	matches[7] holds a line containing boot-finished indicators

    std::string regex_str =        //   whole line                  [0]
                                   //   date/time                   [1]
        "([0-9]{4}-[0-9]{2}-[0-9]{2} [0-9]{2}:[0-9]{2}:[0-9]{2})"
                                   // subgroup ---------------------- [2]
        "((: )|"                   //   empty                       [3]
        ".([0-9]{3}))"             //   mil                         [4]
                                   // subgroup ---------------------- [5]
        "((.*log.c.166.*)|"        //   boot start                  [6]
        "(.*oejs.Abstr.*))";       //   boot end                    [7]


/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/

 	My program reads an input file line-by-line, populating the 
 	regex match indices (listed above) as it encounters them. 

 	Two boost::ptime objects are maintained - t1, corresponding to a 
 	boot-start line, and t2, corresponding to a boot-end line. These
 	objects are initially empty.

 	For each line in the file, a boost::regex_match is attempted at 
 	for the whole line, at matches[0]. If this succeeds, it enters a 
 	loop that will figure out what to print. If not, it moves on. 

 	Upon entering the loop, a date/time string is created with data
 	from matches[1], and a boost::ptime object is created from that 
 	string. 

 	If matches[6] is not empty, it means the line contains "log.c.166". 
 	An boolean called 'is_booting' is set to true, and the t1 ptime 
 	object is assigned the date/time from matches[1].

 	On the other hand, if matches[7] is not empty, it means the line
 	contains "oejs.Abstr", indicating an ending boot. The boolean is
 	set to false, and the t2 ptime object is assigned the date/time. 

 	If 'is_booting' is set to true, but it has found "log.c.166", then
 	a boot-end didn't occur, and the appropriate message is printed.

 	The time difference is calculated by subtracting t1 from t2.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/

 	I kept getting a not-a-date-time error when trying to print a 
 	boost::time_duration element. I also had trouble with months 
 	presenting as "Feb" (instead of "02", for example). Tyler, Chadd, and
 	Prof. Grinberg gave me some email tips about using time_duration
 	accessors better, and also about printing strings directly instead
 	of printing boost::ptime objects.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/

 	Mostly what's above.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/

 	For a long time I thought we were supposed to calculate the 
 	milliseconds that are attached to the timestamp on ending-boot lines,
 	and add those milliseconds to the lack of milliseconds (effectively, 
 	zero milliseconds) from the start-boot lines.

 	So, I maintained a separate regex for this in matches[4]. There is
 	the option, in lines 74-75 of my RegexParsing.cpp file, to uncomment
 	a bit of code and add this functionality. This will give a more 
 	precise time difference calculation. 

 	However, the provided example log file only did precision down to 
 	the second - not the millisecond - so I left this commented out. 

 	I feel like I wasted a lot of time on this, but I'm happier with my
 	program because of it, I guess.


