all:
	g++ -std=c++17 main.cpp \
		src/icommand.cpp \
		src/object.cpp \
		src/eventloop.cpp \
		src/exceptionhandler.cpp \
		src/istate.cpp \
		src/movecommand.cpp \
		src/producer.cpp -o state
	g++ -std=c++17 state_test.cpp \
		src/icommand.cpp \
		src/object.cpp \
		src/eventloop.cpp \
		src/exceptionhandler.cpp \
		src/istate.cpp \
		src/movecommand.cpp -lcppunit -o state_test
test:
	chmod +x state
	./state_test
clean:
	$(RM) state state_test
