#include <vector>
#include <string>
#include <map>

using namespace std;

class ElectionsWithDistricts
{
private:
    vector<string> candidates;
    vector<string> officialCandidates;
    map<string, vector<int>> votesWithDistricts;

public:
    ElectionsWithDistricts() : candidates{}, officialCandidates{}, votesWithDistricts{} {};

    void addCandidate(const string &);
};