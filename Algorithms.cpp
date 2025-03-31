#include "Algorithms.h"
//#include "MainFrame.h"
#include <vector>
#include "details.h"

using namespace std;

vector<details> Algorithms::binknapsack(vector<details>& songs, int time)
{
	ans.clear(); 
	vector<vector<int>> dp(songs.size(), vector<int>(time + 1, 0));

	for (int i = 1; i < songs.size(); i++) {
		for (int j = 1; j <= time; j++) {
			if (j >= songs[i].dur) {
				dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - songs[i].dur] + songs[i].rat);
			}
			else dp[i][j] = dp[i - 1][j];
		}
	}

	
	int tt = time;

	for (int i = songs.size() - 1; i > 0; i--) {
		if (dp[i][tt] != dp[i - 1][tt]) {
			ans.push_back(songs[i-1]);
			tt -= songs[i - 1].dur;
		}
	}


	return ans;

	

}
