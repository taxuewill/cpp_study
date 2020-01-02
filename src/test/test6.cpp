#include <iostream>
#include <vector>
#include <thread>

using namespace std;

class Student{

public:
	Student(){}
	Student(int age){}
    int age;
    string name;

};

class Request
{
public:
	Request(int id) : mId(id) { }
	void process()
	{
		cout << "Processing request " << mId << endl;
	}
private:
	int mId;
};

int main(int argc,char** argv){

    Request req(100);
	thread t{ &Request::process, &req };
	t.join();
    return 0;
}