#include <iostream>
#include <string>
#include <vector>


// TODO: Implement split function here
// Do not change main function

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
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
