#pragma once


#ifndef _PLACEMENT_ERROR_H
#define _PLACEMENT_ERROR_H

#include <stdexcept>

namespace seagame
{

class PlacementError : public std::invalid_argument
{
public:
    PlacementError(const std::string &msg)
        : std::invalid_argument(msg)
    {    }

};

} // seagame


#endif // _PLACEMENT_ERROR_H
