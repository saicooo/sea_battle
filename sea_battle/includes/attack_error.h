#pragma once


#ifndef _ATTACK_ERROR_H
#define _ATTACK_ERROR_H

#include <stdexcept>

namespace seagame
{

class AttackError : public std::invalid_argument
{
public:
    AttackError(const std::string &msg)
        : std::invalid_argument(msg)
    {    }

};

} // seagame


#endif // _ATTACK_ERROR_H