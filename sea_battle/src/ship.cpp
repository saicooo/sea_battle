#include "../ship.h"

#include <stdexcept>


namespace seagame
{

Ship::Ship(Len _len, Orientation _orie)
    : _len(_len), _orientation(_orie), _id(0)
{
    for (std::uint8_t i = 0; i < _len; ++i)
        this->_segments.push_back(Integrity::WHOLE);
    
}

Ship::Ship(Len _len) 
    : Ship(_len, Ship::Orientation::HORIZONTAL)
{    }

Ship::Ship() 
    : Ship(Ship::Len::ONE)
{    }

Ship::Ship(const Ship &other)
    : _id(other.id()), _len(other.len()), _orientation(other.orientation()), _segments(other.segments())
{    }

Ship::Ship(Ship &&other) noexcept 
    : _id(other._id), _len(other._len), _orientation(other._orientation), _segments(std::move(other._segments))
{    }

Ship& 
Ship::operator=(const Ship &other)
{
    if (this != &other)
    {
        this->_id = other.id();
        this->_len = other.len();
        this->_orientation = other.orientation();
        this->_segments = other.segments();
    }
    return *this;
}

Ship& 
Ship::operator=(Ship &&other) noexcept
{
    if (this != &other)
    {
        this->_id = other._id;
        this->_len = other._len;
        this->_orientation = other._orientation;
        this->_segments = std::move(other._segments);
    }
    return *this;
}

void 
Ship::hit(std::uint8_t _i)
{
    if (_i >= this->_len)
        throw std::out_of_range("bad segment");
    
    switch (this->_segments[_i])
    {
    case Integrity::WHOLE:
        this->_segments[_i] = Integrity::HALF_DESTROYED;
        break;
    
    case Integrity::HALF_DESTROYED:
        this->_segments[_i] = Integrity::DESTROYED;
        break;
    
    case Integrity::DESTROYED:
        throw std::logic_error("bad hit");
    
    default:
        throw std::logic_error("bad Ship::Integrity");
    }
}

bool 
Ship::is_destroyed() const noexcept
{
    for (const auto &_seg : this->_segments)
        if (_seg != Integrity::DESTROYED)
            return false;

    return true;

}


std::uint64_t 
Ship::id() const noexcept
{ return this->_id; }

const Ship::Len&
Ship::len() const noexcept
{ return this->_len; }

const Ship::Orientation& 
Ship::orientation() const noexcept
{ return this->_orientation; }

const std::vector<Ship::Integrity>& 
Ship::segments() const noexcept
{ return this->_segments; }

} // seagame


namespace std
{

std::size_t 
hash<seagame::Ship>::operator()(const seagame::Ship& u) const
{
    return hash<string>()(to_string(u.id()) + to_string(u.len()) + to_string(u.orientation()));
}

bool 
equal_to<seagame::Ship>::operator()(const seagame::Ship& lhs, const seagame::Ship& rhs) const
{
    return lhs.len() == rhs.len() && lhs.orientation() == rhs.orientation();
}

std::size_t 
hash<std::reference_wrapper<seagame::Ship>>::operator()(const std::reference_wrapper<seagame::Ship>& u) const
{
    return hash<seagame::Ship>()(u.get());
}

bool 
equal_to<std::reference_wrapper<seagame::Ship>>::operator()(const std::reference_wrapper<seagame::Ship>& lhs, const std::reference_wrapper<seagame::Ship>& rhs) const
{
    return equal_to<seagame::Ship>()(lhs.get(), rhs.get());
}

} // std
