#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <algorithm>

class Person {
protected:
    std::string name;
public:
    Person(std::string name) : name(std::move(name)) {}

    const std::string& getName() const {
        return name;
    }
};

class Student : public Person {
    std::string studentID;
    std::vector<std::string> enrolledCourses;
public:
    Student(std::string name, std::string studentID)
        : Person(std::move(name)), studentID(std::move(studentID)) {}

    void enrollInCourse(const std::string& courseCode) {
        enrolledCourses.push_back(courseCode);
    }

    const std::vector<std::string>& getEnrolledCourses() const {
        return enrolledCourses;
    }
};

class Instructor : public Person {
public:
    Instructor(std::string name) : Person(std::move(name)) {}
};

class Course {
    std::string code;
    std::string title;
    Instructor* instructor;
    std::vector<Student*> students;

public:
    Course(std::string code, std::string title)
        : code(std::move(code)), title(std::move(title)), instructor(nullptr) {}

    void setInstructor(Instructor* inst) {
        instructor = inst;
    }

    void addStudent(Student* student) {
        students.push_back(student);
    }

    const std::string& getCode() const {
        return code;
    }

    const std::string& getTitle() const {
        return title;
    }

     //  mor Metds to display course info, instructor, and enrolled students will be added here
};


class University {
    std::unordered_map<std::string, std::unique_ptr<Course>> courses;
    std::unordered_map<std::string, std::unique_ptr<Student>> students;
    std::unordered_map<std::string, std::unique_ptr<Instructor>> instructors;

public:
    void addCourse(std::unique_ptr<Course> course) {
        courses[course->getCode()] = std::move(course);
    }

    void addStudent(std::unique_ptr<Student> student) {
        students[student->getName()] = std::move(student);
    }

    void addInstructor(std::unique_ptr<Instructor> instructor) {
        instructors[instructor->getName()] = std::move(instructor);
    }

    Course* getCourse(const std::string& code) {
        return courses.count(code) ? courses[code].get() : nullptr;
    }

    Student* getStudent(const std::string& name) {
        return students.count(name) ? students[name].get() : nullptr;
    }

    Instructor* getInstructor(const std::string& name) {
        return instructors.count(name) ? instructors[name].get() : nullptr;
    }

    // Functions to manage enrollments, assign instructors, and list courses will be added here
};



void University::enrollStudentInCourse(const std::string& studentName, const std::string& courseCode) {
    Student* student = getStudent(studentName);
    Course* course = getCourse(courseCode);
    if (student && course) {
        student->enrollInCourse(courseCode);
        course->addStudent(student);
    }
}

void University::assignInstructorToCourse(const std::string& instructorName, const std::string& courseCode) {
    Instructor* instructor = getInstructor(instructorName);
    Course* course = getCourse(courseCode);
    if (instructor && course) {
        course->setInstructor(instructor);
    }
}

// Additinal functions to display universty data



int main() {
    University university;

    // Add some courses
    university.addCourse(std::make_unique<Course>("CS101", "Introduction to Computer Science"));
    university.addCourse(std::make_unique<Course>("CS102", "Advanced Programming"));

    // Add students
    university.addStudent(std::make_unique<Student>("Alice Johnson", "S001"));
    university.addStudent(std::make_unique<Student>("Bob Smith", "S002"));

    // Add instructors
    university.addInstructor(std::make_unique<Instructor>("Dr. Kidus Berhanu"));
    university.addInstructor(std::make_unique<Instructor>("Dr. Jane Smith"));

    // Enroll students in courses and assign instructors
    // These functionalities will be implemented in the next part

    return 0;
}


