#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
struct Doctor;
struct Patient;

/////////////////////// DECLARATION //////////////////////////
struct Doctor
{
	string name;

	vector<Patient*> vect_patien;
	void addPatient(Patient * patient);
	void removePatient(Patient * patient);
	void printAllPatients();
};

struct Patient
{
	string name;

	vector<Doctor*> vect_doctors;
	void addDoctor(Doctor * doctor);
	void removeDoctor(Doctor * doctor) ;
	void printAllDoctors();
};

/////////////////////// DEFINITION //////////////////////////

void Doctor::addPatient(Patient * patient){vect_patien.push_back(patient);}

void Doctor::printAllPatients(){
	cout << "\n==========[ " << name << " ] ===========\n";
	for (size_t i = 0; i < vect_patien.size(); i++)
	{
		Patient * tmp = vect_patien[i];
		cout << tmp->name << '\n';
	}
	cout << "===================\n\n";
}

void Doctor::removePatient(Patient * patient) {
	vect_patien.erase(std::remove(vect_patien.begin(), vect_patien.end(), patient), vect_patien.end());
	//patient->removeDoctor(this);
}
///////////////////////////////////////////////////////////

void Patient::addDoctor(Doctor * doctor){
	vect_doctors.push_back(doctor);
	doctor->addPatient(this);
}

void Patient::removeDoctor(Doctor * doctor) {
	vect_doctors.erase(std::remove(vect_doctors.begin(), vect_doctors.end(), doctor), vect_doctors.end());
	doctor->removePatient(this);
}

void Patient::printAllDoctors(){
	cout << "\n==========[ " << name << " ] ===========\n";
	for (auto e : vect_doctors){cout << e->name << '\n';}
	cout << "===================\n\n";
}
///////////////////////////////////////////////////////////




int main(int argc, char const *argv[])
{
	Doctor d1{"doctor 1"};
	Doctor d2{"doctor 2"};
	Doctor d3{"doctor 3"};

	Patient p1{"patient 1"};
	Patient p2{"patient 2"};
	Patient p3{"patient 3"};

	p1.addDoctor(&d1);
	p1.addDoctor(&d2);
	p1.addDoctor(&d3);

	p1.printAllDoctors();
	d1.printAllPatients();

	p1.removeDoctor(&d1);

	p1.printAllDoctors();
	d1.printAllPatients();


	return 0;
}
