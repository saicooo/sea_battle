#pragma once


#ifndef _DOUBLE_ATTACK_FACTORY_H
#define _DOUBLE_ATTACK_FACTORY_H

#include <memory>

#include "skill_factory.h"
#include "double_attack.h"

namespace seagame
{

class DoubleAttackFactory : public SkillFactory
{
public:
    DoubleAttackFactory(std::shared_ptr<LastResult> _last_res);
    DoubleAttackFactory();

    std::shared_ptr<Skill> create(const Unit& _unit) override;

    SkillName skillname() const noexcept override;

    ~DoubleAttackFactory() override = default;

private:
    std::shared_ptr<LastResult> _last_res;

};

} // seagame


#endif // _DOUBLE_ATTACK_FACTORY_H