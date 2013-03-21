all: ./Obj/Case.o ./Obj/Config.o ./Obj/ContexteJeu.o ./Obj/Ennemi.o ./Obj/Fenetre.o ./Obj/IA.o ./Obj/Image.o ./Obj/Jeu.o ./Obj/Log.o ./Obj/Menu.o ./Obj/Moteur.o ./Obj/Mur.o ./Obj/Plateau.o ./Obj/Projectile.o ./Obj/Rect.o ./Obj/Surface.o ./Obj/Terrain.o ./Obj/Timer.o ./Obj/Tour.o ./Obj/VagueEnnemis.o ./Obj/Main.o
	g++ ./Obj/Case.o ./Obj/Config.o ./Obj/ContexteJeu.o ./Obj/Ennemi.o ./Obj/Fenetre.o ./Obj/IA.o ./Obj/Image.o ./Obj/Jeu.o ./Obj/Log.o ./Obj/Menu.o ./Obj/Moteur.o ./Obj/Mur.o ./Obj/Plateau.o ./Obj/Projectile.o ./Obj/Rect.o ./Obj/Surface.o ./Obj/Terrain.o ./Obj/Timer.o ./Obj/Tour.o ./Obj/VagueEnnemis.o ./Obj/Main.o -o TowerDefense -lSDL -lSDLmain -lSDL_gfx -lstdc++ -I../../libs
	
./Obj/Case.o: ../../src/Case.cpp ../../src/Case.h
	g++ -c ../../src/Case.cpp -o ./Obj/Case.o -I../../libs
	 
./Obj/Config.o: ../../src/Config.cpp ../../src/Config.h
	g++ -c ../../src/Config.cpp -o ./Obj/Config.o -I../../libs

./Obj/ContexteJeu.o: ../../src/ContexteJeu.cpp ../../src/ContexteJeu.h
	g++ -c ../../src/ContexteJeu.cpp -o ./Obj/ContexteJeu.o -I../../libs
	
./Obj/Ennemi.o: ../../src/Ennemi.cpp ../../src/Ennemi.h
	g++ -c ../../src/Ennemi.cpp -o ./Obj/Ennemi.o -I../../libs
	
./Obj/Fenetre.o: ../../src/Fenetre.cpp ../../src/Fenetre.h
	g++ -c ../../src/Fenetre.cpp -o ./Obj/Fenetre.o -I../../libs
	
./Obj/IA.o: ../../src/IA.cpp ../../src/IA.h
	g++ -c ../../src/IA.cpp -o ./Obj/IA.o -I../../libs
	
./Obj/Image.o: ../../src/Image.cpp ../../src/Image.h
	g++ -c ../../src/Image.cpp -o ./Obj/Image.o -I../../libs
		
./Obj/Jeu.o: ../../src/Jeu.cpp ../../src/Jeu.h
	g++ -c ../../src/Jeu.cpp -o ./Obj/Jeu.o -I../../libs

./Obj/Log.o: ../../src/Log.cpp ../../src/Log.h
	g++ -c ../../src/Log.cpp -o ./Obj/Log.o -I../../libs
   
./Obj/Menu.o: ../../src/Menu.cpp ../../src/Menu.h
	g++ -c ../../src/Menu.cpp -o ./Obj/Menu.o -I../../libs
   	   
./Obj/Moteur.o: ../../src/Moteur.cpp ../../src/Moteur.h
	g++ -c ../../src/Moteur.cpp -o ./Obj/Moteur.o -I../../libs

./Obj/Mur.o: ../../src/Mur.cpp ../../src/Mur.h
	g++ -c ../../src/Mur.cpp -o ./Obj/Mur.o -I../../libs
   
./Obj/Plateau.o: ../../src/Plateau.cpp ../../src/Plateau.h
	g++ -c ../../src/Plateau.cpp -o ./Obj/Plateau.o -I../../libs
   
./Obj/Projectile.o: ../../src/Projectile.cpp ../../src/Projectile.h
	g++ -c ../../src/Projectile.cpp -o ./Obj/Projectile.o -I../../libs
	
./Obj/Rect.o: ../../src/Rect.cpp ../../src/Rect.h
	g++ -c ../../src/Rect.cpp -o ./Obj/Rect.o -I../../libs
	
./Obj/Surface.o: ../../src/Surface.cpp ../../src/Surface.h
	g++ -c ../../src/Surface.cpp -o ./Obj/Surface.o -I../../libs
	
./Obj/Terrain.o: ../../src/Terrain.cpp ../../src/Terrain.h
	g++ -c ../../src/Terrain.cpp -o ./Obj/Terrain.o -I../../libs
	
./Obj/Timer.o: ../../src/Timer.cpp ../../src/Timer.h
	g++ -c ../../src/Timer.cpp -o ./Obj/Timer.o -I../../libs
	
./Obj/Tour.o: ../../src/Tour.cpp ../../src/Tour.h
	g++ -c ../../src/Tour.cpp -o ./Obj/Tour.o -I../../libs
   
./Obj/VagueEnnemis.o: ../../src/VagueEnnemis.cpp ../../src/VagueEnnemis.h
	g++ -c ../../src/VagueEnnemis.cpp -o ./Obj/VagueEnnemis.o -I../../libs

./Obj/Main.o: ../../src/Main.cpp
	g++ -c ../../src/Main.cpp -o ./Obj/Main.o -I../../libs
   
clean:
	rm ./Obj/*.o
