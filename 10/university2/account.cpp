/** Class: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Luokassa valmiiksi tehtyjen metodien lisäksi toteutettu
 * bool is_graduated, void add_courses, bool check_completed, void complete,
 * void print_study_state, void print_completed ja void graduate.
 * Kaikki nuo ovat toteutettu että moduulissa university voidaan käyttää
 * käyttöjärjestelmän eri komentoja.
 *
 * Ohjelman kirjoittaja
 * Nimi: Riia Hiironniemi
 * Opiskelijanumero: 150271556
 * Käyttäjätunnus: vcrihi
 * E-Mail:  riia.hiironniemi@tuni.fi
 *
 **/

#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>
#include <algorithm>

Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}

Account::~Account()
{
}

void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}

std::string Account::get_email() const
{
    return email_;
}

std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}

bool Account::get_is_graduated() const
{
    return is_graduated_;
}

void Account::add_courses(Course* code)
{
    // Onko oppilas jo kurssilla
    for ( Course* course : courses_ )
    {
        if ( course == code )
        {
            // Lisätään kurssi suoritettuihin kursseihin
            completed_courses_.push_back(code);

            // Lisätään opintopistelaskuriin suoritetun kurssin pisteet
            int credits = code->get_credits();
            total_credits_ += credits;

            // Poistetaan suoritettu kurssi courses_ vektorista
            courses_.erase(std::remove(courses_.begin(), courses_.end(), code), courses_.end());
            return;
        }
    }

    // Jos onkin uus kurssi niin lisätään se kurssi-vektoriin
    std::cout << SIGNED_UP << std::endl;
    courses_.push_back(code);
}

bool Account::check_completed_courses(Course* code) const
{
    // Käydään läpi suoritettujen kurssien vektori ja palautetaan totuusarvo
    // siitä, löytyikö kyseistä kurssia jo suoritetuista
    for ( Course* course : completed_courses_ )
    {
        if ( course == code )
        {
            return true;
        }
    }
    return false;
}

void Account::complete(Course* code, bool do_print)
{
    // Asetetaan ensin apumuuttuja siitä onko opiskelijalla oikeus suorittaa kurssia
    bool can_complete = false;

    // Yritetään suorittaa sama kurssi uuestaan
    if ( check_completed_courses(code))
    {
        // Nyt kurssia ei voida enää suorittaa uuestaan
        can_complete = false;
    }

    // Oppilas ei ole koko kurssilla
    for ( Course* course : courses_ )
    {
        if ( course == code )
        {
            // Jos opiskelija löytyy kurssilta vaihdetaan totuusarvo trueksi,
            // muutoin se pysyy falsena, koska opiskelija ei ole kurssilla
            can_complete = true;
            break;
        }
    }

    // Jos totuusarvo on false, tulostetaan virheilmoitus
    if ( !can_complete)
    {
        std::cout << NO_SIGNUPS << std::endl;
    }

    // Muulloin totuusarvo on tietty true ja voidaan suorittaa kurssi
    else
    {
        // Jos suoritetaan vain yksi kurssi eikä valmistuta kokonaan ja halutaan tulostus näytölle
        if ( do_print == true)
        {
            // Jos kaikki kunnossa voidaan suorittaa kurssi
            std::cout << COMPLETED << std::endl;
        }

        // Siirretään kurssi suoritettuihin
        add_courses(code);
    }
}

void Account::print_study_state() const
{
    std::cout << "Current:" << std::endl;
    for ( Course* course : courses_)
    {
        // Käytetään luokan Course* metodia print_info(bool)
        course->print_info(true);
    }

    std::cout << "Completed:" << std::endl;

    // Käytetään suoritettujen kurssien tulostamiseen omaa metodia
    print_completed();


}

void Account::print_completed() const
{

    for ( Course* course : completed_courses_)
    {
        // Käytetään luokan Course* metodia print_info(bool)
        course->print_info(true);
    }

    // Tulostetaan vielä opintoåisteet
    std::cout << "Total credits: " << total_credits_ << std::endl;


}

void Account::graduate()
{
    std::cout << GRADUATED << std::endl;

    // Vaihdetaan opiskelija valmistuneeksi
    is_graduated_ = true;

    // Siirretään kaikki kesken olevat kurssit suoritetuiksi
    for ( Course* course : courses_)
    {
        complete(course, false);
    }
}
