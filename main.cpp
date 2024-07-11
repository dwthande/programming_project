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
// Function to load student data from a file
void loadFromFile(const string& filename) {
    ifstream file(filename);
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string firstname, surname, gender, age_str, group_str;
        getline(ss, firstname, ',');
        getline(ss, surname, ',');
        getline(ss, gender, ',');
        getline(ss, age_str, ',');
        getline(ss, group_str, ',');

        int age = stoi(age_str);
        int group = stoi(group_str);
        Student student(firstname, surname, gender, age, group);

        string activity;
        while (getline(ss, activity, ',')) {
            bool found = false;
            // Check if the activity is a sport
            for (auto& sport : sports) {
                if (sport.name == activity) {
                    sport.addStudent(student);
                    student.sports.push_back(activity);
                    found = true;
                    break;
                }
            }
            // If not a sport, check if it's a club
            if (!found) {
                for (auto& club : clubs) {
                    if (club.name == activity) {
                        club.addStudent(student);
                        student.clubs.push_back(activity);
                        break;
                    }
                }
            }
        }
        students.push_back(student);
    }file.close
    file.close();
}

// Function to add a student and their activities
void addStudent() {
    string firstname, surname, gender;
    int age, group;
    vector<string> selectedSports;
    vector<string> selectedClubs;

    // Get student details
    cout << "Enter Firstname: ";
    cin >> firstname;
    cout << "Enter Surname: ";
    cin >> surname;
    cout << "Enter Gender (Male/Female): ";
    cin >> gender;
    cout << "Enter age: ";
    cin >> age;
    cout << "Enter Group (1, 2 or 3): ";
    cin >> group;

 // Ask if the student wants to participate in sports
    cout << "Do you want to participate in sports? (yes/no): ";
    string participateInSports;
    cin >> participateInSports;

    // If student wants to participate in sports
    if (participateInSports == "yes") {
        // Allow selection of one sport
        while (selectedSports.size() < 1) {
            cout << "Select a sport (Rugby, Athletics, Swimming, Football): ";
            string sport;
            cin >> sport;
            bool found = false;
            // Check if the selected sport exists and has remaining capacity
            for (auto& s : sports) {
                if (s.name == sport && s.getRemainingCapacity() > 0) {
                    s.addStudent({firstname, surname, gender, age, group});
                    selectedSports.push_back(sport);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Sport not found or full. Please try again.\n";
            }
        }

        // Allow selection of up to two clubs
        while (selectedClubs.size() < 2) {
            cout << "Select a club (Journalism Club, Red Cross Society, AISEC, Business Club, Computer Science Club): ";
            string club;
            cin >> club;
            bool found = false;
            // Check if the selected club exists and has remaining capacity
            for (auto& c : clubs) {
                if (c.name == club && c.getRemainingCapacity() > 0) {
                    c.addStudent({firstname, surname, gender, age, group});
                    selectedClubs.push_back(club);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Club not found or full. Please try again.\n";
            }
        }
    } else {
        // Allow selection of up to three clubs if no sport is selected
        while (selectedClubs.size() < 1 || selectedClubs.size() > 3) {
            cout << "Select up to 3 clubs (Journalism Club, Red Cross Society, AISEC, Business Club, Computer Science Club): ";
            string club;
            cin >> club;
            bool found = false;
            // Check if the selected club exists and has remaining capacity
            for (auto& c : clubs) {
                if (c.name == club && c.getRemainingCapacity() > 0) {
                    c.addStudent({firstname, surname, gender, age, group});
                    selectedClubs.push_back(club);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Club not found or full. Please try again.\n";
            }
            if (selectedClubs.size() >= 1 && selectedClubs.size() <= 3) {
                break;
            }
        }
    }

    // Create a new student object and add it to the global students vector
    Student newStudent(firstname, surname, gender, age, group);
    newStudent.sports = selectedSports;
    newStudent.clubs = selectedClubs;
    students.push_back(newStudent);

    cout << "Student added successfully!\n";
}
// Function to view all students and their activities
void viewStudents() {
    for (const auto& student : students) {
        cout << student.firstname << " " << student.surname << " (" << student.gender << ", " << student.age << ", Group " << student.group << ")";
        if (!student.sports.empty()) {
            cout << " - Sports: ";
            for (const auto& sport : student.sports) {
                cout << sport << " ";
            }
        }
        if (!student.clubs.empty()) {
            cout << " - Clubs: ";
            for (const auto& club : student.clubs) {
                cout << club << " ";
            }
        }
        cout << endl;
    }
}
