#include "double_attack.h"

namespace seagame
{

DoubleAttack::DoubleAttack(std::shared_ptr<LastResult> _last_res, const Unit &_unit)
    : _unit(_unit), _result(_last_res)
{}

DoubleAttack::DoubleAttack()
    : _unit(), _result(std::make_shared<LastResult>())
{}

void DoubleAttack::use(Field &_fd)
{
    std::equal_to<Unit> eq;

    if (eq(this->_unit, Unit()))
        throw std::invalid_argument("Don't setup unit for DoubleHit");
    
    _fd.shot(this->_unit);

    try { _fd.shot(this->_unit); }
    catch (std::invalid_argument) {    }

    this->_result->set(SkillResultStatus::SUCCESS);
}

SkillName DoubleAttack::skillname() const noexcept
{
    return SkillName::DOUBLEATTACK;
}

std::shared_ptr<LastResult> DoubleAttack::result() const
{
    return this->_result;
}

} // seagame
