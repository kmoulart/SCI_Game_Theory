#include <iostream>
#include <memory>
#include <map>
#include <fstream>
#include <vector>
#include <time.h>

#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <Python.h>

#include "StrategyFetcher.h"
#include "Strategy.h"
#include "Manager.h"

using namespace std;
using namespace boost::numeric::ublas;

void init()
{
    Py_Initialize();
}

void finalize()
{
    Py_Finalize();
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

    return buf;
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc != 2)
        {
            return EXIT_FAILURE;
        }

        init();

        StrategyFetcher strategyFetcher;
        StrategyFetcher::FileList file_list = strategyFetcher.getFileList(argv[1]);

        std::vector<boost::shared_ptr<Strategy>> strategies = std::vector<boost::shared_ptr<Strategy>>();
        strategies.reserve(file_list.size());

        string path = "/tmp/";
        string date = currentDateTime();
        string outputMatrix = path + date + "_matrix.csv";
        cout << outputMatrix << endl;
        ofstream outputMatrixFile;
        outputMatrixFile.open(outputMatrix);


        string outputEvolution = path + date + "_evolution.csv";
        cout << outputEvolution << endl;
        ofstream outputEvolutionFile;
        outputEvolutionFile.open(outputEvolution);

        string history = path + "history.csv";
        cout << history << endl;
        ofstream historyFile;
        historyFile.open(history, ios::app);

        historyFile << "affrontement du " << date << " :" << endl;


        for (const auto& file : file_list)
        {
            strategies.push_back(boost::shared_ptr<Strategy>(new Strategy(file.name, file.population, file.path)));
        }

        outputMatrixFile << ',';
        for (const auto& strategy : strategies)
        {
            outputMatrixFile << strategy->getName() << ',';
            outputEvolutionFile << strategy->getName() << ',';
            historyFile << strategy->getName() << endl;
        }
        outputMatrixFile << endl;
        outputEvolutionFile << endl;
        historyFile << endl;
        
        outputMatrixFile << ',';
        for (unsigned i = 0; i < strategies.size(); ++ i)
        {
            outputMatrixFile << strategies[i]->getPopulation() << ',';
            outputEvolutionFile << strategies[i]->getPopulation() << ',';
        }
        outputMatrixFile << endl;
        outputEvolutionFile << endl;

        matrix<unsigned long long> score_matrix(strategies.size(), strategies.size());
        for (unsigned i = 0; i < score_matrix.size1(); ++ i)
        {
	    outputMatrixFile << strategies[i]->getName() << ',';
            for (unsigned j = i; j < score_matrix.size2(); ++ j)
            {
                int score_1;
                int score_2;
                Manager manager(strategies[i], strategies[j]);
                manager.play(score_1, score_2, 1000);

                score_matrix(i,j) = score_1;
                score_matrix(j,i) = score_2;
            }

            for (unsigned j = 0; j < score_matrix.size2(); ++j) {
                outputMatrixFile << score_matrix(i, j) << ',';
            }
            outputMatrixFile << endl;
        }

        std::vector<std::vector<int>> populations;
		unsigned int total_population = 0;
        populations.reserve(10000);

		{
			std::vector<int> first_populations;
			for (const auto& strategy : strategies)
			{
				first_populations.push_back(strategy->getPopulation());
				total_population += strategy->getPopulation();
			}
			populations.push_back(std::move(first_populations));
		}

        // double : decimal part of the computed population
        // int : index of the corresponding strategy
        multimap<double, int> cut_pop;

        do {
			unsigned long new_pop_total = 0;
            double total_score = 0;
            const std::vector<int>& old_pop = populations[populations.size() - 1];
            std::vector<int> new_pop;
            new_pop.reserve(strategies.size());

            std::vector<double> scores(strategies.size(), 0);

            for (unsigned i = 0; i < strategies.size(); ++i)
            {
                for (unsigned j = 0; j < strategies.size(); ++j)
                {
                    scores[i] += score_matrix(i, j) * old_pop[j];
                }

                scores[i] *= old_pop[i];
                scores[i] -= score_matrix(i, i); // can't fight myself!
                total_score += scores[i];
            }

			// assign new populations with rounded values
            for (unsigned i = 0; i < scores.size(); ++i)
            {
                double pop = double(scores[i]) / total_score * total_population;
                double decimal_part = pop - (long) pop;
                if (decimal_part)
                {
                    cut_pop.insert(pair<double, int>(decimal_part, i));
                }
                new_pop.push_back(pop);
				new_pop_total += pop;
            }

			// get back the rounded elements in the population
			unsigned long missing_pop = total_population - new_pop_total;
			multimap<double, int>::const_reverse_iterator cut_pop_iterator = cut_pop.rbegin();
			for (unsigned int i = 0; i < missing_pop; ++i)
			{
				++new_pop[(cut_pop_iterator++)->second];
			}

			for (const auto& pop : new_pop)
			{
				outputEvolutionFile << pop << ',';
			}

            outputEvolutionFile << endl;

            populations.push_back(std::move(new_pop));
        } while (populations.size() < 1000 && populations[populations.size()-1] != populations[populations.size()-2]);

        outputMatrixFile.close();
        outputEvolutionFile.close();
        finalize();
    }
    catch (const std::exception& e)
    {
        cerr << e.what() << endl;
        Py_Finalize();

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
