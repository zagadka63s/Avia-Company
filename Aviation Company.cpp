#include <iostream>
#include <string>
#include <vector>
#include <map>
using namespace std;

class Ticket { // Класс Ticket, представляющий билет
private:
    int ticketNumber;
    string passengerName;
    int flightNumber;

public:
    Ticket(int number, const string& name, int flight)
        : ticketNumber(number), passengerName(name), flightNumber(flight) {}

    int getTicketNumber() const {
        return ticketNumber;
    }

    std::string getPassengerName() const {
        return passengerName;
    }

    int getFlightNumber() const {
        return flightNumber;
    }
};

class Passenger { // Класс Пассажира
private:
    string name;
    int age;

public:
    Passenger(string passengerName, int passengerAge)
        : name(passengerName), age(passengerAge) {}

    string getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }
};
// Класс Flight описывает полет
class Flight {
private:
    int flightNumber;// Номер полета
    string destination; // Пункта назначения
    string departureTime; // времени вылета
    int capacity; // вместимость
    vector<Passenger> passengers; // Список пассажиров

public:
    Flight(int number, string dest, string departTime, int cap)
        : flightNumber(number), destination(dest), departureTime(departTime), capacity(cap) {}

    int getFlightNumber() const {
        return flightNumber;
    }

    string getDestination() const {
        return destination;
    }

    string getDepartureTime() const {
        return departureTime;
    }

    int getRemainingSeats() const {
        return capacity - passengers.size();
    }

    bool addPassenger(const Passenger& passenger) {
        if (passengers.size() < capacity) {
            passengers.push_back(passenger);
            return true;
        }
        return false;
    }

    void displayInfo() const {
        cout << "Полет " << flightNumber << " на " << destination << ", Вылет: " << departureTime << "\n";
        cout << "Пассажиры на борту:\n";
        for (const Passenger& passenger : passengers) {
            cout << "- " << passenger.getName() << " (" << passenger.getAge() << " лет)\n";
        }
        cout << "Оставшиеся места: " << getRemainingSeats() << "\n";
    }

    Flight() = default;
};

class Airline { 
private:
    vector<Flight> flights; // Список полетов
    map<int, vector<Ticket>> ticketMap;// Сопоставление номера полета и билетов

public:
    // Метод для добавления полета в список
    void addFlight(const Flight& flight) {
        flights.push_back(flight);
    }

    // Метод для поиска полета по номеру
    Flight* findFlight(int flightNumber) {
        for (Flight& flight : flights) {
            if (flight.getFlightNumber() == flightNumber) {
                return &flight;
            }
        }
        return nullptr;
    }

    // Метод для бронирования билета
    bool bookTicket(int flightNumber, const std::string& passengerName) {
        Flight* flight = findFlight(flightNumber);
        if (flight && flight->getRemainingSeats() > 0) {
            int ticketNumber = ticketMap.size() + 1; // Генерация номера билета
            Ticket ticket(ticketNumber, passengerName, flightNumber);
            flight->addPassenger(Passenger(passengerName, 0)); // Возраст можно добавить в будущем

            // Добавление билета в карту билетов
            if (ticketMap.find(flightNumber) == ticketMap.end()) {
                ticketMap[flightNumber] = vector<Ticket>{ ticket };
            }
            else {
                ticketMap[flightNumber].push_back(ticket);
            }

            return true;
        }
        return false;
    }
    // Метод для вывода информации о забронированных билетах
    void displayTicketInfo(int flightNumber) const {
        // Поиск записи с данным ключом
        auto it = ticketMap.find(flightNumber);
        if (it != ticketMap.end()) {
            const vector<Ticket>& tickets = it->second;
            if (tickets.empty()) {
                cout << "Билеты на рейс не забронированы " << flightNumber << "\n";
                return;
            }
            cout << "Забронированные билеты на самолет " << flightNumber << ":\n";
            for (const Ticket& ticket : tickets) {
                cout << "- Ticket " << ticket.getTicketNumber() << ": Пассажир " << ticket.getPassengerName() << "\n";
            }
        }
        else {
            cout << "Билеты на рейс не забронированы " << flightNumber << "\n";
        }
    }

};

int main() {
    setlocale(LC_ALL, "russian");
    Airline airline;

    // Создание объектов Flight и добавление их в авиакомпанию
    Flight flight1(101, "Нью-Йорк", "08:00 AM", 150);
    Flight flight2(202, "Лос-Анджелес", "10:30 AM", 200);

    airline.addFlight(flight1);
    airline.addFlight(flight2);

    // Бронирование билетов для разных полетов
    airline.bookTicket(101, "John Doe");
    airline.bookTicket(101, "Jane Smith");
    airline.bookTicket(202, "Alice Johnson");

    // Вывод информации о забранированных билетах для каждого полета
    airline.displayTicketInfo(101);
    airline.displayTicketInfo(202);

    return 0;
}
