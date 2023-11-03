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
    vector<int> votesWithoutDistricts;
    map<string, vector<string>> list;

    const ElectionResultsFormatter electionResultsFormatter;

public:
    ElectionsWithoutDistricts(const map<string, vector<string>> &list) : list(list), votesWithoutDistricts{}, officialCandidates{}, electionResultsFormatter{} {};

    void addCandidate(const string &);

    void recordVote(const string &);
    void recordVoteForExistingCandidate(const string &);
    void recordVoteForNewCandidate(const string &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;

    map<string, string> results() const;
};