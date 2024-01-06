#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <string>

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

using Dictionary = std::map<std::string, std::set<unsigned int>>;

int main()
{
    // Tiedoston avaaminen
    std::cout << "Input file: ";
    std::string filename;
    std::getline(std::cin, filename);

    std::ifstream file(filename);

    //Onnistuuko?
    if(!file)
    {
        std::cout << "Error! The file " << filename << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }

    // Alusta tietorakenne
    Dictionary dict;

    // Käy tiedosto läpi
    std::string line;
    unsigned int counter = 1;
    while(std::getline(file, line))
    {
        std::vector<std::string> words = split(line, ' ', true);
        for(std::string word : words)
        {
            // Onko jo merkintää dictissä?
            if(dict.find(word) == dict.end())
            {
                //lisätään sana dictiin
                dict.insert({word, {}});
            }
            dict.at(word).insert(counter);

        }
        counter ++;


    }
    file.close();

    //tulostetaan tiedot
    for(Dictionary::iterator iter = dict.begin();
        iter != dict.end(); iter++)
    {
        std::string word = iter->first;
        std::set<unsigned int> rowsN = iter->second;

        std::cout << word << " " << rowsN.size() << ": ";
        // Tulostaa rivit iteroiden
        std::set<unsigned int>::iterator rowsIter = rowsN.begin();
        while(true)
        {
            // Tulostaa rivinumeron
            std::cout << *rowsIter;
            rowsIter++;
            // Ollaanko lopussa?
            if(rowsIter == rowsN.end())
            {
                break;
            }
            std::cout << ", ";
        }
        std::cout << std::endl;

    }

    return EXIT_SUCCESS;
}
