//
//  Exception.h
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#ifndef Game_Theory_Exception_h
#define Game_Theory_Exception_h

#include <exception>
#include <string>

class Exception : public std::exception {
    
    std::string _msg;
    
public:
    
    Exception(const std::string& msg) throw () :
    _msg(msg)
    {
        
    }
    
    const char* what() const throw() {
        return _msg.c_str();
    }
    
    ~Exception() throw() {
        
    }
};

#endif
