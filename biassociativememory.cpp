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
                cout << "\nImage " << i + 1 << ":" << endl;
                PrintImg(imgX);
                cout << "Association " << i + 1 << ":" << endl;
                cout << imgY << endl;
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
                cout << "\nImage " << i + 1 << ":" << endl;
                PrintImg(imgX);
                cout << "Association " << i + 1 << ":" << endl;
                cout << imgY << endl;
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

    CountWeigths();

}

void BiAssociativeMemory::CountWeigths()
{
    Mat<int> A(n, p, fill::zeros);

    for (int i = 0; i < Q; i++)
    {
        A += Xk[i]*Yk[i].t();
    }

    W = A;
    W_ = A.t();
}

void BiAssociativeMemory::Recognize()
{
    int key;
    cout << "Choose distorted image: \n"
            << "1. Distorted image for image 1\n"
            << "2. Distorted image for image 2\n"
            << "3. Distorted image for image 3\n"
            << "4. Original image 1\n"
            << "5. Original image 2\n"
            << "6. Original image 3\n"
            << "7. Use your own distorted image\nChoose:";
    cin >> key;
    string path;
    switch (key) {
        case 1:{
            path = "bad_image1.txt";
            break;
        }
        case 2:{
            path = "bad_image2.txt";
            break;
        }
        case 3:{
            path = "bad_image3.txt";
            break;
        }
        case 4:{
            path = "good_image1.txt";
            break;
        }
        case 5:{
            path = "good_image2.txt";
            break;
        }
        case 6:{
            path = "good_image3.txt";
            break;
        }
        case 7:{
            cout << "Input file name:\n";
            cin >> path;
            break;
        }
        default:{
            printf("Error\n");
            return;
        }
    }

    ReadFromFileRecognImage(path);
    cout << "\nDistorted image:" << endl;
    PrintImg(imgX_);
    vecX_ = StringToVec(imgX_);

    Col<int> X_(n, fill::zeros);
    old_vecX_ = X_;
    Col<int> Y_(p, fill::zeros);
    old_vecY_ = Y_;

    cur_vecX_ = vecX_;
    cur_vecY_ = Y_;

    int iteration = 0;
    bool find = true;

    do{
        old_vecY_ = cur_vecY_;
        cur_vecY_ = conv_to<Col<int>>::from(cur_vecX_.t() * W);

        for (int i = 0; i < p; i++)
        {
            int y;
            y = F(cur_vecY_(i));
            if (y != 0)
                cur_vecY_(i) = y;
            else
                cur_vecY_(i)=old_vecY_(i);
        }


        old_vecX_ = cur_vecX_;
        cur_vecX_ = conv_to<Col<int>>::from(cur_vecY_.t() * W_);

        for (int i = 0; i < n; i++)
        {
            int x;
            x = F(cur_vecX_(i));
            if (x != 0)
                cur_vecX_(i) = x;
            else
                cur_vecX_(i)=old_vecX_(i);
        }

        iteration++;

        if (iteration > 10)
        {
            find = false;
            break;
        }

    } while ((any(cur_vecY_ - old_vecY_)!=0 || any(cur_vecX_ - old_vecX_)!=0));

    cout << "Iteratoins: " << iteration << endl;

    if (find == false)
    {
        cout << "The image isn't recognized" << endl;
        return;
    }

    for (int i = 0; i < Q; i++)
    {
        if (any(Yk[i] - cur_vecY_)!=1)
        {
            cout << "Recognized image:" << endl;
            PrintImg(VecToString(Xk[i]));
            return;
        }
    }
    cout << "The image isn't recognized" << endl;
    return;
}

int BiAssociativeMemory::F(int s)
{
    if (s < 0)
        return -1;
    if (s > 0)
        return 1;

    return 0;

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

void BiAssociativeMemory::ReadFromFileRecognImage(string path)
{
    string buf, X_;
    int n_;

    ifstream file(path);
    if (!file.is_open())
    {
        cout << "The file can not be opened!\n";
        return;
    }
    file >> n_;

    if (n_!=n)
    {
        cout << "Error! The file contains incorrect data!" << endl;
        return;
    }

    getline(file,  buf);

    for (int i = 0; i < buf.length() || i < n; i++)
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
    }
    file.close();

    imgX_ = X_;
    return;
}

double BiAssociativeMemory::CountL()
{
    int m = min(n, p);
    return (m/(4*log(m)));
}

void BiAssociativeMemory::AddX_Y(Mat<int> X, Col<int> Y)
{

}
