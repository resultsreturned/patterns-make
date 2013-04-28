// Generated by Bisonc++ V4.01.00 on Thu, 02 Aug 2012 10:25:16 -0500

#ifndef OPTIONSparser_h_included
#define OPTIONSparser_h_included

// $insert baseclass
#include "OptionsParserbase.h"
// $insert scanner.h
#include "OptionsScanner.h"

#undef OptionsParser
class OptionsParser: public OptionsParserBase
{
    Options* _options;
    // $insert scannerobject
    OptionsScanner d_scanner;

    public:
        OptionsParser(Options* options, std::istream &in = std::cin):
        _options(options),d_scanner(in){}

        int parse();

    private:
        void error(char const *msg);    // called on (syntax) errors
        int lex();                      // returns the next token from the
                                        // lexical scanner.
        void print();                   // use, e.g., d_token, d_loc

    // support functions for parse():
        void executeAction(int ruleNr);
        void errorRecovery();
        int lookup(bool recovery);
        void nextToken();
        void print__();
};

#endif
