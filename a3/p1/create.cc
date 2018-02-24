#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string first = "id ";
  string last = " id";
  //Printing the input twice
  for (int j = 'a'; j < 'z'; j++) {
    char m = j;
    cout << first << m << last << endl;
  }
  for (int j = 'A'; j < 'Z'; j++) {
    char m = j;
    cout << first << m << last << endl;
  }
}
