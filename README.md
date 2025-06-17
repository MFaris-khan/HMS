# Hospital Management System
Technologies: C++, MySQL, Windows Console

Developed a comprehensive console-based Hospital Management System (HMS) using C++ for the application logic and MySQL for database integration. The project is designed to manage core administrative tasks in a healthcare environment and supports a role-based access control system, where users from different departments (admin, reception, doctor, accounts, superuser) have specific permissions.

🔧 Key Features:
User Authentication & Role Management

Secure login system with department-based functionality (admin, doctor, receptionist, accountant).

Admins can manage user accounts and doctor records.

Patient Management

Add, view, update, and delete patient records.

Track patient problems, contact information, and history.

Appointment Scheduling

Schedule appointments between patients and doctors.

Modify or cancel appointments.

Validate doctor/patient IDs for correctness.

Billing System

Generate, view, and delete bills.

Track bill payment status (Paid/Unpaid).

Link bills with responsible staff.

Doctor Records

Add and manage doctor profiles, including contact info, specialization, and shift timings.

Accounts Dashboard

View payment history and outstanding bills for each patient.

License Management

System checks for license validity before granting access.

Robust Error Handling

Handles database errors gracefully and ensures data validation before execution.

📌 Additional Highlights:
Uses MySQL C API (mysql.h) for database interaction.

Utilizes Sleep, system("cls"), and _getch() for user experience on Windows console.

Cleanly separated concerns via OOP: separate classes for Patient, Doctor, Appointment, Bill, Accounts, and User Management.

License expiration mechanism to restrict access based on date.
