all:
	g++ -std=c++17 main.cpp icommand.cpp object.cpp eventloop.cpp exceptionhandler.cpp istate.cpp movecommand.cpp producer.cpp -o state
test:
	chmod +x state
clean:
	$(RM) state
