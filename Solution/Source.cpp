#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <iomanip>
#include <exception>
#include <sstream>
#include <fstream>


// „Q„u„p„|„y„x„…„z„„„u „†„…„~„{„ˆ„y„y „y „}„u„„„€„t„ „{„|„p„ƒ„ƒ„€„r „y „„‚„y „~„u„€„q„‡„€„t„y„}„€„ƒ„„„y „t„€„q„p„r„„„„u „ƒ„r„€„y


// „N„p„Š „€„ƒ„~„€„r„~„€„z „{„|„p„ƒ„ƒ - Date

class Date {
public:
    Date() {
        Year = 1900;
        Month = 01;
        Day = 01;
    }

    Date(const int& year, const int& month, const int& day) {
        Year = year;
        if (month > 12 || month < 1) {
            throw std::out_of_range("Month value is invalid: " + std::to_string(month));
        }
        else { Month = month; }
        Month = month;
        if (day > 31 || day < 1) {
            throw std::out_of_range("Day value is invalid: " + std::to_string(day));
        }
        else { Day = day; }
        Day = day;
    }
   
    int GetYear() const {
        return Year;
    }
    int GetMonth() const {
        return Month;
    }
    int GetDay() const {
        return Day;
    }

private:

    int Year;
    int Month;
    int Day;
};

// „P„u„‚„u„s„‚„…„x„{„p „€„„u„‚„p„„„€„‚„€„r „t„|„‘ „~„p„Š„u„s„€ „{„|„p„ƒ„p Date

bool operator==(const Date& lhs, const Date& rhs) {
    if (lhs.GetDay() == rhs.GetDay() && lhs.GetMonth() == rhs.GetMonth() && lhs.GetYear() == rhs.GetYear()) { return true; }
    return false;
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() < rhs.GetYear()) { return true; }
    else if (lhs.GetYear() > rhs.GetYear()) { return false; }
    else {
        if (lhs.GetMonth() < rhs.GetMonth()) { return true; }
        else if (lhs.GetMonth() > rhs.GetMonth()) { return false; }
        else {
            if (lhs.GetDay() < rhs.GetDay()) { return true; }
            else if (lhs.GetDay() > rhs.GetDay()) { return false; }
            else { return false; }
        }
    }
}

std::ostream& operator<<(std::ostream& stream, const Date& date) {
    stream << date.GetYear() << "-" << date.GetMonth() << "-" << date.GetDay();
    return stream;
}

std::istream& operator>>(std::istream& stream, Date& date) {
    
    std::string str_date;
    stream >> str_date;

    std::stringstream str_stream_date(str_date);

    int year;
    int month;
    int day;

    str_stream_date >> year;
    if (str_stream_date.fail() || str_stream_date.peek() != '-') {
        throw std::logic_error("Wrong date format: " + str_date);
    }
    str_stream_date.ignore(1);

    str_stream_date >> month;
    if (str_stream_date.fail() || str_stream_date.peek() != '-') {
        throw std::logic_error("Wrong date format: " + str_date);
    }
    str_stream_date.ignore(1);

    str_stream_date >> day;
    if (str_stream_date.fail() || !str_stream_date.eof()) {
        throw std::logic_error("Wrong date format: " + str_date);
    }

    date = { year, month, day };

    return stream;
}

// „Q„u„p„|„y„x„p„ˆ„y„‘ „q„p„x„ „t„p„~„~„„‡

class Database {
public:

    bool FindValue(const Date& date, const std::string& event) {
        for (auto a : Events[date]) {
            if (a == event) {
                return true;
            }
        }
        return false;
    }


    void AddEvent(const Date& date, const std::string& event) {
        if (FindValue(date, event) == false) {
            Events[date].push_back(event);
        }        
    }

    bool DeleteEvent(const Date& date, const std::string& event) {
        if (FindValue(date, event) == true) {
            Events[date].erase(std::remove(Events[date].begin(), Events[date].end(), event), Events[date].end());
            std::cout << "Deleted successfully" << std::endl;
            return true;
        }
        std::cout << "Event not found" << std::endl;
        return false;
    }

    int DeleteDate(const Date& date) {
        int N = Events[date].size();
        Events.erase(date);
        std::cout << "Deleted " << N << " events" << std::endl;
        return N;
    }

    void Find(const Date& date) const {
        std::vector<std::string> value;
        if (Events.count(date) > 0) {
            value = Events.at(date);
            for (auto a : value) {
                std::cout << a << std::endl;
            }
        }
    }

    void Print() const {
        std::vector<std::string> value;
        Date date;
        for (auto a : Events) {
            value = a.second;
            for (auto s : value) {
                std::cout << std::setw(4) << std::setfill('0') << a.first.GetYear() << '-';
                std::cout << std::setw(2) << std::setfill('0') << a.first.GetMonth() << '-';
                std::cout << std::setw(2) << std::setfill('0') << a.first.GetDay();
                std::cout << " " << s << std::endl;
            }
        }
    }

private:
    std::map<Date, std::vector<std::string>> Events;
};


int main() {

    try {

        Database db;
        std::string command;

        while (std::getline(std::cin, command)) {
            // „R„‰„y„„„p„z„„„u „{„€„}„p„~„t„ „ƒ „„€„„„€„{„p „r„r„€„t„p „y „€„q„‚„p„q„€„„„p„z„„„u „{„p„w„t„…„

            std::stringstream str_stream_cmd(command);
            std::string operation;
            str_stream_cmd >> operation;

            if (operation == "Add") {
                Date date;
                std::string event;
                str_stream_cmd >> date;
                str_stream_cmd >> event;
                db.AddEvent(date, event);

            }

            else if (operation == "Del") {
                Date date;
                std::string event;
                str_stream_cmd >> date;
                str_stream_cmd >> event;
                
                if (event.size() > 0) {
                    db.DeleteEvent(date, event);
                }
               
                else {
                    int N;
                    N = db.DeleteDate(date);
                }
            }
            
            else if (operation == "Find") {
                Date date;
                str_stream_cmd >> date;
                db.Find(date);
            }
            
            else if (operation == "Print") {
                db.Print();
            }
            
            else if (operation.empty()) {}
            
            else {
                throw std::logic_error("Unknown command: " + operation);
            }
        }
    }
    
    catch (const std::exception& exep) {
        std::cout << exep.what();
    }
    
    return 0;
    
}