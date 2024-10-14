all:
	g++ -std=c++17 equation.cpp -o equation
clean:
	$(RM) equation
