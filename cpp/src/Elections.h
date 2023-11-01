#include <vector>
#include <string>
#include <map>
using namespace std;

class Elections
{

private:
	vector<string> candidates;
	vector<string> officialCandidates;
	vector<int> votesWithoutDistricts;
	map<string, vector<int>> votesWithDistricts;
	map<string, vector<string>> list;
	bool withDistrict;

public:
	Elections(const map<string, vector<string>> &list, bool withDistrict) : list(list), withDistrict(withDistrict), votesWithDistricts(){};

	void addCandidate(const string &candidate);

	void voteFor(const string &elector, const string &candidate, const string &electorDistrict);

	map<string, string> results() const;

private:
	void recordVoteForElectionWithoutDistrict(const string &);
	void recordVoteForExistingCandidateInNoDistrictElections(const string &);
	void recordVoteForNewCandidateInNoDistrictElections(const string &);

	void recordVoteForElectionWithDistricts(const string &, const string &);
	void recordVoteForExistingCandidateInElectionWithDistrict(const string &, vector<int> &) const;
	void recordVoteForNewCandidateInElectionWithDistrict(const string &, vector<int> &);
};
