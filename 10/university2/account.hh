/* Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Class representing a student or a staff account in the university system.
 *
 * Ohjelman kirjoittaja
 * Nimi: Riia Hiironniemi
 * Opiskelijanumero: 150271556
 * Käyttäjätunnus: vcrihi
 * E-Mail:  riia.hiironniemi@tuni.fi
 * */
#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>

class Course;

const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";

class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;

    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;

    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;

    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;

    /**
     * @brief get_is_graduated
     */
    bool get_is_graduated() const;

    /**
     * @brief add_courses
     * @param code
     * Lisää kurssin joko nykyisiin tai suoritettuihin riippuen, onko oppilas jo kurssilla
     */
    void add_courses(Course* code);

    /**
     * @brief check_completed_courses
     * @param code
     * Tarkistaa, onko kyseinen kurssi suoritettujen kurssien vektorissa
     */
    bool check_completed_courses(Course* code) const;

    /**
     * @brief complete
     * @param code
     * @param print, tulostetaanko tekstiä
     * Siirtää parametrinä annetun kurssin suoritettujen kurssien vektoriin virhetarkastelujen mennessä läpi
     */
    void complete(Course* code, bool print);

    /**
     * @brief print_study_state
     * Tulostetaan sen hetken kurssitilanne
     */
    void print_study_state() const;

    /**
     * @brief print_completed
     * Tulostaa suoritetut kurssit ja opiskelijan opintopisteet
     */
    void print_completed() const;

    /**
     * @brief graduate
     * Valmistuu kokonaan ja siirretään kaikki kurssit suoritettujen vektoriin
     */
    void graduate();

private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;

    // Vektoreissa kesken olevat kurssit ja toisessa suoritetut kurrsit
    std::vector<Course*> courses_;
    std::vector<Course*> completed_courses_;

    // Apu totuusarvomuuttuja sille, onko opiskelija valmistunut ja myös countteri opintopisteille
    bool is_graduated_ = false;
    int total_credits_ = 0;


};

#endif // ACCOUNT_HH


