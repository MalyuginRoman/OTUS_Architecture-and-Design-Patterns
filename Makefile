all:
	g++ -std=c++17 adapter.cpp -o adapter
	g++ -std=c++17 test_adapter.cpp icommand.cpp object.cpp -o test_adapter

test:
	chmod +x adapter
	./test_adapter
clean:
	$(RM) adapter test_adapter
