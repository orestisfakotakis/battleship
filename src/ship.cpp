#include "ship.h"
#include <iostream>
#include <typeinfo>
#include <cstdlib>
#include <string>

using namespace std;

int Ship::counter_shipes_created = 0;
int Ship::counter_shipes_died = 0;

Ship::Ship(Naumaxia *n, int taxitita_, int megisti_antoxi_) :
    total_distance(0),
    total_damage(0),
    n(n),
	taxitita(taxitita_),
    apo8ema(0),
    megisti_antoxi(megisti_antoxi_),
    trexousa_antoxi(megisti_antoxi_)
{
    ++counter_shipes_created;
}

Ship::~Ship()
{
    ++counter_shipes_died;
}

int Ship::get_taxutita()
{	
    return taxitita;
}

int Ship::get_apo8ema()
{
    return apo8ema;
}

int Ship::get_antoxi(void)
{
    return trexousa_antoxi;  
}

int Ship::get_megisti_antoxi(void)
{
    return megisti_antoxi;
}

void Ship::set_taxutita(int speed)
{
    taxitita = speed;
}

void Ship::dec_antoxi(int stamina)
{
    trexousa_antoxi -= stamina;
}

void Ship::dec_apo8ema(int apoth)
{
    apo8ema -= apoth;
}

void Ship::inc_antoxi(int stamina)
{
    trexousa_antoxi += stamina;
    if(trexousa_antoxi>megisti_antoxi) trexousa_antoxi = megisti_antoxi;
}

void Ship::inc_apo8ema(int apoth)
{
    apo8ema += apoth;
}

void Ship::set_row(int row_)
{
    row = row_;
}

int Ship::get_row()
{
    return row;
}

void Ship::set_col(int col_)
{
    col = col_;
}

int Ship::get_col()
{
    return col;
}

void Ship::metakinisi()
{
    // Tropopoiisi [row, col] tou karaviou

    for (int step=0; step<taxitita; step++) {
        std::vector<Coords> free_cells = n->getFreeNeigbourCells(row, col);
        if (free_cells.empty()) return; // If not available cell...den tha metakinithw...
        int i = rand() % free_cells.size();
        Coords &new_coord = free_cells[i];
        row = new_coord.row;
        col = new_coord.col;
        total_distance++;
    }

}

void Ship::info(std::ostream& os) const
{
    os << "Ship \n"
          "Type      :  " << getCharCode(true) << std::endl;
    os << "Location  :  [" << row << ", " << col << "]" << std::endl;
    os << "Thisauros :  " << apo8ema << std::endl;
    os << "Antoxi    :  " <<  trexousa_antoxi << std::endl;
    os << "Distance  :  " <<  total_distance << std::endl;
    os << "Damage    :  " << total_damage << std::endl;
}

std::ostream& operator<<(std::ostream& os, const Ship& ship)
{
    ship.info(os);
    return os;
}
