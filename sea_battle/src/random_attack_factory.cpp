#include "random_attack_factory.h"


namespace seagame
{

RangomAttackFactory::RangomAttackFactory(std::shared_ptr<LastResult> _last_res)
    : _last_res(_last_res)
{    }

RangomAttackFactory::RangomAttackFactory()
    : RangomAttackFactory(std::make_shared<LastResult>())
{    }

std::shared_ptr<Skill> RangomAttackFactory::create(const Unit &_unit)
{ return std::make_shared<RandomAttack>(this->_last_res); }


SkillName RangomAttackFactory::skillname() const noexcept
{ return SkillName::DOUBLEATTACK; }

} // seagame