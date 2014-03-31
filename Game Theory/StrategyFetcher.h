//
//  StrategyFetcher.h
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#ifndef __Game_Theory__StrategyFetcher__
#define __Game_Theory__StrategyFetcher__

#include <list>
#include <string>
#include <map>

class StrategyFetcher {

public:

    struct StrategyInfo
    {
        StrategyInfo(const std::string& name, const std::string& path, unsigned int population) :
            name(name),
            path(path),
            population(population)
        {
        }

        std::string name;
        std::string path;
        unsigned int population;
    };
    typedef std::list<StrategyInfo> FileList;

    FileList getFileList(const std::string& path) const;
};

#endif /* defined(__Game_Theory__StrategyFetcher__) */
