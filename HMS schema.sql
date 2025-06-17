-- users table
CREATE TABLE users (
    password VARCHAR(10),
    username VARCHAR(50) PRIMARY KEY,
    dept VARCHAR(10) NOT NULL
);

-- bill table
CREATE TABLE bill (
    b_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    p_id INT NOT NULL,
    bill_date DATETIME DEFAULT CURRENT_TIMESTAMP,
    amount DECIMAL(10,2) NOT NULL,
    state VARCHAR(50) NOT NULL,
    created_by VARCHAR(50) NOT NULL
);

-- doctor table
CREATE TABLE doctor (
    d_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    d_name VARCHAR(50) NOT NULL,
    d_specialization VARCHAR(50) NOT NULL,
    d_number VARCHAR(11) NOT NULL,
    d_shift_start TIME NOT NULL,
    d_shift_end TIME NOT NULL
);

-- patient table
CREATE TABLE patient (
    p_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    p_name VARCHAR(50) NOT NULL,
    p_dob DATE NOT NULL,
    p_number VARCHAR(11) NOT NULL,
    p_address VARCHAR(191) NOT NULL,
    p_problem VARCHAR(255) NOT NULL
);

-- appointment table
CREATE TABLE appointment (
    a_id INT NOT NULL PRIMARY KEY AUTO_INCREMENT,
    p_id INT NOT NULL,
    d_id INT NOT NULL,
    appointment_date DATE NOT NULL,
    appointment_time TIME NOT NULL
);

-- license table
create table license(
ID int primary key,
valid_till date not null,
updated_on datetime default now()
);
