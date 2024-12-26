#pragma once


#ifndef _RANDOM_ATTACK_FACTORY_H
#define _RANDOM_ATTACK_FACTORY_H

#include <memory>

#include "skill_factory.h"
#include "random_attack.h"

namespace seagame
{

class RangomAttackFactory : public SkillFactory
{
public:
    RangomAttackFactory(std::shared_ptr<LastResult> _last_res);
    RangomAttackFactory();

    std::shared_ptr<Skill> create(const Unit& _unit = Unit()) override;

    SkillName skillname() const noexcept override;

    ~RangomAttackFactory() override = default;

private:
    std::shared_ptr<LastResult> _last_res;

};

} // seagame


#endif // _RANDOM_ATTACK_FACTORY_H