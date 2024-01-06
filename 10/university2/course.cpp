/**
 * Class: Course
 * -------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -------------
 * Valmiiksi toetutettujen metodien lisäksi bool sign_up, void print_sign_ups
 * joiden avulla university luokka toteuttaa ohjelmalle annettuja komentoje yhdessä
 * Account luokan kanssa
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Riia Hiironniemi
 * Opiskelijanumero: 150271556
 * Käyttäjätunnus: vcrihi
 * E-Mail:  riia.hiironniemi@tuni.fi
 **/

#include "course.hh"
#include <iostream>

Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}

Course::~Course()
{
}

void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}

void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}

void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}

void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}

const std::string Course::get_code() const
{
    return course_code_;
}

int Course::get_credits() const
{
    return credits_;
}

bool Course::sign_up(Account* student)
{

    // Jos on jo suorittanu tän kurssin nii ei saa uuestaa
    if ( student->check_completed_courses(&*this) )
    {
        std::cout << STUDENT_COMPLETED << std::endl;
        return false;
    }

    // Ei voi ilmottautuu toisen kerran
    for ( Account* account : students_ ){
        if ( student == account ){
            std::cout << STUDENT_EXISTS << std::endl;
            return false;
        }
    }

    // Myöskään opettajat ei voi ilmoo uuestaan
    for ( Account* account : course_staff_ ){
        if ( student == account ){
            std::cout << STUDENT_EXISTS << std::endl;
            return false;
        }
    }

    // Itse lisääminen
    // Lisätään opiskelija opiskelijoiden vektoriin
    students_.push_back(student);

    // Jos lisääminen onnistui palautetaan true, muulloin false
    return true;
}

void Course::print_signups() const
{
    // Käydään kaikki opiskelijat läpi ja haetaan niiden tiedot
    for ( Account* student : students_)
    {
        int account_number = student->get_account_number();
        std::string name = student->get_full_name();
        std::string email = student->get_email();

        std::cout << account_number << ": " << name <<
                     ", " << email << std::endl;
    }
}




