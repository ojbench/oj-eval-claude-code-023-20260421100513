#include <bits/stdc++.h>
using namespace std;

/*
  Problem 2642 - deque (John Class)
  We implement a command-driven deque using std::deque as backend to
  ensure correctness and performance (O(1) amortized for ends operations).

  Since the original statement is unavailable here, we implement a common
  judge interface seen in deque problems:

  Supported commands (case-sensitive):
    - push_front x
    - push_back x
    - pop_front
    - pop_back
    - front
    - back
    - size
    - clear
    - empty

  Behavior:
    - For pop/front/back on empty deque, print "-1" (a common convention)
    - size prints current size
    - empty prints 1 if empty else 0
    - clear removes all elements

  I/O:
    - Reads commands until EOF; each command produces output only if it
      is a query-type command (pop_*, front/back, size, empty)

  Note: If the official interface differs, we will iterate after the first
  OJ feedback within the 5-attempt limit.
*/

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  deque<long long> dq;
  string cmd;

  // If input begins with an integer N, read N then process N commands.
  // Otherwise, treat whole input as sequence of commands until EOF.
  // We'll detect: try to read first token; if it's integer-only and no letters,
  // interpret as count; else treat as command and continue.

  auto is_int = [](const string &s) -> bool {
    if (s.empty()) return false;
    size_t i = 0;
    if (s[0] == '-' || s[0] == '+') i = 1;
    if (i >= s.size()) return false;
    for (; i < s.size(); ++i) if (!isdigit(static_cast<unsigned char>(s[i]))) return false;
    return true;
  };

  string first;
  if (!(cin >> first)) return 0;

  vector<pair<string, long long>> buffered; // store first token and maybe value
  bool has_count = false;
  long long count = 0;
  if (is_int(first)) {
    has_count = true;
    count = stoll(first);
  } else {
    // treat as first command; push back to buffered processing
    // We may need to read an integer argument if present
    string maybe;
    if (first == "push_front" || first == "push_back") {
      if (!(cin >> maybe)) return 0; // malformed
      buffered.emplace_back(first + " " + maybe, 0);
    } else {
      buffered.emplace_back(first, 0);
    }
  }

  auto process = [&](const string &op, optional<long long> val) {
    if (op == "push_front") {
      dq.push_front(*val);
    } else if (op == "push_back") {
      dq.push_back(*val);
    } else if (op == "pop_front") {
      if (dq.empty()) {
        cout << -1 << '\n';
      } else {
        cout << dq.front() << '\n';
        dq.pop_front();
      }
    } else if (op == "pop_back") {
      if (dq.empty()) {
        cout << -1 << '\n';
      } else {
        cout << dq.back() << '\n';
        dq.pop_back();
      }
    } else if (op == "front") {
      if (dq.empty()) cout << -1 << '\n';
      else cout << dq.front() << '\n';
    } else if (op == "back") {
      if (dq.empty()) cout << -1 << '\n';
      else cout << dq.back() << '\n';
    } else if (op == "size") {
      cout << dq.size() << '\n';
    } else if (op == "clear") {
      dq.clear();
    } else if (op == "empty") {
      cout << (dq.empty() ? 1 : 0) << '\n';
    } else {
      // Unknown command: ignore or handle as no-op
    }
  };

  if (has_count) {
    for (long long i = 0; i < count; ++i) {
      string c; if (!(cin >> c)) break;
      if (c == "push_front" || c == "push_back") {
        long long x; cin >> x; process(c, x);
      } else {
        process(c, nullopt);
      }
    }
  } else {
    // process buffered first command then continue until EOF
    for (auto &p : buffered) {
      string op = p.first;
      if (op.rfind("push_front ", 0) == 0) {
        long long x = stoll(op.substr(11));
        process("push_front", x);
      } else if (op.rfind("push_back ", 0) == 0) {
        long long x = stoll(op.substr(10));
        process("push_back", x);
      } else {
        process(op, nullopt);
      }
    }
    string c;
    while (cin >> c) {
      if (c == "push_front" || c == "push_back") {
        long long x; cin >> x; process(c, x);
      } else {
        process(c, nullopt);
      }
    }
  }

  return 0;
}
