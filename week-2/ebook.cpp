#include <vector>
#include <iomanip>
#include <numeric>
#include <iostream>

#include "test_runner.h"
#include "profiler.h"

using namespace std;

class ReadingManager {
 public:
  ReadingManager() : pages_by_user(USERS_LIMIT + 1, 0),
					 users_by_page(PAGES_LIMIT + 1, 0),
					 users(0),
					 max_page(0),
					 rating(PAGES_LIMIT + 1, 1) {}

  void Read(const size_t user_id, const size_t page) {
	max_page = max(max_page, page);
	size_t prev_page = 0, max_p = max_page;
	if (pages_by_user[user_id] == 0) {
	  ++users;
	} else {
	  prev_page = pages_by_user[user_id];
	  max_p = page;
	  --users_by_page[pages_by_user[user_id]];
	}
	pages_by_user[user_id] = page;
	++users_by_page[page];
	if (users > 1) {
	  Adjust(prev_page, max_p);
	}
  }

  [[nodiscard]] double Cheer(const size_t user_id) const {
	if (pages_by_user[user_id] == 0) {
	  return 0;
	}
	if (users == 1) {
	  return 1;
	}
	return rating[pages_by_user[user_id]];
  }

 private:
  static const size_t PAGES_LIMIT = 1000;
  static const size_t USERS_LIMIT = 100'000;

  size_t users, max_page;
  vector<size_t> pages_by_user;
  vector<size_t> users_by_page;
  vector<double> rating;

  void Adjust(const size_t page, const size_t page_up) {
	for (size_t i = page_up; i > page; --i) {
	  size_t others = 0;
	  for (size_t it = 0; it < i; ++it) {
		others += users_by_page[it];
	  }
//	  cout << "rating p"<<i<<" = " << others << " / " << users - 1 << endl;
	  rating[i] =
		  static_cast<double>(others) / static_cast<double>(users - 1);
	}
//	cout << "pages with rating: ";
//	for (size_t it = 0; it < 15; ++it) {
//	  cout << rating[it] << " ";
//	}
//	cout << endl;
//	cout << "users by pages: ";
//	for (size_t it = 0; it < 15; ++it) {
//	  cout << "p" << it << ": " << users_by_page[it] << " ";
//	}
//	cout << endl;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

//  ReadingManager manager;
//  manager.Read(1, 1);
//  manager.Read(1, 3);
//  manager.Read(2, 2);
//  cout << manager.Cheer(1) << endl;
//  ASSERT_EQUAL(manager.Cheer(1), 1.0);
//  ASSERT_EQUAL(manager.Cheer(2), 0.0);
//  {// reverse order
//	manager.Read(4, 5);
//	manager.Read(3, 4);
//	manager.Read(2, 3);
//	manager.Read(1, 2);
//	ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);
//  }

//  { /*two users read two times*/
//	ReadingManager manager;
//	manager.Read(4, 5);
//	manager.Read(3, 4);
//	manager.Read(4, 6);
//	manager.Read(3, 5);
//	ASSERT_EQUAL(manager.Cheer(4), 1.0);
//	ASSERT_EQUAL(manager.Cheer(3), 0.0);
//	manager.Read(10, 2);
//	ASSERT_EQUAL(manager.Cheer(3), 0.5);
//	ASSERT_EQUAL(manager.Cheer(4), 1.0);
//	cout << "tests good" << endl;
//  }

//  ReadingManager manager;
//  manager.Read(1, 1);
//  manager.Read(2, 2);
//  manager.Read(3, 3);
//  ASSERT_EQUAL(manager.Cheer(2), 0.5);
//  manager.Read(4, 4);
//  ASSERT_EQUAL(manager.Cheer(3), 2.0 / 3.0);

  ReadingManager manager;
  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
	string query_type;
	cin >> query_type;
	int user_id;
	cin >> user_id;

	if (query_type == "READ") {
	  int page_count;
	  cin >> page_count;
	  manager.Read(user_id, page_count);
	} else if (query_type == "CHEER") {
	  cout << setprecision(6) << manager.Cheer(user_id) << "\n";
	}
  }

  return 0;
}