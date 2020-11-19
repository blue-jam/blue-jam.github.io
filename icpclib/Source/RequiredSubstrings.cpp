//Aho-Corasick & dp
#include <string>
#include <algorithm>
#include <cfloat>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>

#define ALL(x) (x).begin(),(x).end()
using namespace std;
const double eps = 1e-10;

struct PMA{
    int id;
    PMA *next[0x100];       //next[0] is for fail
    vector<int> accept;
    PMA() { fill(next, next + 0x100, (PMA*)NULL); }
};
//Pattern Matching AutoMaton
void buildPMA(vector<string> &words, vector<PMA*> &vp){
    int n = words.size();
    PMA *root = new PMA;    //createTrie
    root -> id = 0;
    vp.push_back(root);
    int count = 1;
    for(int i = 0; i<n; ++i){
        PMA *v = root;
        int m = words[i].size();
        for(int j = 0; j < m; ++j){
            int c = words[i][j];
            if(v -> next[c] == NULL){
                v -> next[c] = new PMA;
                v -> next[c] -> id = count++;
                vp.push_back(v -> next[c]);
            }
            v = v -> next[c];
        }
        v -> accept.push_back(i);
    }
    queue<PMA*> Q;          //make failure link
    for(int c = 1; c < 0x100; ++c){
        if(root -> next[c] != NULL){
            root -> next[c] -> next[0] = root;
            Q.push(root -> next[c]);
        } else root -> next[c] = root;
    }
    while(!Q.empty()){
        PMA *v = Q.front(); Q.pop();
        for(int c = 1; c < 0x100; ++c){
            if(v -> next[c] != NULL) 
                Q.push(v -> next[c]);
            PMA *r = v -> next[0];
            while(r -> next[c] == NULL) r = r -> next[0];
            if(v -> next[c] != NULL)
                v -> next[c] -> next[0] = r -> next[c];
            else
                v -> next[c] = r -> next[c];
        }
        v -> accept.insert(v -> accept.end(), ALL(v -> next[0] -> accept));
    }
}
int dp[60][2500][1<<6];
#define DIV 1000000009
class RequiredSubstrings {
    public:
    int bitCount(int bit){
        if(bit == 0) return bit;
        else return (bit & 1) + bitCount(bit >> 1);
    }
    int solve(vector <string> words, int C, int L) {
        int n = words.size();
        vector<PMA*> pma;
        cout << "Build PMA Step..." << endl;
        buildPMA(words, pma);

        memset(dp, 0, sizeof(dp));
        cout << "DP Step..." << endl;
        cout << L << "," << (1 << n) << "," << pma.size() << endl;
        dp[0][0][0] = 1;
        for(int i = 0; i < L; ++i){
            for(int j = 0; j < pma.size(); ++j){
                for(int k = 0; k < (1 << n); ++k){
                    for(int c = 'a'; c <= 'z'; ++c){
                        PMA *nv = pma[j];
                        nv = nv -> next[c];
                        int bit = k;
                        for(int l = 0; l < nv -> accept.size(); ++l){
                            bit = bit | (1 << nv -> accept[l]);
                        }
                        dp[i+1][nv -> id][bit] = (dp[i+1][nv -> id][bit] + dp[i][j][k]) % DIV;
                    }
                }
            }
        }
        int res = 0;
        for(int i = 0; i < pma.size(); ++i){
            for(int j = 0; j < (1 << n); ++j){
                if(bitCount(j) == C) res = (res + dp[L][i][j]) % DIV;
            }
        }
        return res;
    }
// BEGIN CUT HERE
	public:
	void run_test(int Case) { if ((Case == -1) || (Case == 0)) test_case_0(); if ((Case == -1) || (Case == 1)) test_case_1(); if ((Case == -1) || (Case == 2)) test_case_2(); if ((Case == -1) || (Case == 3)) test_case_3(); if ((Case == -1) || (Case == 4)) test_case_4(); test_case_5(); test_case_36(); test_case_25(); test_case_101();}
	private:
	template <typename T> string print_array(const vector<T> &V) { ostringstream os; os << "{ "; for (typename vector<T>::const_iterator iter = V.begin(); iter != V.end(); ++iter) os << '\"' << *iter << "\","; os << " }"; return os.str(); }
	void verify_case(int Case, const int &Expected, const int &Received) { cerr << "Test Case #" << Case << "..."; if (Expected == Received) cerr << "PASSED" << endl; else { cerr << "FAILED" << endl; cerr << "\tExpected: \"" << Expected << '\"' << endl; cerr << "\tReceived: \"" << Received << '\"' << endl; } }
	void test_case_0() { string Arr0[] = {"a","aa","aaa","aaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 50; verify_case(0, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_1() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 7; int Arg3 = 31810104; verify_case(1, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_2() { string Arr0[] = {"abcdefgh"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 7; int Arg3 = 0; verify_case(2, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_3() { string Arr0[] = {"a","b","c","d"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 3; int Arg2 = 3; int Arg3 = 24; verify_case(3, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_4() { string Arr0[] = {"ab","bc","xy","yz"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 3; int Arg3 = 2; verify_case(4, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_5() { string Arr0[] = {"abcdef","cd"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 1; int Arg2 = 6; int Arg3 = 2280824; verify_case(5, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_36() { string Arr0[] = {"gyoq", "naiwsgyoqkxewe", "yoqkxewe", "o", "irvmusp"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 2; int Arg2 = 50; int Arg3 = 83105086; verify_case(36, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_25() { string Arr0[] = {"fjktnswcuhkavcxjckuwelzucjobmvehuftr", "nlpbmfbkzqmujnmucyemugeouogsmjnisuh", "qnomlhrfbyzhqmxruxdigoszwadqzddk", "mbxnafanyayreyderinoumwwajtagpkeyw", "xxhfqqrtjdtmrycqmkhofbwhbcxylpadfi", "zccnuypudymiqqhjrnypuyswjiunzjoxtjwm"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 0; int Arg2 = 48; int Arg3 = 570686630; verify_case(25, Arg3, solve(Arg0, Arg1, Arg2)); }
	void test_case_101() { string Arr0[] = {"aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", "baaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "abaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab", "aabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", "aaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"}; vector <string> Arg0(Arr0, Arr0 + (sizeof(Arr0) / sizeof(Arr0[0]))); int Arg1 = 6; int Arg2 = 50; int Arg3 = 0; verify_case(101, Arg3, solve(Arg0, Arg1, Arg2)); }
// END CUT HERE

};
// BEGIN CUT HERE
int main() {

    RequiredSubstrings ___test;

    ___test.run_test(-1);

}
// END CUT HERE
