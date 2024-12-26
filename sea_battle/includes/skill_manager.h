#pragma once


#ifndef _SKILL_MANAGER_H
#define _SKILL_MANAGER_H

#include <queue>
#include <memory>

#include "last_result.h"

#include "double_attack_factory.h"
#include "random_attack_factory.h"
#include "scanner_factory.h"

#include "pop_error.h"


namespace seagame
{

class SkillManager
{
private:
    std::shared_ptr<LastResult> _last_res;
    std::queue<std::shared_ptr<SkillFactory>> _skill_factories;

    std::shared_ptr<DoubleAttackFactory> _double_attack_factory;
    std::shared_ptr<RangomAttackFactory> _random_attack_factory;
    std::shared_ptr<ScannerFactory>_scanner_factory;

public:
    SkillManager();

    SkillManager(const SkillManager &other);
    SkillManager(SkillManager &&other) noexcept;

    ~SkillManager() = default;

    SkillManager& operator=(const SkillManager &other);
    SkillManager& operator=(SkillManager &&other) noexcept;

    void add_skill(SkillName _sname);
    void add_skill();

    SkillName front() const noexcept;

    std::shared_ptr<SkillFactory> pop_skill();

    bool empty() const noexcept;

    std::shared_ptr<LastResult> last_result() const noexcept;

private:
    std::vector<SkillName> __get_random_skills() const noexcept;

};

} // seagame


#endif // _SKILL_MANAGER_H