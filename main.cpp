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
    // vector
    auto start = chrono::high_resolution_clock::now();
    ifstream fin(file);
    switch (i) {
      case 0: {
        while (fin >> s) {
          // vector
          auto start_sv = chrono::high_resolution_clock::now();
          sort(v.begin(), v.end());
          auto end_sv = chrono::high_resolution_clock::now();
          auto vector_sort = duration_cast<microseconds>(end_sv - start_sv);
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

  // list
  auto start_sl = chrono::high_resolution_clock::now();
  l.sort();
  auto end_sl = chrono::high_resolution_clock::now();
  auto list_sort = duration_cast<microseconds>(end_sl - start_sl);

  // set: already sorted by def
  long long s_sort = -1;

  // Race 3: Insert

  // vector
  auto start_vi = chrono::high_resolution_clock::now();
  v.insert(v.begin() + (v.size() / 2), "TESTCODE");
  auto end_vi = high_resolution_clock::now();
  auto vector_insert = duration_cast<microseconds>(end_vi - start_vi);

  // list
  auto start_li = chrono::high_resolution_clock::now();
  auto mid = l.begin();
  advance(mid, (l.size() / 2));
  l.insert(mid, "TESTCODE");
  auto end_li = chrono::high_resolution_clock::now();
  auto list_insert = duration_cast<microseconds>(end_li - start_li);

  // set
  auto start_si = chrono::high_resolution_clock::now();
  st.insert("TESTCODE");
  auto end_si = chrono::high_resolution_clock::now();
  auto set_insert = duration_cast<microseconds>(end_si - start_si);

  // Race 4: Deleting

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

  // from lab 25
  //  cout << "Operation    Vector      List       Set\n";
  //  cout << "Read" << setw(13) << duration_v.count() << setw(12)
  //       << duration_l.count() << setw(12) << duration_s.count() << "\n";
  //  cout << "Sort" << setw(14) << vector_sort.count() << setw(12)
  //       << list_sort.count() << setw(8) << s_sort << "\n";
  //  cout << "Insert" << setw(10) << vector_insert.count() << setw(12)
  //       << list_insert.count() << setw(11) << set_insert.count() << "\n";
  //  cout << "Delete" << setw(10) << vector_delete.count() << setw(12)
  //   << list_delete.count() << setw(11) << set_delete.count() << "\n";

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