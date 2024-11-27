all:
	g++ -std=c++17 main.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp ExceptionHandler.cpp -o ExceptionHandler
	g++ -std=c++17 test_exception.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp ExceptionHandler.cpp -lcppunit -o test_exception
test:
	chmod +x ExceptionHandler
	./test_exception
clean:
	$(RM) ExceptionHandler test_exception
