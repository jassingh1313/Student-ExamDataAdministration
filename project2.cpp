//WAHEGURU JI

#include<iostream>
#include<fstream>
#include "Exam.h"
#include "Student.h"
#include "Person.h"
using namespace std;

int main(){
  //loads in data for Exam objects from input file
  //input file is exams.txt and contains the data for the variables listed below: 
  vector<Exam> Exams; 
  ifstream instream2;
  instream2.open("exams.txt");
  if(!instream2.is_open()){
    cout<<"Couldn't open exams.txt file"<<endl;
    return 1;
  }

  string ExamDate;
  string ExamType; 
  string TotalSeats;
  float highest;
  float avg;
  float lowest;
  string ExamId;
  Exam currExam;
  string indicator;

  getline(instream2, ExamDate);
  currExam.SetExamDate(ExamDate);
  while(!instream2.eof()){

    getline(instream2, ExamType);
    currExam.SetExamType(ExamType);

    getline(instream2, TotalSeats);
    currExam.SetTotalSeats(TotalSeats);

    getline(instream2, ExamId);
    currExam.SetExamId(ExamId);
    

    getline(instream2, indicator);
    if(indicator == "Results:"){
      instream2>>highest>>avg>>lowest;
      instream2.ignore();
      currExam.SetGrades(highest, avg, lowest);
      Exams.push_back(currExam);
    }
    else{
      Exams.push_back(currExam);
      currExam.SetExamDate(indicator);
      continue;
    }
    getline(instream2, ExamDate);
    currExam.SetExamDate(ExamDate);
    
  }
  instream2.close();

  //loads in data for Student objects from input file
  //input file is students.txt and contains the data for the variables listed below: 
  vector<Student> Students;
  ifstream instream1;
  instream1.open("students.txt");
  if(!instream1.is_open()){
    cout<<"Couldn't open students.txt file"<<endl;
    return 1;
  }

  string Name;
  string DOB; 
  string Major;
  string SID;
  Exam_n_Grade Taken;
  Exam_n_Date Scheduled;
  Student currStudent;

  while(!instream1.eof()){
    getline(instream1, Name);
    currStudent.SetName(Name);

    getline(instream1, DOB);
    currStudent.SetDob(DOB);

    getline(instream1, Major);
    currStudent.SetMajor(Major);

    getline(instream1, SID);
    currStudent.SetStudentId(SID);

    //create a new vector each time for each student Exams Taken, so the other students exams don't add up as well.
    currStudent.EraseExamsTaken(); 
    bool flag = true; 
    getline(instream1, Taken.Exam_ID);
    while(flag){
      getline(instream1, Taken.Grade); 
      currStudent.AddExamsTaken(Taken);
      getline(instream1,Taken.Exam_ID);
      if(Taken.Exam_ID == "Stop"){
        flag = false;
      }
    }


    //create a new vector each time for each student, so the other students exams don't add up as well. 
    currStudent.EraseExamsScheduled(); 
    bool flag1 = true;
    getline(instream1, Scheduled.Exam_ID);
    for(int i=0; i<Exams.size(); i++){
      if(Exams.at(i).GetExamId() == Scheduled.Exam_ID){
        Exams.at(i).Register1(SID); 
      }
    }
    while(flag1){
      getline(instream1, Scheduled.Date);
      currStudent.AddExamsScheduled(Scheduled);
      getline(instream1,Scheduled.Exam_ID);
      for(int i=0; i<Exams.size(); i++){
        if(Exams.at(i).GetExamId() == Scheduled.Exam_ID){
          Exams.at(i).Register1(SID); 
        }
      }
      if(Scheduled.Exam_ID == "Stop"){
        flag1 = false;
      }
      //connect the student id with Seats vector in Exam.
      //Add the student id when a particular exam has been scheduled.
    }
    Students.push_back(currStudent);
  }
  instream1.close();


//writes new data to files from user's input.
  ofstream outstream; 
  outstream.open("exams.txt", ios::app);
  if(!outstream.is_open()){
    cout<<"Couldn't open exams.txt file"<<endl;
    return 1;
  }
  ofstream outstream1; 
  outstream1.open("students.txt", ios::app);
  if(!outstream1.is_open()){
    cout<<"Couldn't open students.txt file"<<endl;
    return 1;
  }


  //Main menu:
  cout<<">**********************************<"<<endl;
  cout<<"*Welcome to Exam Management System!*"<<endl;
  cout<<">**********************************<"<<endl<<endl<<endl;
  string repeat_program = "1";

  while(repeat_program == "1"){ 
    cout<<">---------------------**************************------------------------<"<<endl;
    cout<<"*Are you Student or Instructor? Enter 1 for Instructor and 0 for Student*"<<endl; 
    cout<<">---------------------**************************------------------------<"<<endl;
    int choice; 
    cin>>choice;
    //Instructor Menu
    if(choice == 1){
      cout<<"So you are an Instructor."<<endl<<endl;
      cout<<"These are your options:"<<endl<<endl;

      cout<<"-------------------------------------------------------------------"<<endl;
      cout<<"*To create a new exam? Enter 1"<<endl;
      cout<<"-------------------------------------------------------------------"<<endl;
      cout<<"*To see which students have signed up for an upcoming exam? Enter 2"<<endl;
      cout<<"-------------------------------------------------------------------"<<endl;
      cout<<"*To see results of a past exam: Enter 3"<<endl; 
      cout<<"-------------------------------------------------------------------"<<endl;
      int choiceT1; 
      cin>>choiceT1;
      cin.ignore();

      //creates new exam based on instructor input
      if(choiceT1 == 1){
        cout<<"This is the list of all exams: "<<endl;
        for(int i=0; i<Exams.size(); i++){
          cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" at "<<Exams.at(i).GetExamDate()<<endl;
        }
        Exam Exam1;
        cout<<"Pls enter the Exam Date in (hr(##)am/pm, day(##), month(##), year(####)) format as above:"<<endl; 
        string _examdate;
        getline(cin, _examdate);
        outstream<<_examdate<<endl;
        Exam1.SetExamDate(_examdate);
        cout<<"Pls enter the Type of the exam you want to create: (SAT, PSAT, etc.)"<<endl; 
        string _ExamType;
        getline(cin, _ExamType);
        outstream<<_ExamType<<endl;
        Exam1.SetExamType(_ExamType);
        cout<<"Pls enter total number of Seats for this exam."<<endl;
        string _TotalSeats;
        getline(cin,_TotalSeats);
        outstream<<_TotalSeats<<endl;
        Exam1.SetTotalSeats(_TotalSeats);
        cout<<"Please enter an exam id for this exam: "<<endl;
        string _ExamId;
        getline(cin,_ExamId);
        outstream<<_ExamId<<endl;
        Exam1.SetExamId(_ExamId);
        Exams.push_back(Exam1);

        cout<<"This is the new list of all exams: "<<endl;
        for(int i=0; i<Exams.size(); i++){
          cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" at "<<Exams.at(i).GetExamDate()<<endl;
        }

      }


      //retrieves data of students who signed up for a particular exam.
      else if(choiceT1 == 2){
        cout<<"This is the list of all upcoming exams: (hr, day, m, y)"<<endl;
        for(int i=0; i<Exams.size(); i++){
          int Date_length = Exams.at(i).GetExamDate().length();
          if(Exams.at(i).GetExamDate().at(Date_length-2) >= '2'){
            cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" which is taking place at "<<Exams.at(i).GetExamDate()<<endl;
          }
        }
        
        cout<<"Enter the exam Id: "<<endl;
        string _ESignup;
        cin>>_ESignup;
        vector<string> Students_signedup; //vector of student ids.

        cout<<"These are the students that have signed up for this exam: "<<endl;
        for(int i=0; i<Exams.size(); i++){
          if(Exams.at(i).GetExamId() == _ESignup){
            Students_signedup = Exams.at(i).GetSignedUp();
          }
        }

        for(int i=0; i<Students_signedup.size(); i++){
          cout<<Students_signedup.at(i)<<": ";  //returns string student id.
          for(int j=0; j<Students.size(); j++){
            if(Students.at(j).GetStudentId() == Students_signedup.at(i)){
              cout<<Students.at(j).GetName()<<endl; 
            }
          }
        }
      }

      //shows results summary of a past exam to the user. 
      else if(choiceT1 == 3){
        cout<<"This is the list of all past exams: (hr, day, m, y)"<<endl;
        for(int i=0; i<Exams.size(); i++){
          int Date_length = Exams.at(i).GetExamDate().length();
          if(Exams.at(i).GetExamDate().at(Date_length-2) < '2'){
            cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" which took place at "<<Exams.at(i).GetExamDate()<<endl;
          }
        }

        cout<<"Enter the exam Id: "<<endl;
        string _EResultsId;
        getline(cin, _EResultsId); //keep track of these use getline when possible.
        vector<float> ResSummary; 
        for(int i=0; i<Exams.size(); i++){
          if(Exams.at(i).GetExamId() == _EResultsId){
            ResSummary = Exams.at(i).GetGrades();
          }
        }
        cout<<"This is the results summary for this exam: "<<endl;
        cout<<"highest score: "<<ResSummary.at(0)<<endl;
        cout<<"average score: "<<ResSummary.at(1)<<endl;
        cout<<"lowest score: "<<ResSummary.at(2)<<endl;
      }


    }

    else{
      //Student Menu
      cout<<"So you are a Student."<<endl;
      cout<<"Enter your student Id(0-2)"<<endl<<endl;
      string choice_sid;
      cin>>choice_sid;
      cout<<"These are your options:"<<endl<<endl;

      cout<<"---------------------------------------"<<endl;
      cout<<"To opt out of an Exam. Enter 1"<<endl;
      cout<<"---------------------------------------"<<endl;
      cout<<"To sign up for an Exam. Enter 2"<<endl;
      cout<<"---------------------------------------"<<endl;
      cout<<"To check results of past exams. Enter 3"<<endl;
      cout<<"---------------------------------------"<<endl;
      int choiceS1;
      cin>>choiceS1;

      //lets student opt out of a scheduled exam. 
      if(choiceS1 == 1){

        cout<<"This is the list of all upcoming exams: (hr, day, m, y)"<<endl;
        for(int i=0; i<Exams.size(); i++){
          int Date_length = Exams.at(i).GetExamDate().length();
          if(Exams.at(i).GetExamDate().at(Date_length-2) >= '2'){
            cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" which is taking place at "<<Exams.at(i).GetExamDate()<<endl;
          }
        }


        cout<<"You have signed up for: "<<endl;
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).PrintExamsScheduled();
          }
        }
        

        cout<<"Enter the exam id to opt out of: "<<endl;
        string Exam_optout;
        cin>>Exam_optout;
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).Optout(Exam_optout);
          }
        }

        cout<<"You have been removed from this exam. Now your scheduled exams are: "<<endl<<endl;
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).PrintExamsScheduled();
          }
        }
        //updated the scheduled exam of the student, but also need to update the specific exam's seat vector. 
        //update information in filestreams also towards the end for exams.txt and students.txt.
      }


      //lets student sign up for an upcoming exam. 
      else if(choiceS1 == 2){
        cout<<"This is the list of all upcoming exams: (hr, day, m, y)"<<endl;
        for(int i=0; i<Exams.size(); i++){
          int Date_length = Exams.at(i).GetExamDate().length();
          if(Exams.at(i).GetExamDate().at(Date_length-2) >= '2'){
            cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" which is taking place at "<<Exams.at(i).GetExamDate()<<endl;
          }
        }

        cout<<"You have already signed up for: "<<endl;
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).PrintExamsScheduled();
          }
        }

        cout<<"Which exam do you want to sign up for additionally? Enter ExamId: "<<endl;
        string choice_EID;
        cin>>choice_EID; 
        string Associated_date;

        //to check if student has already signed up for an exam and doesn't sign up twice for the same exam.

        //get the specific students exams scheduled vector:
        vector<Exam_n_Date> Student_ScheduledExams;
        for(int i = 0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId() == choice_sid){
            Student_ScheduledExams = Students.at(i).GetExamsScheduled();
          }
        }

        bool repeat = true;
        //take the input exam id and compare with all exam ids in the specific Student's exams scheduled vector.
        while(repeat){
          repeat = false;
          for(int i=0; i<Student_ScheduledExams.size(); i++){
            if(choice_EID == Student_ScheduledExams.at(i).Exam_ID){
              cout<<"You have already signed up for this exam. Sign up for another one."<<endl;
              cin>>choice_EID;
              repeat = true;
            }
          }
        }

        //take exam id, go to specific exam in exams vector, then go to seats vector and insert an element in the seats vector with the student id.
        for(int i=0; i<Exams.size(); i++){
          if(choice_EID == Exams.at(i).GetExamId()){
            Exams.at(i).Register1(choice_sid);
            Associated_date = Exams.at(i).GetExamDate();
          }
        }

        //once checked then update student's exams scheduled vector.
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).SignUp(choice_EID, Associated_date);
          }
        }

        cout<<"You have been added to this exam. Now Scheduled exams are: "<<endl;
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).PrintExamsScheduled();
          }
        }

      }

      //allows student to check his/her results for a previous exam. 
      else if(choiceS1 == 3){
        cout<<"This is the list of all exams: (hr, day, m, y)"<<endl;
        for(int i=0; i<Exams.size(); i++){
          cout<<Exams.at(i).GetExamId()<<": "<<Exams.at(i).GetExamType()<<" which is taking place at "<<Exams.at(i).GetExamDate()<<endl;
        }
        cout<<"These are the list of exams you have taken: "<<endl;
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            Students.at(i).PrintExamsTaken();
          }
        }

        cout<<"Which exam's result would you like to see? (enter the exam Id)"<<endl;
        string see_result; 
        cin>>see_result;
        //enter the exams taken vector and retrieve grade.
        for(int i=0; i<Students.size(); i++){
          if(Students.at(i).GetStudentId()==choice_sid){
            cout<<"You got a score of: "<<Students.at(i).GetGrade(see_result)<<" in this exam."<<endl; 
          }
        }

      }
    }

    cout<<"Do you want to repeat this program? Enter 1 for Yes and 0 for No: "<<endl;
    cin>>repeat_program;
  }

  outstream.close();
  outstream1.close();
  
 

  return 0;

}