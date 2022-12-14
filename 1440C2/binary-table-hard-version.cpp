#include <bits/stdc++.h>
using namespace std;

using Grid = vector<vector<int>>;
using Move = vector<pair<int, int>>;

Grid g;
vector<Move> ops;

Move tl = {{0, 0}, {0, 1}, {1, 0}};
Move tr = {{0, 0}, {0, 1}, {1, 1}};
Move bl = {{0, 0}, {1, 0}, {1, 1}};
Move br = {{0, 1}, {1, 0}, {1, 1}};

map<vector<int>, vector<Move>> memo = {
  {{0, 0, 0, 0}, {}},
  {{0, 0, 0, 1}, {tr, br, bl}},
  {{0, 0, 1, 0}, {bl, tl, br}},
  {{0, 0, 1, 1}, {tr, tl}},
  {{0, 1, 0, 0}, {tr, tl, br}},
  {{0, 1, 0, 1}, {tl, bl}},
  {{0, 1, 1, 0}, {tr, bl}},
  {{0, 1, 1, 1}, {br}},
  {{1, 0, 0, 0}, {tl, tr, bl}},
  {{1, 0, 0, 1}, {tl, br}},
  {{1, 0, 1, 0}, {tr, br}},
  {{1, 0, 1, 1}, {bl}},
  {{1, 1, 0, 0}, {br, bl}},
  {{1, 1, 0, 1}, {tr}},
  {{1, 1, 1, 0}, {tl}},
  {{1, 1, 1, 1}, {tl, br, tr, bl}}
};

void clear(int r, int c) {
  vector<int> state = {
    g[r][c], g[r][c + 1],
    g[r + 1][c], g[r + 1][c + 1]
  };
  vector<Move> ms = memo[state];
  for (auto& m: ms) {
    for (auto& [x, y]: m) {
      x += r;
      y += c;
    }
  }
  ops.insert(ops.end(), ms.begin(), ms.end());
  g[r][c] = g[r][c + 1] = 0;
  g[r + 1][c] = g[r + 1][c + 1] = 0;
}

void flip(int r, int c) {
  g[r][c] = 1 - g[r][c];
}

int bs( vector<int>& arr){
  int mid;
  int ll = 0; int rr = arr.size() - 1;
  while(ll <= rr){
    int mid = (ll+rr)/2;
    if(arr[mid] == 1){
       rr = mid-1;
    }
    else{
      ll= mid+1;
    }
  }

  return ll;
}


int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int t;
  cin >> t;
  while (t--) {
    int n, m;
    cin >> n >> m;
    g.assign(n, vector<int>(m));
    for (int r = 0; r < n; r++) {
      for (int c = 0; c < m; c++) {
        char b;
        cin >> b;
        g[r][c] = b - '0';
      }
    }
    if (n % 2 == 1) {
      int r = n - 1;
      if (g[r][0] == 1) {
        flip(r - 1, 0);
        flip(r - 1, 1);
        flip(r, 0);
        Move m = tl;
        for (auto& [x, y]: m) {
          x += r - 1;
        }
        ops.push_back(m);
      }
      for (int c = 0; c < m - 1; c++) {
        if (g[r][c + 1] == 1) {
          flip(r - 1, c);
          flip(r - 1, c + 1);
          flip(r, c + 1);
          Move m = tr;
          for (auto& [x, y]: m) {
            x += r - 1;
            y += c;
          }
          ops.push_back(m);
        }
      }
    }
    if (m % 2 == 1) {
      int c = m - 1;
      if (g[0][c] == 1) {
        flip(0, c - 1);
        flip(0, c);
        flip(1, c - 1);
        Move m = tl;
        for (auto& [x, y]: m) {
          y += c - 1;
        }
        ops.push_back(m);
      }
      for (int r = 0; r < n - 1; r++) {
        if (g[r + 1][c] == 1) {
          flip(r, c - 1);
          flip(r + 1, c - 1);
          flip(r + 1, c);
          Move m = bl;
          for (auto& [x, y]: m) {
            x += r;
            y += c - 1;
          }
          ops.push_back(m);
        }
      }
    }
    for (int r = 0; r < n - 1; r += 2) {
      for (int c = 0; c < m - 1; c += 2) {
        clear(r, c);
      }
    }
    cout << ops.size() << endl;
    for (auto op: ops) {
      for (auto [x, y]: op) {
        cout << x + 1 << " " << y + 1 << " ";
      }
      cout << endl;
    }
    ops.clear();
  }
  return 0;
}
