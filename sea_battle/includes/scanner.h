
#pragma once


#ifndef _SCANNER_H
#define _SCANNER_H

#include <vector>

#include "unit.h"
#include "field.h"
#include "skill.h"

namespace seagame
{

class Scanner : public Skill
{
public:
    explicit Scanner(std::shared_ptr<LastResult> _last_res, const Unit &_unit);
    Scanner();

    void use(Field &_fd) override;

    std::shared_ptr<LastResult> result() const override;

    SkillName skillname() const noexcept override;

    std::shared_ptr<LastResult> result() const override;
    
    ~Scanner() override = default;

private:
    Unit _unit;
    std::shared_ptr<LastResult> _result;

};

} // seagame


#endif // _SCANNER_H
