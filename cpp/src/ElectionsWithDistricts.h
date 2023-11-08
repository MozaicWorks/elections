#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>

#include "Candidates.h"
#include "ElectionResultsFormatter.h"

using namespace std;

class ElectionsWithDistricts
{
private:
    map<string, vector<int>> votes;

    const ElectionResultsFormatter electionResultsFormatter;
    Electors electors;
    Candidates theCandidates;

public:
    ElectionsWithDistricts(Electors electors) : votes{}, electionResultsFormatter{}, electors(electors), theCandidates{} {};

    void addCandidate(const string &);
    void recordVote(const string &, const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &, vector<int> &) const;
    void recordVoteForNewCandidate(const string &, vector<int> &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};