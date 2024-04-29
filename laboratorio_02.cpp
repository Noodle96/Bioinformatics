#include <bits/stdc++.h>
using namespace std;

using ll = long long;
#define pb push_back

ll total = 0;
vector<ll> foundPatternIndex;

/*
	* Es necesario hacer una precomputacion de la cadena patron para utilizarlo
	  en el algoritmo de KMP, ya que este algoritmo nos permite buscar una subcadena
	  en una cadena principal en tiempo lineal.
*/
void computeLPSArray(string &pat, int M, int* lps){
    int len = 0;
    lps[0] = 0;
    int i = 1;
    while (i < M) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else{
            if (len != 0) {
                len = lps[len - 1];
            }
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
}

/*
	* El algoritmo de KMP es un algoritmo de búsqueda de subcadenas que busca una cadena
	  de texto para una subcadena.
	* Es por ello que utilizamos este algoritmo para que la complejidad sea de O(n)
	* En caso haya una conincidencia de la subcadena con la cadena principal, entonces
	  se almacena el indice de la cadena principal en nuestra vector foundPatternIndex.
*/

void KMPSearch(string pat, string txt){
    int M = pat.size();
    int N = txt.size();
    int lps[M];
    computeLPSArray(pat, M, lps);
    int i = 0;
    int j = 0;
    while ((N - i) >= (M - j)) {
        if (pat[j] == txt[i]){
            j++;
            i++;
        }
        if (j == M) {
			foundPatternIndex.push_back(i-j);
            j = lps[j - 1];
        }
        else if (i < N && pat[j] != txt[i]) {
            if (j != 0) j = lps[j - 1];
            else i = i + 1;
        }
    }
}

/*
	* Antes de llamar a nuestro algoritmo de KMP, necesitamos hacer una comparacion
	  de las cadenas str1 y str2 para saber si cual sera la subcadena y cual sera la
	  cadena principal.
	* En cualquier de los tres casos, verificamos si existe algun elemento en nuestro
	  vector foundPatternIndex, si es asi, entonces existe una inclusion mutua.
*/
void similitud(string str1, string str2){
	if(str1.size() == str2.size()){
		KMPSearch(str1, str2);
		if(foundPatternIndex.size() > 0){
			cout << "La cadena son iguales, Por existe una inclusion mutua" << endl;
		}else{
			cout << "ninguna de las cadena esta contenida en otra" << endl;
		}
	}else if(str1.size() > str2.size()){
		KMPSearch(str2, str1);
		if(foundPatternIndex.size() > 0){
			cout << "La cadena [" <<str2 << "] esta contenida dentro de [" << str1 << "]." << endl;
		}else{
			cout << "ninguna de las cadena esta contenida en otra" << endl;
		}
	}else {
		KMPSearch(str1, str2);
		if(foundPatternIndex.size() > 0	){
			cout << "La cadena [" <<str1 << "] esta contenida dentro de [" << str2 << "]." << endl;
		}else{
			cout << "ninguna de las cadena esta contenida en otra" << endl;
		}
	}
}

/*	
	* Comentario de la funcion contabilizar
	* Hacecmos una comparacion de las cadenas str1 y str2 iterandolas index por index.
	* Si las cadenas son iguales, se suma 1 por cada caracter igual y se resta 2 por cada caracter diferente.
*/
void contabilizar(string str1, string str2){
	int n1 = str1.size();
	int n2 = str2.size();
	int maximoLen = max(n1,n2);
	/*
		* len(n1) == len(n2)
		* Caso particular cuando el tamaño de las cadenas son iguales
		* Ante esta situación hacemos la iteracion hasta el tamñaño de cualquiera de las cadenas
	*/
	if(n1 == n2){
		for(int e = 0 ; e < n1; e++){
			if(str1[e] != str2[e]) total += (-2);
			else total += 1;
		}
		cout << "Cuenta total: " << total << endl;
		return;
	}
	/*
		* len(n1) > len(n2)
		* Caso particular cuando el tamaño de la cadena 1 es mayor que la cadena 2
		* Ante esta situación hacemos la iteracion hasta el tamaño de la cadena 2
		* Luego sumamos la diferencia de los tamaños de las cadenas multiplicado por -2
	*/
	if(n1 > n2){
		for(int e = 0 ; e < n2;e++){
			if(str1[e] != str2[e]) total += (-2);
			else total += 1;
		}
		total += ((n1-n2)*(-2));
		cout << "Cuenta total: " << total << endl;
	}else{
		/*
			* len(n2) > len(n1)
			* Caso particular cuando el tamaño de la cadena 2 es mayor que la cadena 1
			* Ante esta situación hacemos la iteracion hasta el tamaño de la cadena 1
			* Luego sumamos la diferencia de los tamaños de las cadenas multiplicado por -2
		*/
		for(int e = 0 ; e < n1;e++){
			if(str1[e] != str2[e]) total += (-2);
			else total += 1;
		}
		total += ((n2-n1)*(-2));
		cout << "Cuenta total: " << total << endl;
	}

}

void solve(){
	string str1, str2;
	cin>> str1 >> str2;
	contabilizar(str1, str2);
	similitud(str1, str2);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	// #ifdef DEBUG
	// 	freopen("input.txt","r",stdin);
	// 	freopen("output.txt","w",stdout);
	// #endif
	solve();
	return 0;
}