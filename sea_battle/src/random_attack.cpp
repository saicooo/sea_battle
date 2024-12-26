#include "random_attack.h"

namespace seagame
{

RandomAttack::RandomAttack(std::shared_ptr<LastResult> _last_res)
    : _result(_last_res)
{}

RandomAttack::RandomAttack()
    : _result(std::make_shared<LastResult>())
{}

void RandomAttack::use(Field &_fd)
{
    Ship &_ship = _fd.get_deployed_ships().at(
        this->__get_random_unit_of_ship(_fd)
    );

    _ship.hit(
        this->__get_random_index_of_segments(_ship)
    );

    if (_ship.is_destroyed())
        _fd.get_react_for_ship_destroy()();

    this->_result->set(SkillResultStatus::SUCCESS);
}

SkillName RandomAttack::skillname() const noexcept
{
    return SkillName::RANDOMATTACK;
}

std::shared_ptr<LastResult> RandomAttack::result() const
{
    return this->_result;
}

} // seagame
