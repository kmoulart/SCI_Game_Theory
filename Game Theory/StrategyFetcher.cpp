//
//  StrategyFetcher.cpp
//  Game Theory
//
//  Created by Kévin Moulart on 26/11/13.
//  Copyright (c) 2013 Kévin Moulart. All rights reserved.
//

#include "StrategyFetcher.h"

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>

using namespace boost::filesystem;
using namespace std;

StrategyFetcher::FileList StrategyFetcher::getFileList(const string& pathStr) const {
    FileList file_list;
    path parent_path(pathStr);   // p reads clearer than argv[1] in the following code

    try
    {
        if (exists(parent_path))    // does p actually exist?
        {
            if (is_regular_file(parent_path))        // is p a regular file?
                cerr << parent_path << " is not a directory" << endl;

            else if (is_directory(parent_path))      // is p a directory?
            {
                const directory_iterator end_directory = directory_iterator();
                for (directory_iterator directory_it = directory_iterator(parent_path); directory_it != end_directory; ++directory_it)
                {
                    const path& child_path = directory_it->path();

                    if (is_regular_file(child_path) && child_path.extension().string() == ".py")
                    {
                        const string& filepath = child_path.string();
						unsigned int population;
						string pop_str;
						istringstream path_iss(child_path.filename().string());

						getline(path_iss, pop_str, '_');
						istringstream pop_iss(pop_str);
						if (!(pop_iss >> population))
						{
							population = 100;
						}

                        file_list.push_back(StrategyInfo(child_path.filename().string(), filepath, population));
                    }

                }
            }
        }
    } catch (const filesystem_error& e)
    {
        cerr << e.what() << endl;
    }

    return move(file_list);
}
