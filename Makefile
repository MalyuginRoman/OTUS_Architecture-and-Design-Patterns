all:
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o main
	g++ -std=c++17 adapter.cpp -o adapter
	g++ -std=c++17 test_adapter.cpp main.cpp adapter.cpp icommand.cpp object.cpp -o test_adapter
test:
	chmod +x main
	./adapter test_adatper
clean:
	$(RM) main adatper test_adatper
