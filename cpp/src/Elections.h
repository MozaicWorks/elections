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
	void recordVoteWithoutDistrict(const string &);
	void recordVoteWithoutDistrictForCandidateNotFound(const string &);
	void recordVoteWithDistrict(const string &, vector<int> &) const;
	void recordVoteWithDistrictAndCandidateNotFound(const string &, vector<int> &);
	void recordVoteWithExistingDistrict(const string &, const string &);
	void recordVoteWithoutDistrict2(const string &);
};
