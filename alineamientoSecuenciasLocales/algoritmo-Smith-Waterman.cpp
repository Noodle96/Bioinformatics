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
int diag,up,leftt;
string secuenciaOne,secuenciaTwo;
// vector<pair<char,char>> ans;
vector<vector<int>> dp;
int cantidadCadenas = 0;
ofstream salida;
vector<pair<int,int>> posiciones;
vector<string> subcadenasGeneradas;
string subcadena;

int currentState;


/*
	! 0 -> Diagonal
	! 1 -> Up
	! 2 -> Left
*/
vector< vector< array<int,3> > > dp_direcciones;
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


void dfs(int x, int y){
	if(currentState == dp[x][y]){
		//if(x == 0 || y == 0){
		if(currentState == 0){
			// cout << "in x == 0 || y == 0" << endl;
			reverse(all(subcadena));
			subcadenasGeneradas.pb(subcadena);
			// cout << "subcadena generada: " << subcadena << endl;
			cantidadCadenas++;
			return;
		}
		if(dp_direcciones[x][y][0]){
			// cout << "first if" << endl;
			// cout << secuenciaOne[x-1] << " " << secuenciaTwo[y-1] << endl;
			if(x>0 && y >0){
				//ans.pb({secuenciaOne[x-1],secuenciaTwo[y-1]});
				subcadena += secuenciaOne[x-1];
				currentState -= 1;
				dfs(x-1,y-1);
				//ans.pop_back();
			}
		}
	}
	
}

// AGC
// AAAC
// TAGCGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTACGTAGCTAGCTAGCGTACGTACGTACGTAC
// ATCGTCTAGCGATCGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGAT
// ACTGATTCA
// ACGCATCA


// string test = "ATCGTCTAGCGATCGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGATCGCTAGCGATCGTACGTACGTACGTACGTACGTTAGGCTAGCTAGCGTAGCTAGCGAT";


void solve(){
	salida.open("laboratorio_03_05.txt");
	cin>>secuenciaOne>>secuenciaTwo;
	/*
		*Aseguramos que la secuencia mas larga este en las columnas
	*/

	if(secuenciaOne.size()<secuenciaTwo.size()) swap(secuenciaOne,secuenciaTwo);
	// cout << "secuencia One: " <<secuenciaOne << endl;
	// cout << "secuencia two: "<<secuenciaTwo << endl;
	int sizeOne = secuenciaOne.size();
	// cout << "sizeOne: " << sizeOne << endl;
	int sizeTwo = secuenciaTwo.size();
	// cout << "sizeTwo: " << sizeTwo << endl;
	dp.resize(sizeOne+1,vector<int>(sizeTwo+1,0));
	dp_direcciones.resize(sizeOne+1,vector< array<int,3> >(sizeTwo+1,{0,0,0}));
	/*
		*Print Initial matriz
	*/
	// cout << "Print matriz inicial" << endl;
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		cout << dp[e][j] << " ";
	// 	}cout << endl;
	// }cout << endl << endl;
	/*
		*Inicializamos la primera columan de la matriz
	*/
	int val = 0;

	for(int e = 0 ; e < sizeOne+1 ; e++){
		dp[e][0] = val;
		//val -=2;
		// [x][y][1] => up = 1
		if(e != 0) dp_direcciones[e][0][1] = 1;
	}
	/*
		*Inicializamos la primera fila de la matriz
	*/
	//val = 0;
	for(int e = 0 ; e < sizeTwo+1; e++){
		dp[0][e] = val;
		// val -=2;
		// [x][y][2] => left = 1
		if(e != 0) dp_direcciones[0][e][2] = 1;

	}
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		cout << dp[e][j] << " ";
	// 	}cout << endl;
	// }cout << endl << endl;

	/*
		*Aplicamos el algoritmo de Smith Waterman
	*/
	int valorMayor = INT_MIN;
	for(int e = 1 ; e < sizeOne+1; e++){
		for(int j = 1 ;j < sizeTwo+1 ;j++){
			diag = dp[e-1][j-1]+(secuenciaOne[e-1]==secuenciaTwo[j-1]?1:-1);
			up = dp[e-1][j]-2;
			leftt = dp[e][j-1]-2;
			dp[e][j] = max(diag, max(up,max(leftt,0)));
			valorMayor = max(valorMayor,dp[e][j]);
			if(dp[e][j] == diag) dp_direcciones[e][j][0] = 1;
			if(dp[e][j] == up) dp_direcciones[e][j][1] = 1;
			if(dp[e][j] == leftt) dp_direcciones[e][j][2] = 1;
		}
	}
	// print dp_direcciones
	// cout << "dp_direcciones" << endl;
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		for(int w = 0 ; w < 3; w++){
	// 			cout << dp_direcciones[e][j][w] << " ";
	// 		}cout << endl;
	// 	}cout << endl;
	// }cout << endl << endl;

	// cout << "score Optimo: " << dp[sizeOne][sizeTwo] << endl << endl;
	// salida << "score Optimo: " << dp[sizeOne][sizeTwo] << endl << endl;
	/*
		(i) el valor mayor
	*/
	cout << "(i) El valor mayor: " << valorMayor << endl << endl;
	salida << "(i) El valor mayor: " << valorMayor << endl << endl;

	/*
		(ii)la subsecuencia en común entre las cadenas,
	*/
	//buscar las posiciones donde esta el maximo y agregar al vector
	// llamado posiciones
	for(int e = 1 ; e < sizeOne+1; e++){
		for(int j = 1 ;j < sizeTwo+1 ;j++){
			if(dp[e][j]  == valorMayor){
				posiciones.pb({e,j});
			}
		}
	}

	//print posiciones donde esta el  valor maximo
	// cout << "posiciones donde esta el valor maximo" << endl;
	// for(auto e: posiciones){
	// 	cout << e.first << " " << e.second << endl;
	// }cout << endl;
	// return;

	/*
		! dfs para hacer el flood fill al grafo implicito
	*/
	for(auto e: posiciones){
		int i = e.first;
		int j = e.second;
		currentState = valorMayor;
		subcadena = "";
		dfs(i,j);
	}
	cout << "(ii) Subsecuencias en comun:" << endl;
	for(int e = 0 ;e < subcadenasGeneradas.size() ; e++){
		cout <<"Subsecuencia " <<  e+1 << " " << subcadenasGeneradas[e] << endl; 
	}cout <<endl;
	salida << "(ii) Subsecuencias en comun:" << endl;
	for(int e = 0 ;e < subcadenasGeneradas.size() ; e++){
		salida <<"Subsecuencia " <<  e+1 << " " << subcadenasGeneradas[e] << endl; 
	}salida << endl;





	/*
		(iii) posición en donde se encuentra (ambas cadenas)
	*/
	cout << "(iii) posición en donde se encuentra (ambas cadenas)" << endl;
	//verificamos que exista al menos una subcadena generada.
	if(subcadenasGeneradas.size()>=1){
		cout << "En la secuencia 1:" << secuenciaOne << endl;
		similitud(subcadenasGeneradas[0], secuenciaOne);
		// cout << "print posiciones foundPatternIndex 01" << endl;
		cout << "en las siguientes posiciones: ";
		for(auto e : foundPatternIndex){
			cout << e << " ";
		}cout << endl;

		foundPatternIndex.clear();
		cout << "En la secuencia 2:" << secuenciaTwo << endl;
		similitud(subcadenasGeneradas[0], secuenciaTwo);
		// cout << "print posiciones foundPatternIndex 02" << endl;
		cout << "en las siguientes posiciones: ";
		for(auto e : foundPatternIndex){
			cout << e << " ";
		}cout << endl;
		cout << endl;
	}else{
		cout << "(iii) ninguna subcadena" << endl;
	}
	salida << "(iii) posición en donde se encuentra (ambas cadenas)" << endl;
	//verificamos que exista al menos una subcadena generada.
	if(subcadenasGeneradas.size()>=1){
		salida << "En la secuencia 1:" << secuenciaOne << endl;
		foundPatternIndex.clear();
		similitud(subcadenasGeneradas[0], secuenciaOne);
		// cout << "print posiciones foundPatternIndex 01" << endl;
		salida << "en las siguientes posiciones: ";
		for(auto e : foundPatternIndex){
			salida << e << " ";
		}salida << endl;

		foundPatternIndex.clear();
		salida << "En la secuencia 2:" << secuenciaTwo << endl;
		similitud(subcadenasGeneradas[0], secuenciaTwo);
		// cout << "print posiciones foundPatternIndex 02" << endl;
		salida << "en las siguientes posiciones: ";
		for(auto e : foundPatternIndex){
			salida << e << " ";
		}salida << endl;
		salida << endl;
	}else{
		salida << "(iii) ninguna subcadena" << endl;
	}


	/*
		(iv)la matriz de scores,
	*/
	cout << "(iv) Matrix de scores: " << endl;
	for(int e = 0 ; e < sizeOne +1 ; e++){
		for(int j = 0 ; j < sizeTwo+1; j++){
			cout << dp[e][j] << " ";
		}cout << endl;
	}cout << endl;

	salida << "(iv) Matrix de scores: " << endl;
	for(int e = 0 ; e < sizeOne +1 ; e++){
		for(int j = 0 ; j < sizeTwo+1; j++){
			salida << dp[e][j] << " ";
		}salida << endl;
	}salida << endl;;






	/*
		(v)existe en alguna otra subsecuencia.
	*/
	cout << "(v) Existe en alguna otra subsecuencia" << endl;
	cout << ( subcadenasGeneradas.size()>1 ? "SI": "NO") << endl << endl;
	salida << "(v) Existe en alguna otra subsecuencia" << endl;
	salida << ( subcadenasGeneradas.size()>1 ? "SI": "NO") << endl << endl;


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

// test cadenas
// ATCAGAA
// ATCAAAT

// AGCT
// GCA