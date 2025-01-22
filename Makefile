all:
	g++ -std=c++17 client.cpp -o client
	g++ -std=c++17 server.cpp -lcppunit -o server
test:
	chmod +x client
	./server
clean:
	$(RM) client server
