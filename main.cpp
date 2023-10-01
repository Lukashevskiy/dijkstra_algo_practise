#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

vector<vector<pair<int,int>>> vectoR;
vector<int> met, mass;

int mim(){
    int a = 0, massa = 1e8;
    for(int i = 1; i < mass.size(); i++){
        if(met[i] == 0){
            if(mass[i] < massa){
                massa = mass[i];
                a = i;
            }
        }
    }
    return a;
}

int main(int args, char* argv[]){
    int a;
    ifstream cin(argv[1]);
    cin >> a;

    vectoR.resize(a+1);
    met.resize(a+1, 0);
    mass.resize(a+1, 1e8);

    int f, g;

    cin >> f >> g;
    
    --f;
    --g;
    
    mass[f] = 0;
    
    string line;
    stringstream buf;

    getline(cin, line);
    
    int from, to, weight;
    
    while(getline(cin, line)){
        buf << line;
        
        buf >> from >> to >> weight;
        --from;
        --to;
        
        vectoR[from].push_back(make_pair(to, weight));
        
        buf.clear();
    }   


    for(int i = 1; i < a+1; i++){
        int v = mim();
        met[v] = 1;
        for(int j = 0; j < vectoR[v].size(); j++){
            if(mass[vectoR[v][j].first] > mass[v] + vectoR[v][j].second){
                mass[vectoR[v][j].first] = mass[v]+ vectoR[v][j].second;
            }
        }
    }

    if(mass[g] == 1e8 || mass[f] == 1e8){
        cout << -1;
        return 0;
    }else{
        cout << mass[g] + mass[f];
    }
    return 0;
}
