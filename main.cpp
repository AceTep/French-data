#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>


using namespace std;

struct French // struktura kojom izradujemo polje kako bi unijeli podatke iz csv
{
    int num1, num2, num3, nbrImg;
    string date1, time, date2, titleFr, contentFr, agency, URL, textURLFr, titleEng, contentEng, textURLEng;
    float secTo2010, daysTo2010, SVTitle, SVText, SVTextURL;
};

struct Node // kreiranje strukture cvora
{
    French data;
    Node* left;
    Node* right;


    Node (French da)
    {
        data.num1 = da.num1;
        data.num2 = da.num2;
        data.num3 = da.num3;
        data.date1 = da.date1;
        data.time = da.time;
        data.titleFr = da.titleFr;
        data.contentFr = da.contentFr;
        data.agency = da.agency;
        data.URL = da.URL;
        data.textURLFr = da.textURLFr;
        data.nbrImg = da.nbrImg;
        data.secTo2010 = da.secTo2010;
        data.daysTo2010 = da.daysTo2010;
        data.date2 = da.date2;
        data.titleEng = da.titleEng;
        data.contentEng = da.contentEng;
        data.textURLEng = da.textURLEng;
        data.SVTitle = da.SVTitle;
        data.SVText = da.SVText;
        data.SVTextURL = da.SVTextURL;
        left = NULL;
        right = NULL;
    }
};


void LeftRotation(Node *& root) //lijeva rotacija
{
    Node* temp = root->left;
    root->left = temp->right;
    temp->right = root;
    root = temp;
}
void RightRotation(Node*& root) //desno rotacija
{
    Node* temp = root->right;
    root->right = temp->left;
    temp->left = root;
    root = temp;
}
void DoubleLR(Node *& root) //dupla lijeva rotacija
{
    RightRotation(root->left);
    LeftRotation(root);
}
void DoubleRR(Node *& root) //dupla desna rotacija
{
    LeftRotation(root->right);
    RightRotation(root);
}
int height(Node* root) //izracun visine cvora
{
    if(root==NULL) return -1;
    else
    {
        int LHeight = height(root->left);
        int DHeight = height(root->right);
        if(LHeight > DHeight) return LHeight+1;
        else return DHeight+1;
    }
}
/*
Kao index za sortiranje sam izabrao num2 varijablu odnosno 'Numero page' atribut koji unosimo u AVL stablo koje se automatski rotira i sortira
*/
Node* addAVL(Node*& root, French x) // dodavanje odabranog podatka num2 u AVL stablo
{
    if(root == NULL)
        root = new Node(x);
    else if(x.num2 < root->data.num2)
    {
        addAVL(root->left, x);
        if(height(root->left)-height(root->right)==2)
        {
            if(x.num2 < root->left->data.num2)
                LeftRotation(root);
            else DoubleLR(root);
        }
    }
    else if(x.num2 > root->data.num2)
    {
        addAVL(root->right, x);
        if(height(root->right)-height(root->left)==2)
        {
            if(x.num2 > root->right->data.num2)
                RightRotation(root);
            else DoubleRR(root);
        }
    }
    return root;
}

void PrintTreePreOrder(Node *root) //preOrder ispis
{
    if (root==0)
    {
        return;
    }
    cout<<setw(5)<<root->data.num2<<"          ";
    cout<<setw(5)<<root->data.date1<<"     ";
    cout<<setw(5)<<root->data.nbrImg<<"         ";
    cout<<setw(5)<<root->data.daysTo2010<<"     ";
    cout<<setw(5)<<root->data.SVTitle<<"      ";
    cout<<setw(5)<<root->data.titleEng;
    cout<<endl;
    PrintTreePreOrder(root->left);
    PrintTreePreOrder(root->right);
}
void PrintTreeInOrder(Node *root) //inOrder ispis
{
    if (root==0)
    {
        return;
    }
    PrintTreeInOrder(root->left);
    cout<<setw(5)<<root->data.num2<<"          ";
    cout<<setw(5)<<root->data.date1<<"     ";
    cout<<setw(5)<<root->data.nbrImg<<"         ";
    cout<<setw(5)<<root->data.daysTo2010<<"     ";
    cout<<setw(5)<<root->data.SVTitle<<"      ";
    cout<<setw(5)<<root->data.titleEng;
    cout<<endl;
    PrintTreeInOrder(root->right);
}
void PrintTreePostOrder(Node *root) //postOrder ispis
{
    if (root==0)
    {
        return;
    }
    PrintTreePostOrder(root->left);
    PrintTreePostOrder(root->right);
    cout<<setw(5)<<root->data.num2<<"          ";
    cout<<setw(5)<<root->data.date1<<"     ";
    cout<<setw(5)<<root->data.nbrImg<<"         ";
    cout<<setw(5)<<root->data.daysTo2010<<"     ";
    cout<<setw(5)<<root->data.SVTitle<<"      ";
    cout<<setw(5)<<root->data.titleEng;
    cout<<endl;
}


void printTree(Node *root, int sirina) //ispis stabla
{
    if (root==0)
    {
        cout<<setw(sirina)<<"*"<<endl;
        return;
    }
    printTree(root->right, sirina+6);
    cout << setw(sirina);
    cout << root->data.num2 << "<" << endl;
    printTree(root->left, sirina+6);
}

int main()
{
    struct French arr[25]; // deklaracija polja pomocu strukture

    vector<vector<string>> parsedCSV; // stupac
    vector<string> parsedRow; // red
    string line, cell;
    fstream file("dataset.csv", ios::in); // otvaranje datoteke
    if (file.is_open())
    {
        while (getline(file, line)) // podjela csv doc na redke i stupce
        {
            parsedRow.clear();

            stringstream str(line);

            while (getline(str, cell, ';'))
                parsedRow.push_back(cell);
            parsedCSV.push_back(parsedRow);
        }
    }
    else
    {
        cout << "ERROR: Failed to open the file." << endl;
    }
    for (int i = 1; i <= 25; i++) // unos iz stupaca u polje
    {
        arr[i - 1].num1 = stoi(parsedCSV[i][0]);
        arr[i - 1].num2 = stoi(parsedCSV[i][1]);
        arr[i - 1].num3 = stoi(parsedCSV[i][2]);
        arr[i - 1].date1 = parsedCSV[i][3];
        arr[i - 1].time = parsedCSV[i][4];
        arr[i - 1].titleFr = parsedCSV[i][5];
        arr[i - 1].contentFr = parsedCSV[i][6];
        arr[i - 1].agency= parsedCSV[i][7];
        arr[i - 1].URL= parsedCSV[i][8];
        arr[i - 1].textURLFr= parsedCSV[i][9];
        arr[i - 1].nbrImg = stoi(parsedCSV[i][10]);
        arr[i - 1].secTo2010 = stof(parsedCSV[i][11]);
        arr[i - 1].daysTo2010 = stof(parsedCSV[i][12]);
        arr[i - 1].date2 = parsedCSV[i][13];
        arr[i - 1].titleEng = parsedCSV[i][14];
        arr[i - 1].contentEng = parsedCSV[i][15];
        arr[i - 1].textURLEng= parsedCSV[i][16];
        arr[i - 1].SVTitle = stof(parsedCSV[i][17]);
        arr[i - 1].SVText = stof(parsedCSV[i][18]);
        arr[i - 1].SVTextURL = stof(parsedCSV[i][19]);
    }



    Node* root = new Node(arr[0]); // kreiranje glavnog cvora
    for(int i = 1; i<=24; i++) // unos podataka polja u AVL stablo pomocu funkcije
    {
        addAVL(root, arr[i]);
    }
    cout<<"Ispis sortiranih podataka pomocu AVL stabla sa indexom \"Numero Page\""<<endl;
    cout<<"U ISPISU SU UREDENI I MAKNUTI PODACI RADI BOLJE PREGLEDNOSTI"<<endl<<endl;
    int odabir=10;
    while(odabir!=0)
    {
        cout<<"========================"<<endl;
        cout<<"1. Ispis podataka PreOrder"<<endl;
        cout<<"2. Ispis podataka InOrder"<<endl;
        cout<<"3. Ispis podataka PostOrder"<<endl;
        cout<<"4. Ispis stabla"<<endl;
        cout<<"0. Izlaz iz programa"<<endl;
        cout<<"========================"<<endl;
        cout<<"Odaberite nacin ispisa: ";
        cin>>odabir;
        cout<<endl;
        switch(odabir)
        {
        case 1:
            cout<<"Odabrali ste ispis PreOrder redosljedom!"<<endl;
            cout<<setw(5)<<"Numero page |     Date     | Nbr image | days to 2010 |  SVTitle  | Title eng  "<<endl;
            PrintTreePreOrder(root);
            break;
        case 2:
            cout<<"Odabrali ste ispis InOrder redosljedom!"<<endl;
            cout<<setw(5)<<"Numero page |     Date     | Nbr image | days to 2010 |  SVTitle  | Title eng  "<<endl;
            PrintTreeInOrder(root);
            break;
        case 3:
            cout<<"Odabrali ste ispis PostOrder redosljedom!"<<endl;
            cout<<setw(5)<<"Numero page |     Date     | Nbr image | days to 2010 |  SVTitle  | Title eng  "<<endl;
            PrintTreePostOrder(root);
            break;
        case 4:
            cout<<"Odabrali ste ispis stabla!"<<endl;

            printTree(root,5);
            break;
                  case 0:
            break;
        default:
            cout<<"Neispravan unos, pokusajte ponovno!"<<endl;
        }
    }
    file.close();
    return 0;
}
