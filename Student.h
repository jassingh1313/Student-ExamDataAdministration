//WAHEGURU JI
#ifndef STUDENT_H
#define STUDENT_H
#include "Person.h"
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//defines elements for the exams already taken by the student.
struct Exam_n_Grade{
    string Exam_ID; 
    string Grade;
};
//defines elements for the exams scheduled by the student.
struct Exam_n_Date{
    string Exam_ID; 
    string Date; 
};

//inherits some general info from Person
//and store relevant information for a Student.
class Student: public Person{
private:
    string major;
    string StudentId;
    Exam_n_Grade TAKEN; 
    Exam_n_Date SCHEDULED;
    vector<Exam_n_Grade> Exams_taken;
    vector<Exam_n_Date> Exams_Scheduled;

public:
    void SetMajor(string _major){
        major = _major;
    }
    void SetStudentId(string _id){
        StudentId = _id;
    }
    string GetStudentId(){
        return StudentId; 
    }

    //adds an exam to the exams taken vector
    void AddExamsTaken(Exam_n_Grade _Taken){
        TAKEN.Exam_ID = _Taken.Exam_ID; 
        TAKEN.Grade = _Taken.Grade;
        Exams_taken.push_back(TAKEN);
    }

    //gets the grade the student received in a past exam.
    string GetGrade(string _examid){
        for(int i=0; i<Exams_taken.size(); i++){
            if(_examid == Exams_taken.at(i).Exam_ID){
                return Exams_taken.at(i).Grade; 
            }
        }
        return "Couldn't find grade.";
    }

    //adds an exam to the exams scheduled vector
    void AddExamsScheduled(Exam_n_Date _Scheduled){
        SCHEDULED.Exam_ID = _Scheduled.Exam_ID; 
        SCHEDULED.Date = _Scheduled.Date; 
        Exams_Scheduled.push_back(SCHEDULED);
    }

    vector<Exam_n_Date> GetExamsScheduled(){
        return Exams_Scheduled;
    }

    void EraseExamsTaken(){
        Exams_taken.clear();
    }
    void EraseExamsScheduled(){
        Exams_Scheduled.clear();
    }

    //removes a specific exam element from the student's scheduled exam list. 
    void Optout(string exam_id){
        for(int i = 0; i<Exams_Scheduled.size(); i++){
            if(exam_id == Exams_Scheduled.at(i).Exam_ID){
                Exams_Scheduled.erase(Exams_Scheduled.begin()+i);
            }
        }
    }

    void PrintExamsScheduled(){
        for(int i=0; i<Exams_Scheduled.size(); i++){
            cout<<Exams_Scheduled.at(i).Exam_ID<<" which is taking place at "<<Exams_Scheduled.at(i).Date<<endl;
        }
    }
    void PrintExamsTaken(){
        for(int i=0; i<Exams_taken.size(); i++){
            cout<<Exams_taken.at(i).Exam_ID<<endl;
        }
    }

    //gets exam id input and add to Scheduled Exams Vector of Student. 
    void SignUp(string _Examid, string _Date){
        Exam_n_Date Added_Exam;
        Added_Exam.Exam_ID = _Examid; 
        Added_Exam.Date = _Date; 
        Exams_Scheduled.push_back(Added_Exam);
    }
};

#endif