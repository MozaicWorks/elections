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
    map<string, vector<string>> electorsByDistrict;

    const ElectionResultsFormatter electionResultsFormatter;
    Electors electors;

public:
    ElectionsWithDistricts(map<string, vector<string>> electorsByDistrict) : candidates{}, officialCandidates{}, votes{}, electorsByDistrict{electorsByDistrict}, electionResultsFormatter{} {};

    ElectionsWithDistricts(Electors electors) : candidates{}, officialCandidates{}, votes{}, electorsByDistrict{electorsByDistrict}, electionResultsFormatter{}, electors(electors){};

    void addCandidate(const string &);
    void recordVote(const string &, const string &);
    map<string, string> results() const;

private:
    void recordVoteForExistingCandidate(const string &, vector<int> &) const;
    void recordVoteForNewCandidate(const string &, vector<int> &);

    int totalNumberOfVotes() const;
    int numberOfValidVotes() const;
};