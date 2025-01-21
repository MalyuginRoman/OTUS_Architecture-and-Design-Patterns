all:
	g++ -std=c++17 client.cpp -o client
	g++ -std=c++17 endpoint.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp -o endpoint
	g++ -std=c++17 endpoint_test.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp -lcppunit -o endpoint_test
test:
	chmod +x endpoint
	./endpoint_test
	./client
clean:
	$(RM) endpoint endpoint_test client
