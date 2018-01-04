#include "biassociativememory.h"

BiAssociativeMemory::BiAssociativeMemory()
{


    ReadFromFileImg_Ass("test.txt");

    PrintImg(imgX);

}

void BiAssociativeMemory::Educate()
{

}

void BiAssociativeMemory::Recognize()
{

}

void BiAssociativeMemory::PrintImg(string img)
{
    for (int i = 0; i < n; i+=p)
    {
        for (int j = 0; j < p; j++)
        {
            cout << img[i+j];
        }
        cout << endl;
    }
}

void BiAssociativeMemory::ReadFromFileImg_Ass(char* path)
{

    string buf, X_, Y_;

    ifstream file(path);
    if (!file.is_open())
    {
        cout << "The file can not be opened!\n";
        return;
    }
    file >> n;
    file >> p;

    if (n%p!=0)
    {
        cout << "Error! The file contains incorrect data!" << endl;
        return;
    }

    getline(file,  buf);

    for (int i = 0; i < buf.length() || i < n + p; i++)
    {
        if (buf[i]!= DOT && buf[i]!= GRID)
        {
            cout << "Error! The file contains incorrect data!" << endl;
            return;
        }
        if (i < n)
        {
            X_.push_back(buf[i]);
        }
        else
        {
            Y_.push_back(buf[i]);
        }

    }
    file.close();

    imgX = X_;
    imgY = Y_;

}

mat BiAssociativeMemory::VecToMat(vec v)
{
    mat X;

    return X;

}

vec BiAssociativeMemory::StringToVec(string str)
{
    vec Y;

    return Y;
}

string BiAssociativeMemory::MatToImage(mat X)
{
    string img;

    return img;

}

mat BiAssociativeMemory::ReadFromFileRecognImage(char* path)
{
    mat X;

    return X;
}

double BiAssociativeMemory::CountL()
{
    int m = min(n, p);
    return (m/(4*log(m)));
}

void BiAssociativeMemory::AddX_Y(mat X, vec Y)
{

}
