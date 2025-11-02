// COMSC210 | Lab 25 | Tanmayee Chalamalasetti
// IDE Used: VS Code
#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;
using namespace std::chrono;

int main() {
  string file = "codes.txt";
  string s;
  // Race 1: Reading

  // vector
  auto start_v = high_resolution_clock::now();
  ifstream fin1(file);
  vector<string> v;
  while (fin1 >> s) {
    v.push_back(s);
  }
  fin1.close();
  auto end_v = high_resolution_clock::now();
  auto duration_v = duration_cast<microseconds>(end_v - start_v);

  // list
  auto start_l = high_resolution_clock::now();
  ifstream fin2(file);
  list<string> l;
  while (fin2 >> s) {
    l.push_back(s);
  }
  fin2.close();
  auto end_l = high_resolution_clock::now();
  auto duration_l = duration_cast<microseconds>(end_l - start_l);

  // set
  auto start_s = high_resolution_clock::now();
  ifstream fin3(file);
  set<string> st;
  while (fin3 >> s) {
    st.insert(s);
  }
  fin3.close();
  auto end_s = high_resolution_clock::now();
  auto duration_s = duration_cast<microseconds>(end_s - start_s);

  // Race 2: Sorting

  // vector
  auto start_sv = high_resolution_clock::now();
  sort(v.begin(), v.end());
  auto end_sv = high_resolution_clock::now();
  auto vector_sort = duration_cast<microseconds>(end_sv - start_sv);

  // list
  auto start_sl = high_resolution_clock::now();
  l.sort();
  auto end_sl = high_resolution_clock::now();
  auto list_sort = duration_cast<microseconds>(end_sl - start_sl);

  // set: already sorted by def
  long long s_sort = -1;

  // Race 3: Insert

  // vector
  auto start_vi = high_resolution_clock::now();
  v.insert(v.begin() + (v.size() / 2), "TESTCODE");
  auto end_vi = high_resolution_clock::now();
  auto vector_insert = duration_cast<microseconds>(end_vi - start_vi);

  // list
  auto start_li = high_resolution_clock::now();
  auto mid = l.begin();
  advance(mid, (l.size() / 2));
  l.insert(mid, "TESTCODE");
  auto end_li = high_resolution_clock::now();
  auto list_insert = duration_cast<microseconds>(end_li - start_li);

  // set
  auto start_si = high_resolution_clock::now();
  st.insert("TESTCODE");
  auto end_si = high_resolution_clock::now();
  auto set_insert = duration_cast<microseconds>(end_si - start_si);

  // Race 4: Deleting

  // vector
  auto start_vd = high_resolution_clock::now();
  v.erase(v.begin() + (v.size() / 2));
  auto end_vd = high_resolution_clock::now();
  auto vector_delete = duration_cast<microseconds>(end_vd - start_vd);

  // list
  auto start_di = high_resolution_clock::now();
  auto mid_d = l.begin();
  advance(mid_d, (l.size() / 2));
  l.erase(mid_d);
  auto end_di = high_resolution_clock::now();
  auto list_delete = duration_cast<microseconds>(end_di - start_di);

  // set
  auto start_sd = high_resolution_clock::now();
  auto it_d = st.begin();
  advance(it_d, (st.size() / 2));
  st.erase(it_d);
  auto end_sd = high_resolution_clock::now();
  auto set_delete = duration_cast<microseconds>(end_sd - start_sd);

  cout << "Operation    Vector      List       Set\n";
  cout << "Read" << setw(13) << duration_v.count() << setw(12)
       << duration_l.count() << setw(12) << duration_s.count() << "\n";
  cout << "Sort" << setw(14) << vector_sort.count() << setw(12)
       << list_sort.count() << setw(8) << s_sort << "\n";
  cout << "Insert" << setw(10) << vector_insert.count() << setw(12)
       << list_insert.count() << setw(11) << set_insert.count() << "\n";
  cout << "Delete" << setw(10) << vector_delete.count() << setw(12)
       << list_delete.count() << setw(11) << set_delete.count() << "\n";
  return 0;
}
 

/* syntax examples:
auto start = high_resolution_clock::now()
auto end = high_resolution_clock::now()
auto duration = duration_cast<milliseconds>(end - start)
duration.count() references elapsed milliseconds
*/