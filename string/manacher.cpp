#define MANA_SIZE 4000003
string s, manas;
int mana[4000003];

void manacher() {
  int r = -1, centre = -1;
  for (char &c : s) {
    manas.push_back('#');
    manas.push_back(c);
  }
  manas.push_back('#');
  int sz = manas.size();
  for (int i = 0; i < sz; i++) {
    int &ptr = mana[i];
    if (r >= i) ptr = min(r - i, mana[centre * 2 - i]);
    else ptr = 0;
    while (i + ptr + 1 < sz and i - ptr - 1 >= 0 and manas[i + ptr + 1] == manas[i - ptr - 1]) ++ptr;
    if (i + ptr > r) centre = i, r = i + ptr;
  }
}
