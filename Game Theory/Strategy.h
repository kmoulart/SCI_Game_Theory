//
//  Strategy.h
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#ifndef __Game_Theory__Strategy__
#define __Game_Theory__Strategy__

#include <string>
#include <fstream>

#include <Python.h>

class Strategy {
    
    PyObject* _compiled_function;
    
    std::string _name;
	
	unsigned int _population;
    
public:
    
    Strategy(const std::string& name, unsigned int population, const std::string& filepath);
    
    ~Strategy();
    
    void call(PyObject* global_dict, PyObject* local_dict);
    
    const std::string& getName() const;
	
	unsigned int getPopulation() const;
    
private:
    
    void init(const std::string& filepath);
};

#endif /* defined(__Game_Theory__Strategy__) */
