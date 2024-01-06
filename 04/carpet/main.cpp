/* Mysteerimatto
 *
 * Kuvaus:
 *   Ohjelma toteuttaa mysteerimaton, jossa sovelletaan mallintunnistusta
 * (pattern matching). Matto koostuu erivärisistä ruuduista ja samoin
 * malli, mutta mallin koko on aina 2 x 2, eli se koostuu neljästä
 * väriruudusta. Ohjelma etsii mallin esiintymiä matosta.
 *   Ohjelma kysyy ensin maton kokoa (leveys ja pituus). Käyttäjältä
 * kysytään myös, täytetäänkö matto (ruudukko) satunnaisesti arvottavilla
 * vai käyttäjän luettelemilla väreillä. Ensimmäisessä vaihtoehdossa
 * käyttäjältä kysytään satunnaislukugeneraattorin siemenlukua ja
 * jälkimmäisessä häntä pyydetään syöttämään niin monta väriä, kuin matossa
 * on ruutuja, jolloin luetellaan värien alkukirjaimet yhtenä pitkänä
 * merkkijonona.
 *   Joka kierroksella käyttäjältä kysytään etsittävää mallia (neljän
 * merkin/värin muodostamaa merkkijonoa). Ohjelma tulostaa, kuinka monta
 * mallin esiintymää matosta löytyi ja mistä kohdista ne löytyivät.
 *   Ohjelma tarkistaa, oliko käyttäjän antamat värikoodit hyväksyttäviä.
 * Ohjelma päättyy, kun käyttäjä antaa lopetuskomennon (merkki 'q' tai 'Q').
 *
 * Ohjelman kirjoittajat
 * Nimi: Anna Koskinen & Riia Hiironniemi
 * Opiskelijanumero: 150185079 & 150271556
 * Käyttäjätunnus: tsanko & vcrihi
 * E-Mail: anna.i.koskinen@tuni.fi & riia.hiironniemi@tuni.fi
 *
 * Muuta huomioitavaa:
 * Kaikki commitit on tehnyt Riia Hiironniemi, mutta sama ohjelma löytyy molempien käyttäjiltä.
*/

#include <iostream>
#include <string>
#include <vector>
#include <random>

// Värien esittelemiseen luettelotyyppi Color ja vektori
// ENUM_TO_COLOR värit kirjaimina.
enum Color {RED, GREEN, BLUE, YELLOW, WHITE, NUMBER_OF_COLORS};
const std::vector<char> ENUM_TO_COLOR = {'R', 'G', 'B', 'Y', 'W'};

std::vector<std::string> split(std::string line,
                               char separator,
                               bool ignore_empty = false)
// Jakaa parametrina annetun merkkijonon erotinmerkkien
// kohdalta osiin ja palauttaa osat vector-muuttujaan tallennettuna.
// Funktion parametrit ovat: jaettava merkkijono, erotinmerkki ja totuusarvo,
// halutaanko tyhjät välit ohittaa. Palauttaa vektorina erotellut merkkijonot.
{
    std::vector<std::string> splitted_vector = {};
    std::string substring = "";

    // Käydään merkkijono läpi ja lisätään merkkejä substring-muuttujaan
    // niin kauan, kunnes erotin tulee vastaan, jolloin lisätään substring
    // splitted_vector-vektoriin ja tyhjennetään substring.
    for(char c : line)
    {
        if(c == separator)
        {
            if(!(ignore_empty && substring.empty()))
            {
                splitted_vector.push_back(substring);
                substring.clear();
            }
        }
        else
        {
            substring += c;
        }
    }
    // Tyhjennetään turhat tyhjät välit.
    if(!(ignore_empty && substring.empty()))
    {
        splitted_vector.push_back(substring);
        substring.clear();
    }
    return splitted_vector;
}

std::vector<std::string> firstInput()
// Kysyy maton leveyden ja pituuden ja tallentaa ne muuttujiin käyttäen
// split-funktiota ja palauttaa vektorissa leveyden ja korkeuden int arvot.
{
    std::string line = "";
    std::cout << "Enter carpet's width and height: ";
    std::getline(std::cin, line);
    std::vector<std::string> numerics = split(line, ' ', true);
    return numerics;
}


bool inputToColor( std::string color_input,
                       std::vector<Color> &string_to_color)
// Funktio muuttaa syötteenä annetun merkkijonon merkit Color
// tyyppisiksi arvoiksi ja samalla tarkistaa, ettei merkkijono
// sisällä värejä, joita ei löydy luettelotyypistä Color.
// Parametreinä syötetty merkkijon ja vektori, johon Color tyyppiset
// arvot tallennetaan.
// Funktio palauttaa totuusarvon false, jos merkkiä ei ole oikea väri.
// Totuusarvo true palautetaan, jos merkkien muuttaminen Color
// tyyppisiksi onnistuu.
{
    // Käydään läpi merkkijonon color_input arvot ja muutetaan ne Color
    // tyyppisiksi. Palautetaan false, jos merkki ei ole yksi
    // halutuista väreistä.
    for(char letter : color_input)
    {
        if(letter == 'R')
        {
            string_to_color.push_back(RED);
        }
        else if(letter == 'G')
        {
            string_to_color.push_back(GREEN);
        }
        else if(letter == 'B')
        {
            string_to_color.push_back(BLUE);
        }
        else if(letter == 'Y')
        {
            string_to_color.push_back(YELLOW);
        }
        else if(letter == 'W')
        {
            string_to_color.push_back(WHITE);
        }
        else
        {
            return false;
        }
    }
    //Palautetaan true, jos merkkien muuttaminen onnistuu.
    return true;
}

void generateInputCarpet(std::vector<std::vector<Color>> &carpet,
                         std::vector<Color> string_to_color,
                         int width)
// Funktio muodostaa maton, jos käyttäjä antaa maton värit syötteenä.
// Parametreinä vektori carpet, johon sijoitetaan muodostettu matto,
// vektori string_to_color, joka sisältää halutun maton arvot Color
// tyyppisinä sekä kokonaisluku maton leveys.
{
    // Muodostetaan vektori row, johon sijoitetaan maton leveyden verran arvoja.
    std::vector<Color> row = {};

    // For-loop käy läpi jokaisen värin vektorissa string_to_color ja lisää niitä
    // vektoriin row, kunnes maton leveys on saavutettu. Tämän jälkeen täytetty vektori
    // row lisätään vektoriin carpet ja row:n sisälty tyhjennetään.
    // Maton täytty jatkuu samalla tavalla kunnes kaikki värit on käyty läpi.
    for(Color color : string_to_color)
    {
        row.push_back(color);
        int row_width = row.size();
        if(row_width == width)
        {
            carpet.push_back(row);
            row.clear();
        }
    }
}

void generateRandomCarpet(std::vector<std::vector<Color>> &carpet,
                          int width,
                          int height)
// Luo random-kirjaston avulla maton, joka on halutun levyinen ja korkuinen.
// Funktion parametrit ovat: matto vektorina, int maton leveys ja int maton korkeus.
{
    int seed = 0;
    std::cout << "Enter a seed value: ";
    std::cin >> seed;
    std::default_random_engine gen(seed);
    std::uniform_int_distribution<int> distr(0, 4);

    // Käy maton rivi-vektoreita ja rivien sarake-vektoreita läpi ja
    for(int i = 1; i <= height; ++i)
    {
        std::vector<Color> row;
        for(int j = 1; j <= width; ++j)
        {
            row.push_back(Color(distr(gen)));
        }
        carpet.push_back(row);
    }

    // Tyhjentää getlinen valmiiksi
    std::cin.ignore();

}

void start(std::vector<std::vector<Color>> &carpet,
           int width,
           int height)
// Funktio kysyy käyttäjältä, miten hän haluaa muodostaa maton.
// Kysymystä jatketaan kunnes käyttäjä syöttää oikean kirjaimen.
// Funktio kutsuu syötteestä riippuen oikeaa funktiota.
// Parametreinä vektori carpet maton luomista varten, sekä kokonaislukuina
// maton leveys ja korkeus.
{
    std::string start_input = "";
    bool keep_going = true;

    // While-loop:ia jatketaan niin kauan kuin keep_going totuusarvo on true.
    while(keep_going)
    {
        // Kysytään käyttäjää syöttämään R tai I riippuen halutusta maton muodostustavasta.
        std::cout << "Select start (R for random, I for input): ";
        std::getline(std::cin, start_input);

        // Jos syötetty kirjain on R, kutsutaan funktiota generateRandomCarpet maton
        // luomista varten ja pysäytetään while-loop asettamalla keep_going
        // totuusarvoksi false.
        if(start_input == "R" or start_input == "r")
        {
            generateRandomCarpet(carpet, width, height);
            keep_going = false;
        }

        // Jos syötetty kirjain on I, pyydetään käyttäjää syöttämään värejä maton
        //täyttämistä varten ja tarkistetaan, että syötetään oikea määrä oikeita värejä.
        else if(start_input == "I" or start_input == "i")
        {
            // Luodaan vektori, johon voidaan sijoittaa merkkijonon värit Color tyyppeinä.
            std::vector<Color> string_to_vector = {};
            std::string color_input = "";
            std::cout << "Input: ";
            std::getline(std::cin, color_input);
            int color_input_length = color_input.length();

            // Tarkistetaan, että syötetty merkkijono on tarpeeksi pitkä halutun kokoisen
            // maton luomista varten.
            // Jos merkkijono on väärän pituinen, tulostetaan virheilmoitus.
            if(color_input_length != width * height)
            {
                std::cout << " Error: Wrong amount of colors." << std::endl;
            }

            // Tarkistetaan funktion inputToColor avulla, että merkkijono sisältää vain
            // oikeita värejä. Jos inputToColor paluuarvona on false, tulostetaan
            // virheilmoitus.
            else if(!inputToColor(color_input, string_to_vector))
            {
                std::cout << " Error: Unknown color." << std::endl;
                continue;
            }

            // Jos matto on syötetty oikein, kutsutaan generateInputCarpet maton
            // luomista varten ja lopetetaan while-loop.
            else
            {
                generateInputCarpet(carpet, string_to_vector, width);
                keep_going = false;
            }
        }
    }
}

void printCarpet(std::vector<std::vector<Color>> const &carpet)
// Funktio tulostaa muodostetun maton. Parametreinä vektori carpet, joka
// sisältää tiedot maton sisällöstä.
{
    // Käydään carpet-vektorin sisällä olevan row-vektorin sisältämät arvot
    // läpi ja muutetaan Color tyyppiset arvot ENUM_TO_COLOR:in avulla oikeaa
    // väriä vastaavaksi kirjaimeksi.
    // Tulostetaan värit riveittäin.
    for(std::vector<Color> const &row : carpet)
    {
        for(Color color : row)
        {
            std::cout << ' ' << ENUM_TO_COLOR.at(color);
        }
        std::cout << std::endl;
    }
}

void findPattern(std::vector<Color> &pattern,
                 std::vector<std::vector<Color>> carpet)
// Etsii käyttäjän syöttämiä kuvioita matosta ja tallentaa kuvioiden määrän
// ja koordinaatin muuttujiin. Tulostaa kuvioiden määrän ja koordinaatit.
{
    // Luodaan koordinaateille (x, y) omat vektorit.
    std::vector<int> x = {};
    std::vector<int> y = {};
    int last_row = carpet.size() - 1;

    // Löydettyjen kuvioiden määrä tallennetaan muuttujaan.
    int match_count = 0;

    // Käydään mattoa alkio kerrallaan.
    for(int i = 0; i < last_row; ++i)
    {
        int colums = carpet.at(0).size();

        // Jos kaikki alkiot ovat samoja kuin halutussa kuviossa, lisätään
        // kuvioiden laskuriin +1 a koordinaattivektoreihin koordinaatit.
        for(int j = 0; j < colums - 1; ++j)
        {
            if(carpet.at(i).at(j) == pattern.at(0) and
                    carpet.at(i).at(j+1) == pattern.at(1) and
                    carpet.at(i+1).at(j) == pattern.at(2) and
                    carpet.at(i+1).at(j+1) == pattern.at(3))
            {
                match_count += 1;
                x.push_back(j + 1);
                y.push_back(i + 1);
            }
        }
    }

    // Jos kysyttyjä kuvioita löytyi, tulostetaan kaikki koordinaatit järjestyksessä
    // vasemmalta oikealle ja ylhäältä alas.
    if(match_count > 0)
    {
        for(int k = 0; k < match_count; ++k)
        {
            std::cout << " - Found at (" << x.at(k) << ", " << y.at(k) << ")" << std::endl;

        }
    }

    // Tulostetaan myös osumien määrä ja tyhjennetään koordinaatit ja kysytyn kuvion vektori.
    std::cout << " = Matches found: " << match_count << std::endl;
    x.clear();
    y.clear();
    pattern.clear();}

bool inputPattern(std::vector<std::vector<Color>> carpet)
// Funktio kysyy käyttäjää syöttämään matosta etsittäviä värimalleja.
// Parametrinä vektori carpet, jossa on aiemmin muodostettu
// matto. Funktio palauttaa totuusarvon false, jos käyttäjää syöttää kirjaimen q.
// True palautetaan, jos mallin syöttäminen onnistuu.
{
    // Muodostetaan vektori, johon tallennetaan syötetyn mallin värit Color
    // tyyppisinä arvoina.
    std::vector<Color> pattern_to_color;
    bool keep_going = true;

    // While-loop jatkuu niin kauan, kun keep_going totuusarvona on true.
    // Käyttäjää pyydetään syöttämään neljä väriä tai q-kirjaimen, jos
    // ohjelman suoritus halutaan lopettaa.
    while(keep_going)
    {
        std::string input = "";
        std::cout << "Enter 4 colors, or q to quit: ";
        std::getline(std::cin, input);
        int input_lenght = input.length();

        // Muutetaan syötetyn mallin kaikki kirjaimet isoiksi kirjaimiksi ja
        // lisätään ne merkkijonoon input.
        for(int i = 0; i < input_lenght; ++i)
        {
            char upper_case_letter = toupper(input.at(i));
            input += upper_case_letter;
        }

        // Poistetaan syötetystä mallista kirjaimet, joita ei ole muutettu
        // isoiksi, jolloin jää jäljelle oikean mittainen malli isoilla kirjaimilla.
        input.erase(0, input_lenght);

        // Jos käyttäjä syöttää mallin sijaan merkin q, palautetaan totuusarvo false.
        if(input == "q" or input == "Q")
        {
            return false;
        }

        // Tarkistetaan, että syötetty malli on oikean pituinen. Jos pituus on eri kuin neljä,
        // tulostetaan virheilmoitus.
        else if(input_lenght != 4)
        {
            std::cout << " Error: Wrong amount of colors." << std::endl;
        }

        // Tarkistetaan funktion inputToColor avulla, että merkkijono sisältää vain oikeita
        // värejä. Jos inputToColor paluuarvona on false, tulostetaan virheilmoitus.
        else if(!inputToColor(input, pattern_to_color))
        {
            std::cout << " Error: Unknown color." << std::endl;
        }

        // Jos syötetty malli on oikeanlainen, kutsutaan funktiota findPattern, jolla
        // mallia etsitään matosta.
        else
        {
            findPattern(pattern_to_color, carpet);
        }
    }
    return true;
}

int main()
{
    // Muodostetaan vektori numerics, joka sisältää tiedot maton leveydestä ja korkeudesta.
    std::vector<std::string> numerics = firstInput();

    // Vektorin numerics ensimmäinen arvo on leveys ja toinen korkeus. Muutetaan nämä arvot
    // string tyyppisistä kokonaisluvuiksi.
    int width = std::stoi(numerics.at(0));
    int height = std::stoi(numerics.at(1));

    // Tarkistetaan, että matto on oikean kokoinen. Jos leveys tai korkeus on pienempi kuin 2,
    // tulostetaan virheilmoitus ja lopetetaan ohjelma paluuarvolla EXIT_FAILURE.
    if(width < 2 or height < 2)
    {
        std::cout << " Error: Carpet cannot be smaller than pattern." << std::endl;
        return EXIT_FAILURE;
    }

    // Muodostetaan vektori carpet, johon matto ohjelman aikana luodaan.
    std::vector<std::vector<Color>> carpet;

    // Kutsutaan funktiota start, jotta saadaan selville, miten matto halutaan muodostaa.
    // Parametreinä on matto, maton leveys sekä maton korkeus.
    start(carpet, width, height);

    // Tulostetaan matto.
    printCarpet(carpet);

    // Kutsutaan funktiota, joka kysyy värimalleja. Jos funktion paluuarvo on false, ohjelman
    // suoritus loppuu paluuarvoon EXIT_SUCCESS.
    if(!inputPattern(carpet))
    {
        return EXIT_SUCCESS;
    }
}
