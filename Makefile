all:
	g++ -std=c++17 main.cpp \
		src/com/icommand.cpp \
		src/object.cpp \
		src/eventloop.cpp \
		src/exceptionhandler.cpp \
		src/istate.cpp \
		src/com/movecommand.cpp \
		src/producer.cpp -o state
	g++ -std=c++17 state_test.cpp \
		src/com/icommand.cpp \
		src/object.cpp \
		src/eventloop.cpp \
		src/exceptionhandler.cpp \
		src/istate.cpp \
		src/com/movecommand.cpp -lcppunit -o state_test
test:
	chmod +x state
	./state_test
clean:
	$(RM) state state_test
