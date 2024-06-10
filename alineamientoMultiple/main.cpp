#include <bits/stdc++.h>
#define all(x) x.begin(),x.end()
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

string line;
int score_i;
vector<string> sequences;
vector<vector<int>> matriz_scores;
map<int, map<int, pair<bool,pair<string,string> > >> map_first_alignment;

class NeedlemanWunsch{
    private:
        vector<vector<int>> dp;
        vector< vector< array<int,3> > > dp_direcciones;
        int cantidadCadenas;
        vector<pair<char,char>> ans;
        string str1,str2;
        pair<bool, pair<string,string>> particular_pair;
    public:
        NeedlemanWunsch(){
            cantidadCadenas = 0;
            particular_pair = {false,{"",""}};
        };
        ~NeedlemanWunsch(){};
        void clear(){
            dp.clear();
            dp_direcciones.clear();
            cantidadCadenas = 0;
            str1.clear();
            str2.clear();
            ans.clear();
            particular_pair = {false,{"",""}};
        }
        int bestScore(string secuenciaOne, string secuenciaTwo){
            clear();
            // cout << "bestScore" << endl;
            // cout << "secuenciaOne: " << secuenciaOne << endl;
            // cout << "secuenciaTwo: " << secuenciaTwo << endl;
            this->str1 = secuenciaOne; this->str2 = secuenciaTwo;

            //if(secuenciaOne.size()<secuenciaTwo.size()) swap(secuenciaOne,secuenciaTwo);
            int sizeOne = secuenciaOne.size();
	        int sizeTwo = secuenciaTwo.size();
            dp.resize(sizeOne+1,vector<int>(sizeTwo+1,0));
	        dp_direcciones.resize(sizeOne+1,vector< array<int,3> >(sizeTwo+1,{0,0,0}));
            int val = 0;
            for(int e = 0 ; e < sizeOne+1 ; e++){
                dp[e][0] = val;
                val -=2;
                if(e != 0) dp_direcciones[e][0][1] = 1;
            }
            val = 0;
            for(int e = 0 ; e < sizeTwo+1; e++){
                dp[0][e] = val;
                val -=2;
                if(e != 0) dp_direcciones[0][e][2] = 1;
            }
            int diag,up,leftt;
            for(int e = 1 ; e < sizeOne+1; e++){
                for(int j = 1 ;j < sizeTwo+1 ;j++){
                    diag = dp[e-1][j-1]+(secuenciaOne[e-1]==secuenciaTwo[j-1]?1:-1);
                    up = dp[e-1][j]-2;
                    leftt = dp[e][j-1]-2;
                    dp[e][j] = max(diag, max(up,leftt));
                    if(dp[e][j] == diag) dp_direcciones[e][j][0] = 1;
                    if(dp[e][j] == up) dp_direcciones[e][j][1] = 1;
                    if(dp[e][j] == leftt) dp_direcciones[e][j][2] = 1;
                }
	        }
            cout << "in bestScore print dp" << endl;
            cout << "begin dp" << endl;
            for(int e = 0; e < sizeOne+1; e++){
                for(int j = 0 ; j < sizeTwo+1; j++){
                    cout << dp[e][j] << " ";
                }cout << endl;
            } cout << endl;
            cout << "end print dp" << endl;

            cout << "secuencias: " << endl;
            cout << "01: " << str1 << endl;
            cout << "02: " << str2 << endl;
            return dp[sizeOne][sizeTwo];
        }

        void dfs(int x, int y){
            // cout << "dfs " << x <<" " << y << endl;
            if(x == 0 && y == 0){
                // cout << "in x == 0 && y == 0" << endl;
                //printing cadena
                cantidadCadenas++;
                // cout << "Printing Cadena" << endl;

                string a,b;
                for(int e = ans.size()-1; e >= 0 ; e--){
                    // cout << ans[e].first << " ";
                    a += ans[e].first;
                }

                for(int e = ans.size()-1; e >= 0 ; e--){
                    // cout << ans[e].second << " ";
                    b+= ans[e].second;
                }
                cout << a << endl;
                cout << b << endl;

                if(particular_pair.first == false){
                    particular_pair = {true,{a,b}};
                    cout << "a: " << a << endl;
                    cout << "b: " << b << endl;
                }
                // for(int e = ans.size()-1; e >= 0 ; e--){
                // 	cout  << ans[e].first << " ";
                // }cout  << endl;
                // for(int e = ans.size()-1; e >= 0 ; e--){
                // 	cout  << ans[e].second << " ";
                // }cout  << endl << endl;
                



                // if(particular_pair.size() == 0){
                //     particular_pair = ans;
                // }
                // cases.pb({a,b});
                return;
            }
            if(dp_direcciones[x][y][0]){
                // cout << "first if" << endl;
                // cout << secuenciaOne[x-1] << " " << secuenciaTwo[y-1] << endl;
                if(x>0 && y>0){
                    ans.pb({str1[x-1],str2[y-1]});
                    dfs(x-1,y-1);
                    ans.pop_back();
                }
                
            }if(dp_direcciones[x][y][1]){
                // cout << "second if" << endl;
                // cout << secuenciaOne[x-1] << " " << "-" << endl;
                if(x > 0){
                    ans.pb({str1[x-1],'-'});
                        // cout << "Up" << endl;
                    dfs(x-1,y);
                    ans.pop_back();
                }
            }if(dp_direcciones[x][y][2]){
                // cout << "third if" <<endl;
                // cout << secuenciaOne[x-1] << " " << "-" << endl;
                if(x > 0){
                    // ans.pb({str1[x-1],'-'});
                    ans.pb({'-',str2[y-1]});
                    // cout << "Left" << endl;
                    dfs(x,y-1);
                    ans.pop_back();
                }
            }
        }
        int getCantidadCadenas(){
            return cantidadCadenas;
        }
        auto getParticular_pair(){
            return particular_pair;
        }
        void alinearDosSecuencias(string str1, string str2){
            bestScore(str1,str2);
            dfs(str1.size(),str2.size());
            auto ff = getParticular_pair();
            cout << "ff: " << ff.first << " " << ff.second.first << " " << ff.second.second << endl;
        }
};

void solve(){
    fstream salida;
    salida.open("alineamiento_multiple_02.txt", ios::out);
    while(getline(cin,line)){
        // cout << "line is: " << line << endl;
        sequences.emplace_back(line);
    }

    // cout << "print secuences" << endl;
    // for(auto e: sequences){
    //     cout << e << endl;
    // }

    /*
        Inicializar la matriz de scores con 0s
    */
    matriz_scores.resize(sequences.size(),vector<int>(sequences.size(),0));
    // for(int e = 0; e < sequences.size(); e++){
    //     for(int j = 0 ; j < sequences.size(); j++){
    //         cout << matriz_scores[e][j] << " ";
    //     }cout << endl;
    // }cout << endl;

    /*
        Fill the matrix with the scores
    */
    NeedlemanWunsch NW;;
    for(int e = 0; e < sequences.size(); e++){
        for(int j = e ; j < sequences.size(); j++){
            if(e == j){
                matriz_scores[e][j] = 0;
            }else{
                NW.clear();
                score_i = NW.bestScore(sequences[e],sequences[j]);
                // para generar minimo un alineamiento en la recursion
                NW.dfs(sequences[e].size(),sequences[j].size());
                // map_first_alignment[e][j] = NW.getParticularPair();
                map_first_alignment[e][j] = NW.getParticular_pair();
                map_first_alignment[j][e] = NW.getParticular_pair();
                // cout << map_first_alignment[e][j].first << " " << map_first_alignment[e][j].second.first << " " << map_first_alignment[e][j].second.second << endl;
                matriz_scores[e][j] = score_i;
                matriz_scores[j][e] = score_i;
            }
        }
    }
    cout << "(i) print matriz scores" << endl;
    salida << "(i) print matriz scores" << endl;
    for(int e = 0; e < sequences.size(); e++){
        int sumatoria = 0;
        for(int j = 0 ; j < sequences.size(); j++){
            cout << matriz_scores[e][j] << " ";
            salida << matriz_scores[e][j] << " ";
            sumatoria += matriz_scores[e][j];
        }cout << " = " << sumatoria << endl;
        salida << " = " << sumatoria << endl;
    }cout << endl;
    salida << endl;

    /*
        Encontrar el S_c el centro de la matriz
    */
    int maximo = INT_MIN;
    int row_max;
    int S_c;
    for(int e = 0; e < sequences.size(); e++){
        S_c = 0;
        // el [i][i] == 0; no afecta en el row_max
        for(int j = 0 ; j < sequences.size(); j++){
            S_c += matriz_scores[e][j];
        }
        if(S_c > maximo){
            maximo = S_c;
            row_max = e;
        }
    }
    cout << "El centro es: S" << row_max+1 << ": " << sequences[row_max] << endl;
    salida << "El centro es: S" << row_max+1 << ": " << sequences[row_max] << endl;

    // cout << "maximo: " << maximo << endl;
    // cout << "row_max: " << row_max << endl;

    /*
        Encontrar alineamiento de cada secuencia con la estrella
    */
    cout << endl;
    salida << endl;
    cout << "(ii) alineamiento de cada secuencia con la estrella"  << endl;
    salida << "(ii) alineamiento de cada secuencia con la estrella"  << endl;

    int maximo_len_row = INT_MIN;
    maximo_len_row = max(maximo_len_row,(int)sequences[row_max].size());
    for(int e = 0 ; e < sequences.size(); e++){
        // cout << "e: " << e << endl;
        if(e != row_max){
            auto alineamiento = map_first_alignment[e][row_max];
            if(alineamiento.first == false
                || alineamiento.second.first.size() == 0
                || alineamiento.second.second.size() == 0){
                    cout << "assert !!!" << endl;
                    cout << "______________" << endl;
                    cout << alineamiento.first << " " << alineamiento.second.first << " " << alineamiento.second.second << endl;
            }

            // cout << "alineamoento:" << endl;
            // cout  << alineamiento.first << " " << alineamiento.second.first << " " << alineamiento.second.second << endl;
            maximo_len_row = max(maximo_len_row,(int)alineamiento.second.first.size());
            cout << "S" << row_max+1 <<"| ";
            salida << "S" << row_max+1 <<"| ";
            cout << alineamiento.second.second << endl;
            salida << alineamiento.second.second << endl;
            
            cout << "S" << e+1 <<"| ";
            salida << "S" << e+1 <<"| ";
            cout << alineamiento.second.first << endl << endl;
            salida << alineamiento.second.first << endl << endl;

            // cout << "S" << row_max+1 <<"| "<< "any" << endl;
            // cout << "S" << e+1 <<"| "<< "any2" << endl;
            // for(int e = alineamiento.size()-1; e >= 0 ; e--){
            //     cout << ans[e].first << " ";
            // }cout << endl;
            // for(int e = ans.size()-1; e >= 0 ; e--){
            //     cout << ans[e].second << " ";
            // }cout << endl;
            
            
        }
    }
    // salida << "stop" << endl;
    
    // return;
    cout << endl << "(iii) alineamiento múltiple" << endl;
    salida << endl << "(iii) alineamiento múltiple" << endl;
    vector<vector<char>> multipleAligment_representation;
    multipleAligment_representation.resize(sequences.size(),vector<char>(maximo_len_row,'-'));
    // // cout << "print multipleAligment_representation" << endl;

    // para la cadena estrella
    for(int e = 0 ; e < sequences[row_max].size(); e++){
        multipleAligment_representation[row_max][e] = sequences[row_max][e];
    }

    for(int e = 0 ; e  < sequences.size(); e++ ){
        if(e != row_max){
            auto alineamiento = map_first_alignment[e][row_max];
            // cout << "alineamiento test: " << alineamiento.first << " " << alineamiento.second << endl;
            // for(int j = alineamiento.size()-1; j >= 0 ; j--){
            //     multipleAligment_representation[e][index] = alineamiento[j].second;
            //     index++;
            // }
            for(int j = 0 ; j < alineamiento.second.first.size(); j++){
                multipleAligment_representation[e][j] = alineamiento.second.first[j];
            }
        }
    }
    // // print multiple alignment
    for(int e = 0 ; e < sequences.size(); e++){
        cout << "S" << e+1 << "| ";
        salida << "S" << e+1 << "| ";
        for(int j = 0 ; j < multipleAligment_representation[e].size(); j++){
            cout << multipleAligment_representation[e][j];
            salida << multipleAligment_representation[e][j];
        }cout << endl; salida << endl;
    }
}
void test(){
    string t1,t2;
    cin>>t1>>t2;
    NeedlemanWunsch NW;
    NW.alinearDosSecuencias(t1,t2);
    // cout << NW.bestScore(t1,t2) << endl;
    // NW.dfs(t1.size(),t2.size()); // para generar minimo un alineamiento en la recursion
    // cout << "cantidad cadenas: " << NW.getCantidadCadenas() << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #ifdef DEBUG
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    // solve();
    test();
    return 0;
}