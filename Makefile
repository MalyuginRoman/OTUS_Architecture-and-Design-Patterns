all:
	g++ -std=c++17 main.cpp icommand.cpp object.cpp imoving.cpp irotateble.cpp -o main_adapter
	g++ -std=c++17 test_adapter.cpp icommand.cpp object.cpp imoving.cpp irotateble.cpp -lcppunit -o test_adapter

test:
	chmod +x main_adapter
	./test_adapter
clean:
	$(RM) main_adapter test_adapter
