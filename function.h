#ifndef __FUNCTION_H__
#define __FUNCTION_H__
struct Point{
      double x;
      double y;
};
struct Classe {
    std::string label;
    int valeur;
};
struct inter{
      int debut;
      int fin;
      int effectif;
};


      void drawHistogram(std::vector<inter>& hist);
      void saveHistogram(std::vector<inter>& hist , std::string& sortie);
      void drawBDiagram(std::vector<Classe>& donnees);
      void saveBDiagram(std::vector<Classe>& donnees , std::string& sortie);
      void drawCurves(std::vector<Point>& points1 , std::vector<Point>& points2);
      void saveCurves(std::vector<Point>& points1 , std::vector<Point>& points2 , std::string& sortie);
      void readFile(std::string& filename , std::vector<Point>& points);
      void readFile(std::string& data, std::vector<Classe>& donnees);
      void readFile(std::string& data1, std::vector<inter>& hist);
#endif  