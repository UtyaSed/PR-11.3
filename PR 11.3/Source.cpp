#include <iostream>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <iomanip>
#include <string>
#include <Windows.h>

using namespace std;

enum Specialnist { KN, ME, IF, FI, TN };
string specialnistList[] = { "Комп'ютерні науки", "Математика і економіка", "Інформфтика", "Фізика і інформатика", "Трудове навчання" }; // масив назв спеціальностей
struct Student
{
	char prizv[100];
	int kurs;
	Specialnist spec;
	int fiz;
	int mat;
	int specials;
	union 
	{
		int prog;
		int chis_metod;
		int pedagog;
	};
};

void Create(char* fname);
void LoadFile(char* fname);
void Sort(char* fname);
void IndexSort(char* fname, char* gname);
int Search(char* fname);

int main()
{
	SetConsoleCP(1251); 
	SetConsoleOutputCP(1251); 
	char fname[61];
	char gname[61];
	char ch;
	int found;
	do
	{
		cout << endl;
		cout << "Select:" << endl;
		cout << "[1] - Введення та збереження інформації;" << endl;
		cout << "[2] - Завантаження та вивід інформації;" << endl;
		cout << "[3] - Сортування" << endl;
		cout << "[4] - Індексне сортування" << endl;
		cout << "[5] - Пошук" << endl << endl;
		cout << "[0] - Завершення роботи." << endl << endl;
		cout << "Ваш вибір: "; cin >> ch;
		switch (ch)
		{
		case '0':
			break;
		case '1':
			cin.get(); 
			cin.sync(); 
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			Create(fname);
			break;
		case '2':
			cin.get(); 
			cin.sync(); 
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			LoadFile(fname);
			break;
		case '3':
			cin.get(); 
			cin.sync(); 
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			Sort(fname);
			cout << "Файл відсортовано" << endl;
			cout << endl;
			break;
		case '4':
			cin.get(); 
			cin.sync(); 
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			cout << "Назва додаткового файлу: "; cin.getline(gname, sizeof(gname));
			cout << endl;
			IndexSort(fname, gname);
			cout << "Відсортований файл створено!" << endl;
			cout << endl;
			break;
		case '5':
			cin.get();
			cin.sync();
			cout << endl;
			cout << "Назва файлу: "; cin.getline(fname, sizeof(fname));
			cout << endl;
			Sort(fname);
			if ((found = Search(fname)) != -1) {
				cout << "Знайдено студента в позиції \'" << found + 1 << "\"" << endl;
				LoadFile(fname);
			}
			else {
				cout << "Шуканого студента не знайдено" << endl;
			}
			break;
		default:
			cout << "Помилка вводу! ";
		}
	} while (ch != '0');
	return 0;
}
void Create(char* fname)
{
	ofstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	int spec;
	Student student;
	char ch;
	int i = 0;
	do
	{
		cout << "Cтудент № " << i + 1 << ":" << endl; i++;
		cout << "прізвище: "; cin >> student.prizv;
		cout << "курс: "; cin >> student.kurs;
		cout << "оцінка з фізики: "; cin >> student.fiz;
		cout << "оцінка з математики: "; cin >> student.mat;
		cout << "Спеціальність (0 - Комп'ютерні науки, 1 - Математика і економіка, 2 - Інформатика, 3 - Фізика і інформатика, 4 - Трудове навчання): ";  cin >> spec;
		if (spec > 4) {
			cout << endl;
			cout << "============================================================================================================" << endl;
			cout << endl;
			cout << "Схоже, ви ввели неправильне значення спеціальності!" << endl;
			cout << "Програма продовжить роботу з спеціальностю за замовчуванням - комп. науки!" << endl;
			cout << "Перезапустіть програму для введення правильного номера спеціальності." << endl;
			cout << endl;
			cout << "============================================================================================================" << endl;
			cout << endl;
			spec = 0;
		}
		student.spec = (Specialnist)spec; // присвоєння спеціальності
		switch (student.spec)
		{
		case KN:
			cout << "оцінка з програмування: "; cin >> student.prog;
			if (student.prog)
				student.specials = (student.prog);
			cout << endl;
			break;
		case ME:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			if (student.pedagog)
				student.specials = (student.pedagog);
			cout << endl;
			break;
		case IF:
			cout << "оцінка з чисельних методів: "; cin >> student.chis_metod;
			if (student.chis_metod)
				student.specials = (student.chis_metod);
			cout << endl;
			break;
		case FI:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			if (student.pedagog)
				student.specials = (student.pedagog);
			cout << endl;
			break;
		case TN:
			cout << "оцінка з педагогіки: "; cin >> student.pedagog;
			if (student.pedagog)
				student.specials = (student.pedagog);
			cout << endl;
			break;
		}


		if (!f.write((char*)&student, sizeof(Student)))
		{
			cerr << "Помилка запису в файл." << endl;
			f.close();
		}
		cout << "Продовжити? (Y/N) "; cin >> ch;
	} while (ch == 'Y' || ch == 'y');

	f.close();
}


void LoadFile(char* fname)
{
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	Student student;
	cout << "============================================================================================================"
		<< endl;
	cout << " | № | Прізвище | Курс | Cпеціальність | Фізика | Математика | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "------------------------------------------------------------------------------------------------------------"
		<< endl;
	int i = 0;
	while (f.read((char*)&student, sizeof(Student)))
	{
		cout << " |" << setw(2) << right << i + 1 << " "; i++;
		cout << " | " << setw(9) << left << student.prizv
			<<  " | " << setw(2) << right << student.kurs << "  "
			<<  " | " << setw(14) << left << specialnistList[student.spec]
			<< setw(4) << " | " << setw(3) << left << student.fiz << "  "
			<< setw(6) << " | " << setw(6) << left << student.mat << " ";
		switch (student.spec)
		{
		case KN:
			cout << setw(8) << "| " << setw(7) << left << student.prog << setw(19)
				<< " | " << setw(12) << left
				 << "| " << left << " |" << endl;
			break;
		case ME:
			cout << "" << setw(15) << "| " << " "
				 << "" << setw(18) << "| "
				<< setw(6) << "| " << setw(6) << left << student.pedagog << " | " << endl;
			break;
		case IF:
			cout << "" << setw(15) << " | " << setw(9) << " | " << " "
				<< setw(8) << student.chis_metod << " | " << " "
				<< setw(10) << "" << " | " << endl;
			break;
		case FI:
			cout << "" << setw(15) << " | " << " "
				 << "" << setw(18) << " | "
				<< setw(6) << " | " << setw(6) << left << student.pedagog << " | " << endl;
			break;
		case TN:
			cout << "" << setw(15) << " | " << " "
				<< "" << setw(18) << " | "
				<< setw(6) << " | " << setw(6) << left << student.pedagog << " | " << endl;
			break;
		}
	}
	cout << "============================================================================================================"
		<< endl;
	cout << endl;
	f.close();
}

void Sort(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); 
	int size = f.tellg(); 
	size = size / sizeof(Student); 
	f.seekg(0, ios::beg); 
	Student* student = new Student[size];
	Student temp;
	f.read((char*)student, size * sizeof(Student)); 
	f.close();
	for (int i = 0; i < size - 1; i++) { 
		for (int j = size - 1; j > i; j--) {
			string prizvOne = student[j].prizv;
			string prizvTwo = student[j - 1].prizv;
			if ((student[j].spec < student[j - 1].spec)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].specials < student[j - 1].specials)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].specials == student[j - 1].specials &&
					prizvOne < prizvTwo))
			{
				temp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = temp;
			}
		}
	}
	f.close();
	ofstream file(fname, ios::binary);
	file.write((char*)student, size * sizeof(Student));
	file.close();
}

void IndexSort(char* fname, char* gname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return;
	}
	f.seekg(0, ios::end); 
	int size = f.tellg(); 
	size = size / sizeof(Student); 
	f.seekg(0, ios::beg); 
	Student* student = new Student[size];
	Student temp;
	f.read((char*)student, size * sizeof(Student));  
	for (int i = 0; i < size - 1; i++) { 
		for (int j = size - 1; j > i; j--) {
			string prizvOne = student[j].prizv;
			string prizvTwo = student[j - 1].prizv;
			if ((student[j].spec < student[j - 1].spec)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].specials < student[j - 1].specials)
				||
				(student[j].spec == student[j - 1].spec &&
					student[j].specials == student[j - 1].specials &&
					prizvOne < prizvTwo))
			{
				temp = student[j];
				student[j] = student[j - 1];
				student[j - 1] = temp;
			}
		}
	}
	f.close();
	ofstream file(gname, ios::binary);
	if (!file)
	{
		cerr << "Помилка відкриття файлу '" << gname << "'" << endl;
		f.close();
		return;
	}
	file.write((char*)student, size * sizeof(Student));
	file.close();
}

int Search(char* fname) {
	ifstream f(fname, ios::binary);
	if (!f)
	{
		cerr << "Помилка відкриття файлу '" << fname << "'" << endl;
		f.close();
		return -1;
	}
	Specialnist special;
	int ispec, avar;
	string prizv;
	cout << endl;
	cout << "Введіть ключі пошуку: " << endl << endl;
	cout << "cпеціальність (0 - Комп'ютерні науки, 1 - Математика і економіка, 2 - Інформфтика, 3 - Фізика і інформатика, 4 - Трудове навчання): ";
	cin >> ispec;
	special = (Specialnist)ispec;
	cout << " прізвище: "; cin >> prizv;
	cout << " бал з третього предмета: "; cin >> avar;
	cout << endl;

	f.seekg(0, ios::end); 
	int size = f.tellg(); 
	size = size / sizeof(Student);
	f.seekg(0, ios::beg); 
	Student* student = new Student[size];
	f.read((char*)student, size * sizeof(Student));
	int L = 0, R = size, m;
	do { 
		m = (L + R) / 2;
		string OriginalPrizv = student[m].prizv;
		if (OriginalPrizv == prizv && student[m].spec == special && student[m].specials == avar) {
			return m;
		}
		if ((student[m].specials < avar)
			||
			(student[m].specials == avar &&
				student[m].spec < special)
			||
			(student[m].specials == avar &&
				student[m].spec == special &&
				student[m].prizv < prizv)) {
			L = m + 1;
		}
		else {
			R = m - 1;
		}
	} while (L <= R);
	return -1;
}
