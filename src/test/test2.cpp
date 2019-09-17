#include <iostream>
#include <memory>


using namespace std;

int main(int argc,char** argv){
    cout<<"Hello,cpp"<<endl;
    shared_ptr<int> number(new int(),[](int * p){cout<<"delete number "<<*p<<endl;});
    *number=10;
    number.reset();

    cout<<"end..."<<endl;
    return 0;
}