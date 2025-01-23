all:
	g++ -std=c++17 game_server.cpp eventloop.cpp exceptionhandler.cpp icommand.cpp object.cpp producer.cpp -o game_server
	g++ -std=c++17 auto_server.cpp -o auto_server
	g++ -std=c++17 client.cpp -lcppunit -o client
test:
	chmod +x game_server
	./auto_server
	./client
clean:
	$(RM) game_server auto_server client
