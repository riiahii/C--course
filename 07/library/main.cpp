/* Kirjasto
 *
 * Kuvaus:
 * Ohjelma lukee käynnistyessää kirjastojen kokoelmiin liittyviä tietoja tekstitiedostosta ja tallentaa ne
 * std::map-tietorakenteeseen. Käyttäjä voi tehdä hakuja tähän tietorakenteeseen. Library-luokassa voidaan muokata haluttua
 * kirjastoa ja sieltä saadaan myös tietoa kirjaston kirjoista. Ohjelmalle syötetään ensin haluttu tiedosto kirjastoista
 * ja sen jälkeen ohjelmalle voi antaa käskyjä:
 * -libraries: tulostaa aakkosjärjestyksessä kaikki kirjastot
 * -material: tulostaa aakkosjärjestyksessä parametrinä annetun kirjaston kaikki kirjat
 * -books: tulostaa kirjojen nimen aakkosjärjestyksessä kaikki parametrinä annetun kirjaston ja parametrinä annetun tekijän
 * kirjat ja niiden varaustiedot
 * -reservable: tulostaa lyhimmän varausjonon parametrinä annetun tekijän ja parametrinä annetun kirjalle ja kaikki kirjastot
 * aakkosjärjestyksessä, joissa on saman pituinen varausjono
 * -loanable: tulostaa kaikki kirjat, jotka ovat lainattavissa aakkosjärjestyksessä
 *
 *
 *
 * Ohjelman kirjoittajat
 * Nimi: Anna Koskinen & Riia Hiironniemi
 * Opiskelijanumero: 150185079 & 150271556
 * Käyttäjätunnus: tsanko & vcrihi
 * E-Mail: anna.i.koskinen@tuni.fi & riia.hiironniemi@tuni.fi
 *
 * Muuta huomioitavaa:
 * Kaikki commitit on totetettu Riia Hiironniemen käyttäjällä.
 *
 */

#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include "library.hh"
#include <algorithm>

using Database = std::map<std::string, Library>;

// Split erottelee merkkijonon halutuista erotinmerkeistä ja lisää saadut osat vektoriin, jonka funktio palauttaa.
std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    // Jaetaan merkkijono halutuista erorinmerkeistä
    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}

// Validate tarkistaa onko annetun vektorin pituus oikea.
bool validate(const std::vector<std::string> &parts)
{
    return parts.size() == 4;
}

// Funktio avaa syötetyn tekstitiedoston ja lisää Library-luokkiin kirjastojen tiedot
bool readInputFile(const std::string &filename,
                   Database &db)
{
    std::fstream file(filename);

    // Jos tiedostoa ei pystytä avaamaan tulostetaan virheilmoitus
    if(! file) {
        std::cout << "Error: input file cannot be opened" << std::endl;
        return false;
    }

    // Jaetaan csv-tiedoston rivit splitin avulla
    std::string line = "";
    std::vector<std::string> line_parts = {};
    while(std::getline(file, line)) {
        line_parts = split(line, ';', true);

        // Jos kaikkia neljää kohtaa ei ole, tulostetaan virheilmoitus
        if(! validate(line_parts)){
            std::cout << "Error: empty field" << std::endl;
            return false;
        }
        else{
            std::string library = line_parts.at(0);
            std::string author = line_parts.at(1);
            std::string title = line_parts.at(2);
            std::string reservations = line_parts.at(3);

            // Onko kirjasto tietokannassa
            if(db.find(library) == db.end()) {
                db.insert({library, Library(library)});
            }

            // Lisää kirja ja kirjailija
            int r = 0;
            if(reservations != "on-the-shelf") {
                r = std::stoi(reservations);
            }
            db.at(library).addBook(author, title, r);
        }
    }
    file.close();
    return true;
}

// Tulostaa kirjastot aakkosjärjestyksessä
void printLibraries(const Database &db)
{
    for(Database::const_iterator iter = db.begin(); iter != db.end(); ++iter) {
        std::cout << iter->first << std::endl;
    }
}

// Funktio tulostaa lyhyimmän varausjonon tietylle kirjalle ja kirjastot, joissa kirjalla on saman pituinen jono.
// Parametreina Database db, kirjailijan nimi ja kirjan nimi.
void reservableBooks(const Database &db,
                     const std::string &author,
                     const std::string &title)
{
    // Luodaan vektori, johon tallennetaan varausnumerot sekä map, johon tallenetaan sekä varausnumero
    // että kirjastot, mistä kirja löytyy.
    std::vector<int> numbers = {};
    std::map<int, std::vector<std::string>> reservation_numbers = {};

    // Käydään Database läpi ja kutsutaan Library luokan funktiota reservable jokaisella Databasen kirjastolla.
    for(Database::const_iterator iter = db.begin(); iter != db.end(); ++iter) {
        Library library_name(db.at(iter->first));
        int reservation = library_name.reservable(author, title);

        // Lisätään varausnumero vektoriin numbers vain, jos kirja löytyy kirjastosta.
        if(reservation != -1) {
            numbers.push_back(reservation);
        }
        // Luodaan map:iin reservation_numbers uusi kohta, jos varausnumeroa ei vielä ole siellä.
        if(reservation_numbers.find(reservation) == reservation_numbers.end()) {
            reservation_numbers.insert({reservation, {}});
        }
        // Lisätään varausnumeron kohdalle kirjasto, missä varaus sijaitsee.
        reservation_numbers.at(reservation).push_back(iter->first);
    }
    // Jos vektoriin ei ole lisätty yhtään varausnumeroa, eli kirjaa/kirjailijaa ei löydy kirjastosta,
    // tulostetaan virheilmoitus.
    if(numbers.size() == 0) {
        std::cout << "Book is not a library book" << std::endl;
    }
    else {
        // Etsitään pienin varausnumero vektorista numbers.
        std::vector<int>::const_iterator smallest_it;
        smallest_it = std::min_element(numbers.begin(), numbers.end());
        // Tulostetaan varausnumerosta riippuen oikea teksti.
        if(*smallest_it >= 100) {
            std::cout << "Book is not reservable from any library" << std::endl;
        }
        else {
            if(*smallest_it == 0) {
                std::cout << "on the shelf" << std::endl;
            }
            else {
                std::cout << *smallest_it << " reservations" << std::endl;
            }
            // Tulostetaan kaikki kirjastot, joissa on saman mittainen varausjono
            for(std::map<int, std::vector<std::string>>::const_iterator iter = reservation_numbers.begin(); iter != reservation_numbers.end(); ++iter) {
                for(auto lib : reservation_numbers.at(iter->first)) {
                    if(iter->first == *smallest_it)
                    std::cout << "--- " << lib << std::endl;
                }
            }
        }
    }
}

// Etsii kaikkista kirjastoista lainattavissa olevat kirjat ja tulostaa ne aakkosjärjestyksessä
void loanableBooks(Database db){

    // Luodaan lainattaville kirjoille tietosäiliö
    std::map<std::string, std::vector<std::string>> loanable = {};

    // Käydään kirjastoja läpi
    for(std::pair<std::string, Library> pair : db){

        // Haetaan Library-luokasta lainattavissa olevat kirjat loanable()-metodin avulla
        std::map<std::string, std::vector<std::string>> loan = pair.second.loanable();

        // Onko kirja jo tietosäiliössä
        for(auto& loan_author : loan){
            std::string author = loan_author.first;
            std::vector<std::string>& books = loan_author.second;
            auto author_iter = loanable.find(author);

            // Lisätään uudet kirjaiijat ja heidän kirjat tietosäiliöön
            if(author_iter == loanable.end()){
                loanable.insert({author, books});
            }

            // Onko jo tietosäiliössä olevan kirjailijan kaikki kirjat säiliössä
            else{
                for(auto& book : books){
                    auto book_iter = std::find(loanable.at(author).begin(), loanable.at(author).end(), book);

                    // Jos ei vielä ole niin lisätään
                    if(book_iter == loanable.at(author).end()){
                        loanable.at(author).push_back(book);
                    }
                }
            }
            // Järjestetään kirjat aakkosjärjestykseen
            std::sort(loanable.at(author).begin(), loanable.at(author).end());
        }
    }

    // Tulostetaan
    for(auto const& [author_name, book_names] : loanable){
        for(auto const& book_name : book_names){
            std::cout << author_name << ": " << book_name << std::endl;
        }
    }
}

// Ohjelman käyttöliittymä ja sen virhetarkastelut
bool lib(const Database db)
{
    std::string command = "";

    // Jaetaan syöte osiin splitillä
    while(true) {
        std::cout << "lib> ";
        std::getline(std::cin, command);
        std::vector<std::string> splitted_command = {};
        splitted_command = split(command, ' ');

        // Lopettaa ohjelman
        if(command == "quit") {
            return false;
        }

        // Tulostaa kirjastot
        else if(command == "libraries" && splitted_command.size() == 1) {
            printLibraries(db);
        }

        // Tulostaa halutut materiaalit
        else if(splitted_command[0] == "material" && splitted_command.size() == 2) {

            // Jos kirjastoa ei ole tietosäiliössä
            if(db.find(splitted_command[1]) == db.end()){
                std::cout << "Error: unknown library" << std::endl;
                }

            // Etsitään Library-luokasta kirjat
            else{
            std::string library_n = splitted_command[1];
            Library library_name(db.at(library_n));
            library_name.material();
            }
        }

        // Komento 'books'
        else if(splitted_command[0] == "books" && splitted_command.size() == 3){
            std::string author = splitted_command[2];
            std::string library = splitted_command[1];

            // tarkistetaan löytyykö kirjastoa
            if(db.find(library) == db.end()){
                std::cout << "Error: unknown library" << std::endl;
            }

            // Etsitään luokasta halutut tiedot
            else{
                Library my_library(db.at(library));
                my_library.books(author);
            }
        }

        // Jos komento on reservable ja parametrejä on vähintään kolme
        else if(splitted_command[0] == "reservable" && splitted_command.size() >= 3){

            // Komennon ensimmäinen osa on kirjailija ja kirjan nimelle luodaan muuttuja
            std::string author = splitted_command[1];
            std::string title = "";
            int splitted_size = splitted_command.size();

            // Jos kirjan nimessä on usampi sana, muodostetaan yhteinäinen nimi
            for(int index = 2; index < splitted_size; ++index) {

                // Katsotaan onko kirjan nimen ympärillä heittomerkit ja poistetaan ne
                std::string::size_type find_char = splitted_command.at(index).find('"');
                if(find_char != std::string::npos) {
                    splitted_command.at(index).erase(find_char, 1);
                }

                // Lisätään komennosta erotellut kirjan nimet osat yhteen
                // Lisätään tyhjä väli muiden paitsi viimeisen sanan jälkeen
                if(index == splitted_size - 1) {
                    title += splitted_command.at(index);
                }
                else {
                    title += splitted_command.at(index) + " ";
                }
            }
            // Kutsutaan funktiota, joka tulostaa lyhyimmän varausjonon kirjalle
            reservableBooks(db, author, title);
        }

        // Komento 'loanable'
        else if(splitted_command[0] == "loanable" && splitted_command.size() == 1){

            // Käytetään ylempänä olevaa funktiota
            loanableBooks(db);
        }

        // Jos syötetään joku ym. komennoista, mutta annetaan väärä määrä parametrejä
        else if(splitted_command[0] == "libraries"
                or splitted_command[0] =="material"
                or splitted_command[0] == "books"
                or splitted_command[0] == "reservable"
                or splitted_command[0] == "loanable"){
            std::cout << "Error: wrong number of parameters" << std::endl;
        }

        // Jos annetaan väärä komento
        else {
            std::cout << "Error: unknown command" << std::endl;
        }
    }
    return true;
}

int main()
{
    Database db;
    // Avataan tiedosto, jossa tiedot kirjoista
    std::string inputname = "";
    std::cout << "Input file: ";
    std::getline(std::cin, inputname);

    // Tiedoston avaaminen ei onnistu tai csv-tiedostossa ei ole tarpeeksi tietoja ja ohjelma loppuu
    if(!readInputFile(inputname, db)){
        return EXIT_FAILURE;
    }

    // Lopetetaan ohjelma, kun komento on 'quit'
    if(! lib(db)) {
        return EXIT_SUCCESS;
    }
}
