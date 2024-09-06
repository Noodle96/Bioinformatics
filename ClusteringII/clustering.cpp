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
// int n;
double val;
int n,n_;
int value = 1;
int n_minimo;

vector<pair<double, string>> answerLab;

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


vector<string> getEtiqueta(vector<pair<string, vector<pair<string,double>>>> & M){
    vector<string> etiqueta;
    for(auto it = M.begin() ; it != M.end(); it++){
        etiqueta.push_back(it->first);
    }
    return etiqueta;
}

vector<pair<string, vector<pair<string,double>>>> hashOrdered(matrix_double & M){
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
    return print_m;
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
            cout << ot->second  << fixed << setprecision(6) << " ";
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

void loadMatrix(){
    cin>>n;
    double val;
    for(int e = 0 ; e < n; e++){
        for(int j = 0 ;j < value ; j++){
            cin>>matrix[to_string(e)][to_string(j)];
        }
        value++;
    }
    value = 1;
    for(int e = 0 ; e < n; e++){
        for(int j = 0 ;j < value ; j++){
            matrix[to_string(j)][to_string(e)] = matrix[to_string(e)][to_string(j)];
        }
        value++;
    }
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
int ToInt(string str){
    stringstream ss(str);
    int x = 0;
    ss >> x;
    return x;
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

    // conversion de la matrix de similaridad (F) a un vector X
    auto distancia_minina_ordenada = hashOrdered(distancia_minima); 
    vector<double> X;
    int cantidad = 0;
    for(auto it = distancia_minina_ordenada.begin(); it != distancia_minina_ordenada.end(); it++){
        auto ot = it->second.begin();
        for(int c= 0; ot != it->second.end(),c < cantidad; ot++,c++){
            X.push_back(ot->second);
        }
        cantidad++;
    }
    
    cout << "Clusteres Iniciales: ";
    for(int e = 0 ; e < distancia_minima.size(); e++){
        cout << e << " ";
    }cout << endl << endl;
    printMatrix(distancia_minima);
    unordered_map<string, unordered_map<string , double>> matrixCofenica;
    matrixCofenica = distancia_minima;

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

        // construccion de la matrix cofenica
        for(auto it = x.begin(); it != x.end(); it++){
            for(auto ot = y.begin(); ot != y.end(); ot++){
                matrixCofenica[to_string(*it-'0')][to_string(*ot-'0')] = min;
                matrixCofenica[to_string(*ot-'0')][to_string(*it-'0')] = min;
            }
        }
    }
    cout << "print matrix cofenica - Estrategia distancia minima" << endl;
    printMatrix(matrixCofenica);

    // conversion de la matriz a un vector Y
    vector<double> Y;
    int cantidad2 = 0;
    auto matrixCofenicaOrdenada = hashOrdered(matrixCofenica);
    for(auto it = matrixCofenicaOrdenada.begin() ; it != matrixCofenicaOrdenada.end(); it++){
        auto ot = it->second.begin();
        for( int c = 0; ot != it->second.end(), c < cantidad2; ot++,c++){
            Y.push_back(ot->second);
        }
        cantidad2 ++;
    }
    
    // cout << "X size: " << X.size() << endl;
    // for(auto e: X){
    //     cout << e << endl;
    // }
    // cout << endl;
    // cout << "Y size: " << Y.size() << endl;
    // for(auto e: Y){
    //     cout << e << endl;
    // }
    // cout << endl;

    auto r = coeficienteCorrelacion(X,Y);
    cout << "ccc: " << r << endl;
    answerLab.pb({r,"Estrategia Minima"});
}

void estrategia_distancia_maxima(){
    int nivelK = 1;
    distancia_maxima = matrix;

    // conversion de la matrix de similaridad (F) a un vector X
    auto distancia_maxima_ordenada = hashOrdered(distancia_maxima);
    vector<double> X;
    int cantidad = 0;
    for(auto it = distancia_maxima_ordenada.begin(); it != distancia_maxima_ordenada.end(); it++){
        auto ot = it->second.begin();
        for(int c= 0; ot != it->second.end(),c < cantidad; ot++,c++){
            X.push_back(ot->second);
        }
        cantidad++;
    }

    cout << "Clusteres Iniciales: ";
    for(int e = 0 ; e < distancia_maxima.size(); e++){
        cout << e << " ";
    }cout << endl << endl;
    printMatrix(distancia_maxima);
    unordered_map<string, unordered_map<string , double>> matrixCofenica;
    matrixCofenica = distancia_maxima;
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

        // construccion de la matrix cofenica
        for(auto it = x.begin(); it != x.end(); it++){
            for(auto ot = y.begin(); ot != y.end(); ot++){
                matrixCofenica[to_string(*it-'0')][to_string(*ot-'0')] = min;
                matrixCofenica[to_string(*ot-'0')][to_string(*it-'0')] = min;
            }
        }
    }
    cout << "print matrix cofenica - Estrategia distancia maxima" << endl;
    printMatrix(matrixCofenica);
    // conversion de la matriz a un vector Y
    vector<double> Y;
    int cantidad2 = 0;
    auto matrixCofenicaOrdenada = hashOrdered(matrixCofenica);
    for(auto it = matrixCofenicaOrdenada.begin() ; it != matrixCofenicaOrdenada.end(); it++){
        auto ot = it->second.begin();
        for( int c = 0; ot != it->second.end(), c < cantidad2; ot++,c++){
            Y.push_back(ot->second);
        }
        cantidad2 ++;
    }
    auto r = coeficienteCorrelacion(X,Y);
    cout << "ccc: " << r << endl;
    answerLab.pb({r,"Estrategia Maxima"});
}

void estrategia_distancia_ponderada(){
    int nivelK = 1;
    distancia_ponderada = matrix;

     // conversion de la matrix de similaridad (F) a un vector X
    auto distancia_maxima_ponderada = hashOrdered(distancia_ponderada);
    vector<double> X;
    int cantidad = 0;
    for(auto it = distancia_maxima_ponderada.begin(); it != distancia_maxima_ponderada.end(); it++){
        auto ot = it->second.begin();
        for(int c= 0; ot != it->second.end(),c < cantidad; ot++,c++){
            X.push_back(ot->second);
        }
        cantidad++;
    }

    cout << "Clusteres Iniciales: ";
    for(int e = 0 ; e < distancia_ponderada.size(); e++){
        cout << e << " ";
    }cout << endl << endl;
    printMatrix(distancia_ponderada);
    unordered_map<string, unordered_map<string , double>> matrixCofenica;
    matrixCofenica = distancia_ponderada;
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

        // construccion de la matrix cofenica
        for(auto it = x.begin(); it != x.end(); it++){
            for(auto ot = y.begin(); ot != y.end(); ot++){
                matrixCofenica[to_string(*it-'0')][to_string(*ot-'0')] = min;
                matrixCofenica[to_string(*ot-'0')][to_string(*it-'0')] = min;
            }
        }
    }
    cout << "print matrix cofenica - Estrategia distancia ponderada" << endl;
    printMatrix(matrixCofenica);
    // conversion de la matriz a un vector Y
    vector<double> Y;
    int cantidad2 = 0;
    auto matrixCofenicaOrdenada = hashOrdered(matrixCofenica);
    for(auto it = matrixCofenicaOrdenada.begin() ; it != matrixCofenicaOrdenada.end(); it++){
        auto ot = it->second.begin();
        for( int c = 0; ot != it->second.end(), c < cantidad2; ot++,c++){
            Y.push_back(ot->second);
        }
        cantidad2 ++;
    }
    auto r = coeficienteCorrelacion(X,Y);
    cout << "ccc: " << r << endl;
    answerLab.pb({r,"Estrategia Ponderada"});
}


void solve(){
    loadMatrix();
    printMatrix(matrix);
    cout << endl<< endl<< "ESTRATEGIA DE DISTANCIA MINIMA" << endl;
    estrategia_distancia_minima();

    cout << endl << endl <<"ESTRATEGIA DE DISTANCIA MAXIMA" << endl;
    estrategia_distancia_maxima();

    cout << endl << endl <<"ESTRATEGIA DE DISTANCIA PONDERADA" << endl;
    estrategia_distancia_ponderada();

    // Ver cual estrategia es la mejor
    cout << endl << endl<<  "Indicando cual es la estrategia mejor" << endl;
    sort(answerLab.begin(), answerLab.end());
    for(auto e: answerLab   ){
        cout << e.second << ": " << e.first << endl;
    }

    cout << endl << "Estrategia mejor: " << answerLab[2].second << " con un ccc: " << answerLab[2].first <<  endl;
}


void solve2(){
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