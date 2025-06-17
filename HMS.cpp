#include<iostream>
#include<string>
#include<cctype>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include<conio.h>
using namespace std;

const char* HOST = "";
const char* USER = "";
const char* PASS = "";
const char* DB = "";

MYSQL* conn; // Global Connection. Initialzed in connect_database()

string 		Current_User = ""; // This will store name of logged in user to print on bill.
string 		User_Dept = ""; // This will store dept of logged in user (if dept=admin) admin authority=true

// admin - reception - doctor - accounts


class BILL
{
public:
	void all_bills()
	{
		system("cls");
		string query = "SELECT * FROM bill";

		if (mysql_query(conn, query.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);

		MYSQL_ROW  check_row = mysql_fetch_row(res);

		if (check_row == 0)
		{
			system("cls");
			cout << "No Bills found..!\n";
			Sleep(2000);
			return;
		}

		MYSQL_ROW  row;
		mysql_data_seek(res, 0);
		int num_fields = mysql_num_fields(res);

		MYSQL_FIELD* field = mysql_fetch_fields(res);

		cout << "B ID\t\tP ID\t\tBill Date / Time \t\tAmount\t\tState\t\tCreated By\n";
		cout << "-----------------------------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{
			for (int i = 0; i < num_fields; i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
		}
		_getch();
	}
	void create_bill()
	{
		string p_id, amount, state, yn;
		cout << "Enter Patient ID: ";
		cin >> p_id;
		cout << "Enter Amount: ";
		cin >> amount;
		cout << "State: Paid / Unpaid (Y/N): ";
		cin >> yn;
		if (yn == "y")
		{
			state = "Paid";
		}
		else
		{
			state = "Unpaid";
		}

		string bill = "INSERT INTO bill(p_id, amount, state, created_by) VALUES ( '" + p_id + "', '" + amount + "', '" + state + "', '" + Current_User + "' )";

		if (mysql_query(conn, bill.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			system("cls");
			cout << "Bill Created..!\n";
			Sleep(2000);
		}
	}
	void delete_bill()
	{
		string b_id;
		cout << "Enter Bill ID: ";
		cin >> b_id;

		string remove = "DELETE FROM bill WHERE b_id = '" + b_id + "' ";
		if (mysql_query(conn, remove.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			system("cls");
			cout << "Bill removed..!\n";
			Sleep(2000);
		}
	}
	void display_bill()
	{
		string b_id;
		cout << "Enter bill ID: ";
		cin >> b_id;

		if (b_id == "a")
		{
			all_bills();
		}
		else
		{
			string show = "SELECT * FROM bill WHERE b_id = '" + b_id + "' ";
			if (mysql_query(conn, show.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}

			MYSQL_RES* res = mysql_store_result(conn);
			if (res == NULL)
			{
				cout << "No results : " << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}

			MYSQL_ROW row = mysql_fetch_row(res);
			int max = mysql_num_fields(res);
			system("cls");
			cout << "Bill ID: " << row[0] << "\tPatient ID: " << row[1] << "\tDate: " << row[2] << "\t" << "Amount: " << row[3] << "\t" << "Status: " << row[4] << "\n\n" << "Created By: " << row[5];
			_getch();
		}

		
	}

};

class APPOINTMENT
{
public:
	void all_appointments()
	{
		system("cls");
		string query = "SELECT * FROM appointment";

		if (mysql_query(conn, query.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row;

		int num_fields = mysql_num_fields(res);

		MYSQL_FIELD* field = mysql_fetch_fields(res);

		cout << "App ID\t\tP ID\t\tD ID \t\tApp Date\t\tApp Time\n";
		cout << "-----------------------------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{
			for (int i = 0; i < num_fields; i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
		}
		_getch();
	}

	void appointment_details()
	{
		cout << "Enter Appointment ID: ";
		string app_id; cin >> app_id;

		if (app_id == "a")
		{
			APPOINTMENT::all_appointments();
			return;
		}

		string find_appointment = "SELECT * FROM appointment  WHERE app_id = '" + app_id + "' ";

		if (mysql_query(conn, find_appointment.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);

		if (row == 0)
		{
			system("cls");
			cout << "Appointment not found..!\n";
			Sleep(2000);
			return;
		}

		system("cls");
		cout << "Appointment ID: " << row[0] << "\n\nPatient ID: " << row[1] << "\n\nDoctor ID: " << row[2] << "\n\nAppointment Date: " << row[3] << "\n\nAppointment Time: " << row[4] << endl;
		_getch();
	}

	void update_appointment()
	{
		system("cls");
		cout << "Enter Appointment ID: ";
		string ID; cin >> ID;
		system("cls");

		string validate = "select app_id from appointment where app_id = '" + ID + "' ";
		if (mysql_query(conn, validate.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);
			if (row == NULL)
			{
				system("cls");
				cout << "No appointment found..!\n";
				Sleep(2000);
				mysql_free_result(res);
				return;
			}
		}
		system("cls");
		cout << "What do you want to change?\n\n[1] Patient ID\n[2] Doctor ID\n[3] Appointment Date\n[4] Appointment Time\n";
		char op; cin >> op;
		string new_update = "";
		switch (op)
		{
		case'1': {
			system("cls");
			cout << "New Patient ID: ";
			cin >> new_update;

			string check = "SELECT p_id FROM patient WHERE p_id = '" + new_update + "' ";

			if (mysql_query(conn, check.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}

			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);

			if (row == 0)
			{
				system("cls");
				cout << "No patient found with ID: " << new_update << "\nPlease enter patient first.\n";
				Sleep(2000);
				mysql_free_result(res);
				return;
			}

			string validate = "UPDATE appointment set p_id = '" + new_update + "' WHERE app_id = '" + ID + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Appointment updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'2': {
			system("cls");
			cout << "New Doctor ID: ";
			cin >> new_update;

			string check = "SELECT d_id FROM doctor WHERE d_id = '" + new_update + "' ";

			if (mysql_query(conn, check.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}

			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);

			if (row == 0)
			{
				system("cls");
				cout << "No doctor found with ID: " << new_update << "\nPlease enter doctor first.\n";
				Sleep(2000);
				mysql_free_result(res);
				return;
			}

			string validate = "UPDATE appointment set d_id = '" + new_update + "' WHERE app_id = '" + ID + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Appointment updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'3': {
			system("cls");
			cout << "New Appointment Date (YYYY:MM:DD) : ";
			cin >> new_update;
			string validate = "UPDATE appointment set appointment_date = '" + new_update + "' WHERE app_id = '" + ID + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Appointment updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'4': {
			system("cls");
			cout << "New Appointment Time (HH:MM:SS) : ";
			cin >> new_update;
			string validate = "UPDATE appointment set appointment_time = '" + new_update + "' WHERE app_id = '" + ID + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Appointment updated..!\n";
				Sleep(2000);
			}
			break;
		}
		default: {
			system("cls");
			cout << "Enter valid choice\n";
			Sleep(2000);
			break;
		}

		}
	}

	void create_appointment()
	{
		string p_id, d_id, app_date, app_time;
		cout << "Patient ID: ";
		cin >> p_id;
		cout << "\nDoctor ID: ";
		cin >> d_id;
		cout << "\nAppointment Date (YYYY:MM:DD) : ";
		cin >> app_date;
		cout << "\nAppointment Time (HH:MM:SS) : ";
		cin >> app_time;

		string create_app = "INSERT INTO appointment(p_id, d_id, appointment_date, appointment_time ) VALUES ( '" + p_id + "' , '" + d_id + "' , '" + app_date + "' , '" + app_time + "' )";

		if (mysql_query(conn, create_app.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
		}
		else
		{
			system("cls");
			cout << "Appointment Created..!\n";
			Sleep(2000);
		}
	}
	void remove_appointment()
	{
		string ID;
		cout << "Enter appointment ID: ";
		cin >> ID;

		string check = "SELECT a_id from appointment WHERE a_id = '" + ID + "' "; // run this first

		if (mysql_query(conn, check.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);

		if (row == 0)
		{
			system("cls");
			cout << "No appointment found..!\n\a";
			Sleep(2000);
			return;
		}

		string remove = "DELETE FROM appointment WHERE a_id = '" + ID + "' ";

		if (mysql_query(conn, remove.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
		}
		else
		{
			system("cls");
			cout << "Appointment Deleted..!\n";
			Sleep(2000);
		}
	}
};

class PATIENT
{
public:

	void all_patients()
	{
		system("cls");
		string query = "SELECT * FROM patient";

		if (mysql_query(conn, query.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row;

		int num_fields = mysql_num_fields(res);

		MYSQL_FIELD* field = mysql_fetch_fields(res);

		cout << "P ID\t\tName\t\tP DOB\t\t\tNumber\t\t\tAddress\n";
		cout << "-----------------------------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{
			for (int i = 0; i < (num_fields - 1); i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
		}
		_getch();
	}

	void patient_details()
	{
		cout << "Enter Patient ID: ";
		string p_id; cin >> p_id;

		if (p_id == "a")
		{
			PATIENT::all_patients();
			return;
		}

		string find_patient = "SELECT * FROM patient  WHERE p_id = '" + p_id + "' ";

		if (mysql_query(conn, find_patient.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);

		if (row == 0)
		{
			system("cls");
			cout << "Patient not found..!\n";
			Sleep(2000);
			return;
		}

		system("cls");
		cout << "Patient ID: " << row[0] << "\n\nName: " << row[1] << "\n\nDate of Birth: " << row[2] << "\n\nNumber: " << row[3] << "\n\nAddress: " << row[4] << "\n\nProblem: " << row[5] << endl;
		_getch();
	}

	void update_patient()
	{
		system("cls");
		cout << "Patient ID: ";
		string p_id; cin >> p_id;

		string validate = "SELECT p_id from patient WHERE p_id = '" + p_id + "' ";

		if (mysql_query(conn, validate.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);

			if (row == 0)
			{
				cout << "No patient found with ID: " << p_id << endl;
				Sleep(2000);
				mysql_free_result(res);
				return;
			}
		}
		system("cls");
		cout << "What do you want to update?\n[1] Name\n[2] Date of Birth\n[3] Number\n[4] Address\n[5] Problem\n";
		char op; cin >> op;
		string new_update = "";
		switch (op)
		{
		case'1': {
			system("cls");
			cout << "New Name: ";
			cin.ignore();
			getline(cin, new_update);

			string validate = "UPDATE patient set p_name = '" + new_update + "' WHERE p_id = '" + p_id + "' ";

			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Name updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'2': {
			system("cls");
			cout << "New Date of Birth (YYYY:MM:DD) : ";
			cin >> new_update;
			string validate = "UPDATE patient set p_dob = '" + new_update + "' WHERE p_id = '" + p_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Date of birth updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'3': {
			system("cls");
			cout << "New Number : ";
			cin >> new_update;
			string validate = "UPDATE patient set p_number = '" + new_update + "' WHERE p_id = '" + p_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Number updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'4': {
			system("cls");
			cout << "New Address : ";
			cin.ignore();
			getline(cin, new_update);
			string validate = "UPDATE patient set p_address = '" + new_update + "' WHERE p_id = '" + p_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				return;
			}
			else
			{
				system("cls");
				cout << "Address updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'5': {
			cout << "New Problem : ";
			cin.ignore();
			getline(cin, new_update);
			string validate = "UPDATE patient set p_problem = '" + new_update + "' WHERE p_id = '" + p_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "Problem updated..!\n";
				Sleep(2000);
			}
			break;
		}
		default: {
			system("cls");
			cout << "Enter valid Choice\n";
			Sleep(2000);
			break;
		}

		}
	}
	void add_patient()
	{
		string name, dob, no, ad, prob;

		cout << "Patient Name: ";
		cin.ignore();
		getline(cin, name);
		cout << "\nDate of birth (YYYY-MM-DD): ";
		cin >> dob;
		cout << "\nContact Number: ";
		cin >> no;
		cout << "\nAddress: ";
		cin.ignore();
		getline(cin, ad);
		cout << "\nProblem / Disease: ";
		getline(cin, prob);

		string add = "INSERT INTO patient(p_name, p_dob, p_number,p_address,p_problem) VALUES ( '" + name + "' , '" + dob + "' , '" + no + "' , '" + ad + "' , '" + prob + "' ) ";

		if (mysql_query(conn, add.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			_getch();
		}
		else
		{
			system("cls");
			cout << "Patient Added..!\n";
			Sleep(2000);
		}
	}
	void remove_patient()
	{
		system("cls");
		string ID;
		cout << "Enter patient ID to remove: ";
		cin >> ID;

		string check = "SELECT * FROM patient WHERE p_id = '"+ID+"' ";

		if (mysql_query(conn, check.c_str()) != 0)
		{
			cout << mysql_error(conn);
			_getch();
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);

		if (row == 0)
		{
			system("cls");
			cout << "No patients found..!";
			Sleep(2000);
		}
		else
		{
			string remove = "DELETE FROM patient WHERE p_id = '" + ID + "' ";

			if (mysql_query(conn, remove.c_str()) != 0)
			{
				cout << mysql_error(conn);
				Sleep(2000);
			}
			else
			{
				system("cls");
				cout << "Patient removed..!\n";
				Sleep(2000);
			}
		}
	}


};

class ACCOUNTS
{
public:
	char payment_details()
	{
		cout << "[1] Patient Bill History\n[2] Unpaid Bills\n[3] Patient Details\n[*] Exit\n";
		char op; cin >> op;
		switch (op)
		{
			case'1': {
				system("cls");
				cout << "Patient ID: ";
				string id; cin >> id;

				string query = " select * from bill where p_id = '" + id + "' ";
				if (mysql_query(conn, query.c_str()) != 0)
				{
					cout << mysql_error(conn) << endl;
					_getch();
					return'@';
				}

				MYSQL_RES* res = mysql_store_result(conn);
				MYSQL_ROW  row = mysql_fetch_row(res);
				int num_fields = mysql_num_fields(res);

				if (row == 0)
				{
					system("cls");
					cout << "No payments history..!\n";
					Sleep(2000);
					return'@';
				}
				system("cls");
				cout << "B ID\t\tP ID\t\tBill Date / Time\t\tAmount\t\tState\t\tCreated By\n";
				cout << "------------------------------------------------------------------------------------------------------------\n";
				do {

					for (int i = 0; i < num_fields; i++)
					{
						cout << row[i] << "\t\t";
					}
					cout << endl;
				} while ((row = mysql_fetch_row(res)));
				_getch();

				break;
			}
			case'2': {
				system("cls");

				string query = "select * from bill where state = 'unpaid' ";

				if (mysql_query(conn, query.c_str()) != 0)
				{
					cout << mysql_error(conn) << endl;
					Sleep(2000);
					return'@';
				}

				MYSQL_RES* res = mysql_store_result(conn);
				MYSQL_ROW  row = mysql_fetch_row(res);
				int num_fields = mysql_num_fields(res);

				if (row == 0)
				{
					system("cls");
					cout << "No Unpaid Bills..!\n";
					Sleep(2000);
					return'@';
				}
				system("cls");
				cout << "B ID\t\tP ID\t\tBill Date / Time\t\tAmount\t\tState\t\tCreated By\n";
				cout << "------------------------------------------------------------------------------------------------------------\n";
				do {

					for (int i = 0; i < num_fields; i++)
					{
						cout << row[i] << "\t\t";
					}
					cout << endl;
				} while ((row = mysql_fetch_row(res)));
				_getch();

				break;
			}
			case'3': {
				system("cls");
				PATIENT p;
				p.patient_details();
				break;
			}
			case'*': {
				system("cls");
				cout << "Exiting..\n";
				Sleep(2000);
				return '*';
			}
			default: {
				system("cls");
				cout << "Enter valid choice\n";
				Sleep(2000);
				break;
			}
		}
	}

};

class DOCTOR
{
public:

	void all_doctors()
	{
		system("cls");
		string query = "SELECT * FROM doctor";

		if (mysql_query(conn, query.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row;

		int num_fields = mysql_num_fields(res);

		MYSQL_FIELD* field = mysql_fetch_fields(res);

		cout << "D ID\t\tName\t\tSpeciality\t\tNumber\t\t\tStart Time\t\tEndTime\n";
		cout << "-----------------------------------------------------------------------------------------------------------------\n";

		while ((row = mysql_fetch_row(res)))
		{
			for (int i = 0; i < num_fields; i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
		}
		_getch();
	}


	void doctor_details()
	{
		system("cls");
		cout << "Enter Doctor ID: ";
		string d_id; cin >> d_id;

		if (d_id == "a")
		{
			DOCTOR::all_doctors();
			return;
		}

		string find_doctor = "SELECT * FROM doctor WHERE d_id = '" + d_id + "' ";

		if (mysql_query(conn, find_doctor.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);

		if (row == 0)
		{
			system("cls");
			cout << "Doctor not found..!\n";
			Sleep(2000);
			return;
		}

		system("cls");
		cout << "Doctor ID: " << row[0] << "\n\nName: " << row[1] << "\n\nSpecialization: " << row[2] << "\n\nNumber: " << row[3] << "\n\nShift Start: " << row[4] << "\n\nShift End: " << row[5] << endl;
		_getch();
	}

	void update_doctor()
	{
		system("cls");
		cout << "Doctor ID: ";
		string d_id; cin >> d_id;

		string validate = "SELECT d_id from doctor WHERE d_id = '" + d_id + "' ";

		if (mysql_query(conn, validate.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			return;
		}
		else
		{
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);

			if (row == 0)
			{
				cout << "No doctor found with ID: " << d_id << endl;
				Sleep(2000);
				mysql_free_result(res);
				return;
			}
		}
		system("cls");
		cout << "What do you want to update?\n\n[1] Name\n[2] Specialization\n[3] Number\n[4] Shift Start Time\n[5] Shift End Time\n";
		char op; cin >> op;
		string new_update = "";
		switch (op)
		{
		case'1': {
			system("cls");
			cout << "New Name: ";
			cin >> new_update;
			string validate = "UPDATE doctor set d_name = '" + new_update + "' WHERE d_id = '" + d_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				return;
			}
			else
			{
				system("cls");
				cout << "Name updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'2': {
			system("cls");
			cout << "New Specialization: ";
			cin.ignore();
			getline(cin, new_update);
			string validate = "UPDATE doctor set d_specialization = '" + new_update + "' WHERE d_id = '" + d_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				return;
			}
			else
			{
				system("cls");
				cout << "Specialization updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'3': {
			system("cls");
			cout << "New Number: ";
			cin >> new_update;
			string validate = "UPDATE doctor set d_number = '" + new_update + "' WHERE d_id = '" + d_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				return;
			}
			else
			{
				system("cls");
				cout << "Number updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'4': {
			system("cls");
			cout << "New Shift Start Time (HH:MM:SS): ";
			cin >> new_update;
			string validate = "UPDATE doctor set d_shift_start = '" + new_update + "' WHERE d_id = '" + d_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				return;
			}
			else
			{
				system("cls");
				cout << "Start time updated..!\n";
				Sleep(2000);
			}
			break;
		}
		case'5': {
			system("cls");
			cout << "New Shift End Time (HH:MM:SS): ";
			cin >> new_update;
			string validate = "UPDATE doctor set d_shift_end = '" + new_update + "' WHERE d_id = '" + d_id + "' ";
			if (mysql_query(conn, validate.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				Sleep(2000);
				return;
			}
			else
			{
				system("cls");
				cout << "End time updated..!\n";
				Sleep(2000);
			}
			break;
		}
		default: {
			system("cls");
			cout << "Enter valid option\n";
			Sleep(2000);
			break;
		}
		}
	}
	void add_doctor()
	{
		string name, sp, no, s_time, e_time;
		system("cls");
		cout << "Doctor Name: ";
		cin >> name;
		cout << "\nSpecializaion: ";
		cin.ignore();
		getline(cin, sp);
		cout << "\nContact Number: ";
		cin >> no;
		cout << "\nShift Start Time (hh:mm:ss): ";
		cin >> s_time;
		cout << "\nShift End Time(hh:mm:ss): ";
		cin >> e_time;
		string add_doc = "INSERT INTO doctor (d_name, d_specialization, d_number, d_shift_start, d_shift_end) VALUES ( '" + name + "' , '" + sp + "' , '" + no + "' , '" + s_time + "' , '" + e_time + "')";
		if (mysql_query(conn, add_doc.c_str()) != 0)
		{
			cout << mysql_error(conn);
			cin.get();
		}
		else
		{
			system("cls");
			cout << "Doctor Added Successfuly..!\n";
			Sleep(2000);
		}
	}
	void remove_doctor()
	{
		string ID;
		cout << "Enter ID of Doctor to remove: ";
		cin >> ID;

		string check = "SELECT d_id FROM doctor where d_id = '" + ID + "' ";
		if (mysql_query(conn, check.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);
		if (row == 0)
		{
			system("cls");
			cout << "No Doctor found..!\n";
			Sleep(2000);
			return;
		}

		string remove = "DELETE FROM doctor WHERE d_id = '" + ID + "' ";
		if (mysql_query(conn, remove.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			system("cls");
			cout << "Doctor Removed..!\n";
			Sleep(2000);
		}

	}

};

class USER_MANAGEMENT
{
public:

	void all_users()
	{
		system("cls");
		string query = "SELECT * FROM users";

		if (mysql_query(conn, query.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row;

		int num_fields = mysql_num_fields(res);

		MYSQL_FIELD* field = mysql_fetch_fields(res);

		cout << "Username\tDepartment\n";
		cout << "----------------------------\n";


		while ((row = mysql_fetch_row(res)))
		{
			for (int i = 1; i < num_fields; i++)
			{
				cout << row[i] << "\t\t";
			}
			cout << endl;
		}
		_getch();
	}

	void user_details()
	{
		cout << "Enter Username: ";
		string username; cin >> username;

		if (username == "a")
		{
			all_users();
			return;
		}
		else
		{
			string find_user = "SELECT * FROM users WHERE username = '" + username + "' ";

			if (mysql_query(conn, find_user.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
				return;
			}

			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);

			if (row == 0)
			{
				system("cls");
				cout << "Username not found..!\n";
				Sleep(2000);
				return;
			}

			system("cls");
			cout << "Username: " << row[1] << "\n\nPassword: " << row[0] << "\n\nDepartment: " << row[2] << endl;
			_getch();
		}
	}
	void update_user()
	{
		cout << "Please enter username: ";
		string username; cin >> username;
		system("cls");

		string validate = "select username from users where username = '" + username + "' ";
		if (mysql_query(conn, validate.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			MYSQL_RES* res = mysql_store_result(conn);
			MYSQL_ROW  row = mysql_fetch_row(res);
			if (row == NULL)
			{
				cout << "Username not found\n";
				Sleep(2000);
				mysql_free_result(res);
				return;
			}
		}

		cout << "What do you want to change?\n\n[1] Password\n[2] Department\n";
		char op; cin >> op;

		switch (op)
		{
		case '1': {
			system("cls");
			cout << "\nNew Password: ";
			string new_pass; cin >> new_pass;

			switch (check_pass(new_pass))
			{
			case'1': {
				system("cls");
				cout << "Password must be 8 characters long\a\n";
				Sleep(2000);
				return;
			}
			case'2': {
				system("cls");
				cout << "Password must contain symbols\a\n";
				Sleep(2000);
				return;
			}
			case'0': {
				string update_pass = " UPDATE users SET password = '" + new_pass + "' WHERE username = '" + username + "' ";

				if (mysql_query(conn, update_pass.c_str()) != 0)
				{
					cout << mysql_error(conn) << endl;
					Sleep(2000);
				}
				else
				{
					system("cls");
					cout << "Password updated..!\n";
					Sleep(2000);
				}
				break;
			}
			}
			break;
		}
		case '2': {
			system("cls");
			cout << "\nNew Department: ";
			string new_dept; cin >> new_dept;

			string update_dept = " UPDATE users SET dept = '" + new_dept + "' WHERE username = '" + username + "' ";

			if (mysql_query(conn, update_dept.c_str()) != 0)
			{
				cout << mysql_error(conn) << endl;
			}
			else
			{
				system("cls");
				cout << "Department updated..!\n";
				Sleep(2000);
			}
			break;
		}
		default: {
			system("cls");
			cout << "Enter valid choice\n";
			Sleep(2000);
			break;
		}
		}
	}
	bool login()
	{
		string username, password;

		cout << "<<<<<<<<<< Hospital Management System >>>>>>>>>>\n\n";
		cout << "Username: ";
		cin >> username;
		cout << "\nPassword: ";
		cin >> password;

		string find_user = "SELECT username, dept FROM users WHERE username = '" + username + "' AND password = '" + password + "' ";

		if (mysql_query(conn, find_user.c_str()) != 0)
		{
			cout << mysql_error(conn);
			return false;
		}

		MYSQL_RES* res = mysql_store_result(conn);

		int rows = mysql_num_rows(res);

		if (rows > 0)
		{
			system("cls");
			// updating current_user and user_dept

			MYSQL_ROW row = mysql_fetch_row(res);
			if (row != NULL)
			{
				Current_User = row[0];
				User_Dept = row[1];
			}
			cout << User_Dept << " | Login successful..!\n";
			Sleep(2000);
			system("cls");
			return true;
		}
		else
		{
			system("cls");
			cout << "Invalid user..!\n";
			Sleep(2000);
			return false;
		}

		mysql_free_result(res);
	}

	void delete_user()
	{
		string username;
		cout << "Enter username to delete: ";
		cin >> username;

		string check = "SELECT username FROM users where username = '" + username + "' ";
		if (mysql_query(conn, check.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}

		MYSQL_RES* res = mysql_store_result(conn);
		MYSQL_ROW  row = mysql_fetch_row(res);
		if (row == 0)
		{
			system("cls");
			cout << "No user found..!\n";
			Sleep(2000);
			return;
		}

		string remove = "DELETE FROM users WHERE username = '" + username + "' ";
		if (mysql_query(conn, remove.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			Sleep(2000);
			return;
		}
		else
		{
			system("cls");
			cout << "User removed\n";
			Sleep(2000);
		}
	}
	void create_user()
	{
		string username, password, dept;
		cout << "Create username: ";
		cin >> username; // add this username to DB

		do
		{
			cout << "\nCreate password: ";
			cin >> password;
			switch (check_pass(password))
			{
			case '0': {
				cout << "\nEnter department: ";
				cin >> dept;
				break;
			}
			case '1': {
				cout << "Password should be atleast 8 characters long\n";
				break;
			}
			case '2': {
				cout << "Password must contain symbols\n";
				break;
			}
			default: {
				cout << "Error switch #45\n";
				break;
			}
			}

		} while (check_pass(password) != '0');

		string add_user = "INSERT INTO users (username, password, dept) VALUES ('" + username + "', '" + password + "','" + dept + "')";
		
		if (mysql_query(conn, add_user.c_str()) != 0)
		{
			cout << mysql_error(conn) << endl;
			_getch();
		}
		else
		{
			system("cls");
			cout << "User Created..!\n";
			Sleep(2000);
		}

	}

	/*	0 means no error
		1 means length is below 8
		2 means no characters or symbols
	*/

	char check_pass(string& password) // This will check about the strongness of password
	{
		//string error; // this will be set and return to create_user()

		bool status = false; // status will contain if a symbol is found in password or not?

		if (password.length() >= 8)
		{
			for (int i = 0; i < password.length(); i++)
			{
				if (!isalpha(password[i]) && !isdigit(password[i]))
				{
					status = true;
					return '0';
				}
			}
			if (status == false)
			{
				return '2';
			}
		}
		else
		{
			return '1';
		}

	}

};

static void connect_database()
{
	conn = mysql_init(NULL);
	if (!mysql_real_connect(conn, HOST, USER, PASS, DB, 12700, NULL, 0))
	{
		cout << mysql_error(conn);
		return;
	}
}
class MENU
{
public:
	char show_menu()
	{
		menu_header(); // Display Menu heading

		if (User_Dept == "reception")
		{
			cout << "[1] Create\n[2] Update\n[3] Delete\n[4] Details\n[*] Exit\n";
			char op; cin >> op;
			switch (op)
			{
				char ch;
			case'1': {
				menu_header();
				cout << "[1] New Patient\n[2] New Appointment\n[3] New Bill\n";
				cin >> ch;
				switch (ch)
				{
				case'1': {
					cls();
					PATIENT p;
					p.add_patient();
					break;
				}
				case'2': {
					cls();
					APPOINTMENT a;
					a.create_appointment();
					break;
				}
				case'3': {
					cls();
					BILL b;
					b.create_bill();
					break;
				}
				default: {
					cls();
					cout << "Enter valid choice\n";
					Sleep(2000);
					break;
				}
				}
				break;
			}
			case'2': {
				menu_header();
				cout << "[1] Update Patient\n[2] Update Appointment\n";
				cin >> ch;
				switch (ch)
				{
				case'1': {
					cls();
					PATIENT p;
					p.update_patient();
					break;
				}
				case'2': {
					cls();
					APPOINTMENT a;
					a.update_appointment();
					break;
				}
				default: {
					cls();
					cout << "Enter valid choice\n";
					Sleep(2000);
					break;
				}
				}
				break;
			}
			case'3': {
				menu_header();
				cout << "[1] Remove Patient\n[2] Remove Appointment\n[3] Remove Bill\n";
				cin >> ch;
				switch (ch)
				{
				case'1': {
					cls();
					PATIENT p;
					p.remove_patient();
					break;
				}
				case'2': {
					cls();
					APPOINTMENT a;
					a.remove_appointment();
					break;
				}
				case'3': {
					cls();
					BILL b;
					b.delete_bill();
					break;
				}
				default: {
					cls();
					cout << "Enter valid choice\n";
					Sleep(2000);
					break;
				}
				}
				break;
			}
			case '4': {
				menu_header();
				cout << "[1] Patient Details\n[2] Appointment Details\n[3] Bill Details\n[4] Doctor Details\n";
				cin >> ch;
				switch (ch)
				{
				case'1': {
					cls();
					PATIENT p;
					p.patient_details();
					break;
				}
				case'2': {
					cls();
					APPOINTMENT a;
					a.appointment_details();
					break;
				}
				case'3': {
					cls();
					BILL b;
					b.display_bill();
					break;
				}
				case'4': {
					cls();
					DOCTOR d;
					d.doctor_details();
					break;
				}
				default: {
					cls();
					cout << "Enter valid choice\n";
					Sleep(2000);
					break;
				}
				}
				break;
			}
			case'*': {
				system("cls");
				cout << "Exiting..\n";
				Sleep(2000);
				return'*';
			}
			default: {
				system("cls");
				cout << "Enter valid choice\n";
				Sleep(2000);
				break;
			}
			}
		}
		else if (User_Dept == "doctor")
		{
			cout << "[1] Patient Details\n[2] Appointment Details\n[*] Exit\n";
			char ch; cin >> ch;
			switch (ch)
			{
			case'1': {
				cls();
				PATIENT p;
				p.patient_details();
				break;
			}
			case'2': {
				cls();
				APPOINTMENT a;
				a.appointment_details();
				break;
			}
			case'*': {
				system("cls");
				cout << "Exiting..\n";
				Sleep(2000);
				return'*';
			}
			default: {
				cls();
				cout << "Enter valid choice\n";
				Sleep(2000);
				break;
			}
			}
		}
		else if (User_Dept == "accounts")
		{
			ACCOUNTS a;
			a.payment_details();
		}
		else if (User_Dept == "admin")
		{
			cout << "[1] Create\n[2] Update\n[3] Delete\n[4] Details\n[*] Exit\n\n";
			char ch; cin >> ch;
			switch (ch)
			{
				char op;
				case'1': {
					cls();
					cout << "[1] New User\n[2] New Doctor\n\n";
					cin >> op;
					switch (op)
					{
						case'1': {
							cls();
							USER_MANAGEMENT um;
							um.create_user();
							break;
						}
						case'2': {
							cls();
							DOCTOR d;
							d.add_doctor();
							break;
						}
						default: {
							cls();
							cout << "Enter valid choice\n";
							Sleep(2000);
							break;
						}
					}
					break;
				}
				case'2': {
					cls();
					cout << "[1] Update User\n[2] Update Doctor\n\n";
					cin >> op;
					switch (op)
					{
						case'1': {
							cls();
							USER_MANAGEMENT um;
							um.update_user();
							break;
						}
						case'2': {
							cls();
							DOCTOR d;
							d.update_doctor();
							break;
						}
						default: {
							cls();
							cout << "Enter valid choice\n";
							Sleep(2000);
							break;
						}
					}
					break;
				}
				case'3': {
					cls();
					cout << "[1] Remove User\n[2] Remove Doctor\n\n";
					cin >> op;
					switch (op)
					{
						case'1': {
							cls();
							USER_MANAGEMENT um;
							um.delete_user();
							break;
						}
						case'2': {
							cls();
							DOCTOR d;
							d.remove_doctor();
							break;
						}
						default: {
							cls();
							cout << "Enter valid choice\n";
							Sleep(2000);
							break;
						}
					}
					break;
				}
				case'4': {
					cls();
					cout << "[1] User Details\n[2] Doctor Details\n[3] License Expiry\n\n";
					char s; cin >> s;
					switch (s)
					{
						case'1': {
							cls();
							USER_MANAGEMENT um;
							um.user_details();
							break;
						}
						case'2': {
							DOCTOR d;
							d.doctor_details();
							break;
						}
						case'3': {
							system("cls");
							string query = "SELECT valid_till, updated_on from license";
							if (mysql_query(conn, query.c_str()) != 0)
							{
								cout << mysql_error(conn) << endl;
								Sleep(2000);
								return '*';
							}
							MYSQL_RES* res = mysql_store_result(conn);
							MYSQL_ROW  row = mysql_fetch_row(res);
							if (row == 0)
							{
								cout << "Error Checking License Date\n";
								Sleep(2000);
								return '*';
							}
							cout << "Expiry Date: " << row[0] << "\n\nLast updated on: " << row[1];
							cout << endl << endl;
							_getch();
							break;
						}
					}
					break;
				}
				case'*': {
					system("cls");
					cout << "Exiting..\n";
					Sleep(2000);
					return'*';
					break;
				}
				default: {
					system("cls");
					cout << "Enter valid choice\n";
					_getch();
					break;
				}
			}
		}
		else if (User_Dept == "superuser")
		{
			system("cls");
			cout << "[1] Update license\n[*] Exit\n";
			char ch; cin >> ch;
			switch (ch)
			{
				case'1': {
					system("cls");
					cout << "Enter license new date: ";
					string new_date; cin >> new_date;

					string update_license_query = " UPDATE license SET valid_till = '" + new_date + "' AND  WHERE ID = 5683";
					if (mysql_query(conn, update_license_query.c_str()) != 0)
					{
						cout << mysql_error(conn) << endl;
						Sleep(2000);
						return '*';
					}

					system("cls");
					cout << "License Updated..!\n";
					_getch();

					break;
				}
				case'*': {
					system("cls");
					cout << "Exiting..\n";
					Sleep(2000);
					return'*';
				}
				default: {
					system("cls");
					cout << "Enter valid choice\n";
					Sleep(2000);
					break;
				}
			}
		}
		else
		{
			system("cls");
			cout << "No Functions found for Department: " << User_Dept << endl;
			Sleep(2000);
			return '*';
		}
	}

	inline void menu_header() { system("cls"); cout << "<<<<<<<<<< MENU >>>>>>>>>>\n\n"; }
	inline void cls() { system("cls"); }
};

static bool check_license()
{
	string check_license_query = "SELECT curdate(), valid_till from license";
	if (mysql_query(conn, check_license_query.c_str()) != 0)
	{
		cout << mysql_error(conn) << endl;
		Sleep(2000);
		return false;
	}

	MYSQL_RES* res = mysql_store_result(conn);
	MYSQL_ROW  row = mysql_fetch_row(res);

	if (row == 0)
	{
		cout << "Error Checking License\a\n";
		Sleep(2000);
		return false;
	}

	string C(row[0]);
	string V(row[1]);

	if (C > V)
	{
		cout << "Your license has expired..!\a\n";
		_getch();
		return false;
	}
	return true;
}

int main()
{
	SetConsoleTitleA("Hospital Management System");

	connect_database();

	if (check_license())
	{
		system("color f0");

		USER_MANAGEMENT i;
		if (i.login())
		{
			MENU m;
			while (m.show_menu() != '*');
		}
	}

	mysql_close(conn);
	return 0;
}