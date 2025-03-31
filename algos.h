#pragma once
#include "details.h"
#include <vector>
#include <string>
using namespace std;
class algos
{
public :
	vector<details> binknapsack(vector<details>& songs, int time);
	vector<details> frac_knapsack(vector<details>& songs, int time);
	vector<details> kmp(vector<details> songs, wxString pattern);
	vector<int> LPS(wxString patt);
	
	vector<details> ans;
};

