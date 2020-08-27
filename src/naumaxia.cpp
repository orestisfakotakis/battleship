#include "naumaxia.h"
#include "ship.h"
#include "episkeuastiko.h"
#include "eksereunisis.h"
#include "peiratiko.h"
#include "emporiko.h"
#include "utils.h"
#include <iostream>
#include <cstdlib>
#include <typeinfo>

Naumaxia::Naumaxia(int rows, int cols, int num_ship) :
    rows(rows), cols(cols), num_ships(num_ship),
    map(rows, std::vector<Cell>(cols)),
    round_counter(0)
{
    initMap();
    populateMap();
}

// Initializations

void Naumaxia::setWeatherThreshold(int thres)
{
    weather_threshold = thres;
}

void Naumaxia::setTreasureTarget(int k)
{
    target_treasure=k;
}

void Naumaxia::initMap()
{
    // Pithanotita thiss: 30%
    // Pithanotita limani 20%
    Coords temp;
    for(int  row=0; row<rows; row++) {
        for(int col=0;col<cols;col++) {
            int R = rand() % 10; // R = 0-9
            if (R < 3)
                map[row][col].set_thisauros(true);
            if (R < 2)
                map[row][col].set_limani(true);

            map[row][col].set_kairos(R+1);
            temp.col=col; temp.row = row;
            map[row][col].set_coords(temp);
        }
    }
}

void Naumaxia::populateMap()
{
    for (int i=0; i<num_ships; i++) {

        Ship *ship=NULL;

        // Create a ship of random type
        int ship_type = rand() % 4;

        switch (ship_type) {
        case 0: ship = new Episkeuastiko(this); break;
        case 1: ship = new Eksereunisis(this); break;
        case 2: ship = new Peiratiko(this); break;
        case 3: ship = new Emporiko(this); break;
        default: break;
        }

        int row, col;

        // Find a random empty spot to place the new ship
        do {
            row = rand() % rows;
            col = rand() % cols;
        } while (map[row][col].hasShip());

        // Set ship coordinates
        ship->set_row(row);
        ship->set_col(col);

        // Add ship to map
        map[row][col].set_ship(ship);

        karavia.push_back(ship);
    }

}

// Gameplay

void Naumaxia::play()
{
    int user_abort=0;

    do
    {
        clrscrn();
        std::cout << "Round: " << round_counter << std::endl;
        //printMap(KARAVI);

        // Check user
        if (getAsyncKey() == ' ' ) { // key press detected (SPACEBAR)
            std::cout << "Simulation paused by key press." << std::endl;
            user_abort = menu();
        }

        if (user_abort) break;

        // Execute current round
        step();

        // Slow down for user
        Sleep(STEP_DELAY_MSEC);
    }
    while (alive());

    if (user_abort) {
        std::cout << " - Aborted by user " << std::endl;
    }
    else {
        std::cout << " - Simulation finished " << std::endl;
    }

}

void Naumaxia::step()
{
    // A. Actions on round beginning.
    newRoundActions();

    // B.
    metakinisi();
    leitourgia();

    // C. Actions on round end.
    removeDeadShips();
    updateWeather();

    round_counter++;
}

bool Naumaxia::alive()
{
    if (getActiveShipNumber() <= 0)
        return false;

    bool winner_flag = false;

    for (int i=0; i<karavia.size(); i++) {
        if (karavia[i]->get_apo8ema() >= target_treasure) {
            std::cout << "Winner: " << *karavia[i] << std::endl;
            winner_flag = true;
        }
    }

    if (winner_flag)
        return false;
    else
        return true;
}

void Naumaxia::newRoundActions()
{
    for(int  row=0; row<rows; row++) {
        for(int col=0;col<cols;col++) {
            if (map[row][col].hasShip())
            {
                // Apply weather damage
                if (map[row][col].get_kairos() > weather_threshold) {
                    Ship *ship = map[row][col].get_ship();
                    ship->dec_antoxi(1);
                }

                // Steal treasure
                if (map[row][col].get_thisauros()) {
                    Ship *ship = map[row][col].get_ship();
                    ship->inc_apo8ema(1);
                    map[row][col].set_thisauros(false);
                }
            }

            if (map[row][col].get_limani())
            {
                
                // Search the 8 neighbor cells and apply rules
				std::vector<Ship*> geitones;
				geitones = getNeighbours(row,col);
				if(geitones.size()>0)
				{
					for(int i = 0; i != geitones.size(); i++)
					{
						//An einai peiratiko, afairesh antoxhs
						if( typeid(*geitones[i]) == typeid(Peiratiko) )
						{
							geitones[i]->dec_antoxi((int)(geitones[i]->get_antoxi()*LIM_ZIMIA_EPISKEUI_POSOSTO/100.0));
						}
						//Alliws, auksisi antoxis an xreiazetai episkeui
						else if(geitones[i]->get_antoxi() < geitones[i]->get_megisti_antoxi())
						{
							geitones[i]->inc_antoxi((int)(geitones[i]->get_antoxi()*LIM_ZIMIA_EPISKEUI_POSOSTO/100.0));
							//An i antoxi kseperase to megisto, epanafora
						}
					}
				}
            }

        }
    }
}

void Naumaxia::removeDeadShips()
{
    for (int i=0; i<karavia.size(); i++) {
        Ship &ship = *karavia[i];

        if (ship.get_antoxi()<0) {
            int x = ship.get_row();
            int y = ship.get_col();
            map[x][y].set_ship(NULL);
            delete &ship;
            num_ships--;
            karavia.erase(karavia.begin()+i); // This causes vector size to decrease
            i--;
        }

    }

}

void Naumaxia::updateWeather()
{
    for(int  row=0; row<rows; row++) {
        for(int col=0;col<cols;col++) {
            int inc_or_dec = (rand() % 2) ? 1 : -1;
            map[row][col].set_kairos(map[row][col].get_kairos() + inc_or_dec);
        }
    }
}

void Naumaxia::metakinisi()
{
    for (int i=0; i<karavia.size(); i++) {

		int row = karavia[i]->get_row();
		int col = karavia[i]->get_col();

        // Diagrafi ship apo palia thesi
        map[row][col].set_ship(NULL);

        // Metakinisi ship
        karavia[i]->metakinisi();

        // Tropopoiisi map[][] symfwna
        // me tin nea thesi tou karaviou.

        row = karavia[i]->get_row();
        col = karavia[i]->get_col();

        map[row][col].set_ship(karavia[i]);
    }
}

void Naumaxia::leitourgia()
{
    for (int i=0; i<karavia.size(); i++)
	{
		karavia[i]->leitourgia();
		int row = karavia[i]->get_row();
		int col = karavia[i]->get_col();

		map[row][col].set_ship(karavia[i]);
	}
}

// Status

bool Naumaxia::validLocation(int r, int c) const
{
    return !( r<0 || c<0 || r>=rows || c>=cols);
}

int Naumaxia::getActiveShipNumber()
{
    return num_ships;
}

void Naumaxia::printMap(CellAttribute p)
{
    std::cout << "  ";

    for(int col=0;col<cols;col++)
        std::cout << "|" << col;

    std::cout << "|" <<  std::endl << "--";

    for(int col=0;col<cols+1;col++)
        std::cout << "--";

    std::cout <<  std::endl;

    for(int  row=0; row<rows; row++) {
        std::cout << row << " ";
        for(int col=0;col<cols;col++) {
            if (p==THISAUROS)
                std::cout << (map[row][col].get_thisauros()?"|T":"| ");
            else if (p==LIMANI)
                std::cout<<  (map[row][col].get_limani()?"|L":"| ");
            else if (p==KAIROS)
                std::cout << "|" << map[row][col].get_kairos()-1;
            else if (p==KARAVI) {
                if (map[row][col].hasShip())
                    std::cout << "|" << map[row][col].get_ship()->getCharCode();
                else std::cout << "| ";
            }
            else
                return;
        }

        std::cout << "|" << std::endl;
    }

    std::cout << std::endl;
}

std::vector<Cell*> Naumaxia::getNeighbourCells(const int row, const int col)
{
    std::vector<Cell*> neighbour_cells;
    Cell* temp;

    for(int r=row-1 ; r<row+2 ; r++) {
        for(int c=col-1 ; c<col+2 ; c++) {

            // Elegxos ektos oriwn
            if ( !validLocation(r,c))
                continue;

            // Elegxos me tin kentriki thesi
            if ( r==row && c==col)
                continue;

            temp = &map[r][c];

            neighbour_cells.push_back(temp);
        }
    }

    return neighbour_cells;
}

std::vector<Coords> Naumaxia::getFreeNeigbourCells(const int row, const int col)
{
    std::vector<Coords> avail_cells;
    Coords coords;

    for(int r=row-1 ; r<row+2 ; r++) {
        for(int c=col-1 ; c<col+2 ; c++) {

            // Elegxos ektos oriwn
            if ( !validLocation(r,c))
                continue;

            // Elegxos me tin kentriki thesi
            if ( r==row && c==col)
                continue;

            // Elegox yparksis ploiou
            if (map[r][c].hasShip())
                continue;

            coords.col=c;
            coords.row=r;

            avail_cells.push_back(coords);
        }
    }

    return avail_cells;
}

std::vector<Ship*> Naumaxia::getNeighbours(const int row, const int col)
{
    std::vector<Ship*> neighbours;
    Ship* temp;

    for(int r=row-1 ; r<row+2 ; r++) {
        for(int c=col-1 ; c<col+2 ; c++) {

            // Elegxos ektos oriwn
            if ( !validLocation(r,c))
                continue;

            // Elegxos me tin kentriki thesi
            if ( r==row && c==col)
                continue;

            // Elegox yparksis ploiou
            if (!map[r][c].hasShip())
                continue;

            temp = map[r][c].get_ship();

            neighbours.push_back(temp);
        }
    }

    return neighbours;
}

Cell* Naumaxia::getCell(const int row, const int col)
{
	return &map[row][col];
}

// UI

int Naumaxia::menu()
{
    std::cout << " --- MENU ---" << std::endl;
    std::cout << " - Gia exodo,                  patiste 'E' " << std::endl;
    std::cout << " - Gia synexeia,               patiste SPACE " << std::endl;
    std::cout << " - Gia na deite ta  ploia,     patiste 'P' " << std::endl;
    std::cout << "   Gia na deite ton thissauro, patiste 'T' " << std::endl;
    std::cout << "   Gia na deite ton kairo,     patiste 'K' " << std::endl;
    std::cout << "   Gia na deite ta  limania,   patiste 'L' " << std::endl;
    std::cout << " - Gia plirofories sxetika me:"              << std::endl;
    std::cout << "     Karavi,                   patiste 'I' " << std::endl;
    std::cout << "     Simeio xarti,             patiste 'M'" << std::endl;
    std::cout << "     Genikes prosomoiwsis,     patiste 'G'" << std::endl;

    std::cout << std::endl;

    while (1)
    {
        int x,y;
        int k = tolower(getch());

        switch (k) {
        case 'p': printMap(KARAVI);break;
        case 't': printMap(THISAUROS);break;
        case 'k': printMap(KAIROS);break;
        case 'l': printMap(LIMANI);break;

        case 'i':
            printf("Enter [row col]: ");
            scanf("%d %d", &x, &y);
            if (validLocation(x,y) && map[x][y].hasShip())
                std::cout << *map[x][y].get_ship();
            else printf("No ship in [%d, %d] \n", x, y);
            break;

        case 'm':
            printf("Enter [row col]: ");
            scanf("%d %d", &x, &y);
            if (validLocation(x,y))
                std::cout << map[x][y];
            else printf("Invalid location \n", x, y);
            break;

        case 'g':
            std::cout << "Total ships created :  " << Ship::get_total_created_counter() << std::endl;
            std::cout << "Total ships died    :  " << Ship::get_total_created_died() << std::endl;
            std::cout << "Total active ships  :  " << karavia.size() << std::endl;
            break;

        case 'e': return 1;
        case ' ': return 0;
        }
    }

    return 0;
}
