#include "eksereunisis.h"
#include "peiratiko.h"
#include <iostream>
#include <typeinfo>

using namespace std;

int Eksereunisis::counter_ekser_ships_created=0;
int Eksereunisis::counter_ekser_ships_died=0;

Eksereunisis::Eksereunisis(Naumaxia *n) : Ship(n, 1, 10)
{
	counter_ekser_ships_created++;
}

Eksereunisis::~Eksereunisis() 
{
	counter_ekser_ships_died++;
}

void Eksereunisis::leitourgia()
{return;
    std::vector<Cell*> geitonia;
    //Peiratiko* geitonas = NULL;
	Ship* tempship;
    int newrow,newcol;
    geitonia = n->getNeighbourCells(this->row, this->col);

    if(geitonia.size() == 0) return;

    for(int i = 0; i != geitonia.size(); i++)
    {
        //Elegxos gia kakokairia
        if(geitonia[i]->get_kairos() > WEATHER_DAMAGE_THRESHOLD)
        {
            //metakinisi pros thn anti8eth
            newrow =row - (geitonia[i]->get_coords().row - row);
            newcol =col - (geitonia[i]->get_coords().col - col);
            if(newrow >= 0 && newrow < ROWS &&
           newcol >= 0 && newcol < COLS && 
		   !n->getCell(newrow,newcol)->hasShip())
			{
				row = newrow;
				col = newcol;
				n->getCell(row,col)->set_ship(this);
			}	   

            break; // mono mia fora
        }
        //Elegxos an einai peiratiko

        if(geitonia[i]->hasShip()) 
		{
			tempship = geitonia[i]->get_ship();

		
			if(typeid(*tempship) == typeid(Peiratiko))
			{
				//metakinisi pros thn anti8eth
				newrow =row - (tempship->get_row() - row);
				newcol =col - (tempship->get_col() - col);
				if(newrow >= 0 && newrow < ROWS &&
					newcol >= 0 && newcol < COLS && 
					!n->getCell(newrow,newcol)->hasShip())
				{
					row = newrow;
					col = newcol;
					n->getCell(row,col)->set_ship(this);
				}
				break; // mono mia fora
			}
		}

    }
}
