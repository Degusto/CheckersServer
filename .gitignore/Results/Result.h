//
// Created by student on 22.01.18.
//

#ifndef CHECKERSSERVER_RESULT_H
#define CHECKERSSERVER_RESULT_H

#include <string>

using namespace std;

class Result
{
public:
    string status = "OK";
    string error = "";

    bool isSuccess()
    {
        return status == "OK";
    }

    static Result createSuccess()
    {
        return Result();
    }

    static Result createError(string error)
    {
        return Result("FAIL", error);
    }
protected:
    Result()
    {

    }
private:
    Result(string status, string error)
    {
        this->error = error;
        this->status = status;
    }
};

#endif //CHECKERSSERVER_RESULT_H
