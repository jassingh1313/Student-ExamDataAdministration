//WAHEGURU JI 
#ifndef EXAM_H
#define EXAM_H
#include<iostream>
#include<string>
#include<vector>
#include "Student.h"
#include "Person.h"
using namespace std;


class Exam{
private:
//stores all exam related information
    string ExamDate; 
    string ExamType; 
    int totalSeats;
    int currSeats; 
    vector<string> Seats; //stores the data for the seats in the exam. contains student id's to represent each student according to instructions. 
    float highest; //grade summary of past exams
    float avg;
    float lowest;
    string ExamId;
    
public:
    //constructor for the data members.
    Exam(){
        ExamDate = ""; 
        ExamType = "";
        totalSeats = 0;
        currSeats = 0;
        Seats.resize(100); //intializing all seat elements with an empty string to indicate available seat. 
        for(int i=0; i<Seats.size(); i++){
            Seats.at(i) = "";
        }
        float highest;
        float avg;
        float lowest;
        string ExamId; 
    }

    void SetExamDate(string _date){
        ExamDate = _date;
    }
    string GetExamDate(){
        return ExamDate;
    }
    void SetExamType(string _type){
        ExamType = _type; 
    }
    string GetExamType(){
        return ExamType;
    }

    //sets the total seats for the specific exam and resizes seats vector accordingly.
    void SetTotalSeats(string _TotalSeats){
        int _totalSeats = stoi(_TotalSeats); 
        totalSeats = _totalSeats;
        Seats.resize(totalSeats);
        for(int i=0; i<Seats.size(); i++){
            Seats.at(i) = "";
        }
    }

    //prints all the elements of the seats vector.
    void PrintSeats(){
        for(int i = 0; i<Seats.size(); i++){
            cout<<Seats.at(i)<<endl;
        }
    }

    //get a list of students who have signed up for this specific exams. 
    vector<string> GetSignedUp(){
        vector<string> Students_SignedUp;
        for(int i=0; i<Seats.size(); i++){
            if(Seats.at(i) != ""){
                Students_SignedUp.push_back(Seats.at(i));
            }

        }
        return Students_SignedUp;
    }

    
    void SetGrades(float _highest, float _avg, float _lowest){
        highest = _highest;
        avg = _avg; 
        lowest = _lowest;
    }

    //gets a results summary for the exam. 
    vector<float> GetGrades(){
        vector<float> Grades;
        Grades.push_back(highest);
        Grades.push_back(avg);
        Grades.push_back(lowest);
        return Grades;
    }

    void SetExamId(string _examid){
        ExamId = _examid;
    }
    string GetExamId(){
        return ExamId; 
    }
    
    //adds the student's id to an empty seat element to indicate the seat is now booked. 
    void Register1(string _SID){
        Seats.at(currSeats) = _SID;
        currSeats++; 
    }

};

#endif