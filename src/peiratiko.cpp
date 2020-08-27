#include "peiratiko.h"
#include <iostream>
#include <cstdlib>

using namespace std;

int Peiratiko::counter_peir_ships_created=0;
int Peiratiko::counter_peir_ships_died=0;

Peiratiko::Peiratiko(Naumaxia *n) : Ship(n, 1, 10)
{
    total_attacks = 0;
	dinami = rand()%PEIR_MAX_DINAMI + 1; //Elaxisto 1
	counter_peir_ships_created++;
}

Peiratiko::~Peiratiko() 
{
	counter_peir_ships_died++;
}

void Peiratiko::leitourgia()
{
	std::vector<Ship*> geitones;
	geitones.reserve(8);
	Ship* exthros;
	geitones = n->getNeighbours(this->row, this->col);
	if(geitones.size()>0)
	{
		int i = rand()%geitones.size();
		exthros = geitones[i];
		exthros->dec_antoxi(dinami);
        total_attacks += dinami;

		//auksisi thisaurou
		int thisauros_inc = exthros->get_apo8ema()*(float)(PEIR_POSOSTO_THISAUROU)/100.0;
		exthros->dec_apo8ema(thisauros_inc);
		inc_apo8ema(thisauros_inc);
	}

}

int Peiratiko::get_dinami()
{
	return dinami;
}

void Peiratiko::set_dinami(int n)
{
	dinami = n;
}

void Peiratiko::info(std::ostream& os) const
{
    Ship::info(os);
    os << "Attacks   :  " << total_attacks;
}
