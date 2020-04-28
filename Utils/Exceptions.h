#ifndef EXCEPTIONS_H_INCLUDED
#define EXCEPTIONS_H_INCLUDED

//
// Exception type thrown when an error occurs during a file read.
//
struct FileErrorException : public exception
{
    const char * what() const throw ()
    {
        return "There was an error reading the file.";
    }
};

#endif // EXCEPTIONS_H_INCLUDED
