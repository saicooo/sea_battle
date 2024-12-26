#pragma once


#ifndef _SKILL_H
#define _SKILL_H

#include <memory>

#include "unit.h"
#include "last_result.h"
#include "skill_name.h"

namespace seagame
{

class Field;

class Skill 
{
public:
    virtual void use(Field &_fd) = 0;

    virtual std::shared_ptr<LastResult> result() const = 0;

    virtual SkillName skillname() const = 0;

    virtual ~Skill() = 0;

};

} // seagame


#endif // _SKILL_H