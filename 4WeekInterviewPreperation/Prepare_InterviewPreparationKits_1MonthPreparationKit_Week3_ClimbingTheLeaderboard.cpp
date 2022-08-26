/*
An arcade game player wants to climb to the top of the leaderboard and track their
ranking. The game uses Dense Ranking*, so its leaderboard works like this:
    -The player with the highest score is ranked number  on the leaderboard.
    -Players who have equal scores receive the same ranking number, and the next
     player(s) receive the immediately following ranking number.
     * https://en.wikipedia.org/wiki/Ranking#Dense_ranking_.28.221223.22_ranking.29 *
Example
    ranked = [100,90,90,80]
    player = [70,80,105]
    The ranked players will have ranks 1, 2, 2, and 3, respectively. If the player's
    scores are 70, 80, and 105, their rankings after each game are 4th, 3rd, and 1st.
    Return [4,3,1].
Function Description
    Complete the climbingLeaderboard function in the editor below.
    climbingLeaderboard has the following parameter(s):
        -int ranked[n]: the leaderboard scores
        -int player[m]: the player's scores
Returns
    int[m]: the player's rank after each new score
Input Format
    The first line contains an integer , the number of players on the leaderboard.
    The next line contains  space-separated integers ranked[i], the leaderboard scores
    in decreasing order.
    The next line contains an integer, , the number games the player plays.
    The last line contains  space-separated integers player[j], the game scores.
Constraints
    1<=n<=2X10^5
    1<=m<=2X10^5
    0<ranked[i<=10^9,for 0<=i<n
    0<=player[j]<=10^9, for 0<=j<m
    The existing leaderboard, ranked, is in descending order.
    The player's scores, player, are in ascending order.
Subtask
    For 60% of the maximum score:
    1<=n<=200
    1<=m<=200
Sample Input 1
    7
    100 100 50 40 40 20 10
    4
    5 25 50 120
Sample Output 1
    6
    4
    2
    1
Sample Input 2
    6
    100 90 90 80 75 60
    5
    50 65 77 90 102
Sample Output 2
    6
    5
    4
    2
    1
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'climbingLeaderboard' function below.
 *
 * The function is expected to return an INTEGER_ARRAY.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY ranked
 *  2. INTEGER_ARRAY player
 */

vector<int> climbingLeaderboard(vector<int> ranked, vector<int> player) {
    int n = ranked.size();
    int m = player.size();
    int index=m-1;
    int pos = 1;
    int prev = ranked[0];
    vector<int> v(m,0);

    for (int i =0; i<n; i++) {
        if(ranked[i]!=prev){
            prev=ranked[i];
            pos++;
        }
        while(player[index]>=ranked[i]){
            v[index]=pos;
            index--;
            if(index<0){
                break;
            }
        }
    }
    pos++;
    for (int j = 0; j<=index; j++) {
        v[j]=pos;
    }

    return v;
    //worked for several but failed on a few, also timed out on a few
    /*
    vector<int> nPlace;
    vector<int> answer;

    answer.resize(player.size());
    nPlace.resize(ranked.size());
    for(int i = 0; i < ranked.size(); i++)
    {
        if(i == 0)
        {
            nPlace[i] = 1;
        }
        else if(ranked[i] == ranked[i-1])
        {
            nPlace[i] = nPlace[i-1];
        }
        else
        {
            nPlace[i] = nPlace[i-1] + 1;
        }
    }
    cout << "ranked: ";
    for(int i = 0; i < ranked.size(); i++)
    {
        cout << ranked[i] << " ";
    }
    cout << "\nPlace: ";
    for(int i = 0; i < nPlace.size(); i++)
    {
        cout << nPlace[i] << " ";
    }
    cout << endl;
    for(int j = 0; j < player.size(); j++)
    {

        for(int i = 0; i < ranked.size() - 1; i++)
        {
            cout <<":"<< player[j] << " " << ranked[i] << endl;
            if(player[j] > ranked[0])
            {
                cout << "!" << endl;
                answer[j] = 1;
                break;
            }
            else if(player[j] == ranked[i])
            {
                answer[j] = nPlace[i];
            }
            else if(player[j] < ranked[i] && player[j] > ranked[i+1])
            {
                answer[j] = nPlace[i]+1;
                cout << "?" << nPlace[i] << endl;
                break;
            }
            else if(player[j] < ranked[ranked.size() - 1]) {
                answer[j] = nPlace[nPlace.size() - 1] + 1;
                cout << "^"<<endl;
                break;
            }
        }
    }

    return answer;
    */
    //assumed ranked and players would be added to same scoreoard
    //*not the case, want to do them one at a time I guess.
    /*
    bool moved = false;

    //combin player and ranked into new ranked
    for(int i = 0; i < player.size(); i++)
    {
        nRank.push_back(player[i]);
    }
    //sort total list
    do
    {
        moved = false;
        for(int i = 0; i < nRank.size() - 1; i++)
        {
            if(nRank[i] < nRank[i+1])
            {
                int temp = nRank[i];
                nRank[i] = nRank[i+1];
                nRank[i+1] = temp;
                moved = true;
                break;
            }
        }
    }while(moved);

    nPlace.resize(nRank.size());
    for(int i = 0; i < nRank.size(); i++)
    {
        if(i == 0)
        {
            nPlace[i] = 1;
        }
        else if(nRank[i] == nRank[i-1])
        {
            nPlace[i] = nPlace[i-1];
        }
        else
        {
            nPlace[i] = nPlace[i-1] + 1;
        }
    }

    anwser.resize(player.size());
    for(int i = 0; i < player.size(); i++)
    {
        for(int j = 0; j < nRank.size(); j++)
        {
            if(player[i] == nRank[j])
            {
                anwser[i] = nPlace[j];
                cout << "found: \n" << player[i] << " " << nRank[j] << endl
                    << anwser[i] << " " << nPlace[j] << endl;
            }
        }
    }

    cout << "New Ranked List: ";
    for(int i = 0; i < nRank.size(); i++)
    {
        cout << nRank[i] << ", ";
    }
    cout << endl << "New Place List: ";
    for(int i = 0; i < nPlace.size(); i++)
    {
        cout << nPlace[i] << ", ";
    }
    cout << endl;
    return anwser;
    */
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string ranked_count_temp;
    getline(cin, ranked_count_temp);

    int ranked_count = stoi(ltrim(rtrim(ranked_count_temp)));

    string ranked_temp_temp;
    getline(cin, ranked_temp_temp);

    vector<string> ranked_temp = split(rtrim(ranked_temp_temp));

    vector<int> ranked(ranked_count);

    for (int i = 0; i < ranked_count; i++) {
        int ranked_item = stoi(ranked_temp[i]);

        ranked[i] = ranked_item;
    }

    string player_count_temp;
    getline(cin, player_count_temp);

    int player_count = stoi(ltrim(rtrim(player_count_temp)));

    string player_temp_temp;
    getline(cin, player_temp_temp);

    vector<string> player_temp = split(rtrim(player_temp_temp));

    vector<int> player(player_count);

    for (int i = 0; i < player_count; i++) {
        int player_item = stoi(player_temp[i]);

        player[i] = player_item;
    }

    vector<int> result = climbingLeaderboard(ranked, player);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
