#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

#include "ElectionResultsFormatter.h"

using namespace std;

class ElectionsWithDistricts
{
private:
    vector<string> candidates;
    vector<string> officialCandidates;
    map<string, vector<int>> votes;

    const ElectionResultsFormatter electionResultsFormatter;
    Electors electors;

public:
    ElectionsWithDistricts(Electors electors) : candidates{}, officialCandidates{}, votes{}, electionResultsFormatter{}, electors(electors){};

    void addCandidate(const string &);
    void recordVote(const string &, const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &, vector<int> &) const;
    void recordVoteForNewCandidate(const string &, vector<int> &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};