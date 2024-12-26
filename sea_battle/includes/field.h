#pragma once

#ifndef _FIELD_H
#define _FIELD_H

#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <stdexcept>

#include "unit.h"
#include "ship.h"

namespace seagame 
{ 

class Field 
{ 
public: 
    class Size 
    { 
    public: 
        Size(std::uint64_t m, std::uint64_t n); 

        Size(const Size &other); 
        Size(Size &&other) noexcept; 

        ~Size() = default; 

        Size& operator=(const Size &other); 
        Size& operator=(Size &&other) noexcept; 

        std::uint64_t m() const noexcept; 
        std::uint64_t n() const noexcept; 

    private: 
        std::uint64_t _m; 
        std::uint64_t _n; 
    }; 

private: 
    std::unordered_map<Unit, std::reference_wrapper<Ship>> _deployed_ships; 
    std::unordered_set<Unit> _hit_units; 
    std::unordered_set<Unit> _unusable_units; 

    Size _size; 

    std::function<void()> _react_for_ship_destroy;

public: 
    Field(std::uint64_t m, std::uint64_t n); 
    explicit Field(Size size); 

    Field(const Field &other); 
    Field(Field &&other) noexcept; 

    ~Field() = default; 

    Field& operator=(const Field &other); 
    Field& operator=(Field &&other) noexcept; 

    void add_ship(Ship &ship, const Unit &unit); 
    void add_ship(Ship &ship, std::uint64_t x, std::uint64_t y); 

    void shot(const Unit &unit); 
    void shot(std::uint64_t x, std::uint64_t y); 

    const Size& size() const noexcept; 

    void setup_react_for_ship_destroy(std::function<void()> _funct) noexcept;
    std::function<void()> get_react_for_ship_destroy() const noexcept;

    std::unordered_map<Unit, std::reference_wrapper<Ship>>& get_deployed_ships() noexcept;

    Unit __get_unit_of_valid_ship(const Unit &_unit, std::uint8_t &_i);
private:

    void __block_unit(const Unit &unit, const Ship::Orientation &orie, bool flag); 
    void __block_units(const Unit &unit, const Ship &ship, bool flag); 
    void __block_units_for_add(const Unit &unit, const Ship &ship); 
    void __block_units_for_hit(const Unit &unit, const Ship &ship); 

    bool __is_valid_unit(const Unit &u) const noexcept; 
    bool __is_valid_unit(std::uint64_t x, std::uint64_t y) const noexcept; 

    bool __is_same_ship(const Unit &lu, const Unit &unit, std::uint8_t offset); 

    Unit __get_lu_seg_of_ship(const Unit &unit, const Ship::Orientation &orie, std::uint8_t &i); 
}; 

} // seagame 

#endif // _FIELD_H