all:
	g++ main.cpp dominios.cpp comandos.cpp testes.cpp controladoras.cpp "./includes/sqlite3.o" -o teste
	./teste