all:
	g++ -std=c++17 main.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp ExceptionHandler.cpp object.cpp -o MacroCommand
	//g++ -std=c++17 test_exception.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp ExceptionHandler.cpp object.cpp -lcppunit -o test_exception
test:
	chmod +x MacroCommand
	//./test_exception
clean:
	$(RM) MacroCommand //test_exception
