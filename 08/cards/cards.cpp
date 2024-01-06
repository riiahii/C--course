#include "cards.hh"

// TODO: Implement the methods here

Cards::Cards():
    top_(nullptr)
{
    
}

Card_data *Cards::get_topmost()
{
    return top_;
}

void Cards::add(int id)
{
    Card_data *card = new Card_data;
    card->data = id;
    card->next = top_;
    top_ = card;
}

void Cards::print_from_top_to_bottom(std::ostream &s)
{
    int index = 1;
    Card_data *current = top_;
    while(current != nullptr){
        s << index++ << ": " << current->data << std::endl;
        current = current->next;
    }
}

bool Cards::remove(int &id)
{
    if(top_ == nullptr){
        return false;
    }

    Card_data *paallimmainen = top_;
    top_ = paallimmainen->next;

    id = paallimmainen->data;
    delete paallimmainen;
    return true;

}

bool Cards::bottom_to_top()
{
    if(top_ == nullptr){
        return false;
    }
    if(top_->next == nullptr){
        return true;
    }

    Card_data *last = top_, *second_last;
    while(last->next != nullptr){
        second_last = last;
        last = last->next;
    }
    second_last->next = nullptr;
    last->next = top_;
    top_ = last;
    return true;

}

bool Cards::top_to_bottom()
{
    if(top_ == nullptr){
        return false;
    }
    if(top_->next == nullptr){
        return true;
    }

    Card_data *last = top_, *temp = top_;
    while(last->next != nullptr){

        last = last->next;
    }
    top_ = top_->next;
    last->next = temp;
    temp->next = nullptr;
    return true;
}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    if(top_ != nullptr){
        recursive_print(top_, s);
    }
}

Cards::~Cards()
{
    Card_data *current = top_, *temp;
    while(current != nullptr){
        temp = current;
        current = current->next;
        delete temp;
    }

}

int Cards::recursive_print(Card_data *top, std::ostream &s)
{
    if(top->next == nullptr){
        s << 1 << ": " << top->data << std::endl;
        return 1;
    }
    int result = recursive_print(top->next, s);
    s << ++result << ": " << top->data << std::endl;
    return result;
}
