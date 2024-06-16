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
using matrix_double = unordered_map< string, unordered_map<string,double> >;


#define pb push_back
#define mp make_pair

clock_t startTime;
double getCurrentTime() {
    return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}











double val;
int n,n_;

double media(vector<double> &X){
    double sum=0;
    for(auto x:X){
        sum+=x;
    }
    return sum/X.size();
}

double coeficienteCorrelacion(vector<double> &X, vector<double> &Y){
    // cout << X.size() << " " <<Y.size() << endl;
    double mediaX = media(X);
    double mediaY = media(Y);
    double numerador = 0.0;
    double firstDen = 0.0, secondDen = 0.0;
    for(int e = 0 ; e < (int)X.size(); e++){
        numerador += ( (X[e] - mediaX) * (Y[e] - mediaY) );
        firstDen += ( (X[e] - mediaX) * (X[e] - mediaX) );
        secondDen += ( (Y[e] - mediaY) * (Y[e] - mediaY) );
    }
    if(firstDen*secondDen == 0){
        cout << "denominador 0\n";
        return 0;
    }
    double r = numerador / sqrt(firstDen*secondDen);
    return r;
}
void solve(){
    cin>>n;
    n_=n;
    vector<double> X,Y;
    while(n--){
        cin>>val;
        X.pb(val);
    }
    while(n_--){
        cin>>val;
        Y.pb(val);
    }
    // cout << "X: " << endl;
    // for(auto x:X){
    //     cout << x << " ";
    // }
    // cout << endl;
    // cout << "Y: " << endl;
    // for(auto y:Y){
    //     cout << y << " ";
    // }
    // cout << endl;
    auto r = coeficienteCorrelacion(X,Y);
    cout << "r: " <<r << endl;

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