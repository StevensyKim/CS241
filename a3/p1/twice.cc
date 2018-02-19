#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  vector <int> input;
  int i;
  //reading in inputs
  while (cin >> i) {
    input.push_back(i);
  }
  //Printing the input twice
  int len = input.size();
  for (int j = 0; j < 2; j++) {
    for (int k = 0; k < len; k++) {
      cout << input[k] << endl;
    }
  }
}
