#include <iostream>
#include <string>

class Toy{
private:
    std::string name;
public:
    Toy(std::string name) : name(name) { 
        std::cout << "Create by\t" << name << "\n";
    };
    Toy() : Toy("Some Toy"){};

    std::string getName(){return name;}

    ~Toy(){
        std::cout << "Killed!!!\t" << name << "\n";
    }
};

class shared_ptr_toy{
private:
    Toy* m_toy;
    int* m_counter;
public:
    shared_ptr_toy() : m_toy(nullptr), m_counter(nullptr){}
    shared_ptr_toy(Toy* toy){
        m_toy = new Toy(*toy);
        m_counter = new int(0);
        ++(*m_counter);
    }

    shared_ptr_toy(const shared_ptr_toy& other){
        m_toy = new Toy(*other.m_toy);
        m_counter = other.m_counter;
        ++(*m_counter);
    }

    shared_ptr_toy& operator= (const shared_ptr_toy& other){
        if (this == &other) return *this;
        if (m_toy != nullptr){
            delete m_toy;
            delete m_counter;
        }

        m_toy = new Toy(*other.m_toy);
        m_counter = other.m_counter;
        ++(*m_counter);
        return *this;
    }

    ~shared_ptr_toy(){
        if (*m_counter > 0) --(*m_counter);
        if (*m_counter == 0){
            delete m_toy;
            delete m_counter;
        }
    }
};

shared_ptr_toy make_shared_toy(Toy* toy){
    shared_ptr_toy ptr(toy);
    return ptr;
}

shared_ptr_toy make_shared_toy(const std::string &name){
    shared_ptr_toy ptr(new Toy(name));
    return ptr;
}

int main(){
    shared_ptr_toy ptr2 = make_shared_toy(new Toy("ball"));

    Toy *a = new Toy("Tedy");
    shared_ptr_toy ptr1(a);
    ptr2 = ptr1;

    return 0;
}
