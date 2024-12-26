#include "double_attack_factory.h"


namespace seagame
{

DoubleAttackFactory::DoubleAttackFactory(std::shared_ptr<LastResult> _last_res)
    : _last_res(_last_res)
{    }

DoubleAttackFactory::DoubleAttackFactory()
    : DoubleAttackFactory(std::make_shared<LastResult>())
{    }

std::shared_ptr<Skill> DoubleAttackFactory::create(const Unit &_unit)
{ return std::make_shared<DoubleAttack>(this->_last_res, _unit); }


SkillName DoubleAttackFactory::skillname() const noexcept
{ return SkillName::DOUBLEATTACK; }

} // seagame