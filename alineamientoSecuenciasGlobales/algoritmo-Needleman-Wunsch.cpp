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
vector<pair<char,char>> ans;
vector<vector<int>> dp;
int cantidadCadenas = 0;
ofstream salida;

/*
	! 0 -> Diagonal
	! 1 -> Up
	! 2 -> Left
*/
vector< vector< array<int,3> > > dp_direcciones;


void dfs(int x, int y){
	// cout << "dfs " << x <<" " << y << endl;

	if(x == 0 && y == 0){
		// cout << "in x == 0 && y == 0" << endl;
		//printing cadena
		cantidadCadenas++;
		// cout << "Printing Cadena" << endl;
		for(int e = ans.size()-1; e >= 0 ; e--){
			cout << ans[e].first << " ";
		}cout << endl;
		for(int e = ans.size()-1; e >= 0 ; e--){
			cout << ans[e].second << " ";
		}cout << endl;

		for(int e = ans.size()-1; e >= 0 ; e--){
			salida << ans[e].first << " ";
		}salida << endl;
		for(int e = ans.size()-1; e >= 0 ; e--){
			salida << ans[e].second << " ";
		}salida << endl << endl;
		return;
	}
	if(dp_direcciones[x][y][0]){
		// cout << "first if" << endl;
		// cout << secuenciaOne[x-1] << " " << secuenciaTwo[y-1] << endl;
		if(x>0 && y >0){
			ans.pb({secuenciaOne[x-1],secuenciaTwo[y-1]});
			dfs(x-1,y-1);
			ans.pop_back();
		}
		
	}if(dp_direcciones[x][y][1]){
		// cout << "second if" << endl;
		// cout << secuenciaOne[x-1] << " " << "-" << endl;
		if(x > 0){
			ans.pb({secuenciaOne[x-1],'-'});
				// cout << "Up" << endl;
			dfs(x-1,y);
			ans.pop_back();
		}
	}if(dp_direcciones[x][y][2]){
		// cout << "third if" <<endl;
		// cout << secuenciaOne[x-1] << " " << "-" << endl;
		if(x > 0){
			ans.pb({secuenciaOne[x-1],'-'});
			// cout << "Left" << endl;
			dfs(x,y-1);
			ans.pop_back();
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
	salida.open("laboratorioNW.txt");
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
		val -=2;
		// [x][y][1] => up = 1
		if(e != 0) dp_direcciones[e][0][1] = 1;
	}
	/*
		*Inicializamos la primera fila de la matriz
	*/
	val = 0;
	for(int e = 0 ; e < sizeTwo+1; e++){
		dp[0][e] = val;
		val -=2;
		// [x][y][2] => left = 1
		if(e != 0) dp_direcciones[0][e][2] = 1;

	}
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		cout << dp[e][j] << " ";
	// 	}cout << endl;
	// }cout << endl << endl;

	/*
		*Aplicamos el algoritmo de Needleman-Wunsch
	*/
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
	// print dp_direcciones
	// cout << "dp_direcciones" << endl;
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		for(int w = 0 ; w < 3; w++){
	// 			cout << dp_direcciones[e][j][w] << " ";
	// 		}cout << endl;
	// 	}cout << endl;
	// }cout << endl << endl;

	cout << "score Optimo: " << dp[sizeOne][sizeTwo] << endl << endl;
	salida << "score Optimo: " << dp[sizeOne][sizeTwo] << endl << endl;

	cout << "Matrix" << endl;
	for(int e = 0 ; e < sizeOne +1 ; e++){
		for(int j = 0 ; j < sizeTwo+1; j++){
			cout << dp[e][j] << " ";
		}cout << endl;
	}cout << endl;

	salida << "Matrix" << endl;
	for(int e = 0 ; e < sizeOne +1 ; e++){
		for(int j = 0 ; j < sizeTwo+1; j++){
			salida << dp[e][j] << " ";
		}salida << endl;
	}salida << endl;

	/*
		! dfs para hacer el flood fill al grafo implicito
	*/

	// dfs dp_direcciones
	int i = sizeOne;
	int j = sizeTwo;
	cout << "Alineamientos Generados" << endl;
	salida << "Alineamientos Generados" << endl;
	dfs(sizeOne,sizeTwo);

	cout << "Cantidad de alineaminentos producidos: " << cantidadCadenas << endl;
	salida << "Cantidad de alineaminentos producidos: " << cantidadCadenas << endl;
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