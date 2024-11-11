#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Student {
public:
    Student(string firstName, string lastName, string studentId) {
        this->firstName = firstName;
        this->lastName = lastName;
        this->studentId = studentId;
    }

    string getFullName() const {
        return lastName + ", " + firstName;
    }
    string getId() const {
        return studentId;
    }

private:
    string firstName, lastName, studentId;
};

class Assignment {
public:
    Assignment(string name, int maxScore) {
        this->name = name;
        this->maxScore = maxScore;
    }

    string getName() const {
        return name;
    }
    int getMaxScore() const {
        return maxScore;
    }

private:
    string name;
    int maxScore;
};
class Gradebook {
public:
    void add_student(string fName, string lName,string studentId) {
        Student student(fName, lName, studentId);
        students.push_back(student);
    }

    void add_assignment(string name, int maxScore) {
        Assignment assignment(name, maxScore);
        assignments.push_back(assignment);
        grades.push_back(vector<int>(students.size(), -1));
    }

    void enter_grade(string studentID, string assignmentName, int grade) {
        int studentIndex = find_student_index(studentID);
        int assignmentIndex = find_assignment_index(assignmentName);
        if (studentIndex != -1 && assignmentIndex != -1) {
            grades[assignmentIndex][studentIndex] = grade;
        }
    }

    void report() {
        cout << "Last Name, First Name, Student Id";
        for (int j = 0; j < assignments.size(); ++j) {
            cout << ", " << assignments[j].getName();
        }
        cout << "\n";
        for (int i = 0; i < students.size(); ++i) {
            cout << students[i].getFullName() << ", " << students[i].getId();
            for (int j = 0; j < assignments.size(); ++j) {
                int grade = grades[j][i];
                if (grade == -1) {
                    cout << ", none";
                }
                else {
                    cout << ", " << to_string(grade);
                }
            }
            cout << "\n";
        }
    }

private:
    vector<Student> students;
    vector<Assignment> assignments;
    vector<vector<int>> grades;

    int find_student_index(const string& studentId) const {
        for (int i = 0; i < students.size(); ++i) {
            if (students[i].getId() == studentId) {
                return i;
            }
        }
        return -1;
    }

    int find_assignment_index(const string& name) const {
        for (int i = 0; i < assignments.size(); ++i) {
            if (assignments[i].getName() == name) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    Gradebook gradebook;
    gradebook.add_student("Bob","Bobberson", "ABC123");
    gradebook.add_student("Sam","Sammerson", "DEF456");
    gradebook.add_student("Jess","Jesserson", "HIJ789");
    gradebook.add_assignment("Quiz 1", 100);
    gradebook.add_assignment("Lab 1", 50);
    gradebook.add_assignment("Math HW1", 30);
    gradebook.enter_grade("DEF456", "Quiz 1", 95);
    gradebook.enter_grade("ABC123", "Quiz 1", 85);
    gradebook.enter_grade("HIJ789", "Lab 1", 49);
    gradebook.enter_grade("HIJ789", "Quiz 1", 93);
    gradebook.enter_grade("BABC123", "Lab 1", 0);
    gradebook.enter_grade("ABC123", "Math HW1", 23);
    gradebook.report();
    return 0;
}