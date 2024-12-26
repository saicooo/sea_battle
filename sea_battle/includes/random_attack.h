#pragma once


#ifndef _RANDOM_ATTACK_H
#define _RANDOM_ATTACK_H

#include <random>

#include "unit.h"
#include "field.h"
#include "skill.h"

namespace seagame
{

class RandomAttack : public Skill
{
private:
    std::random_device rd;
    std::shared_ptr<LastResult> _result;

public:
    RandomAttack(std::shared_ptr<LastResult> _last_res);
    RandomAttack();

    void use(Field &_fd) override;

    SkillName skillname() const noexcept override;

    std::shared_ptr<LastResult> result() const override;

    ~RandomAttack() override = default;

private:
    Unit __get_random_unit_of_ship(const Field &_fd) noexcept;
    std::uint8_t __get_random_index_of_segments(const Ship &_ship) noexcept;

};

} // seagame


#endif // _RANDOM_ATTACK_H