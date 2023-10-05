#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

class Printer {
public:
    string name;
    int elements;
    int prior;
    string time;
};

class QueuePriority {
    int* Wait;
    int* Pri;
    int MaxQueueLength;
    int QueueLength;
    Printer* PrElements;
    int PrSize;

public:
    QueuePriority(int m);
    ~QueuePriority();
    void Add(int c, int p, const string& n, const string& time);
    int Extract();
    void Clear();
    bool IsEmpty();
    bool IsFull();
    int GetCount();
    void Show();
    void AddPrinter(int e, const string& n, const string& time);
    void Print();
};

void QueuePriority::Show() {
    for (int i = 0; i < QueueLength; i++) {
        cout << Wait[i] << " - " << Pri[i] << "\n\n";
    }
    cout << "\n-------------------------------------\n";
}

void QueuePriority::Print()
{
    for (int i = 0; i < PrSize; i++)
    {
        cout << "Êëèåíò: " << PrElements[i].name << endl;
        cout << "ID êëèåíò: " << PrElements[i].elements << endl;
        cout << "Òåêóùåå âðåìÿ: " << PrElements[i].time << endl;
        cout << endl;
    }
}

QueuePriority::~QueuePriority()
{
    delete[]Wait;
    delete[]Pri;
    delete[]PrElements;
}

QueuePriority::QueuePriority(int m)
{
    MaxQueueLength = m;
    Wait = new int[MaxQueueLength];
    Pri = new int[MaxQueueLength];
    QueueLength = 0;

    PrElements = new Printer[MaxQueueLength];
    PrSize = 0;
}

void QueuePriority::Clear()
{ 
    QueueLength = 0;
}

bool QueuePriority::IsEmpty()
{
    return QueueLength == 0;
}

bool QueuePriority::IsFull()
{
    return QueueLength == MaxQueueLength;
}

int QueuePriority::GetCount()
{
    return QueueLength;
}

void QueuePriority::Add(int c, int p, const string& n, const string& time)
{
    if (!IsFull()) {
        Wait[QueueLength] = c;
        Pri[QueueLength] = p;
        QueueLength++;
    }
    if (!IsFull()) {
        int i = PrSize - 1;
        while (i >= 0 && PrElements[i].prior < p)
        {
            PrElements[i + 1] = PrElements[i];
            i--;
        }
        PrElements[i + 1].elements = c;
        PrElements[i + 1].prior = p;
        PrElements[i + 1].name = n;
        PrElements[i + 1].time = time;
        PrSize++;
    }
}

int QueuePriority::Extract()
{
    if (!IsEmpty()) {
        int max_pri = Pri[0];
        int pos_max_pri = 0;

        for (int i = 1; i < QueueLength; i++)
            if (max_pri < Pri[i]) {
                max_pri = Pri[i];
                pos_max_pri = i;
            }
        int temp1 = Wait[pos_max_pri];
        int temp2 = Pri[pos_max_pri];

        for (int i = pos_max_pri; i < QueueLength - 1; i++) {
            Wait[i] = Wait[i + 1];
            Pri[i] = Pri[i + 1];
        }

        QueueLength--;

        return temp1;

    }
    else return -1;
}

int main()
{
    srand(time(0));
    setlocale(LC_ALL, "");
    QueuePriority Q(25);      
    for (int i = 0; i < 5; i++) {
        char userNameChar = 'A' + i;
        string PrName(1, userNameChar);
        int elements = rand() % 200;

        time_t rawtime;
        struct tm* timeinfo;
        char buffer[80];
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", timeinfo);
        string NewTime(buffer);

        Q.Add(elements, rand() % 12, PrName, NewTime);
    }
    Q.Show();
    Q.Print();

    system("pause");
}

