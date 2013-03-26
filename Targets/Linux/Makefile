all: ./Obj/Case.o ./Obj/Config.o ./Obj/ContexteJeu.o ./Obj/Ennemi.o ./Obj/Fenetre.o ./Obj/IA.o ./Obj/Image.o ./Obj/Jeu.o ./Obj/Log.o ./Obj/Menu.o ./Obj/Moteur.o ./Obj/Mur.o ./Obj/Plateau.o ./Obj/Projectile.o ./Obj/Rect.o ./Obj/Surface.o ./Obj/Terrain.o ./Obj/Timer.o ./Obj/Tour.o ./Obj/VagueEnnemis.o ./Obj/Main.o
	g++ ./Obj/Case.o ./Obj/Config.o ./Obj/ContexteJeu.o ./Obj/Ennemi.o ./Obj/Fenetre.o ./Obj/IA.o ./Obj/Image.o ./Obj/Jeu.o ./Obj/Log.o ./Obj/Menu.o ./Obj/Moteur.o ./Obj/Mur.o ./Obj/Plateau.o ./Obj/Projectile.o ./Obj/Rect.o ./Obj/Surface.o ./Obj/Terrain.o ./Obj/Timer.o ./Obj/Tour.o ./Obj/VagueEnnemis.o ./Obj/Main.o -o TowerDefense -lSDL -lSDLmain -lSDL_gfx -lstdc++ -I../../libs

TD_CXXFLAGS =  -Wall -Wextra

./Obj/Case.o: ../../src/Case.cpp ../../src/Case.h
	g++ -c ../../src/Case.cpp -o ./Obj/Case.o -I../../libs $(TD_CXXFLAGS)
	 
./Obj/Config.o: ../../src/Config.cpp ../../src/Config.h
	g++ -c ../../src/Config.cpp -o ./Obj/Config.o -I../../libs $(TD_CXXFLAGS)

./Obj/ContexteJeu.o: ../../src/ContexteJeu.cpp ../../src/ContexteJeu.h
	g++ -c ../../src/ContexteJeu.cpp -o ./Obj/ContexteJeu.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Ennemi.o: ../../src/Ennemi.cpp ../../src/Ennemi.h
	g++ -c ../../src/Ennemi.cpp -o ./Obj/Ennemi.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Fenetre.o: ../../src/Fenetre.cpp ../../src/Fenetre.h
	g++ -c ../../src/Fenetre.cpp -o ./Obj/Fenetre.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/IA.o: ../../src/IA.cpp ../../src/IA.h
	g++ -c ../../src/IA.cpp -o ./Obj/IA.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Image.o: ../../src/Image.cpp ../../src/Image.h
	g++ -c ../../src/Image.cpp -o ./Obj/Image.o -I../../libs $(TD_CXXFLAGS)
		
./Obj/Jeu.o: ../../src/Jeu.cpp ../../src/Jeu.h
	g++ -c ../../src/Jeu.cpp -o ./Obj/Jeu.o -I../../libs $(TD_CXXFLAGS)

./Obj/Log.o: ../../src/Log.cpp ../../src/Log.h
	g++ -c ../../src/Log.cpp -o ./Obj/Log.o -I../../libs $(TD_CXXFLAGS)
   
./Obj/Menu.o: ../../src/Menu.cpp ../../src/Menu.h
	g++ -c ../../src/Menu.cpp -o ./Obj/Menu.o -I../../libs $(TD_CXXFLAGS)
   	   
./Obj/Moteur.o: ../../src/Moteur.cpp ../../src/Moteur.h
	g++ -c ../../src/Moteur.cpp -o ./Obj/Moteur.o -I../../libs $(TD_CXXFLAGS)

./Obj/Mur.o: ../../src/Mur.cpp ../../src/Mur.h
	g++ -c ../../src/Mur.cpp -o ./Obj/Mur.o -I../../libs $(TD_CXXFLAGS)
   
./Obj/Plateau.o: ../../src/Plateau.cpp ../../src/Plateau.h
	g++ -c ../../src/Plateau.cpp -o ./Obj/Plateau.o -I../../libs $(TD_CXXFLAGS)
   
./Obj/Projectile.o: ../../src/Projectile.cpp ../../src/Projectile.h
	g++ -c ../../src/Projectile.cpp -o ./Obj/Projectile.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Rect.o: ../../src/Rect.cpp ../../src/Rect.h
	g++ -c ../../src/Rect.cpp -o ./Obj/Rect.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Surface.o: ../../src/Surface.cpp ../../src/Surface.h
	g++ -c ../../src/Surface.cpp -o ./Obj/Surface.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Terrain.o: ../../src/Terrain.cpp ../../src/Terrain.h
	g++ -c ../../src/Terrain.cpp -o ./Obj/Terrain.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Timer.o: ../../src/Timer.cpp ../../src/Timer.h
	g++ -c ../../src/Timer.cpp -o ./Obj/Timer.o -I../../libs $(TD_CXXFLAGS)
	
./Obj/Tour.o: ../../src/Tour.cpp ../../src/Tour.h
	g++ -c ../../src/Tour.cpp -o ./Obj/Tour.o -I../../libs $(TD_CXXFLAGS)
   
./Obj/VagueEnnemis.o: ../../src/VagueEnnemis.cpp ../../src/VagueEnnemis.h
	g++ -c ../../src/VagueEnnemis.cpp -o ./Obj/VagueEnnemis.o -I../../libs $(TD_CXXFLAGS)

./Obj/Main.o: ../../src/Main.cpp
	g++ -c ../../src/Main.cpp -o ./Obj/Main.o -I../../libs $(TD_CXXFLAGS)
   
clean:
	rm ./Obj/*.o
