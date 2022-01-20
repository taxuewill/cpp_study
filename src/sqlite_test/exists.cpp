//
// Created by will on 2021/9/28.
//

/**
 *  Example is implemented from here https://www.w3resource.com/sqlite/exists-operator.php
 */
#include "sqlite_orm/sqlite_orm.h"
#include <string>
#include <iostream>

using std::cout;
using std::endl;

struct Customer {
    std::string code;
    std::string name;
    std::string city;
    std::string workingArea;
    std::string country;
    int grade;
    double openingAmt;
    double receiveAmt;
    double paymentAmt;
    double outstandingAmt;
    std::string phoneNo;
    std::string agentCode;
};

struct Agent {
    std::string code;
    std::string name;
    std::string workingArea;
    double comission;
    std::string phoneNo;
    std::string country;
};

struct Order {
    std::string num;
    int amount;
    int advanceAmount;
    std::string date;
    std::string custCode;
    std::string agentCode;
};

int main(int, char **) {
    using namespace sqlite_orm;

    auto storage = make_storage("exists.sqlite",
                                make_table("customer",
                                           make_column("CUST_CODE", &Customer::code, primary_key()),
                                           make_column("CUST_NAME", &Customer::name),
                                           make_column("CUST_CITY", &Customer::city),
                                           make_column("WORKING_AREA", &Customer::workingArea),
                                           make_column("CUST_COUNTRY", &Customer::country),
                                           make_column("GRADE", &Customer::grade),
                                           make_column("OPENING_AMT", &Customer::openingAmt),
                                           make_column("RECEIVE_AMT", &Customer::receiveAmt),
                                           make_column("PAYMENT_AMT", &Customer::paymentAmt),
                                           make_column("OUTSTANDING_AMT", &Customer::outstandingAmt),
                                           make_column("PHONE_NO", &Customer::phoneNo),
                                           make_column("AGENT_CODE", &Customer::agentCode)),
                                make_table("agents",
                                           make_column("AGENT_CODE", &Agent::code, primary_key()),
                                           make_column("AGENT_NAME", &Agent::name),
                                           make_column("WORKING_AREA", &Agent::workingArea),
                                           make_column("COMMISSION", &Agent::comission),
                                           make_column("PHONE_NO", &Agent::phoneNo),
                                           make_column("COUNTRY", &Agent::country)),
                                make_table("orders",
                                           make_column("ORD_NUM", &Order::num, primary_key()),
                                           make_column("ORD_AMOUNT", &Order::amount),
                                           make_column("ADVANCE_AMOUNT", &Order::advanceAmount),
                                           make_column("ORD_DATE", &Order::date),
                                           make_column("CUST_CODE", &Order::custCode),
                                           make_column("AGENT_CODE", &Order::agentCode)));

    storage.sync_schema();

    {
        //  SELECT agent_code,agent_name,working_area,commission
        //  FROM agents
        //  WHERE exists
        //      (SELECT *
        //      FROM customer
        //      WHERE grade=3 AND agents.agent_code=customer.agent_code)
        //  ORDER BY commission;
        auto rows = storage.select(columns(&Agent::code, &Agent::name, &Agent::workingArea, &Agent::comission),
                                   where(exists(select(asterisk<Customer>(),
                                                       where(is_equal(&Customer::grade, 3) and
                                                             is_equal(&Agent::code, &Customer::agentCode))))),
                                   order_by(&Agent::comission));
        cout << "AGENT_CODE  AGENT_NAME                                WORKING_AREA  COMMISSION" << endl;
        cout << "----------  ----------------------------------------  ------------  ----------" << endl;
        for(auto &row: rows) {
            cout << std::get<0>(row) << '\t' << std::get<1>(row) << '\t' << std::get<2>(row) << '\t' << std::get<3>(row)
                 << endl;
        }
    }
    return 0;
}