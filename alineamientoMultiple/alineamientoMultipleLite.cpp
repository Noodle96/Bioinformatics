#include <bits/stdc++.h>
using namespace std;


vector<string> sequences;
vector<vector<int>> matriz_scores;
map<int, map<int, string>> map_first_alignment;


void ejercicio(){
    string line;
    while(getline(cin,line)){
        sequences.emplace_back(line);
    }

    /*
        Inicializar la matriz de scores con 0s
    */
    matriz_scores.resize(sequences.size(),vector<int>(sequences.size(),0));

    /*
        Fill the matrix with the scores
    */
    for(int e = 0; e < sequences.size(); e++){
        for(int j = e ; j < sequences.size(); j++){
            if(e == j){
                matriz_scores[e][j] = 0;
            }else{
                auto [dp, cantidadCadenas, alineacionesTotales, bestScore, ans ] = solve(sequences[e], sequences[j]);


                // map_first_alignment[e][j] = NW.getParticularPair();
                map_first_alignment[e][j] = ans[0]
                map_first_alignment[j][e] = ans[0]
                // cout << map_first_alignment[e][j].first << " " << map_first_alignment[e][j].second.first << " " << map_first_alignment[e][j].second.second << endl;
                matriz_scores[e][j] = bestScore;
                matriz_scores[j][e] = bestScore;
            }
        }
    }
    cout << "(i) print matriz scores" << endl;
    for(int e = 0; e < sequences.size(); e++){
        int sumatoria = 0;
        for(int j = 0 ; j < sequences.size(); j++){
            cout << matriz_scores[e][j] << " ";
            sumatoria += matriz_scores[e][j];
        }cout << " = " << sumatoria << endl;
    }cout << endl;

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

    /*
        Encontrar alineamiento de cada secuencia con la estrella
    */
    cout << endl;
    cout << "(ii) alineamiento de cada secuencia con la estrella"  << endl;

    int maximo_len_row = INT_MIN;
    maximo_len_row = max(maximo_len_row,(int)sequences[row_max].size());
    for(int e = 0 ; e < sequences.size(); e++){
        // cout << "e: " << e << endl;
        if(e != row_max){
            auto alineamiento = map_first_alignment[e][row_max];
            // if(alineamiento.first == false
            //     || alineamiento.second.first.size() == 0
            //     || alineamiento.second.second.size() == 0){
            //         cout << "assert !!!" << endl;
            //         cout << "______________" << endl;
            //         cout << alineamiento.first << " " << alineamiento.second.first << " " << alineamiento.second.second << endl;
            // }

            // cout << "alineamoento:" << endl;
            // cout  << alineamiento.first << " " << alineamiento.second.first << " " << alineamiento.second.second << endl;
            maximo_len_row = max(maximo_len_row,(int)alineamiento.second.first.size());
            cout << "S" << row_max+1 <<"| ";
            cout << alineamiento.first << endl;
            
            cout << "S" << e+1 <<"| ";
            cout << alineamiento.second << endl << endl;
        }
    }
    // salida << "stop" << endl;
    
    // return;
    cout << endl << "(iii) alineamiento múltiple" << endl;
    vector<vector<char>> multipleAligment_representation;
    multipleAligment_representation.resize(sequences.size(),vector<char>(maximo_len_row,'-'));


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
            for(int j = 0 ; j < alineamiento.first.size(); j++){
                multipleAligment_representation[e][j] = alineamiento.second[j];
            }
        }
    }
    // // print multiple alignment
    for(int e = 0 ; e < sequences.size(); e++){
        cout << "S" << e+1 << "| ";
        for(int j = 0 ; j < multipleAligment_representation[e].size(); j++){
            cout << multipleAligment_representation[e][j];
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
    ejercicio();
    return 0;
}
ATTGCCATT
ATGGCCATT
ATCCAATTTT
ATCTTCTT
ACTGACC