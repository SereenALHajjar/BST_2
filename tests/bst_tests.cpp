#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"
#include "bst.hpp"

static key_t k(std::initializer_list<uint8_t> l) { return key_t(l); }
static value_t v(std::initializer_list<uint8_t> l) { return value_t(l); }
#include <string>
static key_t kstr(const std::string& s) {
	key_t out;
	for (auto c : s) out.push_back(static_cast<uint8_t>(c));
	return out;
}
static value_t vstr(const std::string& s) {
	value_t out;
	for (auto c : s) out.push_back(static_cast<uint8_t>(c));
	return out;
}
static std::string tostring(const value_t& vv) {
	std::string s;
	for (auto c : vv) s.push_back(static_cast<char>(c));
	return s;
}

TEST_CASE("put and get basic") {
	BST tree;
	auto key1 = k({1,2,3});
	auto val1 = v({10});

	tree.put(key1, val1);

	auto out = tree.get(key1);
	CHECK(out == val1);
}

TEST_CASE("overwrite existing key") {
	BST tree;
	auto key = k({9});
	auto v1 = v({1});
	auto v2 = v({2});

	tree.put(key, v1);
	CHECK(tree.get(key) == v1);
	tree.put(key, v2);
	CHECK(tree.get(key) == v2);
}

TEST_CASE("missing key returns empty value") {
	BST tree;
	auto missing = k({0,0});
	auto res = tree.get(missing);
	CHECK(res.empty());
}

TEST_CASE("ordering and multiple keys") {
	BST tree;
	tree.put(k({2}), v({20}));
	tree.put(k({1,255}), v({125}));
	tree.put(k({1,0}), v({10}));
	tree.put(k({3}), v({30}));
	CHECK(tree.get(k({1,0})) == v({10}));
	CHECK(tree.get(k({1,255})) == v({125}));
	CHECK(tree.get(k({2})) == v({20}));
	CHECK(tree.get(k({3})) == v({30}));
}

#include <thread>
TEST_CASE("concurrent puts and gets") {
	BST tree;

	auto writer = [&tree](int base) {
		for (int i = 0; i < 100; ++i) {
			key_t key = {static_cast<uint8_t>(base), static_cast<uint8_t>(i)};
			value_t val = {static_cast<uint8_t>(i)};
			tree.put(key, val);
		}
	};

	auto reader = [&tree](int base) {
		for (int i = 0; i < 100; ++i) {
			key_t key = {static_cast<uint8_t>(base), static_cast<uint8_t>(i)};
			auto res = tree.get(key);
			if (!res.empty()) CHECK(res[0] == static_cast<uint8_t>(i));
		}
	};

	std::thread t1(writer, 1);
	std::thread t2(reader, 1);
	std::thread t3(writer, 2);
	std::thread t4(reader, 2);

	t1.join(); t2.join(); t3.join(); t4.join();
}

TEST_CASE("string keys and values") {
	BST tree;
	tree.put(kstr("hello"), vstr("world"));
	CHECK(tostring(tree.get(kstr("hello"))) == "world");

	// missing string key returns empty
	CHECK(tree.get(kstr("no-such-key")).empty());

	// overwrite with string values
	tree.put(kstr("hello"), vstr("again"));
	CHECK(tostring(tree.get(kstr("hello"))) == "again");

	// empty string key/value
	tree.put(kstr(""), vstr("empty"));
	CHECK(tostring(tree.get(kstr(""))) == "empty");
}

TEST_CASE("string ordering and prefix behavior") {
	BST tree;
	tree.put(kstr("ab"), vstr("short"));
	tree.put(kstr("abc"), vstr("long"));

	CHECK(tostring(tree.get(kstr("ab"))) == "short");
	CHECK(tostring(tree.get(kstr("abc"))) == "long");
}