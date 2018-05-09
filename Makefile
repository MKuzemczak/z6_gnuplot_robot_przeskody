#
#  To sa opcje dla kompilacji
#
CXXFLAGS=-g -Iinc -Wall -pedantic -std=c++11

TRGDIR=/tmp/rysowanie_3D

__start__: ./rysowanie_3D
	./rysowanie_3D

./rysowanie_3D: obj obj/main.o obj/lacze_do_gnuplota.o obj/ObiektGraficzny.o obj/Robot.o\
				obj/Path.o obj/Scene.o
	g++ -Wall -pedantic -std=c++11 -o ./rysowanie_3D obj/main.o\
                        obj/lacze_do_gnuplota.o obj/ObiektGraficzny.o obj/Robot.o\
						obj/Path.o obj/Scene.o


obj:
	mkdir -p obj

obj/Scene.o: inc/Scene.hh src/Scene.cpp 
	g++ -c ${CXXFLAGS} -o obj/Scene.o src/Scene.cpp

obj/ObiektGraficzny.o: inc/ObiektGraficzny.hh src/ObiektGraficzny.cpp inc/Wektor3D.hh\
						inc/Vertices.hh
	g++ -c ${CXXFLAGS} -o obj/ObiektGraficzny.o src/ObiektGraficzny.cpp

obj/Robot.o: inc/Robot.hh src/Robot.cpp inc/ObiektGraficzny.hh
	g++ -c ${CXXFLAGS} -o obj/Robot.o src/Robot.cpp

obj/Path.o: inc/Path.hh src/Path.cpp inc/ObiektGraficzny.hh
	g++ -c ${CXXFLAGS} -o obj/Path.o src/Path.cpp

obj/lacze_do_gnuplota.o: inc/lacze_do_gnuplota.hh src/lacze_do_gnuplota.cpp
	g++ -c ${CXXFLAGS} -o obj/lacze_do_gnuplota.o src/lacze_do_gnuplota.cpp

obj/main.o: src/main.cpp inc/lacze_do_gnuplota.hh
	g++ -c ${CXXFLAGS} -o obj/main.o src/main.cpp

clean:
	rm -f obj/*.o ./rysowanie_3D
