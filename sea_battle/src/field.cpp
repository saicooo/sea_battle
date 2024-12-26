#include "field.h" 

namespace seagame 
{ 

Field::Size::Size(std::uint64_t _m, std::uint64_t _n) 
{ 
    if (_m < 1 || _n < 1) 
        throw std::invalid_argument("component of size must be greater than 0"); 

    this->_m = _m; 
    this->_n = _n; 
} 

Field::Size::Size(const Size &other) 
    : _m(other.m()), _n(other.n()) 
{    } 

Field::Size::Size(Size &&other) noexcept 
    : _m(other._m), _n(other._n) 
{    } 

Field::Size& Field::Size::operator=(const Size &other) 
{ 
    if (this != &other) 
    { 
        this->_m = other.m(); 
        this->_n = other.n(); 
    } 
    return *this; 
} 

Field::Size& Field::Size::operator=(Size &&other) noexcept 
{ 
    if (this != &other) 
    { 
        this->_m = other._m; 
        this->_n = other._n; 
    } 
    return *this; 
} 

std::uint64_t Field::Size::m() const noexcept 
{ return this->_m; } 

std::uint64_t Field::Size::n() const noexcept 
{ return this->_n; } 

Field::Field(std::uint64_t _m, std::uint64_t _n) 
    : _size(_m, _n) 
{ 
    if (_m < 1 || _n < 1) 
        throw std::invalid_argument("minimal field size: 1x1"); 
} 

Field::Field(Size _size) 
    : _size(_size) 
{    } 

Field::Field(const Field &other) 
    : _size(other.size()),  
      _deployed_ships(other._deployed_ships),  
      _hit_units(other._hit_units), 
      _unusable_units(other._unusable_units) 
{    } 

Field::Field(Field &&other) noexcept 
    : _size(other._size),  
      _deployed_ships(std::move(other._deployed_ships)),  
      _hit_units(std::move(other._hit_units)), 
      _unusable_units(std::move(other._unusable_units)) 
{    } 

Field& Field::operator=(const Field &other) 
{ 
    if (this != &other) 
    { 
        this->_size = other.size(); 
        this->_deployed_ships = other._deployed_ships; 
        this->_hit_units = other._hit_units; 
        this->_unusable_units = other._unusable_units; 
    } 
    return *this; 
} 

Field& Field::operator=(Field &&other) noexcept 
{ 
    if (this != &other) 
    { 
        this->_size = other._size; 
        this->_deployed_ships = std::move(other._deployed_ships); 
        this->_hit_units = std::move(other._hit_units); 
        this->_unusable_units = std::move(other._unusable_units); 
    } 
    return *this; 
} 

void Field::add_ship(Ship &_ship, const Unit &_unit) 
{ 
    if (this->_unusable_units.find(_unit) != this->_unusable_units.end()) 
        throw std::invalid_argument("bad unit for add ship"); 

    Ship::Len i = Ship::Len::ONE; 
    while (i != _ship.len()) 
    { 
        if (this->_unusable_units.find(Unit( 
            _ship.orientation() == Ship::Orientation::HORIZONTAL  
                ? _unit.x() + i  
                : _unit.x(), 
            _ship.orientation() == Ship::Orientation::VERTICAL  
                ? _unit.y() + i 
                : _unit.y() 
        )) != this->_unusable_units.end()) 
            throw std::invalid_argument("bad unit for add ship"); 

        i = Ship::Len(i + 1); 
    } 

    switch (_ship.orientation()) 
    { 
    case Ship::Orientation::HORIZONTAL: 
        if (!this->__is_valid_unit(_unit.x() + _ship.len() - 1, _unit.y())) 
            throw std::invalid_argument("bad unit for add ship"); 
        break; 

    case Ship::Orientation::VERTICAL: 
        if (!this->__is_valid_unit(_unit.x(), _unit.y() + _ship.len() - 1)) 
            throw std::invalid_argument("bad unit for add ship"); 
        break; 

    default: 
        throw std::logic_error("bad orientation"); 
    } 

    this->_deployed_ships.emplace(_unit, _ship); 
    this->__block_units_for_add(_unit, _ship); 
} 

void Field::add_ship(Ship &_ship, std::uint64_t _x, std::uint64_t _y) 
{ return this->add_ship(_ship, Unit(_x, _y)); } 

void Field::shot(const Unit &_unit) 
{ 
    if (!this->__is_valid_unit(_unit) 
      || this->_hit_units.find(_unit) != this->_hit_units.end()) 
        throw std::invalid_argument("bad unit for shot"); 

    Unit _u0; 
    Unit _u; 
    std::equal_to<Unit> eq; 
    std::uint8_t i; 

    _u = this->__get_lu_seg_of_ship(_unit, Ship::Orientation::HORIZONTAL, i); 

    if (eq(_u, _u0) || !this->__is_same_ship(_u, _unit, i)) 
        _u = this->__get_lu_seg_of_ship(_unit, Ship::Orientation::VERTICAL, i); 

    if (eq(_u, _u0) || !this->__is_same_ship(_u, _unit, i)) 
    { 
        this->_hit_units.insert(_unit); 
        return; 
    } 

    Ship &_ship = this->_deployed_ships.at(_u); 
    _ship.hit(i); 

    if (_ship.segments()[i] == Ship::Integrity::DESTROYED) 
        this->_hit_units.insert(_unit); 

    if (_ship.is_destroyed()) 
    {
        this->__block_units_for_hit(_u, _ship); 
        this->_react_for_ship_destroy();
    }
} 

void Field::shot(std::uint64_t _x, std::uint64_t _y) 
{ return this->shot(Unit(_x, _y)); } 

const Field::Size& Field::size() const noexcept 
{ return this->_size; } 

void Field::setup_react_for_ship_destroy(std::function<void()> _funct) noexcept
{
    this->_react_for_ship_destroy = _funct;
}

std::function<void()> Field::get_react_for_ship_destroy() const noexcept
{
    return this->_react_for_ship_destroy;
}

std::unordered_map<Unit, std::reference_wrapper<Ship>>& Field::get_deployed_ships() noexcept
{
    return this->_deployed_ships;
}


Unit Field::__get_unit_of_valid_ship(const Unit &_unit, std::uint8_t &i)
{
    std::equal_to<Unit> eq;
    Unit _u0;
    Unit _u = this->__get_lu_seg_of_ship(_unit, Ship::Orientation::HORIZONTAL, i);

    if (eq(_u, _u0) || !this->__is_same_ship(_u, _unit, i))
        _u = this->__get_lu_seg_of_ship(_unit, Ship::Orientation::VERTICAL, i);
    
    if (eq(_u, _u0) || !this->__is_same_ship(_u, _unit, i))
        return _u0;

    return _u;

}

void Field::__block_unit(const Unit &_unit, const Ship::Orientation &_orie, bool _flag) 
{ 
    Unit _u; 
    for (std::int8_t i = -1; i < 2; ++i) 
    { 
        _u = Unit( 
            _orie == Ship::Orientation::VERTICAL 
                ? _unit.x() + i 
                : _unit.x(), 
            _orie == Ship::Orientation::HORIZONTAL 
                ? _unit.y() + i 
                : _unit.y() 
        ); 

        if (!this->__is_valid_unit(_u)) 
            continue; 

        if (_flag) 
            this->_unusable_units.insert(_u); 
        else 
            this->_hit_units.insert(_u); 
    } 
} 

void Field::__block_units(const Unit &_unit, const Ship &_ship, bool _flag) 
{ 
    for (std::int8_t i = -1; i <= _ship.len(); ++i) 
        this->__block_unit(Unit( 
            _ship.orientation() == Ship::Orientation::HORIZONTAL 
                ? _unit.x() + i 
                : _unit.x(), 
            _ship.orientation() == Ship::Orientation::VERTICAL 
                ? _unit.y() + i 
                : _unit.y() 
        ), _ship.orientation(), _flag); 
} 

void Field::__block_units_for_add(const Unit &_unit, const Ship &_ship) 
{ return this->__block_units(_unit, _ship, true); } 

void Field::__block_units_for_hit(const Unit &_unit, const Ship &_ship) 
{ return this->__block_units(_unit, _ship, false); } 

bool Field::__is_valid_unit(const Unit &_u) const noexcept 
{ 
    return _u.x() > 0 && _u.x() <= this->_size.m()  
        && _u.y() > 0 && _u.y() <= this->_size.n();  
} 

bool Field::__is_valid_unit(std::uint64_t _x, std::uint64_t _y) const noexcept 
{ return this->__is_valid_unit(Unit(_x, _y)); } 

bool Field::__is_same_ship(const Unit &_lu, const Unit &_unit, std::uint8_t _offset) 
{ 
    Ship &_ship = this->_deployed_ships.at(_lu); 

    if (_ship.len() <= _offset) 
        return false; 

    Unit _u( 
        _ship.orientation() == Ship::Orientation::HORIZONTAL 
            ? _lu.x() + _offset 
            : _lu.x(), 
        _ship.orientation() == Ship::Orientation::VERTICAL 
            ? _lu.y() + _offset 
            : _lu.y() 
    ); 

    std::equal_to<Unit> eq; 
    return eq(_unit, _u); 
} 

Unit Field::__get_lu_seg_of_ship(const Unit &_unit, const Ship::Orientation &_orie, std::uint8_t &i) 
{ 
    Unit _u; 

    for (i = 0; i < 4; ++i) 
    { 
        _u = Unit( 
            _orie == Ship::Orientation::HORIZONTAL 
                ? _unit.x() - i 
                : _unit.x(), 
            _orie == Ship::Orientation::VERTICAL 
                ? _unit.y() - i 
                : _unit.y() 
        ); 

        if (!this->__is_valid_unit(_u)) 
            break; 

        if (this->_deployed_ships.find(_u) != this->_deployed_ships.end()) 
            return _u; 
    } 

    return Unit(); 
} 

} // namespace seagame