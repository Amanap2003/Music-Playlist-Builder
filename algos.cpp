#include "algos.h"
//#include "MainFrame.h"
#include <vector>
#include "details.h"

using namespace std;

vector<details> algos::binknapsack(vector<details>& songs, int time)
{
    ans.clear();

  
    vector<vector<int>> dp(songs.size() + 1, vector<int>(time + 1, 0));

  
    for (size_t i = 1; i <= songs.size(); ++i) {
        for (int j = 1; j <= time; ++j) {
            if (j >= songs[i - 1].dur) {
                dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - songs[i - 1].dur] + songs[i - 1].rat);
            }
            else {
                dp[i][j] = dp[i - 1][j];
            }
        }
    }


    int tt = time;
    for (size_t i = songs.size(); i > 0 && tt > 0; --i) {
        if (dp[i][tt] != dp[i - 1][tt]) {
            ans.push_back(songs[i - 1]);
            tt -= songs[i - 1].dur;
        }
    }

	return ans;



}

vector<details> algos::frac_knapsack(vector<details>& songs, int time)
{
    ans.clear();
  

    
    vector<pair<double, int>> ratioIndex;
    for (size_t i = 0; i < songs.size(); ++i) {
        double ratio = static_cast<double>(songs[i].rat) / songs[i].dur;
        ratioIndex.push_back({ ratio, i });
    }

   
    sort(ratioIndex.begin(), ratioIndex.end(), greater<pair<double, int>>());

    int remainingTime = time;
    for (const auto& ri : ratioIndex) {
        int index = ri.second;
        if (songs[index].dur <= remainingTime) {
          
            ans.push_back(songs[index]);
            remainingTime -= songs[index].dur;
        }
        else {
         
            details fractionalItem = songs[index];
            fractionalItem.dur = remainingTime;
            //fractionalItem.rat = static_cast<int>(remainingTime * ri.first);
            ans.push_back(fractionalItem);
            break;
        }
    }

    return ans;
}

vector<details> algos::kmp(vector<details> songs, wxString pattern)
{
    ans.clear();
   
    vector<int> lps = LPS(pattern);
    
    for (int i = 0; i < songs.size(); i++) {
        int upper = 0;
        int lower = 0;
        wxString str = (songs[i].name) ;
        while (upper < str.size()) {
            if (pattern[lower] == str[upper]) {
                upper++; lower++;
            }
            else {
                if (lower == 0) upper++;
                else lower = lps[lower - 1];
            }

            if (lower == pattern.size()) {
                ans.push_back(songs[i]);
                break;
            }
        }

    }
    return ans;

}

vector<int> algos::LPS(wxString patt)
{
    vector<int> lps(patt.size(), 0);
    int left = 0;
    int right = 1;
    while (right < patt.size()) {
        if (patt[left] == patt[right]) {
            left++; lps[right] = left;
            right++;
        }
        else {
            if (left == 0) right++;
            else left = lps[left - 1];
        }
    }
    return lps;
}
