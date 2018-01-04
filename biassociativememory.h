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
    int p;  //размер ассоциации
    int m;  //количество строк в матрице образа m*p=m
    int Q;  //количество пар образ - ассоциация, на которую обучена сеть
    double L;  //емкость сети
    mat W;  //веса первого слоя p*n
    mat W_; //веса второго слоя n*p

    vector<mat> Xk; //список образов
    vector<vec> Yk; //список ассоциаций

    string imgX;    //строка текущего образа
    string imgY;    //строка текущей ассоциации

    mat X_; //подаваемый искаженный образ

    void ReadFromFileImg_Ass(char* path);   //считать пару образ - ассоциацию
    mat ReadFromFileRecognImage(char* path);   //считать образ для распознавания
    double CountL();  //почитать L
    mat VecToMat(vec v);
    vec StringToVec(string str);
    string MatToImage(mat X);
    void PrintImg(string img);
    void AddX_Y(mat X, vec Y);  //добавить пару образ - ассоциация
};

#endif // BIASSOCIATIVEMEMORY_H
