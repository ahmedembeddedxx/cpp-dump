#include "GRADE-CALCULATOR.h"


// Assignment class
Assignment::Assignment(string assignmentname, double weightage, double totalmarks) {
	this->assignmentname = assignmentname;
	this->weightage = weightage;
	this->totalmarks = totalmarks;
	score = 0;
}

void Assignment::addscore(double i) {
	score += i;
}

void Assignment::deductscore(double i) {
	score = score - (i * score);
}

double Assignment::getweightage() {
	if (score > totalmarks)
		return weightage;
	return (score / totalmarks) * weightage;
}

// Student class
Student::Student() {
	asgmt[0] = new Assignment("MidTerm", 20, 100 * 1);
	asgmt[1] = new Assignment("Final Exam", 25, 100 * 1);
	asgmt[2] = new Assignment("Project 1", 10, 50 * 4);
	asgmt[3] = new Assignment("Project 2", 10, 50 * 2);
	asgmt[4] = new Assignment("Project 3", 10, 10 * 1);
	asgmt[5] = new Assignment("Lab Quizzes", 5, 2 * 13);
	asgmt[6] = new Assignment("Labs", 20, 5 * 59);
	asgmt[7] = new Assignment("ClassWork", 5, 5 * 10);
	asgmt[8] = new Assignment("Homework", 5, 2 * 15);
	finalGrade = "I";
}

// CSVReader class
CSVReader::CSVReader(string filename) {
	fin.open(filename);
}

double CSVReader::calculatetotal(Student& S) {
	double total = 0;
	for (int i = 0; i < 9; i++)
		total += S.asgmt[i]->getweightage();
	if (total > 100)
		return 100.0;
	return total;
}

void CSVReader::readCSV(vector<Student>& stdn) {
	if (!fin.is_open())
	{
		cout << "Error: Could not open the file." << endl;
		return;
	}

	string line;
	while (getline(fin, line))
	{
		Student student;
		int comma_counter = 0;
		char temp[100];
		for (int i = 0; i < line.size(); i++)
		{
			// Extract the data between commas and store it in 'temp'
			int j = 0;
			while (line[i] != ',' && line[i] != '\0')
			{
				temp[j] = line[i];
				i++;
				j++;
			}
			temp[j] = '\0';
			comma_counter++;
			// Based on the comma count, assign the data to the appropriate fields of the 'student' object
			if (comma_counter == 1)
				student.fname = temp;
			else if (comma_counter == 2)
				student.lname = temp;
			else if (comma_counter == 3)
				student.SID = stoi(temp);
			else if (comma_counter == 4)
				student.email = temp;
			else if (comma_counter == 5)
				student.asgmt[0]->addscore(stod(temp));
			else if (comma_counter == 6)
				student.asgmt[1]->addscore(stod(temp));
			else if (comma_counter >= 7 && comma_counter <= 10)
				student.asgmt[2]->addscore(stod(temp));
			else if (comma_counter == 11)
				student.asgmt[2]->deductscore(stod(temp));
			else if (comma_counter >= 12 && comma_counter <= 13)
				student.asgmt[3]->addscore(stod(temp));
			else if (comma_counter == 14)
				student.asgmt[3]->deductscore(stod(temp));
			else if (comma_counter == 15)
				student.asgmt[4]->addscore(stod(temp));
			else if (comma_counter >= 16 && comma_counter <= 28)
				student.asgmt[5]->addscore(stod(temp));
			else if (comma_counter >= 29 && comma_counter <= 92)
				student.asgmt[6]->addscore(stod(temp));
			else if (comma_counter >= 93 && comma_counter <= 102)
				student.asgmt[7]->addscore(stod(temp));
			else if (comma_counter >= 103)
				student.asgmt[8]->addscore(stod(temp));
		}
		stdn.push_back(student);
	}
}

string CSVReader::name(Student S) {
	return S.fname + ' ' + S.lname;
}

int CSVReader::getSID(Student S)
{
	return S.SID;
}

string CSVReader::getgrade(Student S) {
	return S.finalGrade;
}

void CSVReader::setgrade(Student& S, string str) {
	S.finalGrade = str;
}

// GradeCalculator class
GradeCalculator::GradeCalculator(string filename) {

	csv = new CSVReader(filename);
	csv->readCSV(stdn);
	classavg = 0, stddev = 0, median = 0;

}

void GradeCalculator::calculateClassStats() {
	// Calculate the class average.
	classavg = 0;
	for (int i = 0; i < stdn.size(); i++) {
		classavg += csv->calculatetotal(stdn[i]);
	}
	classavg /= stdn.size();

	// Calculate the standard deviation.
	stddev = 0;
	for (int i = 0; i < stdn.size(); i++) {
		double deviation = csv->calculatetotal(stdn[i]) - classavg;
		stddev += deviation * deviation;
	}
	stddev = sqrt(stddev / stdn.size());

	// Calculate the median.
	vector<double> grades;

	for (int i = 0; i < stdn.size(); i++) {
		grades.push_back(csv->calculatetotal(stdn[i]));
	}
	sort(grades.begin(), grades.end());
	int mid = grades.size() / 2;

	if (grades.size() % 2 == 1) {
		median = grades[mid];
	}
	else {
		median = (grades[mid] + grades[mid - 1]) / 2;
	}

}

void GradeCalculator::calculatedata() {
	calculateClassStats();
	for (int i = 0; i < stdn.size(); i++)
		csv->setgrade(stdn[i], getGrade(csv->calculatetotal(stdn[i])));
}

string GradeCalculator::getGrade(double percentage) {
	if (percentage >= 97.5)
		return "A+";
	else if (percentage >= 92.5)
		return "A";
	else if (percentage >= 90.0)
		return "A-";
	else if (percentage >= 87.5)
		return "B+";
	else if (percentage >= 82.5)
		return "B";
	else if (percentage >= 80.0)
		return "B-";
	else if (percentage >= 77.5)
		return "C+";
	else if (percentage >= 70.0)
		return "C";
	else if (percentage >= 60.0)
		return "D";
	else
		return "F";
}

void GradeCalculator::showdata() {
	calculatedata();
	int EMPLID = stdn.size();
	do
	{
		bool is_found = false;
		system("cls");
		for (int i = 0; i < stdn.size(); i++)
		{
			if (EMPLID == csv->getSID(stdn[i]))
			{
				SetConsoleTextAttribute(h, 112);
				is_found = true;
			}
			cout << csv->getSID(stdn[i]) << "\t" << csv->name(stdn[i]) << "\t\t" << csv->calculatetotal(stdn[i]) << "\t\t" << csv->getgrade(stdn[i]) << endl;
			SetConsoleTextAttribute(h, 7);
		}
		if (!is_found)
			cout << endl << "****Record Not Found****" << endl;
		cout << endl << "Class Average: " << classavg << endl;
		cout << "Standard Deviation: " << stddev << endl;
		cout << "Median: " << median << endl;
		cout << "\nSearch by EMPLID(-1 to terminate): ";
		cin >> EMPLID;
		if (EMPLID == -1)
			break;
	} while (true);
}


