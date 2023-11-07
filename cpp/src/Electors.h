#include <string>
#include <map>
#include <vector>

using namespace std;

class Electors
{
private:
    const map<string, vector<string>> &electorsByDistrict;

public:
    Electors() : electorsByDistrict{} {}

    Electors(const map<string, vector<string>> &electorsByDistrict) : electorsByDistrict{electorsByDistrict} {}

    int count() const;
};