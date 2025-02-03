all:
	g++ -std=c++17 main.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp istate.cpp movecommand.cpp producer.cpp -o state
	g++ -std=c++17 state_test.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp istate.cpp movecommand.cpp -lcppunit -o state_test
test:
	chmod +x state
	./state_test
clean:
	$(RM) state state_test
