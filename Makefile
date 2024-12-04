all:
	g++ -std=c++17 main.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp CommandSimpleMacro.cpp ExceptionHandler.cpp object.cpp scope.cpp -o IoC
	g++ -std=c++17 test_IoC.cpp CommandFuelBurn.cpp CommandFuelCheck.cpp CommandLoger.cpp CommandMove.cpp CommandQueue.cpp CommandRepeat.cpp CommandRotate.cpp CommandSimpleMacro.cpp ExceptionHandler.cpp object.cpp scope.cpp -lcppunit -o test_IoC
test:
	chmod +x IoC
	./test_IoC
clean:
	$(RM) IoC test_IoC
