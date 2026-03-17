# Banking Application

![Language](https://img.shields.io/badge/language-C++-00599C?style=flat-square&logo=c%2B%2B)
![Framework](https://img.shields.io/badge/framework-Qt-41CD52?style=flat-square&logo=qt)
![Database](https://img.shields.io/badge/database-SQL-4479A1?style=flat-square&logo=sqlite)

> A desktop banking application implementing account management, transactions and data persistence, built with C++ and the Qt framework.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Technologies](#technologies)
- [Build & Run](#build--run)
- [Database Schema](#database-schema)

---

## Overview

This project is a **desktop banking application** developed in C++ using the **Qt framework** for the graphical user interface. It simulates core banking operations: creating accounts, performing deposits and withdrawals, transferring funds between accounts, and persisting all data in an SQL database.

The project demonstrates proficiency in **object-oriented programming in C++**, **GUI development with Qt**, **SQL integration**, and **software architecture** (MVC pattern).

---

## Features

- Create and manage bank accounts (savings, current)
- Deposit and withdrawal operations with balance validation
- Fund transfers between accounts
- Transaction history with date and amount tracking
- Account statement generation
- Data persistence using SQLite
- Intuitive Qt-based graphical user interface
- Input validation and error handling

---

## Project Structure

```
banking-application-cpp/
├── src/                         # Core application logic (C++ / Qt)
│   ├── main.cpp                 # Application entry point
│   ├── mainwindow.h/.cpp        # Main window UI logic
│   ├── account.h/.cpp           # Base Account class
│   ├── savingsaccount.h/.cpp    # Savings account implementation
│   ├── currentaccount.h/.cpp    # Current account implementation
│   ├── transaction.h/.cpp       # Transaction model
│   ├── databasemanager.h/.cpp   # Database access layer (SQLite)
│   └── bankingsystem.h/.cpp     # Core business logic
│
├── img/                         # Screenshots / UI visuals
│
├── doc/                         # Project documentation
│
├── SPM3.pro                     # Qt project configuration file
├── README.md                    # Project documentation                  
```

---

## Technologies

| Technology | Role |
|------------|------|
| C++17 | Core programming language |
| Qt 5/6 | GUI framework (widgets, signals/slots) |
| SQLite / SQL | Local data persistence |
| Qt Creator | IDE and UI designer |
| qmake | Build system |

---

## Build & Run

### Prerequisites

- Qt 5.15+ or Qt 6.x (with Qt Widgets module)
- C++17 compatible compiler (GCC, Clang, MSVC)
- Qt Creator (recommended) or command-line qmake

### Build with Qt Creator

```
1. Open Qt Creator
2. File > Open Project > select SPM3.pro
3. Configure kit (compiler + Qt version)
4. Click Build > Build Project
5. Click Run
```

### Build from command line

```bash
# Clone the repository
git clone https://github.com/anastasia638/banking-application-cpp.git
cd banking-application-cpp

# Generate Makefile and compile
qmake SPM3.pro
make

# Run the application
./SPM3
```

---

## Database Schema

```sql
CREATE TABLE accounts (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  owner_name TEXT NOT NULL,
  account_type TEXT NOT NULL,   -- 'savings' or 'current'
  balance REAL DEFAULT 0.0,
  created_at TEXT DEFAULT CURRENT_TIMESTAMP
);

CREATE TABLE transactions (
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  account_id INTEGER REFERENCES accounts(id),
  type TEXT NOT NULL,           -- 'deposit', 'withdrawal', 'transfer'
  amount REAL NOT NULL,
  description TEXT,
  created_at TEXT DEFAULT CURRENT_TIMESTAMP
);
```

---

## Skills Demonstrated

- **C++ OOP:** Inheritance, polymorphism, encapsulation (Account hierarchy)
- **Qt Framework:** Widgets, signals and slots, UI forms (`.ui` files)
- **SQL / SQLite:** Database design, CRUD operations, relational integrity
- **MVC Pattern:** Separation of UI, business logic and data layers
- **Error handling:** Input validation, exception management

---

## Author

**Meriem Silmi** — Computer Science Student, France

[![GitHub](https://img.shields.io/badge/GitHub-anastasia638-black?style=flat-square&logo=github)](https://github.com/anastasia638)
