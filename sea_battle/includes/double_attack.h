#pragma once


#ifndef _DOUBLE_ATTACK_H
#define _DOUBLE_ATTACK_H

#include "unit.h"
#include "field.h"
#include "skill.h"

namespace seagame
{

class DoubleAttack : public Skill
{
public:
    DoubleAttack(std::shared_ptr<LastResult> _last_res, const Unit &_unit);
    DoubleAttack();

    void use(Field &_fd) override;

    SkillName skillname() const noexcept override;

    std::shared_ptr<LastResult> result() const override;

    ~DoubleAttack() override = default;

private:
    Unit _unit;
    std::shared_ptr<LastResult> _result;

};

} // seagame


#endif // _DOUBLE_ATTACK_H