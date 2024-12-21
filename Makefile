all:
	g++ -std=c++17 adapter.cpp -o adapter
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o main
	g++ -std=c++17 adapter.cpp main.cpp icommand.cpp object.cpp -o test_adapter
test:
	chmod +x main
	./adapter test_adatper
clean:
	$(RM) test_adatper main test
