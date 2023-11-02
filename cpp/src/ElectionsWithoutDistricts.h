#include <string>
#include <vector>
#include <map>

using namespace std;

class ElectionsWithoutDistricts
{
private:
    vector<string> candidates;
    vector<int> votesWithoutDistricts;
    map<string, vector<string>> list;

public:
    ElectionsWithoutDistricts(const map<string, vector<string>> &list) : list(list), votesWithoutDistricts{} {};

    void addCandidate(const string &);

    void recordVoteForElectionWithoutDistrict(const string &);
    void recordVoteForExistingCandidateInNoDistrictElections(const string &);
    void recordVoteForNewCandidateInNoDistrictElections(const string &);

    int totalNumberOfVotesForElectionsWithoutDistricts() const;
    int numberOfValidVotesForElectionsWithoutDistricts() const;
};