#include<bits/stdc++.h>
using namespace std;
string s,tipo;
map<char, int> dic;

void solve(){
    ofstream salida("laboratorio01.txt", ios::out);
    if (!salida.is_open()) {
     cout << "Error al crear el archivo: " << "lab" << endl;
     }
    cin>>s;
    // convert all uppercase
    transform(s.begin(), s.end(), s.begin(), ::toupper);
    for(int e = 0 ; e < (int)s.size(); e++){
        dic[s[e]]++;
    }
    //ATGC
    auto it_adenina = dic.find('A');
    auto it_timina = dic.find('T');
    auto it_guanina = dic.find('G');
    auto it_citosina = dic.find('C');
    auto it_uracilo = dic.find('U');

    auto it_d = dic.find('D');
    auto it_e = dic.find('E');
    auto it_f = dic.find('F');
    auto it_h = dic.find('H');
    auto it_i = dic.find('I');
    auto it_k = dic.find('K');
    auto it_l = dic.find('L');
    auto it_m = dic.find('M');
    auto it_n = dic.find('N');
    auto it_p = dic.find('P');
    auto it_q = dic.find('Q');
    auto it_r = dic.find('R');
    auto it_s = dic.find('S');
    auto it_v = dic.find('V');
    auto it_w = dic.find('W');
    auto it_y = dic.find('Y');


    // ADN : ACGT
    // ARN : ACGU

    // A	Alanine	
    // C	Cysteine	
    // D	Aspartic acid	
    // E	Glutamic acid	
    // F	Phenylalanine	
    // G	Glycine	
    // H	Histidine	
    // I	Isoleucine	
    // K	Lysine	
    // L	Leucine	
    // M	Methionine	
    // N	Asparagine	
    // P	Proline	
    // Q	Glutamine	
    // R	Arginine	
    // S	Serine	
    // T	Threonine	
    // V	Valine	
    // W	Tryptophan	
    // Y	Tyrosine
    bool alfabeto_restante = it_d != dic.end() || 
           it_e != dic.end() ||
           it_f != dic.end() ||
           it_h != dic.end() ||
           it_i != dic.end() ||
           it_k != dic.end() ||
           it_l != dic.end() ||
           it_m != dic.end() ||
           it_n != dic.end() ||
           it_p != dic.end() ||
           it_q != dic.end() ||
           it_r != dic.end() ||
           it_s != dic.end() ||
           it_v != dic.end() ||
           it_w != dic.end() ||
           it_y != dic.end();

    if(it_uracilo != dic.end()){
        //podria ser ARN o proteina
        if(alfabeto_restante){
            cout << "Proteina" << endl;
            salida << "Proteina" << endl;
            tipo = "PROTEINA";
           }else{
                cout << "ARN" << endl;
                salida << "ARN" << endl;
                tipo = "ARN";
           }

    }else{
        //podria ser ADN o proteina
        // cout << "alfabeto restante: " << alfabeto_restante << endl;
        if(alfabeto_restante){
            cout << "Proteina" << endl;
            salida << "Proteina" << endl;
            tipo = "PROTEINA";
        }else{
            cout << "ADN" << endl;
            salida << "ADN" << endl;
            tipo = "ADN" ;
        }
    }
    //transcripcion
    string transcripcion;
    int len_n = s.size();
    transcripcion.resize(len_n);
    if(tipo == "ADN"){
        // cout << tipo << endl;
        // De adn a ARN
        for(int e = 0 ; e < (int)s.size() ;e++){
            if(s[e] == 'G') transcripcion[e] = 'C';
            else if(s[e] == 'T') transcripcion[e] = 'A';
            else if(s[e] == 'C') transcripcion[e] = 'G';
            else{
                // queda A
                transcripcion[e] = 'U';
            }
        }
        cout << transcripcion << endl;
        salida << transcripcion << endl;

    }else{
        cout  << "no es ADN" << endl;
        salida  << "no es ADN" << endl;
    }
    salida.close();
}
int main(){
    // ios_base::sync_with_stdio(false);
    // #ifdef DEBUG
    //     freopen("input.txt","r",stdin);
    //     freopen("output.txt","w",stdout);
    // #endif
    solve();
    return 0;
}