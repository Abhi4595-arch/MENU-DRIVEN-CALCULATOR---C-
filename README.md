# Menu-Driven Calculator

A modular **Menu-Driven Calculator** built using **C++**, with a structured backend, web-based frontend, calculation history, analytics, and persistent data storage.

The project demonstrates object-oriented programming, modular architecture, REST-style API handling, database integration, input validation, and a responsive web interface.

---

## 📌 Project Overview

The Menu-Driven Calculator is a full-stack calculator application designed to perform multiple mathematical operations through an easy-to-use menu-based interface.

The application consists of:

- A **C++ backend** responsible for calculation logic and API handling
- A **web frontend** built with HTML, CSS, and JavaScript
- **SQLite database** support for storing calculation history
- **History management**
- **Usage analytics**
- **Input validation**
- **Modular and extensible architecture**

The project is designed so that new calculator operations can be added without significantly changing the existing architecture.

---

## ✨ Features

### 🧮 Calculator Operations

The calculator supports multiple mathematical operations, including:

- Addition
- Subtraction
- Multiplication
- Division
- Power
- Square Root
- Percentage
- Average
- Factorial
- Modulus
- Other supported operations implemented in the calculator module

### 📋 Menu-Driven Interface

Users can select an operation from the calculator operation menu and provide the required input values.

The interface dynamically displays the inputs required for the selected operation.

### 🖥️ Web Interface

The frontend provides:

- Dashboard
- Calculator page
- Keypad calculator
- Calculation history
- Analytics
- About section
- Responsive layout
- Interactive operation selection

### 📊 Analytics

The application provides information such as:

- Total calculations
- Operation usage
- Most frequently used operations
- Usage statistics

### 🕘 Calculation History

Previous calculations can be stored and displayed through the history section.

The application provides a clear history interface for viewing previous calculations.

### 💾 Database Support

Calculation data is persisted using a database.

Database-related functionality is implemented separately from the calculator logic to maintain a modular architecture.

### ✅ Input Validation

The project includes validation for calculator inputs and handles invalid or unsupported operations appropriately.

### 🔌 Backend API

The C++ backend provides API functionality for communication between the frontend and calculator engine.

---

## 🏗️ Project Architecture

```text
MENU-DRIVEN-CALCULATOR/
│
├── backend/
│   ├── include/
│   │   ├── analytics/
│   │   ├── api/
│   │   ├── calculator/
│   │   ├── database/
│   │   ├── history/
│   │   ├── logging/
│   │   ├── models/
│   │   └── validation/
│   │
│   ├── src/
│   │   ├── analytics/
│   │   ├── api/
│   │   ├── calculator/
│   │   ├── database/
│   │   ├── history/
│   │   ├── logging/
│   │   ├── models/
│   │   ├── validation/
│   │   └── main.cpp
│   │
│   ├── tests/
│   └── CMakeLists.txt
│
├── data/
│   ├── .gitkeep
│   └── calculations.db
│
├── docs/
│   ├── ENHANCEMENTS.md
│   ├── EXCEPTION_HANDLING.md
│   ├── FLOWCHART.md
│   ├── MODULES.md
│   ├── README.md
│   ├── SAMPLE_OUTPUTS.md
│   └── VIVA.md
│
├── frontend/
│   ├── css/
│   │   └── style.css
│   ├── js/
│   │   └── app.js
│   └── index.html
│
├── CMakeLists.txt
├── InstallationLog.txt
├── LICENSE
└── README.md