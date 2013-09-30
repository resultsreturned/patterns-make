// Info.cpp
// Mara Kim
//
// Globals with program information

#include "Info.h"

// Initialize with external macro
const char *const PROGRAM_NAME = __PROGRAM_NAME,
           *const PROGRAM_VERSION = __PROGRAM_VERSION,
           *const REVISION_HASH = __REVISION_HASH,
           *const REVISION_STATUS = __REVISION_STATUS,
           *const PROGRAM_BUG_ADDRESS = __PROGRAM_BUG_ADDRESS;

void print_version(std::ostream& ostream) {
    ostream << PROGRAM_NAME << " " << PROGRAM_VERSION << "\n";
}

void print_revision(std::ostream& ostream) {
    ostream << REVISION_HASH << "\n"
            << REVISION_STATUS << "\n";
}

void print_version(FILE* stream) {
    fputs(PROGRAM_NAME, stream);
    fputc(' ', stream);
    fputs(PROGRAM_VERSION, stream);
    fputc('\n', stream);
}

void print_revision(FILE* stream) {
    fputs(REVISION_HASH , stream);
    fputc('\n', stream);
    fputs(REVISION_STATUS , stream);
    fputc('\n', stream);
}