//
// Created by machtheg on 7/8/24.
//Programming project BBIT 1st Sem 2024

#include <iostream> // used to enter input into variables, as well as output those inputs to the user
#include <vector> // used to improve the arrays. Provides access to the vector keyword. In addition, stores elements in a linear arrangement. Allows fast access to any random element.
#include <string> // used for storing stings. These are names, clubs, and sports. Without this no string values would be able to be stored.
#include <fstream> // this is the file stream. It allows us to store the input into the .csv files.
#include <sstream> // this is the string stream. Used in performing the input and output of the string values.

using namespace std;

// Classes Implementation
// 1. Student Class -> To store details and selected activities.

class Student {
public:
    // Variable declaration
    string firstname;
    string surname;
    string gender;
    int age;
    int group;
    vector<string> sports;
    vector<string> clubs;

    // Definition of the constructor
    Student(string fn, string sn, string g, int a, int grp)
            : firstname(fn), surname(sn), gender(g), age(a), group(grp) {}
};

// Activity Implementation
// 2. Activity Class -> To store details for students
// Class representing an Activity with a name, maximum capacity, and enrolled students.
class Activity {
public:
    string name;
    int max_capacity;
    vector<Student> students;

    // Constructor to initialize activity name and capacity
    Activity(string n, int cap) : name(std::move(n)), max_capacity(cap) {}
    // Method to add a student to the activity if capacity allows
    bool addStudent(const Student& student) {
        if (students.size() < max_capacity) {
            students.push_back(student);
            return true;
        }
        }
        return false;
    }

    // Method to get the remaining capacity of the activity
    int getRemainingCapacity() const {
        return max_capacity - students.size();
    }
};

// Global list of students, sports, and clubs
vector<Student> students;
vector<Activity> sports;
vector<Activity> clubs;

// Function to initialize activities
void initializeActivities() {
    // Initialize sports
    sports.emplace_back("Rugby", 20);
    sports.emplace_back("Athletics", 20);
    sports.emplace_back("Swimming", 20);
    sports.emplace_back("Soccer", 20); // Corrected "Football" to "Soccer" for consistency

    // Initialize clubs
    clubs.emplace_back("Journalism Club", 60);
    clubs.emplace_back("Red Cross Society", 60);
    clubs.emplace_back("AISEC", 60);
    clubs.emplace_back("Business Club", 60);
    clubs.emplace_back("Computer Science Club", 60);
}
