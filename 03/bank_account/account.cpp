#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit):
    owner_(owner), has_credit_(has_credit), current_(0), credit_limit_(0)

{
    generate_iban();
}

void Account::set_credit_limit(int limit)
{
    if(has_credit_)
    {
        credit_limit_ = limit;
    }
    else
    {
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
    }
}

void Account::save_money(int save)
{
    current_ += save;
}

void Account::take_money(int take)
{
    int end_amount = current_ - take;
    if(has_credit_)
    {
        if(end_amount < -credit_limit_)
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
        }
        else
        {
            current_ = end_amount;
            std::cout << take << " euros taken: new balance of " << iban_ <<
                         " is " << current_ << " euros" << std::endl;
        }
    }
    else if(end_amount < 0)
    {
        std::cout << "Cannot take money: balance underflow" << std::endl;
    }
    else
    {
        current_ = end_amount;
        std::cout << take << " euros taken: new balance of " << iban_ <<
                     " is " << current_ << " euros" << std::endl;
    }
}

void Account::transfer_to(Account& account, int transfer)
{
    int end_amount = current_ - transfer;
    if(has_credit_)
    {
        if(end_amount < -credit_limit_)
        {
            std::cout << "Cannot take money: credit limit overflow" << std::endl;
            std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        }
        else
        {
            current_ = end_amount;
            account.save_money(transfer);
            std::cout << transfer << " euros taken: new balance of " << iban_ <<
                         " is " << current_ << " euros" << std::endl;
        }
    }
    else if(end_amount < 0)
    {
        std::cout << "Cannot take money: balance underflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
    }
    else
    {
        current_ = end_amount;
        account.save_money(transfer);
        std::cout << transfer << " euros taken: new balance of " << iban_ <<
                     " is " << current_ << " euros" << std::endl;
    }
}

void Account::print() const
{
    std::cout << owner_ << " : " << iban_ << " : " << current_ << " euros" <<std::endl;
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
