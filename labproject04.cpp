#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

const double PI = 3.14;

//
class rectBlocks
{
protected:
    double width;
    double height;
    double length;

public:
    rectBlocks()
    {
        width = 0;
        height = 0;
        length = 0;
    }
    rectBlocks(double w, double h, double l)
    {
        width = w;
        height = h;
        length = l;
    }
    double getWidth()
    {
        return width;
    }
    double getHeight()
    {
        return height;
    }
    double getLength()
    {
        return length;
    }
    void set(double w, double h, double l)
    {
        width = w;
        height = h;
        length = l;
    }
    void display()
    {
        
        cout << "Width = " << width << "\n";
        cout << "Height = " << height << "\n";
        cout << "Length = " << length << "\n";
    }
};

class sqrBaseRectBlocks : public rectBlocks
{
public:
    sqrBaseRectBlocks()
    {
        width = 0;
        height = 0;
        length = 1;
    }
    sqrBaseRectBlocks(double base, double l)
    {
        width = base;
        height = base;
        length = l;
    }
    void set(double base, double l)
    {
        width = base;
        height = base;
        length = l;
    }
    void display()
    {
        cout << "\nDisplaying the sqrBaseRectBlock\n";
        cout << "Width = " << width << "\n";
        cout << "Height = " << height << "\n";
        cout << "Length = " << length << "\n";
    }
};

class cylindricalBlocks : public sqrBaseRectBlocks
{
    double baseDiameter;

public:
    cylindricalBlocks()
    {
        baseDiameter = 0;
        length = 1;
    }
    cylindricalBlocks(double base, double l)
    {
        baseDiameter = base;
        length = l;
    }
    void set(double base, int l)
    {
        baseDiameter = base;
        length = l;
    }
    double getSurfaceArea()
    {
        return 2 * PI * (baseDiameter / 2) * length;
    }
    double getTotalArea()
    {
        return 2 * PI * (baseDiameter / 2) * (length + (baseDiameter / 2));
    }
    double getVolume()
    {
        return PI * (baseDiameter / 2) * (baseDiameter / 2) * length;
    }
    void display()
    {
        cout << "\n";
        cout << "Cylindrical Surface Area = " << getSurfaceArea() << "     Base Diameter = " << baseDiameter << "     Length = " << length << "     Area = " << getTotalArea() << "\n";
    }
};

class cuboidBlocks : public sqrBaseRectBlocks
{
public:
    cuboidBlocks()
    {
        width = 0;
        height = 0;
        length = 0;
    }
    cuboidBlocks(int side)
    {
        width = side;
        height = side;
        length = side;
    }
    void set(int side)
    {
        width = side;
        height = side;
        length = side;
    }
    void display()
    {
        cout << "\nDisplaying the cuboidBlock\n";
        cout << "Width = " << width << "\n";
        cout << "Height = " << height << "\n";
        cout << "Length = " << length << "\n";
    }
};

class sphericalBlocks : public cuboidBlocks
{
    double diameter;

public:
    sphericalBlocks()
    {
        diameter = 0;
    }
    sphericalBlocks(int dia)
    {
        diameter = dia;
    }
    double getDiameter()
    {
        return diameter;
    }
    double getSurfaceArea()
    {
        return 4 * PI * (diameter / 2) * (diameter / 2);
    }
    double getVolume()
    {
        return (4 / 3) * PI * (diameter / 2) * (diameter / 2) * (diameter / 2);
    }
    void set(int dia)
    {
        diameter = dia;
    }
    void display()
    {
        cout << "\n";
        cout << "Diameter = " << diameter << "     Spherical surface area = " << getSurfaceArea() << "     Volume = " << getVolume() << "\n";
    }
};

void sortByDiameter(vector<sphericalBlocks> &A)
{
    int minPos;
    for (int i = 0; i < A.size() - 1; i++)
    {
        minPos = i;
        for (int j = i + 1; j < A.size(); j++)
            if (A[j].getDiameter() < A[minPos].getDiameter())
                minPos = j;

        sphericalBlocks temp = A[i];
        A[i] = A[minPos];
        A[minPos] = temp;
    }
}

void sortBySurfceArea(vector<cylindricalBlocks> &A)
{
    int minPos;
    for (int i = 0; i < A.size() - 1; i++)
    {
        minPos = i;
        for (int j = i + 1; j < A.size(); j++)
            if (A[j].getSurfaceArea() < A[minPos].getSurfaceArea())
                minPos = j;

        cylindricalBlocks temp = A[i];
        A[i] = A[minPos];
        A[minPos] = temp;
    }
}

// driver
int main()
{
    ifstream f("dataBlocks.dat", ios::in);

    if (!f.is_open())
    {
        cout << "File not accesible\nExiting....\n";
        exit(1);
    }

    vector<rectBlocks> rects;
    vector<sphericalBlocks> spheres;
    vector<cylindricalBlocks> cylinders;
    int l, w, h, base, dia;
    while (!f.eof())
    {
        f >> w >> h >> l;
        rectBlocks temp1(w, h, l);
        if (w == h && h == l)
        {
            sphericalBlocks temp2(w);
            spheres.push_back(temp2);
        }
        if (w == h)
        {
            cylindricalBlocks temp3(w, l);
            cylinders.push_back(temp3);
        }
        rects.push_back(temp1);
    }
    cout << "\nPrinting the spherical blocks before sorting\n";
    for (int i = 0; i < spheres.size(); i++)
    {
        spheres[i].display();
    }
    sortByDiameter(spheres);
    cout << "\nPrinting the spherical blocks after sorting\n";
    for (int i = 0; i < spheres.size(); i++)
    {
        spheres[i].display();
    }

    cout << "\n\n";

    cout << "\nPrinting the cylindrical blocks before sorting\n";
    for (int i = 0; i < cylinders.size(); i++)
    {
        cylinders[i].display();
    }
    sortBySurfceArea(cylinders);
    cout << "\nPrinting the cylindrical blocks after sorting\n";
    for (int i = 0; i < cylinders.size(); i++)
    {
        cylinders[i].display();
    }

    return 0;
}
