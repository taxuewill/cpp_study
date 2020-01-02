#include <iostream>
#include <memory>

using namespace std;

class Person{
public:
    virtual void test(){
        cout<<"person test"<<endl;
    }
    virtual void test(float age){
        cout<<"float age"<<endl;
    }
    virtual ~Person(){
        cout<<"destroy Person"<<endl;
    }
};

class Student:public Person{
public:
    // using Person::test;
    void test(int aget){
        cout<<"student test"<<endl;
    }
};


int main(int argc,char **argv){
    std::shared_ptr<Person> p1 = std::make_shared<Person>();
    cout<<"p1 count "<<p1.use_count()<<endl;
    std::shared_ptr<Person> p2 = p1;
    p1 = nullptr;
    
    cout<<"p1 count "<<p1.use_count()<<endl;
    cout<<"p2 count "<<p2.use_count()<<endl;
    

   
}