all:
	g++ -std=c++17 queue.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp -o queue
	g++ -std=c++17 queue_test.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp -lcppunit -o queue_test
test:
	chmod +x queue
	./queue_test
clean:
	$(RM) queue queue_test
