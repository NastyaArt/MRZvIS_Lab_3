/**
 *    Автор: Анастасия Артемчук
 */

#ifndef BIASSOCIATIVEMEMORY_H
#define BIASSOCIATIVEMEMORY_H

#include <fstream>
#include <iostream>
#include <armadillo>
/**
 *    Armadillo - библиотека линейной алгебры
 *    Авторы: Dr Ryan Curtin
 *            Dr Conrad Sanderson
 */

using namespace std;
using namespace arma;

#define DOT '.'
#define GRID '#'

class BiAssociativeMemory
{
public:
    BiAssociativeMemory();
    void Educate();
    void Recognize();

private:
    int n;  //размер образа
    int p;  //размер ассоциации и количество рядов в матрице образа
    int m;  //количество строк в матрице образа m*p=n
    int Q;  //количество пар образ - ассоциация, на которую обучена сеть
    double L;  //емкость сети
    Mat<int> W;  //веса первого слоя p*n
    Mat<int> W_; //веса второго слоя n*p

    vector<Col<int>> Xk; //список образов
    vector<Col<int>> Yk; //список ассоциаций

    string imgX;    //строка текущего образа
    string imgY;    //строка текущей ассоциации

    Col<int> vecX;    //строка текущего образа
    Col<int> vecY;    //строка текущей ассоциации

    string imgX_;   //строка подаваемого образа
    Col<int> vecX_; //подаваемый искаженный образ

    void ReadFromFileImg_Ass(string path);   //считать пару образ - ассоциацию
    Mat<int> ReadFromFileRecognImage(string path);   //считать образ для распознавания
    double CountL();  //почитать L
    Mat<int> VecToMat(Col<int> v);
    Col<int> StringToVec(string str);
    string VecToString(Col<int> X);
    void PrintImg(string img);
    void CountWeigths();
    void AddX_Y(Mat<int> X, Col<int> Y);  //добавить пару образ - ассоциация
};

#endif // BIASSOCIATIVEMEMORY_H
