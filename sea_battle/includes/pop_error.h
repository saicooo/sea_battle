#pragma once


#ifndef _POP_ERROR_H
#define _POP_ERROR_H

#include <stdexcept>

namespace seagame
{

class PopError : public std::runtime_error
{
public:
    PopError(const std::string &msg)
        : std::runtime_error(msg)
    {    }

};

} // seagame


#endif // _POP_ERROR_H