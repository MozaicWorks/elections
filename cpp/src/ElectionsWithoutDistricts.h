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
    const ElectionResultsFormatter electionResultsFormatter;
    Electors electors;

public:
    ElectionsWithoutDistricts(Electors electors) : votes{}, officialCandidates{}, electors(electors), electionResultsFormatter{} {};

    void addCandidate(const string &);
    void recordVote(const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &);
    void recordVoteForNewCandidate(const string &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};