#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

std::vector<std::string> split(std::string line, char sep, bool ignore_empty = false)
{
    std::vector<std::string> splitted_vector = {};
    std::string substring = "";

    while(line.find(sep) != std::string::npos)
    {
        substring = line.substr(0, line.find(sep));
        line = line.substr(line.find(sep)+1, std::string::npos);

        if (!(ignore_empty && substring.empty()))
        {
            splitted_vector.push_back(substring);

        }


    }
    if (!(ignore_empty && line.empty()))
    {
        splitted_vector.push_back(line);

    }
    return splitted_vector;
}

int main()
{
    std::string inputname = "";
    std::cout << "Input file: ";
    std::getline(std::cin, inputname);
    std::ifstream input(inputname);

    if(!input)
    {
        std::cout << "Error! The file " << inputname << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Final scores:" << std::endl;

    std::map<std::string, int> points;
    std::string row = "";
    std::vector<std::string> splitted_rows;
    while(std::getline(input, row))
    {
        std::vector splitted_rows = split(row, ':', true);
        int point = std::stoi(splitted_rows.at(1));
        if(points.find(splitted_rows.at(0)) != points.end())
        {
            points.at(splitted_rows.at(0)) += point;
        }
        else
        {
            points.insert( { splitted_rows.at(0), point});
        }
    }

    std::map<std::string, int>::iterator iter;
    iter = points.begin();
    while(iter != points.end())
    {
        std::cout << iter->first << ": " << iter->second << std::endl;
        iter++;
    }



    return EXIT_SUCCESS;
}
