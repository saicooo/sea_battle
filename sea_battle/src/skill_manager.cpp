
#include "skill_manager.h"

namespace seagame
{

SkillManager::SkillManager()
    : _last_res(std::make_shared<LastResult>()),
      _double_attack_factory(std::make_shared<DoubleAttackFactory>(_last_res)),
      _random_attack_factory(std::make_shared<RangomAttackFactory>(_last_res)),
      _scanner_factory(std::make_shared<ScannerFactory>(_last_res))
{
    for (const auto &skillname : this->__get_random_skills())
        this->add_skill(skillname);

}


SkillManager::SkillManager(const SkillManager &other)
    : _last_res(other._last_res), 
      _skill_factories(other._skill_factories)
{    }

SkillManager::SkillManager(SkillManager &&other) noexcept
    : _last_res(std::move(other._last_res)), 
      _skill_factories(std::move(other._skill_factories))
{    }


SkillManager& 
SkillManager::operator=(const SkillManager &other)
{
    if (this != &other)
    {
        this->_last_res = other._last_res;
        this->_skill_factories = other._skill_factories;
    }
    return *this;
}

SkillManager&
SkillManager::operator=(SkillManager &&other) noexcept
{
    if (this != &other)
    {
        this->_last_res = std::move(other._last_res);
        this->_skill_factories = std::move(other._skill_factories);
    }
    return *this;
}

void 
SkillManager::add_skill(SkillName _sname)
{
    std::shared_ptr<SkillFactory> _sf;

    switch (_sname)
    {
        case SkillName::DOUBLEATTACK:
            _sf = this->_double_attack_factory;
            break;

        case SkillName::RANDOMATTACK:
            _sf = this->_random_attack_factory;
            break;

        case SkillName::SCANNER:
            _sf = this->_scanner_factory;
            break;

        default:
            throw std::logic_error("bad skill name");

    }
    this->_skill_factories.push(_sf);
}

void 
SkillManager::add_skill()
{
    return this->add_skill(
        this->__get_random_skills()[0]
    );
}

void custom_shuffle(std::vector<SkillName>& vec) {
    std::random_device rd;
    std::mt19937 g(rd());
    for (size_t i = vec.size() - 1; i > 0; --i) {
        std::uniform_int_distribution<> dis(0, i);
        std::swap(vec[i], vec[dis(g)]);
    }
}


std::vector<SkillName> SkillManager::__get_random_skills() const noexcept
{
    std::vector<SkillName> _set_skills = {
        SkillName::DOUBLEATTACK,
        SkillName::RANDOMATTACK,
        SkillName::SCANNER
    };

    custom_shuffle(_set_skills);

    return _set_skills;

}

SkillName SkillManager::front() const noexcept
{ return this->_skill_factories.front()->skillname(); }

std::shared_ptr<SkillFactory> SkillManager::pop_skill()
{
    if (this->empty())
        throw PopError("Skills not found");

    std::shared_ptr<SkillFactory> _front_skill = this->_skill_factories.front();
    this->_skill_factories.pop();
    return _front_skill;
}


bool SkillManager::empty() const noexcept
{ return this->_skill_factories.empty(); }

std::shared_ptr<LastResult> SkillManager::last_result() const noexcept
{ return this->_last_res; }

} // seagame

