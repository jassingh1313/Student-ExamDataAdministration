#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;

//this is a base class for the derived Student Class.
//Some common general elements from Person can be inherited by Student. Such as name and date of birth. 
class Person{
protected:
    string FullName;
    string dob;
public:
    void SetName(string _fullname){
        FullName = _fullname;
    }
    string GetName(){
        return FullName;
    }
    void SetDob(string _dob){
        dob = _dob;
    }
};

#endif