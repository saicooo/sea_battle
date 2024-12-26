#pragma once


#ifndef _LAST_SKILL_RESULT_H
#define _LAST_SKILL_RESULT_H

#include <cstdint>
#include <iostream>

namespace seagame
{

enum  SkillResultStatus
{
    NONE,
    FOUND_SHIP,
    NOT_FOUND_SHIP,
    SUCCESS
};

class LastResult
{
public:
	LastResult();

    SkillResultStatus get() const noexcept;

    void set(SkillResultStatus _status) noexcept;

	~LastResult() = default;

private:
	SkillResultStatus _status;

};

} // seagame


std::ostream& operator<<(std::ostream& os, seagame::SkillResultStatus _s);


#endif // _LAST_SKILL_RESULT_H
