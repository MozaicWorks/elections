#pragma once

#include <string>

using namespace std;

class Percent
{
private:
    const int partial;
    const int total;

public:
    Percent(const int partial, const int total) : partial(partial), total(total) {}
    float value() const;
    string format() const;
};