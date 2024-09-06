#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define mp make_pair

int diag,up,leftt;
string secuenciaOne,secuenciaTwo;
vector<pair<char,char>> ans;
vector<vector<int>> dp;
int cantidadCadenas = 0;
vector<pair<string, string>> alineacionesTotales;

/*
	! 0 -> Diagonal
	! 1 -> Up
	! 2 -> Left
*/
vector< vector< array<int,3> > > dp_direcciones;


void dfs(int x, int y){
	if(x == 0 && y == 0){
		cantidadCadenas++;
		// cout << "Printing Cadena" << endl;
        string first="",second="";
		for(int e = ans.size()-1; e >= 0 ; e--){
			// cout << ans[e].first << " ";
            first += ans[e].first;
		}
        // cout << endl;
		for(int e = ans.size()-1; e >= 0 ; e--){
			// cout << ans[e].second << " ";
            second += ans[e].second;
		}
        // cout << endl;
        alineacionesTotales.pb({first,second});
		return;
	}
	if(dp_direcciones[x][y][0]){
		if(x>0 && y >0){
			ans.pb({secuenciaOne[x-1],secuenciaTwo[y-1]});
			dfs(x-1,y-1);
			ans.pop_back();
		}
		
	}if(dp_direcciones[x][y][1]){
		if(x > 0){
			ans.pb({secuenciaOne[x-1],'-'});
			dfs(x-1,y);
			ans.pop_back();
		}
	}if(dp_direcciones[x][y][2]){
		if(y > 0){
			ans.pb({'-',secuenciaTwo[y-1]});
			dfs(x,y-1);
			ans.pop_back();
		}
	}
}
void solve(){
	cin>>secuenciaOne>>secuenciaTwo;
	/*
		*Aseguramos que la secuencia mas larga este en las columnas
	*/
	if(secuenciaOne.size()<secuenciaTwo.size()) swap(secuenciaOne,secuenciaTwo);
	int sizeOne = secuenciaOne.size();
	int sizeTwo = secuenciaTwo.size();
	dp.resize(sizeOne+1,vector<int>(sizeTwo+1,0));
	dp_direcciones.resize(sizeOne+1,vector< array<int,3> >(sizeTwo+1,{0,0,0}));
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

	cout << "Matrix" << endl;
	for(int e = 0 ; e < sizeOne +1 ; e++){
		for(int j = 0 ; j < sizeTwo+1; j++){
			cout << dp[e][j] << " ";
		}cout << endl;
	}cout << endl;


	// cout << "print direcciones " << endl;
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		for(int w = 0 ; w < 3; w++){
	// 			cout << dp_direcciones[e][j][w] << " ";
	// 		}cout << endl;
	// 	}cout << endl;
	// }

	/*
		! dfs para hacer el flood fill al grafo implicito
	*/

	// dfs dp_direcciones
	int i = sizeOne;
	int j = sizeTwo;
	cout << "Alineamientos Generados" << endl;
	dfs(sizeOne,sizeTwo);
	cout << "Cantidad de alineaminentos producidos: " << cantidadCadenas << endl;
    cout << "alineacionesTotales" << endl;
    for(auto x:alineacionesTotales){
        cout << x.first << endl;
        cout << x.second << endl<< endl;
    }

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