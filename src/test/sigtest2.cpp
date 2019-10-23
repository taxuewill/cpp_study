#include <signal.h>
#include <unistd.h>

#include <iostream>

using namespace std;

void ouch(int sig){
    cout<<"\nOuch! - I got "<<sig<<endl;
    (void)signal(SIGINT, SIG_DFL);
}

int main(){
    cout<<"Hello,signal"<<endl;
    signal(SIGINT,ouch);
    while(true){
        cout<<"..."<<endl;
        sleep(1);
    }

    return 0;
}