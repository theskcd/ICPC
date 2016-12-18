all:
	$(CXX) -pthread -std=c++11 -Wall -Wextra example.cpp -o example

test:
	 ./example || exit 1