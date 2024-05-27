/*
	^ Compile : g++ -O2 -std=c++11 -pthread hello_world.cpp -o hello_world
	^ Run: ./a.out
*/
#include <bits/stdc++.h>
#include <thread>
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

clock_t startTime, endTime;
double getCurrentTime() {
	return (double)(clock() - startTime) / CLOCKS_PER_SEC;
}

int diag,up,leftt;
string secuenciaOne,secuenciaTwo;
vector<pair<char,char>> ans;
vector<vector<int>> dp;
int cantidadCadenas = 0;
ofstream salida;
vector<pair<int, int>> indices;
const uint64_t num_threads = 8;
std::vector<std::vector<pair<int,int>>> chunks;
int chunk_size;
std::vector<thread> threads;
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
		// for(int e = ans.size()-1; e >= 0 ; e--){
		// 	cout << ans[e].first << " ";
		// }cout << endl;
		// for(int e = ans.size()-1; e >= 0 ; e--){
		// 	cout << ans[e].second << " ";
		// }cout << endl;

		// for(int e = ans.size()-1; e >= 0 ; e--){
		// 	salida << ans[e].first << " ";
		// }salida << endl;
		// for(int e = ans.size()-1; e >= 0 ; e--){
		// 	salida << ans[e].second << " ";
		// }salida << endl << endl;
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


void procesarChunk(int id){
	// cout << "Procesamiento " << id  << endl;
	//if(chunks[id].size() == 0) return;
	for(auto [row,col]: chunks[id]){
		if(row == 0 || col == 0) continue;
		else{
			diag = dp[row-1][col-1]+(secuenciaOne[row-1]==secuenciaTwo[col-1]?1:-1);
			up = dp[row-1][col]-2;
			leftt = dp[row][col-1]-2;
			dp[row][col] = max(diag, max(up,leftt));
			if(dp[row][col] == diag) dp_direcciones[row][col][0] = 1;
			if(dp[row][col] == up) dp_direcciones[row][col][1] = 1;
			if(dp[row][col] == leftt) dp_direcciones[row][col][2] = 1;
		}
	}
}

void solve(){
	salida.open("laboratorioNWParalelo_04.txt");
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
	// for(int e = 1 ; e < sizeOne+1; e++){
	// 	for(int j = 1 ;j < sizeTwo+1 ;j++){
	// 		diag = dp[e-1][j-1]+(secuenciaOne[e-1]==secuenciaTwo[j-1]?1:-1);
	// 		up = dp[e-1][j]-2;
	// 		leftt = dp[e][j-1]-2;
	// 		dp[e][j] = max(diag, max(up,leftt));
	// 		if(dp[e][j] == diag) dp_direcciones[e][j][0] = 1;
	// 		if(dp[e][j] == up) dp_direcciones[e][j][1] = 1;
	// 		if(dp[e][j] == leftt) dp_direcciones[e][j][2] = 1;
	// 	}
	// }
    // row

	// Aqui empieza el paralelismo
	startTime = clock();
	salida << "Tiempo Inicio: " << (double)(startTime)  / CLOCKS_PER_SEC << " segundos" << endl;
	for (int e = 0; e < sizeOne+1; e++){
		// cout << "e: " << e << endl;
		int col = 0;
		int e_ = e;
		while (1){
			indices.push_back({e_, col});
			if (e_ == 0 || col == sizeTwo) break;
			e_--; col++;
		}
        auto total_size = indices.size();
		// cout << "total size: " << total_size << endl;
        if(total_size % num_threads == 0) chunk_size = total_size / num_threads;
		else chunk_size = total_size / num_threads + 1;
		// cout << "chunk size: " << chunk_size << endl;
        // cout << "begin" << endl;

		chunks.resize(num_threads,vector<pair<int,int>>(0));

		int id = 0;
        for (size_t i = 0; i < indices.size(); i += chunk_size) {
            size_t chunk_end = min(i + chunk_size, total_size);
            //chunks.push_back(std::vector<pair<int,int>>(indices.begin() + i, indices.begin() + chunk_end));
			chunks[id] = std::vector<pair<int,int>>(indices.begin() + i, indices.begin() + chunk_end);
			id++;
        }
        // cout << "container chunk size" << endl;
		// cout << chunks.size() << endl;
        // for(auto e = 0 ; e < chunks.size(); e++){
		// 	cout << "chunk " << e << endl;
		// 	for(auto j: chunks[e]){
		// 		cout << j.first << " " << j.second << endl;
		// 	}
		// }

		for (int idT = 0; idT < num_threads; idT++) threads.emplace_back(procesarChunk, idT);
		// cout << "between" << endl;
		for (auto &thread : threads) thread.join();
		// cout << "final" << endl;
		threads.clear();
		indices.clear();
		chunks.clear();
	}
	// return;
	//col
	for(int j = 1; j < sizeTwo+1; j++){
		int row = sizeOne;
		int j_ = j;
		while(1){
			indices.push_back({row,j_});
			if(row == 0 || j_ == sizeTwo) break;
			row--; j_++;
		}
		auto total_size = indices.size();
		// cout << "total size: " << total_size << endl;
        if(total_size % num_threads == 0) chunk_size = total_size / num_threads;
		else chunk_size = total_size / num_threads + 1;
		// cout << "chunk size: " << chunk_size << endl;
        // cout << "begin" << endl;

		chunks.resize(num_threads,vector<pair<int,int>>(0));

		int id = 0;
        for (size_t i = 0; i < indices.size(); i += chunk_size) {
            size_t chunk_end = min(i + chunk_size, total_size);
            //chunks.push_back(std::vector<pair<int,int>>(indices.begin() + i, indices.begin() + chunk_end));
			chunks[id] = std::vector<pair<int,int>>(indices.begin() + i, indices.begin() + chunk_end);
			id++;
        }
		// cout << "container chunk size" << endl;
		// cout << chunks.size() << endl;
        // for(auto e = 0 ; e < chunks.size(); e++){
		// 	cout << "chunk " << e << endl;
		// 	for(auto j: chunks[e]){
		// 		cout << j.first << " " << j.second << endl;
		// 	}
		// }

		for (int idT = 0; idT < num_threads; idT++) threads.emplace_back(procesarChunk, idT);
		for (auto &thread : threads) thread.join();
		threads.clear();
		indices.clear();
		chunks.clear();
	}
	endTime = clock();
	salida << "Tiempo Final: " << (double)(endTime)  / CLOCKS_PER_SEC << " segundos" << endl;

	// Aqui terminea el paralelismo
	salida << "Tiempo de ejecucion: " << getCurrentTime() << "s" << endl;
	// salida << "Tiempo de ejecucion: " << getCurrentTime() << "s" << endl;
	// print dp_direcciones
	// cout << "dp_direcciones" << endl;
	// for(int e = 0 ; e < sizeOne +1 ; e++){
	// 	for(int j = 0 ; j < sizeTwo+1; j++){
	// 		for(int w = 0 ; w < 3; w++){
	// 			cout << dp_direcciones[e][j][w] << " ";
	// 		}cout << endl;
	// 	}cout << endl;
	// }cout << endl << endl;


    // return;
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
	// int i = sizeOne;
	// int j = sizeTwo;
	// cout << "Alineamientos Generados" << endl;
	// salida << "Alineamientos Generados" << endl;
	// dfs(sizeOne,sizeTwo);

	// cout << "Cantidad de alineaminentos producidos: " << cantidadCadenas << endl;
	// salida << "Cantidad de alineaminentos producidos: " << cantidadCadenas << endl;
}
int main(){
	// ios_base::sync_with_stdio(false);
	// cin.tie(0);
	#ifdef DEBUG
		freopen("input.txt","r",stdin);
		freopen("output.txt","w",stdout);
	#endif
	solve();
	return 0;
}