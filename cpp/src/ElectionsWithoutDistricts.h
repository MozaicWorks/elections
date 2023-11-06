#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>

#include "ElectionResultsFormatter.h"

using namespace std;

class ElectionsWithoutDistricts
{
private:
    vector<string> candidates;
    vector<string> officialCandidates;
    vector<int> votes;
    map<string, vector<string>> electorsByDistrict;

    const ElectionResultsFormatter electionResultsFormatter;

public:
    ElectionsWithoutDistricts(const map<string, vector<string>> &electorsByDistrict) : electorsByDistrict(electorsByDistrict), votes{}, officialCandidates{}, electionResultsFormatter{} {};

    void addCandidate(const string &);
    void recordVote(const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &);
    void recordVoteForNewCandidate(const string &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};