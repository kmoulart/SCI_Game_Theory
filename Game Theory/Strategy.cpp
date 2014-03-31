//
//  Strategy.cpp
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#include "Strategy.h"

#include <vector>

#include "Exception.h"

using namespace std;

Strategy::Strategy(const std::string& name, unsigned int population, const std::string& filepath) :
_compiled_function(NULL),
_name(name),
_population(population)
{
    init(filepath);
}

void Strategy::init(const std::string& filepath)
{
    std::ifstream ifs(filepath);
    
    ifs.seekg(0, std::ifstream::end);
    size_t size = ifs.tellg();
    
    vector<char> content;
    content.reserve(size+1);
    
    ifs.seekg(0, ifstream::beg);
    
    ifs.read(&content[0], sizeof(char) * size);
    content[size] = '\0';
    
    _compiled_function = Py_CompileString(&content[0], "test", Py_file_input);
    
    if (_compiled_function == NULL)
    {
        PyErr_Print();
        throw Exception("Unable to compile the python file: " + filepath);
    }
    Py_INCREF(_compiled_function);
}

void Strategy::call(PyObject* global_dict, PyObject* local_dict)
{
    PyEval_EvalCode(_compiled_function, global_dict, local_dict);
}

const std::string& Strategy::getName() const
{
    return _name;
}

unsigned int Strategy::getPopulation() const
{
    return _population;
}

Strategy::~Strategy() {
    Py_DecRef(_compiled_function);
}