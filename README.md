# StudentManagementSystem
The Student Management System is a robust C++ application designed to streamline the management of student records in an efficient and secure manner. This project demonstrates the power of object-oriented programming by offering a modular and maintainable codebase, integrated with a MySQL database for persistent data storage.

## Features

#### CRUD Operations: Add, delete, and view student records.

#### Database Integration: Persistent data storage using MySQL, adaptable for MS SQL.

#### Thread Safety: Uses mutex locks for secure, concurrent database operations.

#### Object-Oriented Design: Clean, modular code leveraging encapsulation and abstraction.

## Technologies Used

#### Programming Language: C++

#### Database Management System: MySQL (configurable for MS SQL)

#### Libraries:

#### MySQL Connector/C++

#### Standard Template Library (STL)

#### Additional Features: Multi-threading for secure operations

## Environment Configuration

### 1. MySQL Installation

#### a.Download and install the MySQL Community Server.

#### b.Set up a root user and password during installation.

#### c.Use tools like MySQL Workbench or command-line tools to manage the database.

### 2. C++ Compiler Setup

#### Install a C++ compiler supporting C++11 or later:

#### Windows: Visual Studio (recommended)

#### Linux/macOS: GCC or Clang

#### Configure your development environment:

#### Use an IDE like Visual Studio, CLion, or Code::Blocks.

#### Alternatively, use a text editor and compile via the command line.

### 3. MySQL Connector/C++ Installation

#### Download the MySQL Connector/C++.

#### Follow the instructions to install and link the connector library.

#### Ensure the mysql.h header file and libmysql.dll are available and linked in your project.

### 4. Database Preparation

#### Run the following SQL commands to set up the database:

CREATE DATABASE student_db;
USE student_db;
CREATE TABLE students (
    id INT AUTO_INCREMENT PRIMARY KEY,
    name VARCHAR(255) NOT NULL,
    age INT NOT NULL,
    course VARCHAR(255) NOT NULL
);

#### Running the Application

1. Compile the Program

Use the following command to compile the program (adjust paths for MySQL libraries as needed):

g++ student_db_mgmt.cpp -o student_db_mgmt -lmysqlclient -pthread

2. Run the Program

Execute the compiled binary:

./student_db_mgmt

3. Interact with the Program

Follow the prompts to:

Add a student (supports multi-word names and courses).

Delete a student by ID.

View all student records.

## Troubleshooting

#### 1. MySQL Connection Issues

Ensure the MySQL server is running.

Verify connection details in the code (e.g., host, username, password).

#### 2. Missing MySQL Connector Files

Check that the mysql.h header file and libmysql.dll are correctly linked.

#### 3. Compilation Errors

Ensure the MySQL Connector library paths are included during compilation.

### Contributions

Contributions are welcome! Feel free to open issues or submit pull requests to improve the system.

