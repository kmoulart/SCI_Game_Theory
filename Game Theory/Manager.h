//
//  Manager.h
//  Game Theory
//
//  Created by Kévin Moulart on 02/12/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#ifndef __Game_Theory__Manager__
#define __Game_Theory__Manager__

#include <iostream>

#include "Player.h"
#include "Strategy.h"

class Manager {
    Player _player_1;
    Player _player_2;
private:
    void updateScores(PyObject* current_move_1, PyObject* current_move_2, int& score_1, int& score_2);
    
public:
    Manager(boost::shared_ptr<Strategy> strategy_1, boost::shared_ptr<Strategy> strategy_2);
    
    void play(int& score_1, int& score_2, int nb_round);
};

#endif /* defined(__Game_Theory__Manager__) */
