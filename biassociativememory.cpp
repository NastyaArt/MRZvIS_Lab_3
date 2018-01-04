#include "biassociativememory.h"

BiAssociativeMemory::BiAssociativeMemory()
{

    int key;
    cout << "Use standart images(1) or your own(2)?\nChoose:";
    cin >> key;
    switch (key) {
        case 1:{
            n = 15;
            p = 3;
            m = n/p;
            Q = 3;
            cout << "\nQ = " << Q;
            cout << "\nn = " << n;
            cout << "\np = " << p << endl;
            for (int i = 0; i < Q; i++)
            {
                ReadFromFileImg_Ass("image" + to_string(i + 1) + ".txt");
                PrintImg(imgX);
                vecX = StringToVec(imgX);
                Xk.push_back(vecX);
                vecY = StringToVec(imgY);
                Yk.push_back(vecY);
            }
            break;
        }
        case 2:{
            string path;
            cout << "Input number of images:\n";
            cin >> Q;
            cout << "Input n:\n";
            cin >> n;
            cout << "Input p:\n";
            cin >> p;
            if (n%p!=0)
            {
                cout << "Error! The file contains incorrect data!" << endl;
                return;
            }
            m = n/p;
            for (int i = 0; i < Q; i++)
            {
                cout << "Input file name:\n";
                cin >> path;
                ReadFromFileImg_Ass(path);
                PrintImg(imgX);
                vecX = StringToVec(imgX);
                Xk.push_back(vecX);
                vecY = StringToVec(imgY);
                Yk.push_back(vecY);
            }
            break;
        }
        default:{
            printf("Error\n");
            return;
        }
    }

}

void BiAssociativeMemory::CountWeigths()
{

}

void BiAssociativeMemory::Educate()
{

}

void BiAssociativeMemory::Recognize()
{

}

void BiAssociativeMemory::PrintImg(string img)
{
    int k = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            cout << img[i+k];
            k+=m;
        }
        k = 0;
        cout << endl;
    }
    cout << endl;
}

void BiAssociativeMemory::ReadFromFileImg_Ass(string path)
{

    string buf, X_, Y_;
    int n_, p_;

    ifstream file(path);
    if (!file.is_open())
    {
        cout << "The file can not be opened!\n";
        return;
    }
    file >> n_;
    file >> p_;

    if (n_!=n || p_!=p)
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

Mat<int> BiAssociativeMemory::VecToMat(Col<int> v)
{
    Mat<int> X(m, p);


    int k = 0;
    for (int i = 0; i < p; i++)
    {
        for (int j = 0; j < m; j++)
        {
            X(j, i) = v(k);
            k++;
        }
    }

    return X;

}

Col<int> BiAssociativeMemory::StringToVec(string str)
{
    Col<int> Y(str.length());

    for (int i = 0; i < str.length(); i++)
    {
        if (str[i]==DOT)
            Y(i)= -1;
        else if (str[i]==GRID)
            Y(i)= 1;
    }

    return Y;
}

string BiAssociativeMemory::VecToString(Col<int> X)
{
    string img;

    for (int i = 0; i < X.size(); i++)
    {
        if (X(i)==-1)
            img.push_back(DOT);
        else if (X(i)==1)
            img.push_back(GRID);
    }

    return img;

}

Mat<int> BiAssociativeMemory::ReadFromFileRecognImage(string path)
{
    Mat<int> X;

    return X;
}

double BiAssociativeMemory::CountL()
{
    int m = min(n, p);
    return (m/(4*log(m)));
}

void BiAssociativeMemory::AddX_Y(Mat<int> X, Col<int> Y)
{

}
