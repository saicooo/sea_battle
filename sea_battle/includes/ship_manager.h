#pragma once

#ifndef _SHIP_MANAGER_H
#define _SHIP_MANAGER_H

#include <vector>
#include <cstdint>
#include <type_traits>

#include "ship.h"

namespace seagame 
{ 

class ShipManager 
{ 
public: 
    using ArrayOfLens = std::initializer_list<Ship::Len>; 

private: 
    std::vector<Ship> _container; 
    // If ships need identifiers, use the indices in the vector as identifiers

public: 
    template <class T, 
    typename std::void_t< 
        typename std::remove_reference<T>::type::value_type, 
        typename std::remove_reference<T>::type::iterator, 
        typename std::remove_reference<T>::type::const_iterator 
    >* = nullptr> 
    ShipManager(const T &lens) 
    { 
        static_assert(std::is_same< 
            typename std::remove_reference<T>::type::value_type, 
            Ship::Len 
        >::value, "Container must contain seagame::Ship::Len"); 

        this->__construct(lens); 
    } 

    ShipManager(const ArrayOfLens &lens); 

    ShipManager(); 

    ShipManager(const ShipManager &other); 
    ShipManager(ShipManager &&other) noexcept; 

    ~ShipManager() = default; 

    ShipManager& operator=(const ShipManager &other); 
    ShipManager& operator=(ShipManager &&other) noexcept; 

    std::uint64_t new_ship(Ship::Len len, Ship::Orientation orientation); 
    std::uint64_t new_ship(Ship::Len len); 

    Ship& operator[](std::uint64_t id); 
    const Ship& operator[](std::uint64_t id) const; 

    const std::vector<Ship>& container() const noexcept; 
    std::size_t amt() const noexcept; 

private: 
    template <class T> 
    inline void __construct(const T &lens) 
    { 
        for (const auto &len : lens) 
            this->new_ship(len); 
    } 

}; 

} // seagame 

#endif // _SHIP_MANAGER_H