#include "last_result.h"

namespace seagame
{


LastResult::LastResult() 
	: _status(SkillResultStatus::NONE)
{    }

SkillResultStatus 
LastResult::get() const noexcept
{ return this->_status; }

void 
LastResult::set(SkillResultStatus _status) noexcept
{
	this->_status = _status;

}

} // seagame


std::ostream& 
operator<<(std::ostream& os, seagame::SkillResultStatus _s)
{
    switch (_s)
    {
    case seagame::SkillResultStatus::FOUND_SHIP:
        os << "Found ship";
        break;

    case seagame::SkillResultStatus::NOT_FOUND_SHIP:
        os << "Not found ship";
        break;

    case seagame::SkillResultStatus::SUCCESS:
        os << "Successful";
        break;

    case seagame::SkillResultStatus::NONE:
        os << "None status";
        break;

    default:
        throw std::logic_error("Bad skill name");

    }

	return os;

}
