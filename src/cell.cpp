#include <iostream>
#include "cell.h"

using namespace std;

void Cell::set_kairos(int t){
	if ( t>0 && t<=10)	
		kairos=t;
}

void Cell::set_limani(bool lima) {
	limani=lima;	
}

void Cell::set_thisauros(bool thisau){
	thisauros=thisau;
}

void Cell::set_ship(Ship *ship_) {
	ship = ship_;
}

int Cell::get_kairos(void){
	return kairos;
}

bool Cell::get_limani(void) {
	return limani;
}

bool Cell::get_thisauros(void){
	return thisauros;
}

Ship* Cell::get_ship() {
	return ship;
}

Coords Cell::get_coords()
{
    return coords;
}

void Cell::set_coords(Coords coords_)
{
    coords = coords_;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell)
{
    os << "Cell \n"
          "Location   :  [" << cell.coords.row << ", " << cell.coords.col << "]" << std::endl;
    os << "Kairos     :  " << cell.kairos << std::endl;
    os << "Thisauros  :  " << (cell.thisauros? "YES": "NO") << std::endl;
    os << "Limani     :  " << (cell.limani? "YES": "NO") << std::endl;
    os << "Karavi     :  " << (cell.hasShip()? "YES": "NO") << std::endl;

    return os;
}
