#include <iostream>
#include <vector>
#include <string>
#include "function.h"
#include <fstream>
#include <iomanip>

void readFile(std::string& data , std::vector<Point>& points){
    std::ifstream fichier(data);
    if(!fichier){
      std::cerr <<"Impossible d'ouvrir le fichier "<<data<<std::endl;
      return;
    }
    double x,y;
    while(fichier >>x>>y){
        points.push_back({x,y});
    }
    fichier.close(); 
}

void readFile(std::string& data, std::vector<Classe>& donnees) {
    std::ifstream fichier(data);
    if (!fichier) {
        std::cerr << "Impossible d'ouvrir le fichier " <<data<< std::endl;
        return;
    }
    std::string label;
    int valeur;
    while (fichier >> label >> valeur) {
        donnees.push_back({label, valeur});
    }
    fichier.close();

}

void readFile(std::string& data1, std::vector<inter>& hist) {
    std::ifstream fichier(data1);
    if (!fichier) {
        std::cerr << "Impossible d'ouvrir le fichier !" <<data1<< std::endl;
        return;
    }

    std::string intervalle;
    int frequence;
    while (fichier >> intervalle >> frequence) {
        size_t tiret = intervalle.find('-');
        int debut = std::stoi(intervalle.substr(0, tiret));
        int fin = std::stoi(intervalle.substr(tiret + 1));
        hist.push_back({debut, fin, frequence});
    }
    fichier.close();
}

void drawHistogram(std::vector<inter>& hist) {
    const int largeurMax = 50;
    int max= 0;
    for (auto& data : hist) {
        if (data.effectif> max) max= data.effectif;
    }
    for (auto& data : hist) {
        int amplitude = data.fin - data.debut;  // Nombre de classes dans l'intervalle
        int fpc = data.effectif / amplitude;

        for (int valeur = data.debut; valeur < data.fin; ++valeur) {
            std::cout << std::setw(2) << valeur << " | ";
            int longueurBarre = static_cast<int>((static_cast<double>(fpc)/max)*largeurMax);
            for (int i = 0; i < longueurBarre; ++i) {
                std::cout << '#';
            }
            std::cout<< " (" <<fpc<< ")" << std::endl;
        }
    }
     std::cout <<R"(
 _   _  ____  ___  ____  _____  ___  ____    __    __  __  __  __  ____ 
( )_( )(_  _)/ __)(_  _)(  _  )/ __)(  _ \  /__\  (  \/  )(  \/  )( ___)
 ) _ (  _)(_ \__ \  )(   )(_)(( (_-. )   / /(__)\  )    (  )    (  )__) 
(_) (_)(____)(___/ (__) (_____)\___/(_)\_)(__)(__)(_/\/\_)(_/\/\_)(____)
)"<<std::endl;
}


void saveHistogram(std::vector<inter>& hist , std::string& sortie) {
    std::ofstream fichier(sortie);
    if (!fichier) {
        std::cerr << "Impossible de créerle fichier de sauvegarde !" <<sortie<< std::endl;
        return;
    }
    const int largeurMax = 50;
    int max= 0;
    for (auto& data : hist) {
        if (data.effectif> max) max= data.effectif;
    }
    for (auto& data : hist) {
        int amplitude = data.fin-data.debut;  // Nombre de classes dans l'intervalle
        int fpc = data.effectif/amplitude;

        for (int valeur = data.debut; valeur < data.fin; ++valeur) {
            std::cout << std::setw(2) << valeur << " | ";
            int longueurBarre = static_cast<int>((static_cast<double>(fpc)/max)*largeurMax);
            for (int i = 0; i < longueurBarre; ++i) {
                fichier << '#';
            }
            fichier << " (" <<fpc<< ")" << std::endl;
        }
    }
    fichier <<R"(
 _   _  ____  ___  ____  _____  ___  ____    __    __  __  __  __  ____ 
( )_( )(_  _)/ __)(_  _)(  _  )/ __)(  _ \  /__\  (  \/  )(  \/  )( ___)
 ) _ (  _)(_ \__ \  )(   )(_)(( (_-. )   / /(__)\  )    (  )    (  )__) 
(_) (_)(____)(___/ (__) (_____)\___/(_)\_)(__)(__)(_/\/\_)(_/\/\_)(____)
)"<<std::endl;
}



void drawCurves(const std::vector<Point>& points1 , const  std::vector<Point>& points2){
 const int longueur=80;
  const int hauteur=20;

    double minX = std::min(points1.front().x, points2.front().x);
    double maxX = std::max(points1.front().x, points2.front().x);
    double minY = std::min(points1.front().y, points2.front().y);
    double maxY = std::max(points1.front().y, points2.front().y);

    // Trouver les min et max pour les deux ensembles de points
    for (auto& point : points1) {
        if (point.x<minX) minX=point.x;
        if (point.x>maxX) maxX=point.x;
        if (point.y<minY) minY=point.y;
        if (point.y>maxY) maxY=point.y;
    }
    for (auto& point : points2) {
        if (point.x<minX) minX=point.x;
        if (point.x>maxX) maxX=point.x;
        if (point.y<minY) minY=point.y;
        if (point.y>maxY) maxY=point.y;
    }

   
    for (int i=0; i<=hauteur; i++) {
        double y = minY + (hauteur - i) * (maxY - minY) / hauteur;
        std::cout << std::setw(6) << std::setprecision(2) << std::fixed << y << " | ";

        for (int j = 0; j <= longueur; ++j) {
            double x = minX + j * (maxX - minX)/longueur;

            bool estPoint1 = false, estPoint2 = false;
            for (auto& point : points1) {
                if (std::abs(point.x - x) < 0.1 && std::abs(point.y -y) <0.1) {
                    estPoint1 = true;
                    break;
                }
            }
            for (auto& point : points2) {
                if (std::abs(point.x - x) < 0.1 && std::abs(point.y-y) < 0.1) {
                    estPoint2 = true;
                    break;
                }
            }

            if (estPoint1 && estPoint2) {
                std::cout << 'X';  // Intersection des deux courbes
            } else if (estPoint1) {
                std::cout << '*';  // Courbe 1
            } else if (estPoint2) {
                std::cout << '#';  // Courbe 2
            } else if (std::abs(x)<0.1 && std::abs(y)<0.1) {
                std::cout << '+';
            } else if (std::abs(x)< 0.1) {
                std::cout << '|';
            } else if (std::abs(y)< 0.1) {
                std::cout << '-';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << std::endl;
    }

   
    std::cout << "      ";
    for (int i=0; i<=longueur; i++) {
        double x = minX+i*(maxX-minX)/longueur;
        if (i%10==0) {
            std::cout << std::setw(4) << std::setprecision(1) << std::fixed << x;
        } else {
            std::cout << ' ';
        }
    }
    std::cout << std::endl;
    std::cout<<R"(
  ___  __   _  _  ____  ____  ____  ____      ____  ____  ____      ____  __   __ _   ___  ____  __  __   __ _  ____       __    ____  ____    ____       
 / __)/  \ / )( \(  _ \(  _ \(  __)/ ___)    (    \(  __)/ ___)    (  __)/  \ (  ( \ / __)(_  _)(  )/  \ (  ( \/ ___)     /  \  (  __)(_  _)  (___ \      
( (__(  O )) \/ ( )   / ) _ ( ) _) \___ \     ) D  )) _) \___ \     ) _)(  O )/    /( (__   )(   )((  O )/    /\___ \    (_/ /   ) _)   )(     / __/      
 \___)\__/ \____/(__\_)(____/(____)(____/    (____/(____)(____/    (__)  \__/ \_)__) \___) (__) (__)\__/ \_)__)(____/     (__)  (____) (__)   (____)      
)"<<std::endl;
}

void saveCurves(const std::vector<Point>& points1 , const  std::vector<Point>& points2 , std::string& sortie){
   
   std::ofstream fichier(sortie);
    if (!fichier) {
        std::cerr << "Impossible de créer le fichier de sauvegarde !" <<sortie<< std::endl;
        return;
    }
    const int longueur=80;
    const int hauteur=20;

    double minX = std::min(points1.front().x, points2.front().x);
    double maxX = std::max(points1.front().x, points2.front().x);
    double minY = std::min(points1.front().y, points2.front().y);
    double maxY = std::max(points1.front().y, points2.front().y);

    // Trouver les min et max pour les deux ensembles de points
    for (auto& point : points1) {
        if (point.x<minX) minX=point.x;
        if (point.x>maxX) maxX=point.x;
        if (point.y<minY) minY=point.y;
        if (point.y>maxY) maxY=point.y;
    }
    for (auto& point : points2) {
        if (point.x<minX) minX=point.x;
        if (point.x>maxX) maxX=point.x;
        if (point.y<minY) minY=point.y;
        if (point.y>maxY) maxY=point.y;
    }

   
    for (int i=0; i<=hauteur; i++) {
        double y = minY + (hauteur - i) * (maxY - minY) / hauteur;
        fichier << std::setw(6) << std::setprecision(2) << std::fixed << y << " | ";

        for (int j = 0; j <= longueur; ++j) {
            double x = minX + j * (maxX - minX)/longueur;

            bool estPoint1 = false, estPoint2 = false;
            for (auto& point : points1) {
                if (std::abs(point.x - x) < 0.1 && std::abs(point.y -y) <0.1) {
                    estPoint1 = true;
                    break;
                }
            }
            for (auto& point : points2) {
                if (std::abs(point.x - x) < 0.1 && std::abs(point.y-y) < 0.1) {
                    estPoint2 = true;
                    break;
                }
            }

            if (estPoint1 && estPoint2) {
                fichier << 'X';  // Intersection des deux courbes
            } else if (estPoint1) {
                fichier << '*';  // Courbe 1
            } else if (estPoint2) {
                fichier << '#';  // Courbe 2
            } else if (std::abs(x)<0.1 && std::abs(y)<0.1) {
                fichier << '+';
            } else if (std::abs(x)< 0.1) {
                fichier << '|';
            } else if (std::abs(y)< 0.1) {
                fichier << '-';
            } else {
                fichier << ' ';
            }
        }
        fichier << std::endl;
    }

   
    fichier << "      ";
    for (int i=0; i<=longueur; i++) {
        double x = minX+i*(maxX-minX)/longueur;
        if (i%10==0) {
            fichier<< std::setw(4) << std::setprecision(1) << std::fixed << x;
        } else {
            fichier << ' ';
        }
    }
    fichier << std::endl;
    fichier<<R"(
  ___  __   _  _  ____  ____  ____  ____      ____  ____  ____      ____  __   __ _   ___  ____  __  __   __ _  ____       __    ____  ____    ____       
 / __)/  \ / )( \(  _ \(  _ \(  __)/ ___)    (    \(  __)/ ___)    (  __)/  \ (  ( \ / __)(_  _)(  )/  \ (  ( \/ ___)     /  \  (  __)(_  _)  (___ \      
( (__(  O )) \/ ( )   / ) _ ( ) _) \___ \     ) D  )) _) \___ \     ) _)(  O )/    /( (__   )(   )((  O )/    /\___ \    (_/ /   ) _)   )(     / __/      
 \___)\__/ \____/(__\_)(____/(____)(____/    (____/(____)(____/    (__)  \__/ \_)__) \___) (__) (__)\__/ \_)__)(____/     (__)  (____) (__)   (____)      
)"<<std::endl;
}


void drawBDiagram(const std::vector<Classe>& donnees) {
    const int largeurMax = 50; // Largeur maximale d'une barre

    // Trouver la valeur maximale pour la normalisation
    int vmax = 0;
    for (auto& data : donnees) {
        if (data.valeur > vmax) vmax = data.valeur;
    }

    // Afficher le diagramme
    for ( auto& data : donnees) {
        std::cout << std::setw(10) << std::left << data.label << " | ";

        int longueurBarre = static_cast<int>((static_cast<double>(data.valeur) / vmax) * largeurMax);
        for (int i = 0; i < longueurBarre; ++i) {
            std::cout << '=';
        }
        std::cout << " (" << data.valeur << ")" << std::endl;
       
    }
     std::cout<<R"(
 ____  ____    __    ___  ____    __    __  __  __  __  ____      __      ____    __    _  _  ____  ____ 
(  _ \(_  _)  /__\  / __)(  _ \  /__\  (  \/  )(  \/  )( ___)    /__\    (  _ \  /__\  ( \( )(  _ \( ___)
 )(_) )_)(_  /(__)\( (_-. )   / /(__)\  )    (  )    (  )__)    /(__)\    ) _ < /(__)\  )  (  )(_) ))__) 
(____/(____)(__)(__)\___/(_)\_)(__)(__)(_/\/\_)(_/\/\_)(____)  (__)(__)  (____/(__)(__)(_)\_)(____/(____)
)"<<std::endl;
}



void saveBDiagram(const std::vector<Classe>& donnees , std::string& sortie) {

    std::ofstream fichier(sortie);
    if (!fichier) {
        std::cerr << "Impossible de créer le fichier de sauvegarde !" <<sortie<< std::endl;
        return;
    }
    const int largeurMax = 50; // Largeur maximale d'une barre

    // Trouver la valeur maximale pour la normalisation
    int vmax = 0;
    for (auto& data : donnees) {
        if (data.valeur > vmax) vmax = data.valeur;
    }

    // Afficher le diagramme
    for ( auto& data : donnees) {
        fichier << std::setw(10) << std::left << data.label << " | ";

        int longueurBarre = static_cast<int>((static_cast<double>(data.valeur) / vmax) * largeurMax);
        for (int i = 0; i < longueurBarre; ++i) {
            fichier << '=';
        }
        fichier << " (" << data.valeur << ")" << std::endl;
       
    }
     fichier<<R"(
 ____  ____    __    ___  ____    __    __  __  __  __  ____      __      ____    __    _  _  ____  ____ 
(  _ \(_  _)  /__\  / __)(  _ \  /__\  (  \/  )(  \/  )( ___)    /__\    (  _ \  /__\  ( \( )(  _ \( ___)
 )(_) )_)(_  /(__)\( (_-. )   / /(__)\  )    (  )    (  )__)    /(__)\    ) _ < /(__)\  )  (  )(_) ))__) 
(____/(____)(__)(__)\___/(_)\_)(__)(__)(_/\/\_)(_/\/\_)(____)  (__)(__)  (____/(__)(__)(_)\_)(____/(____)
)"<<std::endl;
}