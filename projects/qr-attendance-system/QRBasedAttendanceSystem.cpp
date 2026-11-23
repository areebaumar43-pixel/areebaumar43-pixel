#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;

// Student Class
class Student
{
public:
    string Student_ID;
    string Student_Name;
    string Student_Department;

    void getDetails()
    {
        cout << "Enter Student ID: ";
        getline(cin, Student_ID);

        cout << "Enter Student Name: ";
        getline(cin, Student_Name);

        cout << "Enter Department: ";
        getline(cin, Student_Department);
    }

    void displayStudent()
    {
        cout << "ID: " << Student_ID << endl;
        cout << "Name: " << Student_Name << endl;
        cout << "Department: " << Student_Department << endl;
    }
};

// Attendance Class
class Attendance
{
public:
    string Student_ID;
    string Date;
    string Status;
    string qrData;

    void markAttendance(string id, string code)
    {
        Student_ID = id;
        qrData = code;

        time_t now = time(0);
        Date = ctime(&now);

        Status = "Present";
    }

    void showRecord()
    {
        cout << "Student ID: " << Student_ID << endl;
        cout << "Date: " << Date;
        cout << "Status: " << Status << endl;
    }
};

// QR Class
class QR
{
public:
    string qrData;

    void generateQR(string sessionName)
    {
        qrData = sessionName + "_UKM";

        cout << "\nQR Code Generated Successfully!" << endl;
        cout << "QR Code: " << qrData << endl;
    }

    bool verifyQR(string code)
    {
        if (code == qrData && qrData != "")
            return true;

        return false;
    }
};

// System Class
class AttendanceSystem
{
public:
    vector<Student> students;
    vector<Attendance> records;
    QR qr;

    // Add Student
    void addStudent()
    {
        Student s;

        cout << "\n--- Add Student ---\n";
        s.getDetails();

        students.push_back(s);

        cout << "Student Added Successfully!" << endl;
    }

    // Display Students
    void displayStudents()
    {
        if (students.empty())
        {
            cout << "No Students Found!" << endl;
            return;
        }

        for (int i = 0; i < students.size(); i++)
        {
            cout << "\nStudent " << i + 1 << endl;
            students[i].displayStudent();
        }
    }

    // Generate QR
    void generateSessionQR()
    {
        string sessionName;

        cout << "Enter Lecture Name: ";
        getline(cin, sessionName);

        qr.generateQR(sessionName);
    }

    // Mark Attendance
    void scanAndMarkAttendance()
    {
        string id, code;
        bool found = false;

        cout << "\nEnter Student ID: ";
        getline(cin, id);

        for (int i = 0; i < students.size(); i++)
        {
            if (students[i].Student_ID == id)
            {
                found = true;
                break;
            }
        }

        if (found == false)
        {
            cout << "Student Not Found!" << endl;
            return;
        }

        cout << "Enter QR Code: ";
        getline(cin, code);

        if (qr.verifyQR(code))
        {
            for (int i = 0; i < records.size(); i++)
            {
                if (records[i].Student_ID == id &&
                    records[i].qrData == code)
                {
                    cout << "Attendance Already Marked!" << endl;
                    return;
                }
            }

            Attendance a;
            a.markAttendance(id, code);

            records.push_back(a);

            cout << "Attendance Marked Successfully!" << endl;
        }
        else
        {
            cout << "Invalid QR Code!" << endl;
        }
    }

    // Attendance Report
    void showAttendanceReport()
    {
        if (records.empty())
        {
            cout << "No Attendance Records!" << endl;
            return;
        }

        for (int i = 0; i < records.size(); i++)
        {
            cout << "\nRecord " << i + 1 << endl;
            records[i].showRecord();
        }
    }

    // Search Student Attendance
    void searchStudentAttendance()
    {
        string id;
        bool found = false;

        cout << "Enter Student ID: ";
        getline(cin, id);

        for (int i = 0; i < records.size(); i++)
        {
            if (records[i].Student_ID == id)
            {
                records[i].showRecord();
                found = true;
            }
        }

        if (found == false)
        {
            cout << "No Attendance Found!" << endl;
        }
    }

    // Main Menu
    void menu()
    {
        int choice;

        do
        {
            cout << "\n============================\n";
            cout << " QR BASED ATTENDANCE SYSTEM\n";
            cout << "============================\n";

            cout << "1. Add Student" << endl;
            cout << "2. Display Students" << endl;
            cout << "3. Generate QR Code" << endl;
            cout << "4. Mark Attendance" << endl;
            cout << "5. Attendance Report" << endl;
            cout << "6. Search Attendance" << endl;
            cout << "7. Exit" << endl;

            cout << "\nEnter Choice: ";
            cin >> choice;
            cin.ignore();

            switch (choice)
            {
            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                generateSessionQR();
                break;

            case 4:
                scanAndMarkAttendance();
                break;

            case 5:
                showAttendanceReport();
                break;

            case 6:
                searchStudentAttendance();
                break;

            case 7:
                cout << "Thank You!" << endl;
                break;

            default:
                cout << "Invalid Choice!" << endl;
            }

        } while (choice != 7);
    }
};

// Main Function
int main()
{
    AttendanceSystem system;

    system.menu();

    return 0;
}
