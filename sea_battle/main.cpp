#include "ship_manager.h"
#include "field.h"
#include "ship.h"
#include "unit.h"
#include "skill_name.h"

#include <memory>
#include <iostream>

#include "skill_manager.h"
#include "placement_error.h"

using Unit = seagame::Unit;
using SkillName = seagame::SkillName;


int main()
{
   seagame::ShipManager sm;

    try
    {
        sm = seagame::ShipManager({
            seagame::Ship::Len::TWO,
            seagame::Ship::Len::FOUR
        });
    }
    catch (const std::invalid_argument& err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    }


    std::uint64_t i = sm.new_ship(
        seagame::Ship::Len::THREE,
        seagame::Ship::Orientation::VERTICAL
    );


    seagame::Field field(1, 1);

    try
    {
        field = seagame::Field(5, 5);
    } catch (const std::invalid_argument& err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    }


    try
    {
        field.add_ship(sm[i], Unit(2, 1));
        field.add_ship(sm[0], Unit(4, 2));
        field.add_ship(sm[1], Unit(2, 5));
    } catch (const seagame::PlacementError &err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    }
    

    try
    {
        field.shot(Unit(1, 1));
    } catch (const std::invalid_argument &err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    }

    
    seagame::SkillManager skill_manager;
    
    field.setup_react_for_ship_destroy([&skill_manager](){
        skill_manager.add_skill();
    });

    std::shared_ptr<seagame::SkillFactory> _f_skill;
    std::shared_ptr<seagame::Skill> _skill;
    for (std::size_t i = 0; i < 3; ++i)
    {
        try
        {
            _f_skill = skill_manager.pop_skill();
        } catch (const seagame::PopError &err)
        {
            std::cerr << "Error: " << err.what() << std::endl;
            continue;
        }

        _skill = _f_skill->create(Unit(2, 3));
        
        try
        {
            _skill->use(field);
        } catch (const std::invalid_argument &err)
        {
            std::cerr << "Error: " << err.what() << std::endl;
        }

        std::cout << _skill->result()->get() << std::endl;
        
    }

    skill_manager.add_skill(SkillName::DOUBLEATTACK);
    skill_manager.add_skill(SkillName::DOUBLEATTACK);

    try
    {
        skill_manager.pop_skill()->create(Unit(4, 2))->use(field);
        skill_manager.pop_skill()->create(Unit(5, 2))->use(field);
    
    } catch (const std::invalid_argument &err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    } catch (const seagame::PopError &err)
    {
        std::cerr << "Error: " << err.what() << std::endl;
    }
    
    std::cout << "-----" << std::endl;
    
    std::cout << sm[i].segments()[0] << ' ';
    std::cout << sm[i].segments()[1] << ' ';
    std::cout << sm[i].segments()[2] << std::endl;

    std::cout << sm[0].segments()[0] << ' ';
    std::cout << sm[0].segments()[1] << std::endl;

    std::cout << sm[1].segments()[0] << ' ';
    std::cout << sm[1].segments()[1] << ' ';
    std::cout << sm[1].segments()[2] << ' ';
    std::cout << sm[1].segments()[3] << std::endl;

    std::cout << "-----" << std::endl;

    std::cout << skill_manager.empty() << std::endl;

    std::cout << "-----" << std::endl;


    return 0;

}