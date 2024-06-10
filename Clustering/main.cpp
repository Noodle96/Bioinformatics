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
matrix_double matrix,distancia_minima,distancia_maxima,distancia_ponderada;
int n;
void loadMatrix(){
    cin>>n;
    for(int e = 0 ; e < n; e++){
        for(int j = 0 ;j < n ; j++){
            cin>>matrix[to_string(e)][to_string(j)];
        }
    }
}

vector<string> getEtiqueta(vector<pair<string, vector<pair<string,double>>>> & M){
    vector<string> etiqueta;
    for(auto it = M.begin() ; it != M.end(); it++){
        etiqueta.push_back(it->first);
    }
    return etiqueta;
}


vector<string> getEtiquetaWithHash(matrix_double & M){
    vector<pair<string, vector<pair<string,double>>>> print_m;
    for(auto it = M.begin() ; it != M.end(); it++){
        vector<pair<string,double>> temp;
        for(auto ot = it->second.begin() ; ot != it->second.end()  ; ot++){
            // cout << ot->second << " ";
            temp.push_back({ot->first,ot->second});
        }
        // cout << endl;
        print_m.push_back({it->first,temp});
    }
    // cout << endl;
    sort(all(print_m));
    for(auto it = print_m.begin() ; it != print_m.end(); it++){
        sort(all(it->second));
    }
    vector<string> etiqueta;
    etiqueta = getEtiqueta(print_m);
    return etiqueta;
}



void printMatrix(matrix_double & M){
    vector<pair<string, vector<pair<string,double>>>> print_m;
    for(auto it = M.begin() ; it != M.end(); it++){
        vector<pair<string,double>> temp;
        for(auto ot = it->second.begin() ; ot != it->second.end()  ; ot++){
            // cout << ot->second << " ";
            temp.push_back({ot->first,ot->second});
        }
        // cout << endl;
        print_m.push_back({it->first,temp});
    }
    // cout << endl;
    sort(all(print_m));
    for(auto it = print_m.begin() ; it != print_m.end(); it++){
        sort(all(it->second));
    }
    vector<string> etiqueta;
    etiqueta = getEtiqueta(print_m);
    cout << "  ";
    for(auto e:etiqueta){
        cout << e << " ";
    }cout << endl;
    auto index = 0;
    for(auto it = print_m.begin() ; it != print_m.end(); it++){
        // cout << it->first << "->";
        cout << etiqueta[index++]<< " ";
        for(auto ot = it->second.begin() ; ot != it->second.end() ; ot++){
            // cout << ot->first << " " << ot->second << " ";
            cout << ot->second << " ";
        }
        cout << endl;
    }
    cout << endl;

    // for(int e = 0 ; e < n; e++){
    //     for(int j = 0 ;j < n ; j++){
    //         cout<<M[e][j]<<" ";
    //     }
    //     cout<<endl;
    // }
    // cout << endl;
}

pair<string, pair<string,double>> getMinAndClusters(matrix_double &M){
    string x,y; double min = DBL_MAX;
    for(auto it = M.begin() ; it != M.end(); it++){
        // cout << it->first << endl;
        for(auto ot = it->second.begin() ; ot != it->second.end(); ot++){
            // cout << ot->first << "->" << ot->second << " ";
            if(it->first != ot->first){
                if(ot->second < min){
                    min = ot->second;
                    x = it->first;
                    y = ot->first;
                }
            }
            
        }
        // cout << endl; 
    }
    // cout << endl;
    return {x,{y,min}};
}

void estrategia_distancia_minima(){
    int nivelK = 1;
    distancia_minima = matrix;
    cout << "Clusteres Iniciales: ";
    for(int e = 0 ; e < distancia_minima.size(); e++){
        cout << e << " ";
    }cout << endl << endl;
    printMatrix(distancia_minima);
    while(distancia_minima.size() >= 2){
        // cout << "distancia_minima size: " << distancia_minima.size() << endl;
        auto x_y_min = getMinAndClusters(distancia_minima);
        auto x = x_y_min.first;
        auto y = x_y_min.second.first;
        auto min = x_y_min.second.second;
        // cout << x_y_min.first << " " << x_y_min.second.first << " " << x_y_min.second.second << endl;
        // merge clusters
        string new_cluster;
        if(x<y) new_cluster = x + y;
        else new_cluster = y + x;
        // cout << "new cluster: " << new_cluster << endl; 

        // UPDATE ROW
        for(auto it = distancia_minima.begin() ; it != distancia_minima.end(); it++){
            if(it->first == x){
                for(auto ot = it->second.begin() ; ot != it->second.end(); ot++){
                    auto minimoDistance = (distancia_minima[x][ot->first] < distancia_minima[y][ot->first]) ? distancia_minima[x][ot->first] : distancia_minima[y][ot->first];
                    distancia_minima[new_cluster][ot->first] = minimoDistance;
                }
            }
        }
        //DELETE ROW
        distancia_minima.erase(x);
        distancia_minima.erase(y);
        
        // DELETE COLUMN
        for (auto& rowPair : distancia_minima) {
            auto& rowMap = rowPair.second;
            rowMap.erase(y);
            rowMap.erase(x);
        }
        for(auto it = distancia_minima.begin() ; it != distancia_minima.end(); it++){
            distancia_minima[it->first][new_cluster] = distancia_minima[new_cluster][it->first]; 
        }
        cout << "Nivel K = " << nivelK++ << endl;
        cout << "Clusteres más proximos " << x << " y " << y << " (" << min << ")" << endl;
        cout << "Entonces quedaria: ";
        auto etiqueta = getEtiquetaWithHash(distancia_minima);
        for(auto e: etiqueta){
            cout << e << " ";
        }cout << endl;
        printMatrix(distancia_minima);
    }
}

void estrategia_distancia_maxima(){
    int nivelK = 1;
    distancia_maxima = matrix;
    cout << "Clusteres Iniciales: ";
    for(int e = 0 ; e < distancia_maxima.size(); e++){
        cout << e << " ";
    }cout << endl << endl;
    printMatrix(distancia_maxima);
    while(distancia_maxima.size() >= 2){
        // cout << "distancia_minima size: " << distancia_minima.size() << endl;
        auto x_y_min = getMinAndClusters(distancia_maxima);
        auto x = x_y_min.first;
        auto y = x_y_min.second.first;
        auto min = x_y_min.second.second;
        // cout << x_y_min.first << " " << x_y_min.second.first << " " << x_y_min.second.second << endl;
        // merge clusters
        string new_cluster;
        if(x<y) new_cluster = x + y;
        else new_cluster = y + x;
        // cout << "new cluster: " << new_cluster << endl; 

        // UPDATE ROW
        for(auto it = distancia_maxima.begin() ; it != distancia_maxima.end(); it++){
            if(it->first == x){
                for(auto ot = it->second.begin() ; ot != it->second.end(); ot++){
                    auto maximoDistance = (distancia_maxima[x][ot->first] > distancia_maxima[y][ot->first]) ? distancia_maxima[x][ot->first] : distancia_maxima[y][ot->first];
                    distancia_maxima[new_cluster][ot->first] = maximoDistance;
                }
            }
        }
        //DELETE ROW
        distancia_maxima.erase(x);
        distancia_maxima.erase(y);
        
        // DELETE COLUMN
        for (auto& rowPair : distancia_maxima) {
            auto& rowMap = rowPair.second;
            rowMap.erase(y);
            rowMap.erase(x);
        }
        for(auto it = distancia_maxima.begin() ; it != distancia_maxima.end(); it++){
            distancia_maxima[it->first][new_cluster] = distancia_maxima[new_cluster][it->first]; 
        }
        cout << "Nivel K = " << nivelK++ << endl;
        cout << "Clusteres más proximos " << x << " y " << y << " (" << min << ")" << endl;
        cout << "Entonces quedaria: ";
        auto etiqueta = getEtiquetaWithHash(distancia_maxima);
        for(auto e: etiqueta){
            cout << e << " ";
        }cout << endl;
        printMatrix(distancia_maxima);
    }
}
void estrategia_distancia_ponderada(){
    int nivelK = 1;
    distancia_ponderada = matrix;
    cout << "Clusteres Iniciales: ";
    for(int e = 0 ; e < distancia_ponderada.size(); e++){
        cout << e << " ";
    }cout << endl << endl;
    printMatrix(distancia_ponderada);
    while(distancia_ponderada.size() >= 2){
        // cout << "distancia_minima size: " << distancia_minima.size() << endl;
        auto x_y_min = getMinAndClusters(distancia_ponderada);
        auto x = x_y_min.first;
        auto y = x_y_min.second.first;
        auto min = x_y_min.second.second;
        // cout << x_y_min.first << " " << x_y_min.second.first << " " << x_y_min.second.second << endl;
        // merge clusters
        string new_cluster;
        if(x<y) new_cluster = x + y;
        else new_cluster = y + x;
        // cout << "new cluster: " << new_cluster << endl; 

        // UPDATE ROW
        for(auto it = distancia_ponderada.begin() ; it != distancia_ponderada.end(); it++){
            if(it->first == x){
                for(auto ot = it->second.begin() ; ot != it->second.end(); ot++){
                    auto distancePonderada = (distancia_ponderada[x][ot->first]+distancia_ponderada[y][ot->first]) /2.0;
                    distancia_ponderada[new_cluster][ot->first] = distancePonderada;
                }
            }
        }
        //DELETE ROW
        distancia_ponderada.erase(x);
        distancia_ponderada.erase(y);
        
        // DELETE COLUMN
        for (auto& rowPair : distancia_ponderada) {
            auto& rowMap = rowPair.second;
            rowMap.erase(y);
            rowMap.erase(x);
        }
        for(auto it = distancia_ponderada.begin() ; it != distancia_ponderada.end(); it++){
            distancia_ponderada[it->first][new_cluster] = distancia_ponderada[new_cluster][it->first]; 
        }
        cout << "Nivel K = " << nivelK++ << endl;
        cout << "Clusteres más proximos " << x << " y " << y << " (" << min << ")" << endl;
        cout << "Entonces quedaria: ";
        auto etiqueta = getEtiquetaWithHash(distancia_ponderada);
        for(auto e: etiqueta){
            cout << e << " ";
        }cout << endl;
        printMatrix(distancia_ponderada);
    }
}

void solve(){
    loadMatrix();
    // printMatrix(matrix);
    cout << "ESTRATEGIA DE DISTANCIA MINIMA" << endl;
    estrategia_distancia_minima();

    cout << "ESTRATEGIA DE DISTANCIA MAXIMA" << endl;
    estrategia_distancia_maxima();

    cout << "ESTRATEGIA DE DISTANCIA PONDERADA" << endl;
    estrategia_distancia_ponderada();

}

void test(){
    // vector<string> vec{"c","bdfg","a"};
    // sort(all(vec));
    // for(auto it = vec.begin() ; it != vec.end(); it++){
    //     cout << *it << endl;
    // }

    double a = 3.244;
    double b = 4.67;
    double c = min(a,b);
    cout << c << endl;
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