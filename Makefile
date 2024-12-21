all:
	g++ -std=c++17 adapter.cpp -o adapter
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o main_adapter
	g++ -std=c++17 test_adapter.cpp icommand.cpp object.cpp -o test_adapter
test:
	chmod +x main_adapter
	./adapter
	./test_adatper
clean:
	$(RM) main_adapter adatper test_adatper
