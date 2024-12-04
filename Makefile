all:
	g++ -std=c++17 main.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp CommandSimpleMacro.cpp ExceptionHandler.cpp object.cpp scope.cpp -o MacroCommand
	g++ -std=c++17 test_macrocommand.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp CommandSimpleMacro.cpp ExceptionHandler.cpp object.cpp scope.cpp -lcppunit -o test_macrocommand
test:
	chmod +x MacroCommand
	./test_macrocommand
clean:
	$(RM) MacroCommand test_macrocommand
