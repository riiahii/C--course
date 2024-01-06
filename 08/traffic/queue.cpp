#include "queue.hh"

// Implement the member functions of Queue here

Queue::Queue(unsigned int cycle):
    first_(nullptr), last_(nullptr), is_green_(false), cycle_(cycle)
{

}

Queue::~Queue()
{
    Vehicle* current = first_, *temp;
    while(current != nullptr){
        temp = current;
        current = current->next;
        delete temp;
    }
}

void Queue::enqueue(const string &reg)
{
    Vehicle* newVehicle = new Vehicle;
      newVehicle->reg_num = reg;
      newVehicle->next = nullptr;

      // If the queue is empty, set the new vehicle as the first
      if (first_ == nullptr) {
        first_ = newVehicle;
        if(is_green_){
            cout << "GREEN: The vehicle " << first_->reg_num << " need not stop to wait" << endl;
            dequeue();
        }
      }
      else {
        // Otherwise, add the new vehicle to the end of the queue
        last_->next = newVehicle;
      }
      last_ = newVehicle;


}

void Queue::switch_light()
{

    if (!is_green_) {
            // Vaihdetaan valo vihreäksi
            is_green_ = true;
            cout << "GREEN: ";
            // Laskuri vihreän valon aikana eteenpäin päästettäville ajoneuvoille
            unsigned int count = 0;

            if(first_ != nullptr){
                cout << "Vehicle(s) ";

            // Käydään läpi jonon ajoneuvot ja päästetään enintään cycle_ ajoneuvoa eteenpäin
            while (first_ && count < cycle_) {
                cout << first_->reg_num << " ";
                dequeue();
                ++count;
            }
            cout << "can go on" << endl;

            // Asetetaan valo takaisin punaiseksi
            is_green_ = false;
            }
            // Jos jonossa ei ole autoja
            else{
                cout << "No vehicles waiting in traffic lights" << endl;
            }
            }
    else {
        // Valo oli vihreä, vaihdetaan se punaiseksi
        is_green_ = false;
            cout << "RED: No vehicles waiting in traffic lights" << endl;


        }
}

void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}

void Queue::print() const
{
    string color = "RED";
    if(is_green_){
        color = "GREEN";
    }
    cout << color << ": ";
    if(first_ != nullptr){
        cout << "Vehicle(s) ";

        Vehicle* current = first_;
                while (current != nullptr) {
                    cout << current->reg_num << " ";
                    current = current->next;
                }
                cout << "waiting in traffic lights" << endl;
    }
    else {
           cout << "No vehicles waiting in traffic lights" << endl;
       }
}

bool Queue::dequeue()
{
    if (!is_green_ || first_ == nullptr) {
            // Valo on punainen tai jono on tyhjä, ei voida poistaa mitään
            return false;
        }
        else {
            // Poistetaan ensimmäinen ajoneuvo jonosta
            Vehicle* old_first = first_;
            first_ = first_->next;
            delete old_first;
            return true;
        }
}
