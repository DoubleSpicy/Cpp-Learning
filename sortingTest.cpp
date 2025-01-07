#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> getOrder(vector<vector<int>>& tasks) {
        // for(int i = 0; i < tasks.size(); i++){
        //     tasks[i].push_back(i);
        // }

        sort(tasks.begin(), tasks.end(), [](const vector<int>& a, const vector<int>& b){
            if(a[0] <= b[0]){
                return true;
            }
            return false;
        });
        vector<int> ans;
        return ans;
    }
};

int main(){
    Solution test;
    vector<vector<int>> input = {{142,185},{142,74},{669,253},{669,953},{669,694},{669,474},{669,839},{457,87},{457,371},{457,510},{457,691},{457,237},{457,225},{457,413},{457,935},{457,703},{669,709},{669,18},{669,687},{669,911},{669,741},{669,526},{669,900},{669,842},{767,624},{767,802},{287,690},{287,438},{287,406},{287,561},{287,518},{287,769},{287,709},{107,420},{107,277},{107,119},{107,28},{894,373},{894,592},{894,698},{894,947},{894,120},{894,296},{894,429},{894,792},{894,677},{13,6},{13,551},{13,85},{13,930},{13,749},{13,195},{13,629},{13,481},{13,873},{669,324},{669,659},{366,76},{366,385},{366,437},{366,72},{366,518},{366,7},{366,454},{366,382},{366,128},{366,134},{21,824},{21,5},{88,156},{88,331},{88,698},{88,595},{88,403},{380,607},{292,771},{292,323},{292,17},{292,712},{292,202},{292,183},{860,13},{860,632},{860,816},{860,890},{860,179},{860,873},{860,969},{860,960},{860,155},{128,796},{128,582},{128,978},{128,255}};
    test.getOrder(input);
    return 0;
}