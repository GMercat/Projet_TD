TowerDef2: ../Obj/Jeu.o ../Obj/Moteur.o ../Obj/IA.o ../Obj/Timer.o ../Obj/Plateau.o ../Obj/Menu.o ../Obj/Case.o ../Obj/Tour.o ../Obj/Ennemi.o ../Obj/Projectile.o ../Obj/Config.o ../Obj/Image.o ../Obj/Main.o
	g++ ../Obj/Jeu.o ../Obj/Moteur.o ../Obj/IA.o ../Obj/Timer.o ../Obj/Plateau.o ../Obj/Menu.o ../Obj/Case.o ../Obj/Tour.o ../Obj/Ennemi.o ../Obj/Projectile.o ../Obj/Config.o ../Obj/Image.o ../Obj/Main.o -o TowerDef -lSDL -lSDLmain -lstdc++ -I./libs
   
../Obj/Jeu.o: ../src/Jeu.cpp ../include/Jeu.h
	g++ -c ../src/Jeu.cpp -o ../Obj/Jeu.o -lSDL -lSDLmain -lstdc++ -I../libs
   
../Obj/Moteur.o: ../src/Moteur.cpp ../include/Moteur.h
	g++ -c ../src/Moteur.cpp -o ../Obj/Moteur.o -lSDL -lSDLmain -lstdc++ -I../libs

../Obj/IA.o: ../src/IA.cpp ../include/IA.h
	g++ -c ../src/IA.cpp -o ../Obj/IA.o -lSDL -lSDLmain -lstdc++ -I../libs
   
../Obj/Timer.o: ../src/Timer.cpp ../include/Timer.h
	g++ -c ../src/Timer.cpp -o ../Obj/Timer.o -lSDL -lSDLmain -lstdc++ -I../libs
   
../Obj/Plateau.o: ../src/Plateau.cpp ../include/Plateau.h
	g++ -c ../src/Plateau.cpp -o ../Obj/Plateau.o -lSDL -lSDLmain -lstdc++ -I../libs
   
../Obj/Menu.o: ../src/Menu.cpp ../include/Menu.h
	g++ -c ../src/Menu.cpp -o ../Obj/Menu.o -lSDL -lSDLmain -lstdc++ -I../libs
   
../Obj/Case.o: ../src/Case.cpp ../include/Case.h
	g++ -c ../src/Case.cpp -o ../Obj/Case.o -lSDL -lSDLmain -lstdc++ -I../libs
	
../Obj/Tour.o: ../src/Tour.cpp ../include/Tour.h
	g++ -c ../src/Tour.cpp -o ../Obj/Tour.o -lSDL -lSDLmain -lstdc++ -I../libs
   
../Obj/Ennemi.o: ../src/Ennemi.cpp ../include/Ennemi.h
	g++ -c ../src/Ennemi.cpp -o ../Obj/Ennemi.o -lSDL -lSDLmain -lstdc++ -I../libs

../Obj/Projectile.o: ../src/Projectile.cpp ../include/Projectile.h
	g++ -c ../src/Projectile.cpp -o ../Obj/Projectile.o -lSDL -lSDLmain -lstdc++ -I../libs
	
../Obj/Config.o: ../src/Config.cpp ../include/Config.h
	g++ -c ../src/Config.cpp -o ../Obj/Config.o -lSDL -lSDLmain -lstdc++ -I../libs
	
../Obj/Image.o: ../src/Image.cpp ../include/Image.h
	g++ -c ../src/Image.cpp -o ../Obj/Image.o -lSDL -lSDLmain -lstdc++ -I../libs

../Obj/Main.o: ../src/Main.cpp
	g++ -c ../src/Main.cpp -o ../Obj/Main.o -lSDL -lSDLmain -lstdc++ -I../libs
   
clean:
	rm ../Obj/*.o
