#include <iostream>
#include <queue>
#include <limits.h>
using namespace std;

int main(){
    FILE* f1 = fopen("inputBFS.txt", "r");
    FILE* f2 = fopen("outputBFS.txt", "w");
    int N = 0, n = 0, s = 0, e = 0, p = 0;
    bool flag = true;
    fscanf(f1, "%d", &N);
    for(int l = 0; l < N; l++){
        fscanf(f1, "%d %d %d", &n, &s, &e);
        int map[n][n];
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                fscanf(f1, "%d", &map[i][j]);
            }
        }
        queue<int> q;
        q.push(s);
        bool seen[n];
        int dist[n];
        for(int i = 0; i < n; i++){
            dist[i] = INT_MAX;
            seen[i] = false;
        }
        dist[s] = 0;
        while (!q.empty()) {
            p = q.front();
            q.pop();
            if(!seen[p]){
                seen[p] = true;
                if(p == e){
                    flag = false;
                    break;
                }
                for(int i = 0; i < n; i++){
                    if(map[p][i] == 1 && !seen[i]){
                        q.push(i);
                        if(dist[i] > dist[p] + 1){
                            dist[i] = dist[p] + 1;
                        }
                    }
                }
            }
        }
        if(flag){
            fprintf(f2, "-1\n");
        }
        else{
            fprintf(f2, "%d\n", dist[e]);
            flag = true;
        }
    }
    fclose(f1);
    fclose(f2);
    return 0;
}
