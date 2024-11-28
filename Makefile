all:
	g++ -std=c++17 main.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp ExceptionHandler.cpp object.cpp -o MacroCommand
test:
	chmod +x MacroCommand
clean:
	$(RM) MacroCommand
