#pragma once
#ifndef GRADE_CALCULATOR_H
#define GRADE_CALCULATOR_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <windows.h>
using namespace std;
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
class Assignment;

class Student;

class CSVReader;

class GradeCalculator;

class Assignment {
private:
    string assignmentname;
    double weightage;
    double score, totalmarks;

public:
    Assignment(string assignmentname, double weightage, double totalmarks);

    void addscore(double i);

    void deductscore(double i);

    double getweightage();
};

class Student {
    friend class CSVReader;

private:
    string fname, lname, email;
    int SID;
    Assignment* asgmt[9];
    string finalGrade;

public:
    Student();
};

class CSVReader {
private:
    ifstream fin;

public:
    CSVReader(string filename);

    double calculatetotal(Student& S);

    void readCSV(vector<Student>& stdn);

    string name(Student S);

    string getgrade(Student S);

    void setgrade(Student& S, string str);

    int getSID(Student S);
};

class GradeCalculator {
private:
    CSVReader* csv;
    vector<Student> stdn;
    double classavg, stddev, median;

    void calculateClassStats();

    void calculatedata();

    string getGrade(double percentage);

public:
    GradeCalculator(string filename);
    void showdata();
};

#endif // GRADE_CALCULATOR_H
