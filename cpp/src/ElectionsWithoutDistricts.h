#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <iomanip>

#include "Candidates.h"
#include "Votes.h"
#include "ElectionResultsFormatter.h"

using namespace std;

class ElectionsWithoutDistricts
{
private:
    const ElectionResultsFormatter electionResultsFormatter;
    Electors electors;
    Candidates candidates;
    Votes theVotes;

public:
    ElectionsWithoutDistricts(Electors electors) : theVotes{}, electors(electors), electionResultsFormatter{}, candidates{} {};

    void addCandidate(const string &);
    void recordVote(const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &);
    void recordVoteForNewCandidate(const string &);

    int numberOfValidVotes() const;
};