all:
	g++ -std=c++17 main.cpp icommand.cpp imoving.cpp irotateble.cpp object.cpp -o main_adapter
	g++ -std=c++17 test_adapter.cpp icommand.cpp imoving.cpp irotateble.cpp object.cpp -lcppunit -o test_adapter

test:
	chmod +x main_adapter
	./test_adapter
clean:
	$(RM) main_adapter test_adapter
