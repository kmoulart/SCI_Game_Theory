//
//  Player.cpp
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#include "Player.h"

#include <Python.h>

#include "Exception.h"

Player::Player(boost::shared_ptr<Strategy> strategy) :
_strategy(strategy),
_private_memory(Py_None),
_last_move_key(Py_BuildValue("s", "last_move")),
_private_memory_key(Py_BuildValue("s", "memory")),
_result_key(Py_BuildValue("s", "coop"))
{
    _main_module = PyImport_AddModule("__main__");
    _global_dict = PyModule_GetDict(_main_module);
    _local_dict = PyDict_New();
    Py_INCREF(_local_dict);
}

/**
 * @param (PyLong) the last opponent move.
 * @return (PyLong) 1 if the player chooses to betray, 0 otherwise.
 */
PyObject* Player::play(PyObject* opponent_move)
{
    //PyDict_Clear(_local_dict);
    //PyErr_Print();
    
    PyDict_SetItem(_local_dict, _last_move_key, opponent_move);
    Py_INCREF(_last_move_key);
    PyDict_SetItem(_local_dict, _private_memory_key, _private_memory);
    Py_INCREF(_private_memory_key);
    PyDict_SetItem(_local_dict, _result_key, _private_memory);
    Py_INCREF(_result_key);
    
    _strategy->call(_global_dict, _local_dict);
    
    _private_memory = PyDict_GetItem(_local_dict, _private_memory_key);
    Py_INCREF(_private_memory);
    PyObject* result = PyDict_GetItem(_local_dict, _result_key);
    Py_INCREF(result);
    
    if (result == NULL)
    {
        throw Exception(_strategy->getName() + " didn't return a result.");
    }
    
    return result;
}

Player::~Player()
{
    if (_private_memory != Py_None)
    {
        Py_DecRef(_private_memory);
    }
    
    //PyDict_Clear(_local_dict);
    //PyErr_Print();
    //Py_DecRef(_local_dict);
    //PyDict_Clear(_global_dict);
    Py_DecRef(_main_module);
    Py_DecRef(_last_move_key);
    Py_DecRef(_private_memory_key);
    Py_DecRef(_result_key);
}