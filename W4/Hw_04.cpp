#include <iostream>
#include <string>
#include <vector>
using namespace std;

// ---------------- Appointment ----------------
class Appointment {

public:
    enum Status { SCHEDULED, COMPLETED, CANCELED };
private:
    static int nextId;
    int id;
    int patientId;
    int doctorId;
    string date, time, status;

    int nextId = 1;
public:
    Appointment(int pid, int did, string d, string t)
        : id(nextId++), patientId(pid), doctorId(did), date(d), time(t), status("Scheduled") {}
    int getId() { 
        return id; }
    void setStatus(string s) { status = s; }
    void display() const {
        cout << "Appointment " << id << ": Patient " << patientId
             << ", Doctor " << doctorId << ", " << date << " " << time
             << " | Status: " << status << endl;
    }
};


// ---------------- Patient ----------------
class Patient {
protected:
    int id;
    string name;
    int age;
public:
    Patient(int id, string n, int a) : id(id), name(n), age(a) {}
    virtual Appointment scheduleAppointment(int doctorId, string date, string time) {
        cout << name << " schedules a normal appointment.\n";
        return Appointment(id, doctorId, date, time);
    }
    virtual void printInfo() {
        cout << "Patient " << id << ": " << name << ", age " << age << endl;
    }
    int getId() const { return id; }
};

// ---------------- ChronicPatient ----------------
class ChronicPatient : public Patient {
    string condition;
public:
    ChronicPatient(int id, string n, int a, string c) : Patient(id, n, a), condition(c) {}
    Appointment scheduleAppointment(int doctorId, string date, string time) override {
        cout << name << " (chronic: " << condition << ") schedules a follow-up.\n";
        return Appointment(id, doctorId, date, time);
    }
    void printInfo() override {
        cout << "Chronic Patient " << id << ": " << name << ", age " << age
             << " | Condition: " << condition << endl;
    }
};

// ---------------- Doctor ----------------
class Doctor {
    int id;
    string name, specialty;
public:
    Doctor(int id, string n, string s) : id(id), name(n), specialty(s) {}
    void printInfo() { cout << "Doctor " << id << ": " << name << " (" << specialty << ")\n"; }
    int getId() const { return id; }
};

// ---------------- Clinic ----------------
class Clinic {
    vector<Patient*> patients;
    vector<Doctor> doctors;
    vector<Appointment> appointments;
public:
    void addPatient(Patient* p) { patients.push_back(p); }
    void addDoctor(Doctor d) { doctors.push_back(d); }
    void schedule(int pid, int did, string date, string time) {
        for (auto p : patients) {
            if (p->getId() == pid) {
                appointments.push_back(p->scheduleAppointment(did, date, time));
                return;
            }
        }
        cout << "Patient not found.\n";
    }
    void showAll() {
        cout << "\n--- Patients ---\n";
        for (auto p : patients) p->printInfo();
        cout << "\n--- Doctors ---\n";
        for (auto &d : doctors) d.printInfo();
        cout << "\n--- Appointments ---\n";
        for (auto &a : appointments) a.display();
    }
    ~Clinic() { for (auto p : patients) delete p; }
};

// ---------------- Main ----------------
int main() {
    Clinic clinic;
    clinic.addDoctor(Doctor(1, "Alice", "General"));
    clinic.addDoctor(Doctor(2, "Bob", "Cardiology"));

    clinic.addPatient(new Patient(1, "John Doe", 30));
    clinic.addPatient(new ChronicPatient(2, "Mary Smith", 55, "Diabetes"));

    clinic.schedule(1, 1, "2025-09-20", "09:00");
    clinic.schedule(2, 2, "2025-09-21", "10:00");

    clinic.showAll();
    return 0;
}
