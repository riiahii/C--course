/**
 * Class: University
 * -----------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet / Programming 2: Structures
 * -----------------
 * Valmiiksi toteutettujen lisäksi lisätty toiminnat täydennettäviin metodeihin
 *
 * Ohjelman kirjoittaja
 * Nimi: Riia Hiironniemi
 * Opiskelijanumero: 150271556
 * Käyttäjätunnus: vcrihi
 * E-Mail:  riia.hiironniemi@tuni.fi
 **/

#include "university.hh"
#include <iostream>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);
    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);
    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));
    std::map<int, Account*>::iterator iter = accounts_.find(account);
    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}

void University::sign_up(Params params)
{
    // Tehdään syötteiden virhetarkastelu samalla kaavalla kuin muissakin metodeissa
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    // Onko kyseinen oppilas jo valimistunut
    if ( accounts_.at(account)->get_is_graduated() )
    {
        std::cout << ALREADY_GRADUATED << std::endl;
        return;
    }

    // Jos tarvittavat ehdot täyttyvät, lisätään kurssi oppilaalle
    if ( courses_.at(code)->sign_up(accounts_.at(account)) )
    {
        accounts_.at(account)->add_courses(courses_.at(code));
    }
}

void University::complete(Params params)
{
    // Tehdään syötteiden virhetarkastelu samalla kaavalla kuin muissakin metodeissa
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));
    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    // Suoritetaan kurssi ja tulostetaan siitä viesti Account moduulilla
    accounts_.at(account)->complete(courses_.at(code), true);
}

void University::print_signups(Params params)
{
    // Tehdään syötteiden virhetarkastelu samalla kaavalla kuin muissakin metodeissa
    std::string code = params.at(0);

    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    // Tulostetaan kurssin opiskelijat Course moduulilla
    courses_.at(code)->print_signups();

}

void University::print_completed(Params params)
{
    // Tehdään syötteiden virhetarkastelu samalla kaavalla kuin muissakin metodeissa
    int account = std::stoi(params.at(0));

    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    // Tulostetaan suoritetut kurssit Account moduulilla
    accounts_.at(account)->print_completed();

}

void University::print_study_state(Params params)
{
    // Tehdään syötteiden virhetarkastelu samalla kaavalla kuin muissakin metodeissa
    int account = std::stoi(params.at(0));

    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    // Tulostetaan tilanne Account moduulilla
    accounts_.at(account)->print_study_state();

}

void University::graduate(Params params)
{
    // Tehdään syötteiden virhetarkastelu samalla kaavalla kuin muissakin metodeissa
    int account = std::stoi(params.at(0));

    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    // Suoritetaan valmistuminen Account moduulilla
    accounts_.at(account)->graduate();
}
