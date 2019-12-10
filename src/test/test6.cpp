#include <iostream>
#include <vector>

using namespace std;

struct Student{
    int age;
    string name;
};

int main(int argc,char** argv){

    vector<Student> studentVec;
    Student s1;
    s1.age = 10;
    studentVec.push_back(s1);
    cout<<studentVec.size()<<endl;
    cout<<studentVec.capacity()<<endl;
    Student s2;
    s2.age = 11;
    s2.name = "xiaoming";
    studentVec.insert(studentVec.begin()+1,s2);
    cout<<studentVec.size()<<endl;
    cout<<studentVec.capacity()<<endl;
    Student s3;
    s3.age = 12;
    s3.name = "lili";
    studentVec.insert(studentVec.end(),s3);
    cout<<studentVec.size()<<endl;
    cout<<studentVec.capacity()<<endl;
    return 0;
}