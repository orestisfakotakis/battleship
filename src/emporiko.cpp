#include "emporiko.h"
#include <iostream>
#include "defs.h"

using namespace std;


int Emporiko::counter_empor_ships_created=0;
int Emporiko::counter_empor_ships_died=0;

Emporiko::Emporiko(Naumaxia *n) : Ship(n, 2, 8)
{
    total_treasure_acquired=0;
	counter_empor_ships_created++;
}

Emporiko::~Emporiko() 
{
	counter_empor_ships_died++;
}

void Emporiko::leitourgia() 
{
    std::vector<Cell*> geiton_kelia;
    geiton_kelia = n->getNeighbourCells(row, col);

    //Elegxos gia limani
    for(int i = 0 ; i != geiton_kelia.size(); i++)
    {
        if(geiton_kelia[i]->get_limani())
        {
            total_treasure_acquired += EMPOR_AUKSISI_THISAUROU;
            inc_apo8ema(EMPOR_AUKSISI_THISAUROU);
            break; //mono mia fora
        }

    }
}

void Emporiko::info(std::ostream& os) const
{
    Ship::info(os);
    os << "Treasure acquired :  " << total_treasure_acquired;
}
