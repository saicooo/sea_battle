#include "scanner_factory.h"


namespace seagame
{

ScannerFactory::ScannerFactory(std::shared_ptr<LastResult> _last_res)
    : _last_res(_last_res)
{    }

ScannerFactory::ScannerFactory()
    : ScannerFactory(std::make_shared<LastResult>())
{    }

std::shared_ptr<Skill> ScannerFactory::create(const Unit &_unit)
{ return std::make_shared<Scanner>(this->_last_res, _unit); }


SkillName ScannerFactory::skillname() const noexcept
{ return SkillName::DOUBLEATTACK; }

} // seagame
