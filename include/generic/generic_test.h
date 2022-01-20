//
// Created by will on 2022/1/20.
//

#ifndef CPP_STUDY_GENERIC_TEST_H
#define CPP_STUDY_GENERIC_TEST_H
#include <memory>


template<typename T>
class Student{
public:
    typedef T t_type;
private:
    std::shared_ptr<t_type> member_t_;

};

#endif //CPP_STUDY_GENERIC_TEST_H
