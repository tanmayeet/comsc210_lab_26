// COMSC210 | Lab 26 | Tanmayee Chalamalasetti
// IDE Used: VS Code
// Referenced solution code to Lab 25 for this lab
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>
using namespace std;
using namespace std::chrono;

const int structs = 3;
const int rows = 4, cols = 3;
const int sims = 15;
const int W = 10;

int main() {
  string file = "codes.txt";
  int results[sims][rows][cols];
  int avg[rows][cols] = {0};
  string s;
  vector<string> v;
  list<string> l;
  set<string> st;

  for (int run = 0; run < sims; run++) {
    v.clear();
    l.clear();
    st.clear();

    // Race 1: Reading
    for (int i = 0; i < structs; i++) {
      // vector
      ifstream fin(file);
      auto start = chrono::high_resolution_clock::now();
      switch (i) {
        case 0: {
          while (fin >> s) {
            v.push_back(s);
          }
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][0][i] = duration.count();
          break;
        }
        case 1: {
          // list
          while (fin >> s) {
            l.push_back(s);
          }
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][0][i] = duration.count();
          break;
        }
        case 2: {
          // set
          while (fin >> s) {
            st.insert(s);
          }
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][0][i] = duration.count();
          break;
        }
      }
      fin.close();
    }

    // Race 2: Sorting
    for (int i = 0; i < structs; i++) {
      auto start = chrono::high_resolution_clock::now();
      switch (i) {
        case 0: {
          // vector
          sort(v.begin(), v.end());
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][1][i] = duration.count();
          break;
        }

        case 1: {
          // list
          l.sort();
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][1][i] = duration.count();
          break;
        }
        case 2: {
          // set
          results[run][1][i] = -1;
          break;
        }
      }
    }

    // Race 3: Insert
    for (int i = 0; i < structs; i++) {
      auto start = chrono::high_resolution_clock::now();
      switch (i) {
        case 0: {
          // vector
          v.insert(v.begin() + (v.size() / 2), "TESTCODE");
          auto end = high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][2][i] = duration.count();
          break;
        }
        case 1: {
          // list
          auto it = l.begin();
          advance(it, (l.size() / 2));
          l.insert(it, "TESTCODE");
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][2][i] = duration.count();
          break;
        }
        case 2: {
          // set
          st.insert("TESTCODE");
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][2][i] = duration.count();
          break;
        }
      }
    }
    // Race 4: Deleting
    for (int i = 0; i < structs; i++) {
      auto start = chrono::high_resolution_clock::now();
      switch (i) {
        case 0: {
          // vector
          v.erase(v.begin() + (v.size() / 2));
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][3][i] = duration.count();
          break;
        }
        case 1: {
          // list
          auto mid = l.begin();
          advance(mid, (l.size() / 2));
          l.erase(mid);
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][3][i] = duration.count();
          break;
        }
        case 2: {
          // set
          auto it = st.begin();
          advance(it, (st.size() / 2));
          st.erase(it);
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[run][3][i] = duration.count();
          break;
        }
      }
    }
  }

  for (int s = 0; s < sims; s++) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        avg[i][j] += results[s][i][j];
      }
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      avg[i][j] /= sims;
    }
  }

  // New output method
  string labels[] = {"Read", "Sort", "Insert", "Delete"};
  cout << "Number of simulations: " << sims << endl;
  cout << setw(W) << "Operation" << setw(W) << "Vector" << setw(W) << "List"
       << setw(W) << "Set" << endl;
  for (int i = 0; i < 4; ++i) {
    cout << setw(W) << labels[i];
    for (int j = 0; j < cols; j++) {
      cout << setw(W) << avg[i][j];
    }
    cout << endl;
  }
  return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/