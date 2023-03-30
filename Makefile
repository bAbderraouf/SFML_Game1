All : compile link

test : compile link run

compile : 
	g++ -c *.cpp

link :
	g++ *.o -static -o main -lsfml-graphics -lsfml-window -lsfml-system 

clean :
	rm *.o
	rm *.exe
	clear

run :
	main.exe