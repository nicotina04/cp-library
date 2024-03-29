/*
 * https://usaco.guide/general/fast-io?lang=cpp
 */
#include "bits/stdc++.h"

using namespace std;

inline namespace Input {
  constexpr int BUF_SZ = 1 << 17;
  char buf[BUF_SZ];
  int pos, len;
  char next_char() {
    if (pos == len) {
      pos = 0;
      len = (int)fread(buf, 1, BUF_SZ, stdin);
      if (!len) return EOF;
    }
    return buf[pos++];
  }

  int_fast64_t read_int() {
    int_fast64_t x;
    char ch;
    int sgn = 1;
    while (!isdigit(ch = next_char())) if (ch == '-') sgn *= -1;
    x = ch - '0';
    while (isdigit(ch = next_char())) x = x * 10 + (ch - '0');
    return x * sgn;
  }

  string read_string() {
    string ret;
    char ch;
    while (isspace(ch = next_char())) {}
    ret.push_back(ch);
    while (not isspace(ch = next_char()) and ch != EOF) ret.push_back(ch);
    return ret;
  }
  
  double read_double() { return stod(read_string());}
} // namespace Input

inline namespace Output {
  const int BUF_SZ = 1 << 17;
  char buf[BUF_SZ];
  int pos;

  void flush_out() {
    fwrite(buf, 1, pos, stdout);
    pos = 0;
  }

  void write_char(char c) {
    if (pos == BUF_SZ) flush_out();
    buf[pos++] = c;
  }

  void write_int(int_fast64_t x, char delim = '\n') {
    static char num_buf[100];
    if (x < 0) {
      write_char('-');
      x *= -1;
    }
    int len = 0;
    for (; x >= 10; x /= 10) num_buf[len++] = (char)('0' + (x % 10));
    write_char((char)('0' + x));
    while (len) write_char(num_buf[--len]);
    write_char(delim);
  }

  // auto-flush output when program exits
  void init_output() { assert(atexit(flush_out) == 0); }
} // namespace Output
