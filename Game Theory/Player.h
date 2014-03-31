//
//  Player.h
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#ifndef __Game_Theory__Player__
#define __Game_Theory__Player__

#include <boost/shared_ptr.hpp>

#include "Strategy.h"

class Player {
    
    boost::shared_ptr<Strategy> _strategy;
    
    PyObject* _private_memory;
    PyObject* _main_module;
    PyObject* _global_dict;
    PyObject* _local_dict;
    
    PyObject* _last_move_key;
    PyObject* _private_memory_key;
    PyObject* _result_key;
    
public:
    
    Player(boost::shared_ptr<Strategy> strategy);
    
    /**
     * @param (PyLong) the last opponent move.
     * @return (PyLong) 1 if the player chooses to betray, 0 otherwise.
     */
    PyObject* play(PyObject* opponent_move);
    
    ~Player();
};

#endif /* defined(__Game_Theory__Player__) */
