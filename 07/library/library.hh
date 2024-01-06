#ifndef LIBRARY_HH
#define LIBRARY_HH

#include <string>
#include <map>
#include <vector>

struct Book;

using Collection = std::map<std::string, std::vector<Book>>;

// Kirjojen tiedot tallennetaan structissa
struct Book
{
    std::string author;
    std::string title;
    int reservations;
};

class Library
{
    // Kirjastoluokan metodit
public:
    Library(const std::string &library_name);

    void addAuthor(const std::string &author);
    void addBook(const std::string &author,
                 const std::string &title,
                 int &reservations);
    void material();
    void books(const std::string &author) const;
    int reservable(const std::string &author,
                   const std::string &title);
    std::map<std::string, std::vector<std::string>> loanable();

    // Kirjaston nimi ja aineisto tietosäiliössä
private:
    std::string library_name_;
    Collection collection_;

};

#endif // LIBRARY_HH
