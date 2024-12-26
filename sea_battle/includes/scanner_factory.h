#pragma once


#ifndef _SCANNER_FACTORY_H
#define _SCANNER_FACTORY_H

#include <memory>

#include "skill_factory.h"
#include "scanner.h"

namespace seagame
{

class ScannerFactory : public SkillFactory
{
public:
    explicit ScannerFactory(std::shared_ptr<LastResult> _last_res);
    ScannerFactory();

    std::shared_ptr<Skill> create(const Unit& _unit) override;

    SkillName skillname() const noexcept override;

    ~ScannerFactory() override = default;

private:
    std::shared_ptr<LastResult> _last_res;

};

} // seagame


#endif // _SCANNER_FACTORY_H