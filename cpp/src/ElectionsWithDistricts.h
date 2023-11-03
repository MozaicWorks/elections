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
    void recordVoteForElectionWithDistricts(const string &, const string &);

private:
    void recordVoteForExistingCandidateInElectionWithDistrict(const string &, vector<int> &) const;
    void recordVoteForNewCandidateInElectionWithDistrict(const string &, vector<int> &);
};