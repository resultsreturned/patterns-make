// main.cpp
// A main function that reports help and version info 
//
// Copyright (C) 2013 Mara Kim
//
// This program is free software: you can redistribute it and/or modify it under
// the terms of the GNU General Public License as published by the Free Software
// Foundation, either version 3 of the License, or (at your option) any later
// version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
// FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
// details.
//
// You should have received a copy of the GNU General Public License along with
// this program. If not, see http://www.gnu.org/licenses/.


#include "Initializer.h"
#include "Options.h"
#include "Foo.h"
#include <iostream>

int main(int argc, char** argv) {
    // Initialize
    // argcount, argvector, argument usage, description
    Initializer init(argc, argv, "ARG0 ARG1",
                     "A Barebones C++ Project\v"
                     "Be sure to provide two non-option arguments!");

    // Describe options
    init.option("foo", 'f', "MYFOO", "Set MYFOO",
                [&] (char* arg, Initializer::state* state) -> int {
                    if(arg)
                        Options::Instance()->set(Project::FOO,arg);
                    return 0;
                });
    init.option("switch", 's', 0, "Set SWITCH = true",
                [&] (char* arg, Initializer::state* state) -> int {
                    Options::Instance()->set(Project::SWITCH,true);
                    return 0;
                });
    init.option("loop", 'l', 0, "Run an infinite loop",
                [&] (char* arg, Initializer::state* state) -> int {
                    Options::Instance()->set(Project::LOOP,true);
                    return 0;
                });
    init.option("crash", 'c', 0, "Cause a crash",
                [&] (char* arg, Initializer::state* state) -> int {
                    Options::Instance()->set(Project::CRASH,true);
                    return 0;
                });
    init.option("num", 'n', "NUM", "Set MYNUM = NUM",
                [&] (char* arg, Initializer::state* state) -> int {
                    if(Options::Instance()->assign(Project::MYNUM,arg))
                        return 0;
                    else {
                        Initializer::error(state,"Error converting '%s' to double", arg);
                        return 1;
                    }
                });
    init.event(Initializer::ARG, // Handle arguments
               [&] (char* arg, Initializer::state* state) -> int {
                   if(state->arg_num >= 2)
                       return Initializer::UNKNOWN;
                   Options::Instance()->set(Project::ARGUMENTS,state->arg_num,arg);
                   return 0;
               });
    init.event(Initializer::END, // Check argument count
               [&] (char* arg, Initializer::state* state) -> int {
                   if(state->arg_num < 2)
                       Initializer::usage(state);
                   return 0;
               });

    // Parse arguments
    init.parse();

    // run program

    std::cout << "\nBegin Example:\n\n";

    std::cout << Options::Instance()->get(Project::GREETING) << std::endl;
    Foo foo;
    foo.bar();

    if(Options::Instance()->get(Project::CRASH)) {
        int* i = new int(10);
        delete i;
        delete i;
    }
    if(Options::Instance()->get(Project::LOOP))
        std::cout << "Looping indefinitely..." << std::endl;
    while(Options::Instance()->get(Project::LOOP)) {
    }

    return 0;
}
