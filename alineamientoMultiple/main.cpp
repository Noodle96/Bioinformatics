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
map<int, map<int, vector<pair<char,char>>>> map_first_alignment;


class NeedlemanWunsch{
    private:
        vector<vector<int>> dp;
        vector< vector< array<int,3> > > dp_direcciones;
        int cantidadCadenas;
        vector<pair<char,char>> ans;
        string str1,str2;
        vector<pair<char, char>> particular_pair;
    public:
        NeedlemanWunsch(){
            cantidadCadenas = 0;
        };
        ~NeedlemanWunsch(){};
        void clear(){
            dp.clear();
            dp_direcciones.clear();
            cantidadCadenas = 0;
            str1.clear();
            str2.clear();
            ans.clear();
            particular_pair.clear();
        }
        int bestScore(string secuenciaOne, string secuenciaTwo){
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
            // cout << "in bestScore print dp" << endl;
            // for(int e = 0; e < sizeOne+1; e++){
            //     for(int j = 0 ; j < sizeTwo+1; j++){
            //         cout << dp[e][j] << " ";
            //     }cout << endl;
            // } cout << endl;
            // cout << "end print dp" << endl;

            // cout << "secuencias: " << endl;
            // cout << "01: " << str1 << endl;
            // cout << "02: " << str2 << endl;
            return dp[sizeOne][sizeTwo];
        }

        void dfs(int x, int y){
            // cout << "dfs " << x <<" " << y << endl;
            if(x == 0 && y == 0){
                // cout << "in x == 0 && y == 0" << endl;
                //printing cadena
                cantidadCadenas++;
                // cout << "Printing Cadena" << endl;
                // for(int e = ans.size()-1; e >= 0 ; e--){
                //     cout << ans[e].first << " ";
                // }cout << endl;
                // for(int e = ans.size()-1; e >= 0 ; e--){
                //     cout << ans[e].second << " ";
                // }cout << endl;

                // for(int e = ans.size()-1; e >= 0 ; e--){
                // 	salida << ans[e].first << " ";
                // }salida << endl;
                // for(int e = ans.size()-1; e >= 0 ; e--){
                // 	salida << ans[e].second << " ";
                // }salida << endl << endl;
                if(particular_pair.size() == 0){
                    particular_pair = ans;
                }
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
        vector<pair<char,char>> getParticularPair(){
            return particular_pair;
        }
};

void solve(){
    fstream salida;
    salida.open("alineamiento_multiple_00.txt", ios::out);
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
                map_first_alignment[e][j] = NW.getParticularPair();
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
        if(e != row_max){
            // cout << (map_first_alignment[row_max][e].size() == 0) <<  endl;
            if(map_first_alignment[row_max][e].empty()){
                cout << "No hubo concidencias" << endl;
                cout << "S" << row_max+1 <<"| "<< sequences[row_max] << endl;
                cout << "S" << e+1 <<"| "<< "vacio" << endl;
                salida << "No hubo concidencias" << endl;
                salida << "S" << row_max+1 <<"| "<< sequences[row_max] << endl;
                salida << "S" << e+1 <<"| "<< "vacio" << endl;
                return;
            }else{
                auto alineamiento = map_first_alignment[row_max][e];
                maximo_len_row = max(maximo_len_row,(int)alineamiento.size());
                cout << "S" << row_max+1 <<"| ";
                salida << "S" << row_max+1 <<"| ";
                for(int e = alineamiento.size()-1; e >= 0 ; e--){
                    cout << alineamiento[e].first << " ";
                    salida << alineamiento[e].first << " ";
                }cout << endl;
                salida << endl;
                cout << "S" << e+1 <<"| ";
                salida << "S" << e+1 <<"| ";
                for(int e = alineamiento.size()-1; e >= 0 ; e--){
                    cout << alineamiento[e].second << " ";
                    salida << alineamiento[e].second << " ";
                }cout << endl;
                salida << endl;

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
    }
    cout << endl << "(iii) alineamiento múltiple" << endl;
    salida << endl << "(iii) alineamiento múltiple" << endl;
    vector<vector<char>> multipleAligment_representation;
    multipleAligment_representation.resize(sequences.size(),vector<char>(maximo_len_row,'-'));
    // cout << "print multipleAligment_representation" << endl;

    // para la cadena estrella
    for(int e = 0 ; e < sequences[row_max].size(); e++){
        multipleAligment_representation[row_max][e] = sequences[row_max][e];
    }

    for(int e = 0 ; e  < sequences.size(); e++ ){
        if(e != row_max){
            auto alineamiento = map_first_alignment[row_max][e];
            int index = 0;
            for(int j = alineamiento.size()-1; j >= 0 ; j--){
                multipleAligment_representation[e][index] = alineamiento[j].second;
                index++;
            }
        }
    }
    // print multiple alignment
    for(int e = 0 ; e < sequences.size(); e++){
        cout << "S" << e+1 << "| ";
        salida << "S" << e+1 << "| ";
        for(int j = 0 ; j < multipleAligment_representation[e].size(); j++){
            cout << multipleAligment_representation[e][j] << " ";
            salida << multipleAligment_representation[e][j] << " ";
        }cout << endl; salida << endl;
    }
}
void test(){
    string t1,t2;
    cin>>t1>>t2;
    NeedlemanWunsch NW;
    cout << NW.bestScore(t1,t2) << endl;
    NW.dfs(t1.size(),t2.size()); // para generar minimo un alineamiento en la recursion
    cout << "cantidad cadenas: " << NW.getCantidadCadenas() << endl;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    #ifdef DEBUG
        freopen("input.txt","r",stdin);
        freopen("output.txt","w",stdout);
    #endif
    solve();
    // test();
    return 0;
}