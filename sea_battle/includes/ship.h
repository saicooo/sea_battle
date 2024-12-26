#pragma once


#ifndef _SHIP_H
#define _SHIP_H

#include <cstdint>
#include <vector>
#include <string>

namespace seagame
{

class ShipManager;

class Ship
{
    friend ShipManager;

public:
    enum Orientation
    {
        HORIZONTAL,
        VERTICAL
    };
    
    enum Integrity
    {
        WHOLE = 2,
        HALF_DESTROYED = 1,
        DESTROYED = 0
    };
    
    enum Len
    {
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4
    };

private:
    std::uint64_t _id;
    Len _len;
    Orientation _orientation;
    std::vector<Integrity> _segments;

    explicit Ship(Len _len, Orientation _orie);
    explicit Ship(Len _len);
    Ship();

public:
    Ship(const Ship &other);
    Ship(Ship &&other) noexcept;

    ~Ship() = default;

    Ship& operator=(const Ship &other);
    Ship& operator=(Ship &&other) noexcept;

    void hit(std::uint8_t _i);
    bool is_destroyed() const noexcept;
    
    std::uint64_t id() const noexcept;
    const Len& len() const noexcept;
    const Orientation& orientation() const noexcept;
    const std::vector<Integrity>& segments() const noexcept;

};

} // seagame


namespace std
{

template <>
struct hash<seagame::Ship>
{
    std::size_t operator()(const seagame::Ship& u) const;
};

template <>
struct equal_to<seagame::Ship>
{
    bool operator()(const seagame::Ship& lhs, const seagame::Ship& rhs) const;
};

template <>
struct hash<std::reference_wrapper<seagame::Ship>>
{
    std::size_t operator()(const std::reference_wrapper<seagame::Ship>& u) const;
};

template <>
struct equal_to<std::reference_wrapper<seagame::Ship>>
{
    bool operator()(const std::reference_wrapper<seagame::Ship>& lhs, const std::reference_wrapper<seagame::Ship>& rhs) const;
};

} // std


#endif // _SHIP_H
