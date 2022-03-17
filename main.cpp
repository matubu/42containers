#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "vector.hpp"
#include <stack>
#include "stack.hpp"
#include <map>
#include "map.hpp"

#define ENDL "\033[0m" << "\n"
#define NOBENCH
#define DEFAULT_ITER 100000
#define SLOW_ITER 10

bool success = true;

#define DEBUG(_vec, _namespace) { \
	std::cout << " - \033[92m" << #_namespace << ENDL; \
	std::cout << "    [\033[33m" << _vec.size() << "\033[0m/\033[33m" << _vec.capacity() << "\033[0m] \033[0m \033[90m(" << _vec.data() << ")" << ENDL; \
	for (size_t i = 0; i < _vec.size(); i++) \
		std::cout << "    - [\033[33m" << i << "\033[0m] -> \033[33m" << _vec[i] << ENDL; \
}

#define RUN(_namespace, _vec, _cmd) { \
	_namespace::vector<type> &vec = _vec; \
	int i = 0; (void)i; _cmd; \
	if (debug) DEBUG(_vec, _namespace); \
}

# define BENCH(_return, _namespace, _vec, _cmd) { \
	_namespace::vector<type> &vec = _vec; \
	clock_t start = clock(); \
	for (int j = 0; j < 32; j++) \
	{ \
		for (int y = 0; y < iter; y++) \
		{ \
			int i = y + j * iter; \
			(void)i; \
			_cmd; \
		} \
		std::cout << "█" << std::flush; \
	} \
	_return = (double)(clock() - start) / CLOCKS_PER_SEC * 1000; \
}

#define SHOW(_this_ms, _other_ms, _namespace) \
	std::cout << (_this_ms <= _other_ms ? "\033[92m" : "\033[91m") \
		<< std::setw(3) << #_namespace << " -> " << _this_ms << "ms   \033[90m(" << iter * 32 << " times)" << ENDL;

#define NEW_TEST_SUITE() \
	std::vector<type> real, real_bench; \
	ft::vector<type> mine, mine_bench; \
	int iter = DEFAULT_ITER; \
	bool debug = true;

#define SLOW(cmd) \
	iter = SLOW_ITER; \
	cmd; \
	iter = DEFAULT_ITER;

#define COMPARE(a, b) { \
	bool some = false; \
	if (a.size() == b.size()) { \
		for (unsigned long i = 0; i < a.size(); i++) \
			if (a[i] != b[i]) some = true; \
	} \
	else \
		some = true; \
	if (some) success = false; \
	std::cout << (some ? "\033[101;30m" : "\033[102;30m") << " >>> " << (some ? "❌ " : "✅ ") << ENDL; \
}

#define NO_DEBUG(cmd) \
	debug = false; \
	cmd; \
	debug = true;

#define TEST(cmd) { \
	std::cout << ENDL << "\033[94m" << #cmd << ENDL; \
	RUN(std, real, cmd); \
	RUN(ft, mine, cmd); \
	COMPARE(real, mine); \
	double	std_ms, ft_ms; \
	std::cout << "\033[94m"; \
	BENCH(std_ms, std, real_bench, cmd); \
	std::cout << "\033[91m"; \
	BENCH(ft_ms, ft, mine_bench, cmd); \
	std::cout << "\33[2K\r"; \
	SHOW(std_ms, ft_ms, std); \
	SHOW(ft_ms, std_ms, ft); \
	std::cout << ENDL; \
}

#define CLEAR() (void)iter;

void	scope_map(void)
{
	typedef ft::pair<std::string, std::string> type;
	ft::map<std::string, std::string> map;

	#define get(key) { \
		ft::map<std::string, std::string>::iterator it = map.find(key); \
		if (it == map.end()) std::cout << std::endl << "cannot retrieve " << key << std::endl; \
		else std::cout << "✅" << std::flush; \
	}
	
	map.insert(type("1", "one"));
	map.insert(type("2", "two"));
	map.insert(type("1", "second one"));
	map.insert(type("4", "four"));
	map.insert(type("3", "three"));
	map.insert(type("5", "five"));

	for (int i = 5; i++ < 100;)
	{
		std::stringstream ss;
		ss << i;
		map.insert(type(ss.str(), "+" + ss.str()));
	}
	for (int i = 200; i-- > 100;)
	{
		std::stringstream ss;
		ss << i;
		map.insert(type(ss.str(), "+" + ss.str()));
	}

	//map.debug();

	map.erase("0");
	map.erase("6");
	map.erase("0");
	map.erase("1");
	map.erase("1");
	map.erase("6");
	map.erase("3");
	map.erase("2");
	map.erase("5");
	map.erase("4");

	//map.debug();

	for (int i = 0; i++ < 200;)
	{
		std::stringstream ss;
		ss << i;
		get(ss.str());
	}

	for (int i = 5; i++ < 100;)
	{
		std::stringstream ss;
		ss << i;
		map.erase(ss.str());
	}

	//map.debug();

	for (ft::map<std::string, std::string>::iterator it = map.end(); it-- != map.begin();)
		std::cout << it->first << " = " << it->second << std::endl;

	for (int i = 200; i-- > 100;)
	{
		std::stringstream ss;
		ss << i;
		map.erase(ss.str());
	}

	//map.debug();
}

void	scope_int(void)
{
	typedef int type;
	NEW_TEST_SUITE()

	TEST(vec.insert(vec.end(), 1, 1))
	SLOW(
		TEST(vec.insert(vec.begin(), 1, 3))
	)
	TEST(vec.insert(vec.end(), 1, 2))
	TEST(vec.push_back(1))
	TEST(vec.push_back(*vec.begin()))
	TEST(vec.front())
	TEST(vec.pop_back())
	TEST(vec.push_back(3))
	TEST(vec.push_back(2))
	TEST(vec.reserve(5))
	TEST(vec.clear())
	TEST(vec.resize(1))
	TEST(vec.push_back(i))
	TEST(vec[i + 1] += 2)
	TEST(vec[i]++)
	TEST(vec.erase(vec.end() - 2))
	TEST(vec.push_back(i+3))
	TEST(vec.push_back(i+2))
	TEST(vec.push_back(i+1))
	TEST(vec.erase(vec.end() - 3, vec.end() - 1))
	SLOW(
		TEST(vec.insert(vec.begin() + 1, 7, i + 7))
		TEST(vec.erase(vec.begin() + 5))
		TEST(vec.erase(vec.begin(), vec.begin() + 3))
		TEST(vec.insert(vec.begin(), 200))
		TEST(vec.insert(vec.begin(), 2, 300))
	)
	int	arr [] = { 501,502,503 };
	TEST(vec.assign(5, 10))
	TEST(vec.assign(arr, arr+2))
	SLOW(
		TEST(vec.insert(vec.begin(), arr, arr + 3))
	)
	SLOW(NO_DEBUG(
		TEST(vec.resize(1000000))
		TEST(vec.resize(1000001))
	))
	CLEAR()
}

void scope_string(void)
{
	typedef std::string type;
	NEW_TEST_SUITE();

	std::string s = "Hello World";
	TEST(vec.push_back(s))
	CLEAR()
}

int	main(int argc, char **argv)
{
	(void)argc;
	(void)argv;
	scope_map();
	scope_int();
	scope_string();

	if (success)
		std::cout << ENDL << "\033[102;30m >>> Success <<< " << ENDL;
	else
		std::cout << ENDL << "\033[101;30m >>> Failure <<< " << ENDL;
	#ifdef __APPLE__
	if (argc <= 0)
		return (1);
	std::string cmd = "leaks " + std::string(argv[0]).substr(2);
	std::cout << cmd << ENDL;
	system(cmd.c_str());
	#endif
	return (0);
}
