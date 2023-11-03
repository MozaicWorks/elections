#include "ElectionsWithDistricts.h"

void ElectionsWithDistricts::addCandidate(const string &candidate)
{
    officialCandidates.push_back(candidate);
    candidates.push_back(candidate);
    votesWithDistricts["District 1"].push_back(0);
    votesWithDistricts["District 2"].push_back(0);
    votesWithDistricts["District 3"].push_back(0);
}