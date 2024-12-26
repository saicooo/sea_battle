#include "scanner.h"

namespace seagame
{

Scanner::Scanner(std::shared_ptr<LastResult> _last_res, const Unit &_unit)
    : _unit(_unit), _result(_last_res)
{}

Scanner::Scanner()
    : _unit(), _result(std::make_shared<LastResult>())
{}

void Scanner::use(Field &_fd)
{
    std::equal_to<Unit> eq;

    if (eq(this->_unit, Unit()))
        throw std::invalid_argument("uninstall data");
    
    if (this->_unit.x() >= _fd.size().m()
     || this->_unit.y() >= _fd.size().n())
        throw std::invalid_argument("bad unit");

    std::uint8_t _i;
    Unit _u;
    Unit _u0;
    
    for (const auto &_i_unit : std::vector<Unit>({
        Unit(this->_unit.x(), this->_unit.y()),
        Unit(this->_unit.x() + 1, this->_unit.y()),
        Unit(this->_unit.x(), this->_unit.y() + 1),
        Unit(this->_unit.x() + 1, this->_unit.y() + 1)
    }))
    {
        _u = _fd.__get_unit_of_valid_ship(_i_unit, _i);

        if (!eq(_u, _u0))
        {
            this->_result->set(SkillResultStatus::FOUND_SHIP);
            return;
        }

    }

    this->_result->set(SkillResultStatus::NOT_FOUND_SHIP);

}

SkillName Scanner::skillname() const noexcept
{
    return SkillName::SCANNER;
}

std::shared_ptr<LastResult> Scanner::result() const
{
    return this->_result;
}

} // seagame
