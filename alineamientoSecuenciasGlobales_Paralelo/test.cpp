#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
#define msg(str,str2) cout << str << str2<< endl
using namespace std;

using ll = long long;
using ld = long double;
using uint = unsigned int;
using ull = unsigned long long;
template<typename T>
using pair2 = pair<T, T>;
using pii = pair<int, int>;
using pli = pair<ll, int>;
using pll = pair<ll, ll>;

#define pb push_back
#define mp make_pair

int gcd(int a,int b){
    if(a%b==0) return b;
    else return gcd(b,a%b);
}

clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

int numThreads = 4;
std::vector<int> indices = {1};
int total_size = indices.size();
int chunk_size;
std::vector<std::vector<int>> chunks;

void solve(){
    if(total_size % numThreads == 0) chunk_size = total_size/numThreads;
    else chunk_size = total_size/numThreads + 1;
    cout << total_size << " " << chunk_size << endl;
    // return;
    for (int i = 0; i < total_size; i += chunk_size) {
        int chunk_end = min(i + chunk_size, total_size);
        chunks.push_back(std::vector<int>(indices.begin() + i, indices.begin() + chunk_end));
    }
    cout << "print chink" << endl;
    for(int e = 0 ; e < chunks.size(); e++){
        cout << "chunk: " << e << endl;
        for(auto j: chunks[e]){
            cout << j << " ";
        }cout << endl;
    }
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #ifdef DEBUG
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    solve();
    return 0;
}