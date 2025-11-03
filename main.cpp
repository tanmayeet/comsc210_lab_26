// COMSC210 | Lab 26 | Tanmayee Chalamalasetti
// IDE Used: VS Code
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
const int rows = 4, cols = 3, depth = 3;
const int W = 10;

int main() {
  string file = "codes.txt";
  int results[rows][cols][depth];
  string s;
  vector<string> v;
  list<string> l;
  set<string> st;

  // Race 1: Reading
  for (int i = 0; i < structs; i++) {
    // vector
    auto start = chrono::high_resolution_clock::now();
    ifstream fin(file);
    switch (i) {
      case 0: {
        while (fin >> s) {
          v.push_back(s);
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[0][i][0] = duration.count();
          break;
        }
      }
      case 1: {
        // list
        while (fin >> s) {
          l.push_back(s);
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[0][i][0] = duration.count();
          break;
        }
      }
      case 2: {
        // set
        while (fin >> s) {
          st.insert(s);
          auto end = chrono::high_resolution_clock::now();
          auto duration = duration_cast<microseconds>(end - start);
          results[0][i][0] = duration.count();
          break;
        }
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
        auto vector_sort = duration_cast<microseconds>(end - start);
      }
      case 1: {
        // list
        l.sort();
        auto end = chrono::high_resolution_clock::now();
        auto list_sort = duration_cast<microseconds>(end - start);
        break;
      }
      case 2: {
        // set
        long long s_sort = -1;
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
        auto vector_insert = duration_cast<microseconds>(end - start);
      }
      case 1: {
        // list
        auto mid = l.begin();
        advance(mid, (l.size() / 2));
        l.insert(mid, "TESTCODE");
        auto end = chrono::high_resolution_clock::now();
        auto list_insert = duration_cast<microseconds>(end - start);
      }
      case 2: {
        // set
        st.insert("TESTCODE");
        auto end = chrono::high_resolution_clock::now();
        auto set_insert = duration_cast<microseconds>(end - start);
      }
    }
  }
  // Race 4: Deleting
  for (int i = 0; i < structs; i++) {
    auto start = chrono::high_resolution_clock::now();
    switch (i) {
      case 0: {
        // vector
        auto start_vd = chrono::high_resolution_clock::now();
        v.erase(v.begin() + (v.size() / 2));
        auto end_vd = chrono::high_resolution_clock::now();
        auto vector_delete = duration_cast<microseconds>(end_vd - start_vd);
      }
      case 1: {
        // list
        auto start_di = chrono::high_resolution_clock::now();
        auto mid_d = l.begin();
        advance(mid_d, (l.size() / 2));
        l.erase(mid_d);
        auto end_di = chrono::high_resolution_clock::now();
        auto list_delete = duration_cast<microseconds>(end_di - start_di);
      }
      case 2: {
        // set
        auto start_sd = chrono::high_resolution_clock::now();
        auto it_d = st.begin();
        advance(it_d, (st.size() / 2));
        st.erase(it_d);
        auto end_sd = chrono::high_resolution_clock::now();
        auto set_delete = duration_cast<microseconds>(end_sd - start_sd);
      }
    }
  }
  // vector
  auto start_vd = chrono::high_resolution_clock::now();
  v.erase(v.begin() + (v.size() / 2));
  auto end_vd = chrono::high_resolution_clock::now();
  auto vector_delete = duration_cast<microseconds>(end_vd - start_vd);

  // list
  auto start_di = chrono::high_resolution_clock::now();
  auto mid_d = l.begin();
  advance(mid_d, (l.size() / 2));
  l.erase(mid_d);
  auto end_di = chrono::high_resolution_clock::now();
  auto list_delete = duration_cast<microseconds>(end_di - start_di);

  // set
  auto start_sd = chrono::high_resolution_clock::now();
  auto it_d = st.begin();
  advance(it_d, (st.size() / 2));
  st.erase(it_d);
  auto end_sd = chrono::high_resolution_clock::now();
  auto set_delete = duration_cast<microseconds>(end_sd - start_sd);

  // New output method
  string labels[] = {"Read", "Sort", "Insert", "Delete"};
  string colV[] = {
      to_string(duration_v.count()), to_string(vector_sort.count()),
      to_string(vector_insert.count()), to_string(vector_delete.count())};

  string colL[] = {to_string(duration_l.count()), to_string(list_sort.count()),
                   to_string(list_insert.count()),
                   to_string(list_delete.count())};

  string colS[] = {to_string(duration_s.count()), to_string(s_sort),
                   to_string(set_insert.count()),
                   to_string(set_delete.count())};

  cout << left << setw(W) << "Operation" << right << setw(W) << "Vector"
       << setw(W) << "List" << setw(W) << "Set" << "\n";
  for (int i = 0; i < 4; ++i) {
    cout << left << setw(W) << labels[i] << right << setw(W) << colV[i]
         << setw(W) << colL[i] << setw(W) << colS[i] << "\n";
  }
  return 0;
}

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/