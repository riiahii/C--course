#include <iostream>
#include <string>
#include <fstream>
#include <vector>


int main()
{
    std::string inputname = "";
    std::cout << "Input file: ";
    std::getline(std::cin, inputname);

    std::string outputname = "";
    std::cout << "Output file: ";
    std::getline(std::cin, outputname);

    std::ifstream input(inputname);

    if(! input)
    {
        std::cout << "Error! The file " << inputname << " cannot be opened." << std::endl;
        return EXIT_FAILURE;
    }
    else
    {
        std::vector<std::string> rows = {};

        std::string row = "";
        while(std::getline(input, row))
        {
            rows.push_back(row);
        }
        input.close();

        std::ofstream output(outputname);

        if(! output)
        {
            std::cout << "Error! The file " << outputname << " cannot be opened." << std::endl;
            return EXIT_FAILURE;
        }
        output.clear();
        int counter = 1;
        for( std::string i : rows)
        {
            output << counter << " " << i << std::endl;
            counter++;
        }
        output.close();
    }

    return EXIT_SUCCESS;
}
