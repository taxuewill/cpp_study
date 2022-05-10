//
// Created by will on 2022/5/10.
//
#include <iostream>


#include <boost/core/noncopyable.hpp>
#include <boost/function.hpp>


using namespace std;

class ScopeGuard : private boost::noncopyable {

public:
    ScopeGuard(boost::function<void()> const &call_on_exit) : function_(call_on_exit), is_active_(true) {
        cout << "create ScopeGuard" << endl;
    }

    ~ScopeGuard() {
        cout << "destroy ScopeGuard" << endl;
        if (is_active_ && function_) {
            function_();
        }
    }

    void Disable() {
        is_active_ = false;
    }

private:
    boost::function<void()> const function_;
    bool is_active_;

};

int main() {
    cout << "Hello,Boost!!!" << endl;
    boost::function0<void> callback = []{
        cout<<"this is callback"<<endl;
    };
    if (callback) {
        cout << "callback is not null" << endl;
    } else {
        cout << "callback is null" << endl;
        cout << "empty is " << callback.empty() << endl;
    }

    ScopeGuard scope_guard(callback);
    scope_guard.Disable();


    return 0;
}

