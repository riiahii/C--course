#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using Network = std::unordered_map<std::string, std::vector<std::string>>;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


void store(std::string const &p1, std::string const &p2, Network &nw)
{
    // Onko henkilö jo tietokannassa
    if(nw.find(p1) == nw.end()) {
        nw.insert({p1, {}});
    }
    if(nw.find(p2) == nw.end()) {
        nw.insert({p2, {}});
    }
    nw.at(p1).push_back(p2);
}

void print_recursive(std::string const &id, Network const &nw, std::string const dots = "")
{
    //Tulostetaan pisteet ja nimi
    std::cout << dots << id << std::endl;

    //Käydään henkilön aliverkkoa läpi
    std::vector<std::string> subnetwork = nw.at(id);
    for(std::string const &marketer : subnetwork) {
        print_recursive(marketer, nw, dots + "..");
    }
}

int count_recursive(std::string const &id, Network const &nw)
{
    int result = 0;
    for(std::string const &marketer : nw.at(id)) {
        result += 1 + count_recursive(marketer, nw);
    }
    return result;
}

int depth_recursive(std::string const &id, Network const &nw)
{
    int depth_record = 0;
    for(std::string const &marketer : nw.at(id)) {
        int d = depth_recursive(marketer, nw);
        if(d > depth_record) {
            depth_record = d;
        }
    }
    return depth_record + 1;
}
int main()
{
    Network nw;



    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store(id1, id2, nw);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print_recursive(id, nw);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << count_recursive(id, nw) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std::cout << depth_recursive(id, nw) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
