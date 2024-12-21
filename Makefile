all:
	g++ -std=c++17 adapter.cpp -o adapter
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o main
test:
	chmod +x adapter
	./main
clean:
	$(RM) adapter main
