#include <iostream>
#include <queue>

using namespace std;

const int MOD = 10000;

void bfs(int a, int b) {
  int visited[10000] = {};
  queue<pair<string, int>> q;

  q.push({"", a});
  visited[a] = 1;
  while (!q.empty()) {
    auto [command, n] = q.front();

    q.pop();
    if (n == b) {
      cout << command << '\n';
      break;
    }

    int m;

    m = (2 * n) % MOD;
    if (!visited[m]) {
      visited[m] = 1;
      q.push({command + "D", m});
    }
    m = (n == 0 ? 9999 : n - 1);
    if (!visited[m]) {
      visited[m] = 1;
      q.push({command + "S", m});
    }
    m = (n % 1000) * 10 + n / 1000;
    if (!visited[m]) {
      visited[m] = 1;
      q.push({command + "L", m});
    }
    m = (n % 10) * 1000 + n / 10;
    if (!visited[m]) {
      visited[m] = 1;
      q.push({command + "R", m});
    }
  }
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int T;
  int A, B;

  cin >> T;
  while (T--) {
    cin >> A >> B;
    bfs(A, B);
  }
}