all:
	g++ -std=c++17 main.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp ExceptionHandler.cpp -o ExceptionHandler
test:
	chmod +x ExceptionHandler
clean:
	$(RM) ExceptionHandler
