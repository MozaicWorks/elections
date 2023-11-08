#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>

#include "Candidates.h"
#include "ElectionResultsFormatter.h"

using namespace std;

class ElectionsWithoutDistricts
{
private:
    vector<int> votes;
    const ElectionResultsFormatter electionResultsFormatter;
    Electors electors;
    Candidates candidates;

public:
    ElectionsWithoutDistricts(Electors electors) : votes{}, electors(electors), electionResultsFormatter{}, candidates{} {};

    void addCandidate(const string &);
    void recordVote(const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &);
    void recordVoteForNewCandidate(const string &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};