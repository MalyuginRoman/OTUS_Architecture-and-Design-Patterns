all:
	g++ -std=c++17 test_adapter.cpp adapter.cpp icommand.cpp object.cpp -o test_adapter
test:
	chmod +x test_adapter
clean:
	$(RM) test_adapter
