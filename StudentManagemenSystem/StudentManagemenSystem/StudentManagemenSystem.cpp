// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

// Student Database Management System in C++
// Technologies: C++, MySQL, OOP, Data Structures, Multi-threading, Encryption/Decryption

#include <iostream>
#include <string>
#include <vector>
#include <mutex>
#include <mysql.h>

std::mutex db_mutex; // Mutex for thread-safe database operations

class DatabaseManager {
private:
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

public:
    DatabaseManager() {
        conn = mysql_init(nullptr);
        if (!conn) {
            std::cerr << "MySQL initialization failed!" << std::endl;
            exit(EXIT_FAILURE);
        }

        connect();
    }

    ~DatabaseManager() {
        mysql_close(conn);
    }

    void connect() {
        if (!mysql_real_connect(conn, "localhost", "root", "1iso*help", "student_db", 3306, nullptr, 0)) {
            std::cerr << "MySQL connection failed: " << mysql_error(conn) << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    void executeQuery(const std::string& query) {
        std::lock_guard<std::mutex> lock(db_mutex);
        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Query execution failed: " << mysql_error(conn) << std::endl;
        }
        else {
            std::cout << "Query executed successfully." << std::endl;
        }
    }

    void fetchQuery(const std::string& query) {
        std::lock_guard<std::mutex> lock(db_mutex);
        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Query execution failed: " << mysql_error(conn) << std::endl;
            return;
        }

        res = mysql_store_result(conn);
        if (!res) {
            std::cerr << "Failed to retrieve result set: " << mysql_error(conn) << std::endl;
            return;
        }

        int num_fields = mysql_num_fields(res);
        while ((row = mysql_fetch_row(res))) {
            for (int i = 0; i < num_fields; ++i) {
                std::cout << (row[i] ? row[i] : "NULL") << "\t";
            }
            std::cout << std::endl;
        }

        mysql_free_result(res);
    }
};

class User {
protected:
    std::string username;
    std::string password;

public:
    virtual void menu() = 0;
};

class Admin : public User {
private:
    DatabaseManager& dbManager;

public:
    Admin(DatabaseManager& dbManager) : dbManager(dbManager) {}

    void addStudent(const std::string& name, int age, const std::string& course) {
        std::string query = "INSERT INTO students (name, age, course) VALUES ('" + name + "', " + std::to_string(age) + ", '" + course + "');";
        dbManager.executeQuery(query);
        std::cout << "Student added successfully." << std::endl;
    }

    void deleteStudent(int id) {
        std::string query = "DELETE FROM students WHERE id = " + std::to_string(id) + ";";
        dbManager.executeQuery(query);
        std::cout << "Student deleted successfully." << std::endl;
    }

    void viewStudents() {
        std::string query = "SELECT * FROM students;";
        dbManager.fetchQuery(query);
    }

    void menu() override {
        int choice;
        do {
            std::cout << "\nAdmin Menu:\n1. Add Student\n2. Delete Student\n3. View Students\n4. Logout\nEnter your choice: ";
            std::cin >> choice;

            switch (choice) {
            case 1: {
                std::string name, course;
                int age;
                std::cout << "Enter student name: ";
                std::cin >> name;
                std::cout << "Enter student age: ";
                std::cin >> age;
                std::cout << "Enter student course: ";
                std::cin >> course;
                addStudent(name, age, course);
                break;
            }
            case 2: {
                int id;
                std::cout << "Enter student ID to delete: ";
                std::cin >> id;
                deleteStudent(id);
                break;
            }
            case 3:
                viewStudents();
                break;
            case 4:
                std::cout << "Logging out..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice!" << std::endl;
            }
        } while (choice != 4);
    }
};

int main() {
    DatabaseManager dbManager;

    Admin admin(dbManager);
    admin.menu();

    return 0;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
