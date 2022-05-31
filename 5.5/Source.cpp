#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

struct Facult
{
	char name[100];
	int numb;
};

struct Student
{
	char name[100];
	int fis;
	int math;
	int prog;
};

struct Global
{
	Facult facult;
	Student stud;
	int kurs;
};

void create(int& n);
void print(string name);
void add();
void print_aver();
void del_2();
void sort(int n);
double aver(Global g);
int menu();
bool check(int a);

int main() {
	int n;				// "print(1)\nenter(2)\nadd(3)\nprint 4.5(4)\ndelete 2(5)\nsort(6)\nexit(0)\n"
	int con;
	string str;
	do {
		do {
			con = menu();
		} while (!check(con));
		switch (con)
		{
		case 1:
			cout << "Name: "; cin >> str;
			print(str);
			break;
		case 2:
			create(n);
			break;
		case 3:
			add();
			n += 1;
			break;
		case 4:
			print_aver();
			break;
		case 5:
			del_2();
			break;
		case 6:
			sort(n);
			break;
		default:
			break;
		}
	} while (con != 0);
}

void create(int& n) {
	fstream f("file.txt", ios::binary | ios::out | ios::trunc);
	Global tmp;
	cout << "Enter n: "; cin >> n;
	for (int i = 0; i < n; i++) {
		cout << "Facultet: "; cin >> tmp.facult.name;
		cout << "Number: "; cin >> tmp.facult.numb;
		cout << "Kurs: "; cin >> tmp.kurs;
		cout << "Student: "; cin >> tmp.stud.name;
		cout << "Phisics: "; cin >> tmp.stud.fis;
		cout << "Math: "; cin >> tmp.stud.math;
		cout << "Programing: "; cin >> tmp.stud.prog;
		f.write((char*)&tmp, sizeof(tmp));

	}
}
void print(string name) {
	fstream f(name, ios::binary | ios::in);
	cout << "--------------------------------------------------------------------" << endl;
	cout << "| Facultet | Number | Kurs | Student | Phisics | Math | Programing |" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	Global tmp;
	f.read((char*)&tmp, sizeof(tmp));

	while (!f.eof()) {
		cout << '|' << setw(10) << tmp.facult.name << '|' << setw(8) << tmp.facult.numb << '|'
			<< setw(6) << tmp.kurs << '|' << setw(9) << tmp.stud.name << '|'
			<< setw(9) << tmp.stud.fis << '|' << setw(6) << tmp.stud.math << '|' << setw(12) << tmp.stud.prog << '|' << endl;

		f.read((char*)&tmp, sizeof(tmp));
	}

	cout << "--------------------------------------------------------------------" << endl;
}
void add() {
	fstream f("file.txt", ios::binary | ios::out);
	Global tmp;

	cout << "Facultet: "; cin >> tmp.facult.name;
	cout << "Number: "; cin >> tmp.facult.numb;
	cout << "Kurs: "; cin >> tmp.kurs;
	cout << "Student: "; cin >> tmp.stud.name;
	cout << "Phisics: "; cin >> tmp.stud.fis;
	cout << "Math: "; cin >> tmp.stud.math;
	cout << "Programing: "; cin >> tmp.stud.prog;
	f.write((char*)&tmp, sizeof(tmp));
}

void print_aver() {
	fstream f("file.txt", ios::binary | ios::in);
	cout << "--------------------------------------------------------------------" << endl;
	cout << "| Facultet | Number | Kurs | Student | Phisics | Math | Programing |" << endl;
	cout << "--------------------------------------------------------------------" << endl;
	Global tmp;
	f.read((char*)&tmp, sizeof(tmp));

	while (!f.eof()) {
		if (aver(tmp) == 4.5) {
			cout << '|' << setw(10) << tmp.facult.name << '|' << setw(8) << tmp.facult.numb << '|'
				<< setw(6) << tmp.kurs << '|' << setw(9) << tmp.stud.name << '|'
				<< setw(9) << tmp.stud.fis << '|' << setw(6) << tmp.stud.math << '|' << setw(12) << tmp.stud.prog << '|' << endl;
		}

		f.read((char*)&tmp, sizeof(tmp));
	}

	cout << "--------------------------------------------------------------------" << endl;
}
void del_2() {
	fstream f("file.txt", ios::binary | ios::in);
	fstream s("save.txt", ios::binary | ios::out | ios::trunc);


	Global tmp;
	f.read((char*)&tmp, sizeof(tmp));

	while (!f.eof()) {
		if (!(tmp.stud.prog == 2 && tmp.stud.fis == 2 && tmp.stud.math == 2)) {
			s.write((char*)&tmp, sizeof(tmp));
		}

		f.read((char*)&tmp, sizeof(tmp));
	}

	f.close();
	s.close();

	f.open("file.txt", ios::binary | ios::out | ios::trunc);
	s.open("save.txt", ios::binary | ios::in);

	s.read((char*)&tmp, sizeof(tmp));
	while (!s.eof()) {
		f.write((char*)&tmp, sizeof(tmp));
		s.read((char*)&tmp, sizeof(tmp));
	}
}

void sort(int n) {
	fstream f("file.txt", ios::binary | ios::in);
	fstream s("save.txt", ios::binary | ios::out | ios::trunc);
	double min_a = 6;
	double trp;
	double* q = new double[n];
	double q_min;
	Global tmp;
	int qn = 0;

	for (int i = 0; i < n; i++) {
		f.read((char*)&tmp, sizeof(tmp));
		q[i] = aver(tmp);
	}
	f.close();
	q_min = q[0];
	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			if (q[j] < q[i]) {
				trp = q[i];
				q[i] = q[j];
				q[j] = trp;
			}
		}
	}
	for (int i = 0; i < n; i++) {
		f.open("file.txt", ios::binary | ios::in);
		for (int j = 0; j < n; j++) {
			f.read((char*)&tmp, sizeof(tmp));
			if (aver(tmp) == q[qn]) {
				s.write((char*)&tmp, sizeof(tmp));
				qn++;
			}
		}
		f.close();
	}


	f.close();
	s.close();

	f.open("file.txt", ios::binary | ios::out | ios::trunc);
	s.open("save.txt", ios::binary | ios::in);

	s.read((char*)&tmp, sizeof(tmp));
	while (!s.eof()) {
		f.write((char*)&tmp, sizeof(tmp));
		s.read((char*)&tmp, sizeof(tmp));
	}
}

double aver(Global g) {
	return (double)(g.stud.prog + g.stud.math + g.stud.fis) / 3;
}

int menu() {
	int f;
	cout << "print(1)\nenter(2)\nadd(3)\nprint 4.5(4)\ndelete 2(5)\nsort(6)\nexit(0)\n";
	cin >> f;
	return f;
}

bool check(int a) {
	if (a < 0 || a > 6) {
		return false;
	}
	else {
		return true;
	}
}
