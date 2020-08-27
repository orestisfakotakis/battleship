#include "episkeuastiko.h"
#include <iostream>
#include "defs.h"

using namespace std;

int Episkeuastiko::counter_epis_ships_created=0;
int Episkeuastiko::counter_epis_ships_died=0;

Episkeuastiko::Episkeuastiko(Naumaxia *n) : Ship(n, 2, 9)
{
	counter_epis_ships_created++;
}

Episkeuastiko::~Episkeuastiko() 
{
	counter_epis_ships_died++;
}

void Episkeuastiko::leitourgia()
{
	std::vector<Ship*> geitones;
	Ship* geitonas;
	int episkeui,diff;
	geitones = n->getNeighbours(this->row, this->col);
	if(geitones.size()>0)
	{
		for(int i = 0; i != geitones.size(); i++)
		{
			geitonas = geitones[i];
			//An exei zhmia kai thisauro na plhrwsei
			if(geitonas->get_antoxi()<geitonas->get_megisti_antoxi()
					&& geitonas->get_apo8ema() >= EPISK_ANTALAGMA_THISAUROU)
			{
				diff = geitonas->get_megisti_antoxi()-geitonas->get_antoxi();
				//Min kseperasei megisti_antoxi
				episkeui = (diff > EPISK_AUKSISI_ANTOXIS) ? EPISK_AUKSISI_ANTOXIS : diff;
				geitonas->inc_antoxi(episkeui);
				geitonas->dec_apo8ema(EPISK_ANTALAGMA_THISAUROU);
				inc_apo8ema(EPISK_ANTALAGMA_THISAUROU);
                total_treasure_acquired += EPISK_ANTALAGMA_THISAUROU;
			}
		}
    }
}

void Episkeuastiko::info(std::ostream& os) const
{
    Ship::info(os);
    os << "Treasure acquired :  " << total_treasure_acquired;
}
