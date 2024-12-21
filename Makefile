all:
	g++ -std=c++17 adapter.cpp -o adapter
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o main
	g++ -std=c++17 adapter.cpp main.cpp icommand.cpp object.cpp -o test
test:
	chmod +x adapter
	./main test
clean:
	$(RM) adapter main test
