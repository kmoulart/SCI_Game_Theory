//
//  Manager.cpp
//  Game Theory
//
//  Created by Kévin Moulart on 02/12/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#include "Manager.h"
#include <Python.h>
#include <cstring>

Manager::Manager(boost::shared_ptr<Strategy> strategy_1, boost::shared_ptr<Strategy> strategy_2) :
_player_1(strategy_1),
_player_2(strategy_2)
{
}

void Manager::play(int& score_1, int& score_2, int nb_round)
{
    PyObject* last_move_player_1 = Py_None;
    PyObject* last_move_player_2 = Py_None;
    score_1 = 0;
    score_2 = 0;
    
    for (int i = 0; i < nb_round; ++i) {
        PyObject* current_move_1 = _player_1.play(last_move_player_2);
        PyObject* current_move_2 = _player_2.play(last_move_player_1);
        
        Py_DecRef(last_move_player_1);
        Py_DecRef(last_move_player_2);
        
        last_move_player_1 = current_move_1;
        last_move_player_2 = current_move_2;
        
        updateScores(current_move_1, current_move_2, score_1, score_2);
    }
}

void Manager::updateScores(PyObject* current_move_1, PyObject* current_move_2, int& score_1, int& score_2)
{
    long move_long_1 = PyLong_AsLong(current_move_1);
    long move_long_2 = PyLong_AsLong(current_move_2);
    
    if (move_long_1 == move_long_2)
    {
        if (move_long_1) {
            score_1 += 3;
            score_2 += 3;
        } else {
            score_1 += 1;
            score_2 += 1;
        }
    } else {
        if (move_long_1) {
            score_1 += 0;
            score_2 += 5;
        } else {
            score_1 += 5;
            score_2 += 0;
        }
    }
}