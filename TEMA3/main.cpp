#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <typeinfo>
using namespace std;
///PURECEL MIHAI
///GRUPA 144
///C++11


class Car{
protected:
    int id;
    string marca,model;

public:
    //Constr and destr
    Car();
    Car(const string _marca);
    Car(int _id, string _marca="", string _model = "");
    Car(const Car&);
    virtual ~Car();
    //Operators
    friend istream& operator>>(istream& in, Car&);
    friend ostream& operator<<(ostream& out, Car&);
    Car &operator=(const Car&);
    //Functions
    virtual void afis(ostream &out);
    void setid(int _id);
    int getid(){
        return id;
    }

};
Car::Car(){
    id = 0;
    marca = model = "";
}
Car::Car(const string _marca){
    id = 0;
    marca = _marca;
}
Car::Car(int _id, string _marca, string _model){
    id = _id;
    marca = _marca;
    model = _model;
}
Car::Car(const Car& car){
    id = car.id;
    marca = car.marca;
    model = car.model;
}
Car::~Car(){
    id = 0;
}
istream &operator>>(istream& in, Car& car){
    string _marca, _model;
    cout<<"MARCA: ";
    while(!_marca.length())
        getline(in, _marca);
    cout<<"MODEL: ";
    while(!_model.length())
        getline(in, _model);
    car.model = _model;
    car.marca = _marca;
    return in;
}
ostream &operator<<(ostream& out, Car& car){
    car.afis(out);
    return out;
}
void Car::afis(ostream& out){
    out<<"ID="<<id;
    out<<": Denumire: ";
    out<<marca<<" ";
    out<<model<<"\n";
}
Car &Car::operator=(const Car& daddy){
    id = daddy.id;
    marca = daddy.marca;
    model = daddy.model;
    return *this;
}
void Car::setid(int _id){
    id  = _id;
}



class Coupe:public Car{
protected:
    string color;
    string tip_carburant;
public:
    //Constr and destr
    Coupe();
    Coupe(int _id, string _marca = "", string _model = "", string _color = "", string _tip_carburant = "");
    Coupe(const Coupe&);
    virtual ~Coupe();
    //Operators
    friend istream& operator>>(istream& in, Coupe&);
    friend ostream& operator<<(ostream& out, Coupe&);
    Coupe &operator=(const Coupe&);
    //Functions
    virtual void afis(ostream &out);
};
Coupe::Coupe():Car(){
    color = tip_carburant = "";
}
Coupe::Coupe(int _id, string _marca, string _model, string _color, string _tip_carburant):Car(_id, _marca, _model){
    color = _color;
    tip_carburant = _tip_carburant;
}
Coupe::Coupe(const Coupe& daddy):Car(daddy){
    color = daddy.color;
    tip_carburant = daddy.tip_carburant;
}
Coupe::~Coupe(){
    color = "";
    tip_carburant = "";
}
istream &operator>>(istream &in, Coupe &masina){
    in>>dynamic_cast<Car&>(masina);
    string _color, _tip_carb;
    cout<<"CULOAREA: ";
    while(!_color.length())
        getline(in, _color);


    bool ok = 0;
    while(!ok){
        ok = 1;
        try{
            cout<<"TIP CARBURANT (benzina/motorina/hybrid): ";
            getline(in, _tip_carb);
            if(_tip_carb != "benzina" && _tip_carb != "motorina" && _tip_carb != "hybrid")
                throw 1;
        }
        catch(int){
            ok = 0;
            cout<<"Invalid input (all characters must be lowercase and no spaces should be inserted); You have to type in exactly one of the words:benzina/motorina/hybrid\n";
        }

    }


    masina.color = _color;
    masina.tip_carburant = _tip_carb;
    return in;
}
void Coupe::afis(ostream &out){
    Car::afis(out);
    out<<"      Culoare: "<<color<<"\n      Tip carburant: "<<tip_carburant<<"\n";
}
ostream &operator<<(ostream &out, Coupe &masina){
    masina.afis(out);
    return out;
}
Coupe& Coupe::operator=(const Coupe& masina){
    Car::operator=(masina);
    color = masina.color;
    tip_carburant = masina.tip_carburant;
    return *this;
}


class CoupeFourDoor:public Coupe{
    int norma_de_poluare;
public:
    //Constr and destr
    CoupeFourDoor();
    CoupeFourDoor(int _id, string _marca = "", string _model = "", string _color = "", string _tip_carburant = "", int _norma_de_poluare=0);
    CoupeFourDoor(const CoupeFourDoor&);
    ~CoupeFourDoor();
    //Operators
    friend istream& operator>>(istream& in, CoupeFourDoor&);
    friend ostream& operator<<(ostream& out, CoupeFourDoor&);
    CoupeFourDoor &operator=(const CoupeFourDoor&);
    //Functions
    void afis(ostream &out);
};
CoupeFourDoor::CoupeFourDoor():Coupe(){
    norma_de_poluare = 0;
}
CoupeFourDoor::CoupeFourDoor(int _id, string _marca, string _model, string _color, string _tip_carburant, int _norma_de_poluare):Coupe(){
    norma_de_poluare = _norma_de_poluare;
}
CoupeFourDoor::CoupeFourDoor(const CoupeFourDoor& daddy):Coupe(daddy){
    norma_de_poluare = daddy.norma_de_poluare;
}
CoupeFourDoor::~CoupeFourDoor(){
    norma_de_poluare = 0;
}
istream &operator>>(istream &in, CoupeFourDoor &masina){
    in>>dynamic_cast<Coupe&>(masina);
    string _norma;

    bool ok = false;
    while(!ok){
        ok = true;
        try{
            cout<<"INTRODUCETI NORMA DE POLUARE (numar intre 1 si 5): EURO";
            in>>_norma;
            if(_norma.length() != 1)
                throw 10;
            if(_norma.front() < '1' || _norma.front() > '5')
                throw 3.2;
        }
        catch(int){
            cout<<"The input should not have more than one character (not inserting anything is not valid)\n";
            ok = false;
        }
        catch(double){
            cout<<"The input is not a number between 1  and 5\n";
            ok = false;
        }

    }
    masina.norma_de_poluare = _norma.front()-'0';


    return in;
}
void CoupeFourDoor::afis(ostream &out){
    Coupe::afis(out);
    out<<"      Norma de poluare: EURO"<<norma_de_poluare<<"\n";
}
ostream &operator<<(ostream &out, CoupeFourDoor& masina){
    masina.afis(out);
    return out;
}
CoupeFourDoor &CoupeFourDoor::operator=(const CoupeFourDoor& daddy){
    Coupe::operator=(daddy);
    norma_de_poluare = daddy.norma_de_poluare;
    return *this;
}

class HotHatch:public Car{
    int numar_cilindrii_motor;
    double zero_to_100;
public:
    //Constr and destr
    HotHatch();
    HotHatch(int _id, string _marca = "", string _model = "", int _numar_cil = 0, int _Z100 = 0);
    HotHatch(const HotHatch&);
    ~HotHatch();
    //Operators
    friend istream& operator>>(istream& in, HotHatch&);
    friend ostream& operator<<(ostream& out, HotHatch&);
    HotHatch &operator=(const HotHatch&);
    //Functions
    void afis(ostream &out);
    double getspeed();
};
HotHatch::HotHatch():Car(){
    numar_cilindrii_motor = 0;
    zero_to_100 = 0;
}
HotHatch::HotHatch(int _id, string _marca , string _model, int _numar_cil, int _Z100):Car(_id, _marca, _model){
    numar_cilindrii_motor = _numar_cil;
    zero_to_100 = _Z100;
}
HotHatch::HotHatch(const HotHatch& daddy):Car(daddy){
    numar_cilindrii_motor = daddy.numar_cilindrii_motor;
    zero_to_100 = daddy.zero_to_100;
}
HotHatch::~HotHatch(){
    numar_cilindrii_motor = zero_to_100 = 0;
}
istream &operator>>(istream &in, HotHatch& masina){
    in>>dynamic_cast<Car&>(masina);
    string _nr_cil, _zto100;
    bool ok = 0;
    int aux;
    while(!ok){
        ok = 1;
        try{
            cout<<"NUMAR CILINDRII MOTOR (0 <= x <= 30): ";
            getline(in, _nr_cil);
            if(!_nr_cil.length()){
                throw 's';
            }
            for(char c:_nr_cil){
                if(c < '0' || c > '9')
                    throw 3;
            }
            aux = atoi(_nr_cil.c_str());
            if(aux < 0 || aux > 30)
                throw 2.2;

        }
        catch(char){
            ok = 0;
            cout<<"Not inserting anything is not valid\n";
        }
        catch(int){
            ok = 0;
            cout<<"Invalid input (MUST be an integer number)\n";
        }
        catch(double){
            ok = 0;
            cout<<"Number is either too big or to small (it has to be between 0 and 30)\n";
        }

    }
    ok = 0;
    double aux2;
    while(!ok){
        ok = 1;
        try{
            cout<<"ATINGE 100 KM/H INTR-UN TIMP DE (secunde): ";
            getline(in, _zto100);
            if(!_zto100.length())
                throw 'c';
            bool punct = false;
            int beforepoint=0;
            for(char c:_zto100){
                if(punct == false)
                    beforepoint++;
                if(c < '0' || c > '9'){
                    if(c != '.' || punct)
                        throw 3;
                    else
                        punct = true;
                }
            }
            if(punct)
                beforepoint--;
            aux2 = atof(_zto100.c_str());
            if(beforepoint >= 3)
                throw "ouch";
            if(aux < 0 )
                throw 2.2;
        }
        catch(char){
            ok = 0;
            cout<<"Not inserting anything is not valid\n";
        }
        catch(int){
            ok = 0;
            cout<<"Invalid input (MUST be a positive number)\n";
        }
        catch(double){
            ok = 0;
            cout<<"Number cannot be negative\n";
        }
        catch(char const*){
            ok = 0;
            cout<<"A sports car's acceleration cannot be 0 or a number bigger than or equal to 100 (seconds)\n";
        }
    }

    masina.numar_cilindrii_motor = aux;
    masina.zero_to_100 = aux2;
    return in;
}
double HotHatch::getspeed(){
    return zero_to_100;
}
void HotHatch::afis(ostream &out){
    Car::afis(out);
    out<<"      Numar cilindrii motor: "<<numar_cilindrii_motor<<"\n      Acceleratie de la 0 la 100 km/h in "<<zero_to_100<<" secunde\n";
}
ostream &operator<<(ostream &out, HotHatch& masina){
    masina.afis(out);
    return out;
}
HotHatch &HotHatch::operator=(const HotHatch &daddy){
    Car::operator=(daddy);
    numar_cilindrii_motor = daddy.numar_cilindrii_motor;
    zero_to_100 = daddy.zero_to_100;
    return *this;
}

class Cabrio:public Car{
    bool roof_type;
    ///roof == 0 => textil;       roof == 1 => metallic;
public:
    //Constr and destr
    Cabrio();
    Cabrio(int _id, string _marca = "", string _model = "", bool _roof_t = 0);
    Cabrio(const Cabrio&);
    ~Cabrio();
    //Operators
    friend istream& operator>>(istream& in, Cabrio&);
    friend ostream& operator<<(ostream& out, Cabrio&);
    Cabrio &operator=(const Cabrio&);
    //Functions
    bool getrooftype();
    void afis(ostream &out);
};
Cabrio::Cabrio():Car(){
    roof_type = 0;
}
Cabrio::Cabrio(int _id, string _marca, string _model, bool _roof_t):Car(_id, _marca, _model){
    roof_type = _roof_t;
}
Cabrio::Cabrio(const Cabrio& daddy):Car(daddy){
    roof_type = daddy.roof_type;
}
Cabrio::~Cabrio(){
    roof_type = 0;
}
istream &operator>>(istream &in, Cabrio& masina){
    in>>dynamic_cast<Car&>(masina);
    string optiune;
    bool ok = 0;
    while(!ok){
        ok = 1;
        try{
            cout<<"TIPUL DE PLAFON (0=textil, 1=metalic): ";
            getline(in, optiune);
            if(optiune.length() != 1)
                throw 1;
            if(optiune.front() != '0' && optiune.front() != '1')
                throw 2.3;
        }
        catch(int){
            cout<<"Input should olny be one character long (not inserting anything is not valid either)\n";
            ok = 0;
        }
        catch(double){
            cout<<"You must insert either 1 or 0; No other input is accepted\n";
            ok = 0;
        }
    }

    masina.roof_type = optiune.front()-'0';
    return in;
}
bool Cabrio::getrooftype(){
    return roof_type;
}
void Cabrio::afis(ostream &out){
    Car::afis(out);
    out<<"      Tip acoperis: ";
    if(roof_type == 0)
        out<<"textil\n";
    else
        out<<"metalic\n";
}
ostream &operator<<(ostream &out, Cabrio& masina){
    masina.afis(out);
    return out;
}
Cabrio &Cabrio::operator=(const Cabrio &daddy){
    Car::operator=(daddy);
    roof_type = daddy.roof_type;
    return *this;
}



class Supersport:public Car{
    int max_speed;
    int price;
public:
    //Constr and destr
    Supersport();
    Supersport(int _id, string _marca = "", string _model = "", int _max_speed = 0, int _price = 0);
    Supersport(const Supersport&);
    ~Supersport();
    //Operators
    friend istream& operator>>(istream& in, Supersport&);
    friend ostream& operator<<(ostream& out, Supersport&);
    Supersport &operator=(const Supersport&);
    //Functions
    void afis(ostream &out);
};
Supersport::Supersport():Car(){
    max_speed = price = 0;
}
Supersport::Supersport(int _id, string _marca, string _model, int _max_speed, int _price):Car(_id, _marca, _model){
    max_speed = _max_speed;
    price = _price;
}
Supersport::Supersport(const Supersport& daddy):Car(daddy){
    max_speed = daddy.max_speed;
    price = daddy.max_speed;
}
Supersport::~Supersport(){
    max_speed = price = 0;
}
istream &operator>>(istream &in, Supersport &masina){
    in>>dynamic_cast<Car&>(masina);
    string _max_speed, _price;
    bool ok = 0;
    int aux1, aux2;
    while(!ok){
        ok = 1;
        try{
            cout<<"VITEZA MAXIMA PE CARE O ATINGE MASINA (km/h): ";
            getline(in, _max_speed);
            if(!_max_speed.length())
                throw 'a';
            for(char c:_max_speed){
                if(c < '0' || c > '9')
                    throw 3;
            }
            aux1 = atoi(_max_speed.c_str());
            if(aux1 <= 0 || aux1 > 600)
                throw 5.2;
        }
        catch(char){
            cout<<"Not inserting anything is not valid\n";
            ok = 0;
        }
        catch(int){
            cout<<"You have to insert a valid positive number (can only contain characters from 0 to 9)\n";
            ok = 0;
        }
        catch(double){
            cout<<"Number is either zero or too big (a car can not go faster than 600 km/h, nor can it have its speed 0 km/h)\n";
            ok = 0;
        }

    }

    ok = 0;
    while(!ok){
        ok = 1;
        try{
            cout<<"PRETUL MASINII (euro): ";
            getline(in, _price);
            if(!_price.length())
                throw 'a';
            if(_price.length() > 9)
                throw "really?";
            for(char c:_price){
                if(c < '0' || c > '9')
                    throw 3;
            }
            aux2 = atoi(_price.c_str());
            if(aux2 < 0)
                throw 5.2;
        }
        catch(char){
            cout<<"Not inserting anything is not valid\n";
            ok = 0;
        }
        catch(int){
            cout<<"You have to insert a valid positive number (can only contain characters from 0 to 9\n";
            ok = 0;
        }
        catch(double){
            cout<<"Number has to be positive (0 means it's free)\n";
            ok = 0;
        }
        catch(char const*){
            cout<<"There are no cars that are that expensive!\n";
            ok = 0;
        }
    }

    masina.max_speed = aux1;
    masina.price = aux2;
    return in;
}
void Supersport::afis(ostream &out){
    Car::afis(out);
    out<<"      Viteza maxima: "<<max_speed<<" km/h\n      Pret: "<<price<<" euro\n";
}
ostream &operator<<(ostream &out, Supersport& masina){
    masina.afis(out);
    return out;
}
Supersport &Supersport::operator=(const Supersport& daddy){
    Car::operator=(daddy);
    max_speed = daddy.max_speed;
    price = daddy.price;
    return *this;
}


template <class T> class Expozitie;
template<class T> ostream& operator<< ( ostream& out, const Expozitie<T> &daddy );

template<class T> class Expozitie{
    int dim = 0;
    static int car_id;
    vector<T*> V;
public:
    //Constr. and destr.
    Expozitie();
    Expozitie(int _dim);
    Expozitie(const Expozitie&);
    ~Expozitie();
    //Overloaded operators
    friend ostream &operator<< <>(ostream &out, const Expozitie &daddy);
    //Functions
    template<class U> void push_back(U &C);

};
template<class T> Expozitie<T>::Expozitie(){
    dim = 0;

}
template<class T> Expozitie<T>::Expozitie(int _dim){
    dim = _dim;
    V.resize(dim);
}
template<class T> Expozitie<T>::Expozitie(const Expozitie& old_expo){
    for(T* C:V)
        delete C;

    this->dim = old_expo.dim;
    V.resize(dim);
    for(int i=0;i<dim; i++){
        T *aux = new T;
        aux = old_expo.V[i];
        this->V[i] = aux;
    }

}
template<class T> Expozitie<T>::~Expozitie(){
    for(int i = 0;i< dim;i++)
        delete V[i];
    V.resize(0);
    dim = 0;
}
template<class T> int Expozitie<T>::car_id = 0;
template<class T> template<class U> void Expozitie<T>::push_back(U &C){
    U *aux = new U;
    *aux = C;
    V.push_back(aux);
    dim = V.size();
    V[dim-1] -> setid(++car_id);
}
template<class T> ostream &operator<<(ostream &out, const Expozitie<T> &daddy){
    for(int i = 0;i< daddy.dim;i++)
        (daddy.V[i]) -> afis(out);
        out<<"\n";
    return out;
}

template<> class Expozitie<Supersport>{
    int nr_stoc, nr_vandute;
    static int car_id;
    vector<Supersport*>Stoc, Vandute;
public:
    //Constr. and destr.
    Expozitie(){
        nr_stoc = nr_vandute = 0;
    }
    Expozitie(int _dim1, int _dim2){
        nr_stoc = _dim1;
        nr_vandute = _dim2;
        Stoc.resize(nr_stoc);
        Vandute.resize(nr_vandute);
    }
    Expozitie(const Expozitie& old_expo){
        for(Supersport* C:Stoc)
            delete C;
        for(Supersport* C:Vandute)
            delete C;
        this->nr_stoc = old_expo.nr_stoc;
        this->nr_vandute = old_expo.nr_vandute;
        Stoc.resize(nr_stoc);
        Vandute.resize(nr_vandute);
        for(int i = 0; i<nr_stoc; i++){
            Supersport *aux = new Supersport;
            aux = old_expo.Stoc[i];
            this->Stoc[i] = aux;
        }
        for(int i = 0; i<nr_vandute; i++){
            Supersport *aux = new Supersport;
            aux = old_expo.Vandute[i];
            this->Vandute[i] = aux;
        }
    }
    ~Expozitie(){
        for(int i = 0;i< nr_stoc;i++)
            delete Stoc[i];
        Stoc.resize(0);
        nr_stoc = 0;

        for(int i = 0;i< nr_vandute;i++)
            delete Vandute[i];
        Vandute.resize(0);
        nr_vandute = 0;
    }
    //Overloaded operators
    Expozitie &operator-=(int _id);
    //Functions
    void add_to_stock(Supersport &C);
    bool sell(int _id);
    void showexpo(ostream& out);
    void showsold(ostream& out);
};
int Expozitie<Supersport>::car_id = 0;
void Expozitie<Supersport>::add_to_stock(Supersport &C){
    Supersport *aux = new Supersport;
    *aux = C;
    Stoc.push_back(aux);
    nr_stoc = Stoc.size();
    Stoc[nr_stoc-1] -> setid(++car_id);

}
Expozitie<Supersport> &Expozitie<Supersport>::operator-=(int _id){
    if(!sell(_id))
        cout<<"ID inexistent; Nimic nu a fost vandut.\n";
    return *this;
}
bool Expozitie<Supersport>::sell(int _id){
    if(Stoc.empty())
        return 0;
    for(int i = 0;i<nr_stoc;i++){
        if(Stoc[i]->getid() == _id){
            Supersport *aux = new Supersport;
            *aux = *Stoc[i];
            Vandute.push_back(aux);
            nr_vandute = Vandute.size();
            if(Stoc.size() > 1){
                Stoc[i] = Stoc[Stoc.size()-1];
                Stoc[Stoc.size()-1] = aux;
            }
            Stoc.pop_back();
            nr_stoc = Stoc.size();
            return 1;
        }
    }
    return 0;
}
void Expozitie<Supersport>::showexpo(ostream &out){
    if(Stoc.empty()){
        out<<"    Expozitia este momentan goala.\n";
        return;
    }
    out<<"    Masinile care se afla in expozitie sunt:\n";
    for(Supersport *C:Stoc)
        out<<*C<<"\n";
    out<<"\n";
}
void Expozitie<Supersport>::showsold(ostream &out){
    if(Vandute.empty()){
        out<<"    Nicio masina nu a fost vanduta momentan.\n";
        return;
    }
    out<<"    Masinile care au fost in expozitie, dar au fost vandute, sunt:\n";
    for(Supersport *C:Vandute)
        out<<*C<<"\n";
    out<<"\n";
}



template<class T> void citire_afisare_MASINI(string &n, Expozitie<T> &expo){
    Car m1;
    Coupe m2;
    CoupeFourDoor m3;
    HotHatch m4;
    Cabrio m5;
    Supersport m6;
    T t1;
    if(typeid(m1).name() != typeid(t1).name() && typeid(m2).name() != typeid(t1).name() && typeid(m3).name() != typeid(t1).name() && typeid(m4).name() != typeid(t1).name() && typeid(m5).name() != typeid(t1).name() && typeid(m6).name() != typeid(t1).name()){
        cout<<"The function was called for a type other than Car or its derived types\n";
        return;
    }

    bool ok=0;
    int nr_masini;
    cout<<"Bun venit la targul masinilor sport din luna mai! \nAcesta contine o expozitie auto mixta, in care se regasesc toate tipurile de masini sport: \n    Coupe, Coupe in 4 usi, HotHatch, Cabrio si Supersport\n\n";
    while(!ok){
        ok =1;
        try{
            cout<<"Introduceti numarul de masini care vor fi introduse: ";
            getline(cin, n);
            for(char c:n){
                if(c < '0' || c > '9')
                    throw 3;
            }
            if(!n.length() || n.length() > 9)
                throw 's';
            nr_masini = atoi(n.c_str());

        }
        catch(int){
            cout<<"you have not inserted a number\n";
            ok = 0;
        }
        catch(char){
            cout<<"You either didn't insert anything or the number you have inserted is too big\n";
            ok = 0;
        }

    }
    if(nr_masini == 0)
        return;


    if(typeid(m1).name() == typeid(t1).name()){
        cout<<"Pentru fiecare masina introdusa, veti specifica intai tipul acesteia, dupa cum urmeaza:\n    1 = Coupe;\n    2 = Coupe in 4 usi;\n    3 = HotHatch;\n    4 = Cabrio;\n    5 = Supersport;\n    0 = Masina basic;\n";
        string fakeop;
        int op;
        for(int i=0;i<nr_masini;i++){
            ok = 0;
            while(!ok){
                ok = 1;
                try{
                    cout<<"\nTIP MASINA:";
                    getline(cin, fakeop);
                    if(fakeop.length() != 1 || (fakeop.front() < '0'  || fakeop.front() > '5'))
                        throw 33;
                    op = atoi(fakeop.c_str());
                }
                catch(int){
                    cout<<"Va rugam introduceti O SINGURA cifra intre 0 si 5 (nu se accepta sa nu introduceti nimic)\n";
                    ok = 0;
                }
            }

                switch(op){
                case 0:{
                    Car aux;
                    cin>>aux;
                    expo.push_back(aux);
                    break;
                    }
                case 1:{
                    Coupe aux;
                    cin>>aux;
                    expo.push_back(aux);
                    break;
                    }
                case 2:{
                    CoupeFourDoor aux;
                    cin>>aux;
                    expo.push_back(aux);
                    break;
                    }
                case 3:{
                    HotHatch aux;
                    cin>>aux;
                    expo.push_back(aux);
                    break;
                    }
                case 4:{
                    Cabrio aux;
                    cin>>aux;
                    expo.push_back(aux);
                    break;
                    }
                case 5:{
                    Supersport aux;
                    cin>>aux;
                    expo.push_back(aux);
                    break;
                    }
                default:{
                    break;
                    }
                }

            }

        cout<<"\nMasinile expuse:\n"<<expo;
        cout<<"=====================================================================================================\n";
        cout<<"                    <o~o/                                         <o~o/                              \n";
        cout<<"  -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -    -   \n";
        cout<<"      \\o~o>                         \\o~o>                                       \\o~o>             \n";
        cout<<"=====================================================================================================\n\n";
    }
    else{
        cout<<"Bun venit la expozitia auto! In aceasta expozitie se regasesc doar masini de tip "<<typeid(t1).name()<<"\n";

    }


}

void meniu_supersport(Expozitie<Supersport> &expo){
    system("pause");
    cout<<"\nBun venit la expozitia de masini Supersport!\n\n";
    cout<<"Acesta este un meniu in care puteti gestiona expozitia (ea este momentan goala).\nUrmatoarele operatii sunt posibile:    1 = Expunerea unei noi masini;\n";
    cout<<"                                       2 = Vanzarea masinii supersport respective ID-ului precizat de utilizator;\n                                       3 = Afisarea masinilor expuse;\n";
    cout<<"                                       4 = Afisarea masinilor vandute;\n                                       0 = Iesire;\n";
    string fakeop;
    int op;
    while(true){
        cout<<"\nDati optiune: ";
        bool ok = 0;
        while(!ok){         ///Citesc optiunea
            try{
                ok = 1;
                getline(cin, fakeop);
                if(fakeop.length() == 0)
                    throw 't';
                if(fakeop.length() > 1)
                    throw 5;
                for(char c:fakeop)
                    if(c < '0' || c > '9')
                        throw 2.2;
                op = atoi(fakeop.c_str());
            }
            catch(char){
                ok = 0;
            }
            catch(int){
                cout<<"Number is too big, negative, or not actually a number!\n";
                ok = 0;
            }
            catch(double){
                cout<<"That is not a number!\n";
                ok = 0;
            }
        }


        switch(op){
            case 0:{
                break;
                }
            case 1:{
                cout<<"Introduceti datele pentru noua masina:\n";
                Supersport aux;
                cin>>aux;
                expo.add_to_stock(aux);
                break;
                }
            case 2:{
                cout<<"Masina cu urmatorul ID va fi vanduta. ";
                cout<<"ID = ";
                string fakeid;
                int _id;
                ok = 0;
                while(!ok){         ///Citesc id-ul
                    try{
                        ok = 1;
                        getline(cin, fakeid);
                        if(fakeid.length() == 0)
                            throw 't';
                        if(fakeid.length() > 9)
                            throw 5;
                        for(char c:fakeid)
                            if(c < '0' || c > '9')
                                throw 2.2;
                        _id = atoi(fakeid.c_str());
                    }
                    catch(char){
                        ok = 0;
                    }
                    catch(int){
                        cout<<"Number is too big or not a number\n                                      ID = ";
                        ok = 0;
                    }
                    catch(double){
                        cout<<"That is not a number!\n                                      ID = ";
                        ok = 0;
                    }
                }
                expo -= _id;
                break;
                }
            case 3:{
                expo.showexpo(cout);
                break;
                }
            case 4:{
                expo.showsold(cout);
                break;
                }
            default:{
                cout<<"    Optiune invalida\n";
                }

        }
        if(op == 0)
            break;
    }




}

int main()
{
    Expozitie<Car> expo;
    string n;
    citire_afisare_MASINI(n, expo);

    Expozitie<Supersport> superexpo;
    meniu_supersport(superexpo);

    return 0;
}
