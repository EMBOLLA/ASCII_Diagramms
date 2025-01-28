#include <iostream>
#include <vector>
#include <string>
#include "function.h"
#include <fstream>
#include <cmath>
#include <windows.h>



int main(int argc,char **argv){
  int choix,bfr,z;
  do{
    bfr=choix;
    std::cout << "\n=== ASCII DIAGRAMM GENERATOR ===\n";
    std::cout << "1. Desinner un histogramme"<<std::endl;
    std::cout << "2. Dessiner un diagramme à bande"<<std::endl;
    std::cout << "3. Dessiner des courbes de fonctions"<<std::endl;
    std::cout << "4. Sauvegarder le graphe pécédent et quitter"<<std::endl;
    std::cout << "5. Afficher l'aide "<<std::endl;
    std::cout << "Votre choix=> ";
    std::cin >> choix;

    switch (choix){
    case 1:{
      std::string file="data(1).txt";
      std::vector<inter> hist;
      readFile(file,hist);
      drawHistogram(hist);
     break;
    }
    case 2:{
     std::string file="data.txt";
     std::vector<Classe> BD;
     readFile(file,BD);
     drawBDiagram(BD);
     break;
    }
    case 3:{
      std::string file1="curve1.txt";
      std::string file2="curve2.txt";
      std::vector<Point> points1,points2;
      readFile(file1,points1);
      readFile(file2,points2);
      drawCurves(points1,points2);
     break;
    }
    case 4:{
      std::string file1="save.txt";
      switch (bfr){
       case 1:{
        std::string sortie="save.txt";
        std::string file="data(1).txt";
        std::vector<inter> hist;
        readFile(file,hist);
        saveHistogram(hist,sortie);
     break;
    }
    case 2:{
      std::string sortie="save.txt";
      std::string file="data.txt";
      std::vector<Classe> BD;
      readFile(file,BD);
      saveBDiagram(BD,sortie);
     break;
    }
    case 3:{
      std::string sortie="save.txt";
      std::string file1="curve1.txt";
      std::string file2="curve2.txt";
      std::vector<Point> points1,points2;
      readFile(file1,points1);
      readFile(file2,points2);
      saveCurves(points1,points2,sortie);
     break;
    }
       
      
      default:
      std::cout<<"Vous navez pas déssiné de graphe précédemment!"<<std::endl;
        break;
      }
     break;
    }
    default:{
      std::cout<<"Option invalide!!"<<std::endl;
     break;
    }

      
    }
  }while(choix!=4);
  return 0;
}