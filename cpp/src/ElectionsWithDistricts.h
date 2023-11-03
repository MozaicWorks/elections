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
    map<string, vector<int>> votesWithDistricts;
    map<string, vector<string>> list;

    const ElectionResultsFormatter electionResultsFormatter;

public:
    ElectionsWithDistricts(map<string, vector<string>> list) : candidates{}, officialCandidates{}, votesWithDistricts{}, list{list}, electionResultsFormatter{} {};

    void addCandidate(const string &);
    void recordVote(const string &, const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &, vector<int> &) const;
    void recordVoteForNewCandidate(const string &, vector<int> &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};