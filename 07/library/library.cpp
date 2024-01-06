#include "library.hh"
#include <algorithm>
#include <iostream>

Library::Library(const std::string &library_name):
    library_name_(library_name),
    collection_({})
{

}

// Lisää kirjailijan kirjastoon.
void Library::addAuthor(const std::string &author)
{
     // Jos kirjailijaa ei vielä ole Collectionissa se lisätään sinne ja luodaan tyhjä vektori kirjoille.
    if(collection_.find(author) == collection_.end()) {
        collection_.insert({author, {}});
    }
}

// Lisää kirjan kirjastoon Book-tyyppisenä. Parametreinä kirjailijan nimi, kirjan nimi ja varausnumero.
void Library::addBook(const std::string &author,
                      const std::string &title,
                      int &reservations)
{
     // Luodaan Book, jossa halutun kirjan tiedot ja lisätään se Collectioniin oikean kirjailijan paikalle.
    Book book{author, title, reservations};
    addAuthor(author);
    collection_.at(author).push_back(book);
}

// Tulostaa aakkosjärjestyksessä kaikki kirjaston kirjat
void Library::material()
{
    for(Collection::const_iterator iter = collection_.begin(); iter != collection_.end(); ++iter) {
        for(const auto& book : iter->second) {
            std::cout << book.author << ": " << book.title << std::endl;
        }
    }
}

// Vertailee kirjojen nimiä aakkosjärjestyksessä
bool compareTitle(const Book& b1,
                  const Book& b2)
{
    return b1.title < b2.title;
}

// Tulostaa kirjastosta löytyvät syötetyn kirjailijan kaikki kirjat aakkosjärjestyksessä
void Library::books(const std::string &author) const
{
   Collection::const_iterator it = collection_.find(author);

   // Tarkistaa löytyykö kirjailijaa kirjastosta
   if (it == collection_.end()) {
       std::cout << "Error: unknown author" << std::endl;
       return;
   }
   std::vector books = it->second;

   // Järjestetään kirjat niiden nimien mukaan
   std::sort(books.begin(), books.end(), compareTitle);

   // Tulostetaan tiedot
   for (const auto& book : books) {

       // Jos ei ole varauksia tulostetaan std::string
       if(book.reservations == 0){
           std::cout << book.title << " --- on the shelf" << std::endl;
       }

       // Muulloin varausten määrä int
       else{
       std::cout << book.title << " --- " << book.reservations << " reservations" << std::endl;
       }
   }
}

// Tarkistaa löytyykö haluttu kirja kirjastosta ja mikä sen varausnumero on.
// Parametreinä kirjailijan ja kirjan nimi.
// Jos kirja löytyy palautetaan kirjastossa oleva varausnumero, muuten -1.
int Library::reservable(const std::string &author,
                        const std::string &title)
{
    int reservation_number = -1;
    for(Collection::const_iterator iter = collection_.begin(); iter != collection_.end(); ++iter) {
        for(const auto& book : iter->second) {
            if(book.author == author && book.title == title) {
                reservation_number = book.reservations;
            }
    }
    }
    return reservation_number;
}

// Tarkistaa kirjaston kaikki kirjat ja palauttaa std::mapissä kaikki ne kirjat, jotka voi lainata
std::map<std::string, std::vector<std::string>> Library::loanable(){
    std::map<std::string, std::vector<std::string>> loan = {};
    for(std::pair<std::string, std::vector<Book>> pair : collection_){
        for(Book book : pair.second){
            if(book.reservations == 0){
                if(loan.find(book.author) == loan.end()){
                    loan.insert({book.author, {}});
                   }
                loan.at(book.author).push_back(book.title);
            }
        }
    }
    return loan;
}


