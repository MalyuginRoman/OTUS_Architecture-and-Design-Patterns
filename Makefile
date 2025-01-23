all:
	g++ -std=c++17 server.cpp eventloop.cpp exceptionhandler.cpp icommand.cpp object.cpp producer.cpp -o server
	g++ -std=c++17 client.cpp -lcppunit -o client
test:
	chmod +x server
	./client
clean:
	$(RM) server client
