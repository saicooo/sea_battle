#include "ship_manager.h" 

namespace seagame 
{ 

ShipManager::ShipManager(const ArrayOfLens &_lens) 
{ 
    this->__construct(_lens); 
} 

ShipManager::ShipManager() : ShipManager({}) 
{    } 

ShipManager::ShipManager(const ShipManager &other) 
    : _container(other.container()) 
{    } 

ShipManager::ShipManager(ShipManager &&other) noexcept 
    : _container(std::move(other._container)) 
{    } 

ShipManager& ShipManager::operator=(const ShipManager &other) 
{ 
    if (this != &other) 
    { 
        this->_container = other.container(); 
    } 
    return *this; 
} 

ShipManager& ShipManager::operator=(ShipManager &&other) noexcept 
{ 
    if (this != &other) 
    { 
        this->_container = std::move(other._container); 
    } 
    return *this; 
} 

std::uint64_t ShipManager::new_ship(Ship::Len _len, Ship::Orientation _orie) 
{ 
    Ship _ship(_len, _orie); 
    _ship._id = this->amt(); 
    this->_container.push_back(_ship); 
    return _ship._id; 
} 

std::uint64_t ShipManager::new_ship(Ship::Len _len) 
{ return this->new_ship(_len, Ship::Orientation::HORIZONTAL); } 

Ship& ShipManager::operator[](std::uint64_t _id) 
{ return this->_container.at(_id); } 

const Ship& ShipManager::operator[](std::uint64_t _id) const 
{ return this->_container.at(_id); } 

const std::vector<Ship>& ShipManager::container() const noexcept 
{ return this->_container; } 

std::size_t ShipManager::amt() const noexcept 
{ return this->_container.size(); } 

} // seagame