/*
 * https://usaco.guide/general/fast-io?lang=cpp
 */
#include "bits/stdc++.h"

using namespace std;

inline namespace Input {
  const int BUF_SZ = 1 << 17;
  char buf[BUF_SZ];
  int pos;
  int len;
  char next_char() {
    if (pos == len) {
      pos = 0;
      len = (int)fread(buf, 1, BUF_SZ, stdin);
      if (!len) {
        return EOF;
      }
    }
    return buf[pos++];
  }

  // change to long long if you need
  int read_int() {
    int x;
    char ch;
    int sgn = 1;
    while (!isdigit(ch = next_char())) {
      if (ch == '-') {
        sgn *= -1;
      }
    }
    x = ch - '0';
    while (isdigit(ch = next_char())) {
      x = x * 10 + (ch - '0');
    }
    return x * sgn;
  }
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
    if (pos == BUF_SZ) {
      flush_out();
    }
    buf[pos++] = c;
  }

  void write_int(long long x, char delim = '\n') {
    static char num_buf[100];
    if (x < 0) {
      write_char('-');
      x *= -1;
    }
    int len = 0;
    for (; x >= 10; x /= 10) {
      num_buf[len++] = (char)('0' + (x % 10));
    }
    write_char((char)('0' + x));
    while (len) {
      write_char(num_buf[--len]);
    }
    write_char(delim);
  }

  // auto-flush output when program exits
  void init_output() { assert(atexit(flush_out) == 0); }
} // namespace Output
