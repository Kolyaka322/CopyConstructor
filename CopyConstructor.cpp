#include <iostream>
#include <cstring>

class Person {
private:
    char* fullName;
    int age;

public:
    Person() : fullName(nullptr), age(0) {
        fullName = new char[1] {'\0'};
    }

    Person(const char* name, int a) : age(a) {
        if (name) {
            size_t len = std::strlen(name);
            fullName = new char[len + 1];
            std::strcpy(fullName, name);
        }
        else {
            fullName = new char[1] {'\0'};
        }
    }

    Person(const Person& other) : age(other.age) {
        if (other.fullName) {
            size_t len = std::strlen(other.fullName);
            fullName = new char[len + 1];
            std::strcpy(fullName, other.fullName);
        }
        else {
            fullName = new char[1] {'\0'};
        }
    }

    Person& operator=(const Person& other) {
        if (this == &other) return *this;
        delete[] fullName;
        age = other.age;
        if (other.fullName) {
            size_t len = std::strlen(other.fullName);
            fullName = new char[len + 1];
            std::strcpy(fullName, other.fullName);
        }
        else {
            fullName = new char[1] {'\0'};
        }
        return *this;
    }

    ~Person() {
        delete[] fullName;
    }

    void print() const {
        std::cout << "ПІБ: " << fullName << ", Вік: " << age;
    }
};

class Apartment {
private:
    Person* residents;
    int residentCount;
    int apartmentNumber;

public:
    Apartment() : residents(nullptr), residentCount(0), apartmentNumber(0) {}

    Apartment(int aptNum, int count, const Person* arr) : apartmentNumber(aptNum), residentCount(count) {
        if (residentCount > 0 && arr) {
            residents = new Person[residentCount];
            for (int i = 0; i < residentCount; ++i) {
                residents[i] = arr[i];
            }
        }
        else {
            residents = nullptr;
            residentCount = 0;
        }
    }

    Apartment(const Apartment& other) : apartmentNumber(other.apartmentNumber), residentCount(other.residentCount) {
        if (residentCount > 0 && other.residents) {
            residents = new Person[residentCount];
            for (int i = 0; i < residentCount; ++i) {
                residents[i] = other.residents[i];
            }
        }
        else {
            residents = nullptr;
            residentCount = 0;
        }
    }

    Apartment& operator=(const Apartment& other) {
        if (this == &other) return *this;
        delete[] residents;
        apartmentNumber = other.apartmentNumber;
        residentCount = other.residentCount;
        if (residentCount > 0 && other.residents) {
            residents = new Person[residentCount];
            for (int i = 0; i < residentCount; ++i) {
                residents[i] = other.residents[i];
            }
        }
        else {
            residents = nullptr;
            residentCount = 0;
        }
        return *this;
    }

    ~Apartment() {
        delete[] residents;
    }

    void print() const {
        std::cout << "Квартира № " << apartmentNumber << ", Кількість мешканців: " << residentCount << "\n";
        for (int i = 0; i < residentCount; ++i) {
            std::cout << "  ";
            residents[i].print();
            std::cout << "\n";
        }
    }
};

class Building {
private:
    char* address;
    Apartment* apartments;
    int apartmentCount;

public:
    Building() : address(nullptr), apartments(nullptr), apartmentCount(0) {
        address = new char[1] {'\0'};
    }

    Building(const char* addr, int count, const Apartment* arr) : apartmentCount(count) {
        if (addr) {
            size_t len = std::strlen(addr);
            address = new char[len + 1];
            std::strcpy(address, addr);
        }
        else {
            address = new char[1] {'\0'};
        }

        if (apartmentCount > 0 && arr) {
            apartments = new Apartment[apartmentCount];
            for (int i = 0; i < apartmentCount; ++i) {
                apartments[i] = arr[i];
            }
        }
        else {
            apartments = nullptr;
            apartmentCount = 0;
        }
    }

    Building(const Building& other) : apartmentCount(other.apartmentCount) {
        if (other.address) {
            size_t len = std::strlen(other.address);
            address = new char[len + 1];
            std::strcpy(address, other.address);
        }
        else {
            address = new char[1] {'\0'};
        }

        if (apartmentCount > 0 && other.apartments) {
            apartments = new Apartment[apartmentCount];
            for (int i = 0; i < apartmentCount; ++i) {
                apartments[i] = other.apartments[i];
            }
        }
        else {
            apartments = nullptr;
            apartmentCount = 0;
        }
    }

    Building& operator=(const Building& other) {
        if (this == &other) return *this;
        delete[] address;
        delete[] apartments;

        apartmentCount = other.apartmentCount;
        if (other.address) {
            size_t len = std::strlen(other.address);
            address = new char[len + 1];
            std::strcpy(address, other.address);
        }
        else {
            address = new char[1] {'\0'};
        }

        if (apartmentCount > 0 && other.apartments) {
            apartments = new Apartment[apartmentCount];
            for (int i = 0; i < apartmentCount; ++i) {
                apartments[i] = other.apartments[i];
            }
        }
        else {
            apartments = nullptr;
            apartmentCount = 0;
        }
        return *this;
    }

    ~Building() {
        delete[] address;
        delete[] apartments;
    }

    void print() const {
        std::cout << "Будинок за адресою: " << address << ", Всього квартир: " << apartmentCount << "\n";
        for (int i = 0; i < apartmentCount; ++i) {
            apartments[i].print();
        }
    }
};

int main() {
    system("chcp 1251>null");
    Person p1("Іванов Іван Іванович", 30);
    Person p2("Петренко Олена Сергіївна", 25);
    Person p3("Сидоренко Петро Петрович", 40);

    Person apt1_residents[] = { p1, p2 };
    Apartment apt1(12, 2, apt1_residents);

    Person apt2_residents[] = { p3 };
    Apartment apt2(15, 1, apt2_residents);

    Apartment building_apartments[] = { apt1, apt2 };
    Building house("вул. Хрещатик, 1", 2, building_apartments);

    std::cout << "--- Оригінальний будинок ---\n";
    house.print();

    std::cout << "\n--- Копія будинку (перевірка конструктора копіювання) ---\n";
    Building houseCopy = house;
    houseCopy.print();

    return 0;
}
