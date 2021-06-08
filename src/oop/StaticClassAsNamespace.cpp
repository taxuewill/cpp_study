// Base class for classes used as namespaces.  HotSpot style prefers
// using classes for grouping.  Deriving from this class indicates the
// derived class is intended to be a namespace, with no instances ever
// created.
#include <iostream>

using namespace std;

struct AllStatic{
    AllStatic() = delete;
    ~AllStatic() = delete;
};

class SubClass : AllStatic{
public:
    static void test(){
        cout<<"this is test"<<endl;
    }
};


int main(){
    cout<<"AllStatic Test"<<endl;
//    SubClass subClass;
//    subClass.test()
    SubClass::test();
    return 0;
}