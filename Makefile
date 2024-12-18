all:
	g++ -std=c++17 main.cpp icommand.cpp object.cpp -o IoC
test:
	chmod +x IoC
	./test_IoC
clean:
	$(RM) IoC
