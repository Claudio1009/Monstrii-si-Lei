#include <string>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <random>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>
#include <sstream>
#include <stdexcept>

using namespace std;
class Generator
{
public:
    Generator() : generator_(std::random_device{}()) {}

    // Generează un nume aleatoriu
    std::string GenereazaNume()
    {
        static const char *nume[] = {"Anabelle", "John", "Marie", "Travis", "Elena", "Ahmed", "Davies", "Antonio", "Xander", "Medelin", "Kylie", "Kendall", "Kim", "Fred"};
        static const char *prenume[] = {"Cage", "Scott", "Doe", "Smith", "Al Raed", "Raider", "Evans", "Stark", "Shaggy", "Ionita", "West", "Adams", "Future", "Ciupitu"};

        std::uniform_int_distribution<int> distribution(0, 13);
        return std::string(nume[distribution(generator_)]) + " " + prenume[distribution(generator_)];
    }

private:
    std::mt19937 generator_;
};

class actori
{
public:
    int generatoractorifig()
    {
        // Deschideți fișierul CSV pentru scriere
        std::cout << "Do you want to add new data to the file (y/n)? ";
        char add_data;
        std::cin >> add_data;

        if (add_data == 'y')
        {
            FILE *file = fopen("wednesdayCast.csv", "a");
            if (file == NULL)
            {
                // Eroare la deschiderea fișierului
                return 1;
            }

            Generator generator;
            // Generați aleatoriu 132 de actori cu nume și rol de figurant
            for (int i = 0; i < 132; i++)
            {
                // Generează un nume aleatoriu
                std::string nume = generator.GenereazaNume();

                // Scrieți numele și rolul actorului în fișierul CSV
                fprintf(file, "%s,figurant\n", nume.c_str());
            }
            // Închideți fișierul CSV
            fclose(file);
        }
    }
    int listaActori()
    {
        FILE *file = fopen("wednesdayCast.csv", "r");
        if (file == NULL)
        {

            return 1;
        }
        char nume[256], rol[256];

        fscanf(file, "%*[^\n]\n");

        while (fscanf(file, "%[^,],%[^\n]\n", nume, rol) == 2)
        {
            printf("Actorul %s a jucat rolul %s.\n", nume, rol);
        }
        fclose(file);
    }
};

class MonstersCounter
{
protected:
// Un map pentru a stoca numărul de monștri din fiecare tip
    std::map<std::string, int> counts;
    int vampireCost = 230;
    int werewolfCost = 555;
    int mermaidCost = 345;
    int seerCost = 157;
    int humanCost = 55;

// O listă cu tipurile de monștri
    std::vector<std::string> monsterTypes{ "Vampiri", "Vârcolaci", "Sirene", "Clarvăzători", "Om" };
public:
    MonstersCounter()
    {
// Inițializăm numărul de monștri pentru fiecare tip la 0
        for (const auto& type : monsterTypes)
        {
            counts[type]= 0;
        }
    }

// Getter pentru membru counts
    std::map<std::string, int> getCounts() const
    {
        return counts;
    }

// Setter pentru membru counts
    void setCounts(const std::map<std::string, int>& newCounts)
    {
        counts = newCounts;
    }

// Getter pentru membru monsterTypes
    std::vector<std::string> getMonsterTypes() const
    {
        return monsterTypes;
    }

// Setter pentru membru monsterTypes
    void setMonsterTypes(const std::vector<std::string>& newTypes)
    {
        monsterTypes = newTypes;
    }

// Getter pentru vampireCost
    int getVampireCost() const
    {
        return vampireCost;
    }

// Setter pentru vampireCost
    void setVampireCost(int newCost)
    {
        vampireCost = newCost;
    }

// Getter pentru werewolfCost
    int getWerewolfCost() const
    {
        return werewolfCost;
    }

// Setter pentru werewolfCost
    void setWerewolfCost(int newCost)
    {
        werewolfCost = newCost;
    }

// Getter pentru mermaidCost
    int getMermaidCost() const
    {
        return mermaidCost;
    }

// Setter pentru mermaidCost
    void setMermaidCost(int newCost)
    {
        mermaidCost = newCost;
    }

// Getter pentru seerCost
    int getSeerCost() const
    {
        return seerCost;
    }

// Setter pentru seerCost
    void setSeerCost(int newCost)
    {
        seerCost = newCost;
    }
// Getter pentru humanCost
    int getHumanCost() const
    {
        return humanCost;
    }

// Setter pentru humanCost
    void setHumanCost(int newCost)
    {
        humanCost = newCost;
    }

// Adaugă un monstru de un anumit tip la numărătoare
    virtual void addMonster(const std::string& type)
    {
        counts[type]++;
    }

// Generează aleator un monstru pentru o persoană
    virtual std::string generateMonster(const std::string& name)
    {
        // Amestecăm lista cu tipurile de monștri
        std::random_shuffle(monsterTypes.begin(), monsterTypes.end());

        // Luăm primul element din listă pentru a obține un tip aleator de monstru
        std::string monsterType = monsterTypes[0];

        // Adăugăm monstrul la numărătoare
        addMonster(monsterType);

        return monsterType;
    }

// Procesează datele din fișierul "wednesdayCast.csv" și afișează numărul de monștri din fiecare tip
    void countPersonaje()
    {
        // Deschide fișierul "wednesdayCast.csv"
        std::ifstream file("wednesdayCast.csv");

        // Citim fiecare linie din fișier
        std::string line;
        while (std::getline(file, line))
        {
            // Separăm informațiile din linie după virgulă
            std::istringstream linestream(line);
            std::string cell;

            // Primul element din linie este numele persoanei
            std::getline(linestream, cell, ',');

            // Generăm aleator un monstru pentru persoana respectivă
            generateMonster(cell);
        }

        // Închide fișierul
        file.close();

        // Afișează numărul de monștri din fiecare tip
        int vampireCount = 0;
        int werewolfCount = 0;
        int mermaidCount = 0;
        int seerCount = 0;
        int humanCount = 0;

        // Afișează numărul de monștri din fiecare tip
        std::map<std::string, int> counts = getCounts();
        for (const auto& [type, count] : counts)
        {
            if (type == "Vampiri")
            {
                vampireCount = count;
            }
            else if (type == "Vârcolaci")
            {
                werewolfCount = count;
            }
            else if (type == "Sirene")
            {
                mermaidCount = count;
            }
            else if (type == "Clarvăzători")
            {
                seerCount = count;
            }
            else if (type == "Om")
            {
                humanCount = count;
            }
        }
        std::cout << "Numarul de vampiri: " << vampireCount << std::endl;
        std::cout << "Numarul de varcolaci: " << werewolfCount << std::endl;
        std::cout << "Numarul de sirene: " << mermaidCount << std::endl;
        std::cout << "Numarul de clarvazatori: " << seerCount << std::endl;
        std::cout << "Numarul de oameni: " << humanCount << std::endl;
    }
    int calculateProduct()
    {
        countPersonaje();
        // Obținem numărul de vampiri și vârcolaci
        int vampireCount = counts["Vampiri"];
        int werewolfCount = counts["Varcolaci"];
        int mermaidCount = counts["Sirene"];
        int seerCount = counts["Clarvazatori"];
        int humanCount = counts["Om"];

        // Calculăm produsul dintre numărul de vampiri și costul pentru un vampir
        int vampireProduct = vampireCount * vampireCost;

        // Calculăm produsul dintre numărul de vârcolaci și costul pentru un vârcolac
        int werewolfProduct = werewolfCount * werewolfCost;

        // Calculăm produsul dintre numărul de vampiri și costul pentru un vampir
        int mermaidProduct = mermaidCount * mermaidCost;

        // Calculăm produsul dintre numărul de vârcolaci și costul pentru un vârcolac
        int seerProduct = seerCount * seerCost;

        // Calculăm produsul dintre numărul de vampiri și costul pentru un vampir
        int humanProduct = humanCount * humanCost;

        // Calculăm și returnăm suma celor două produse
        return vampireProduct + werewolfProduct + mermaidProduct + seerProduct + humanProduct;
    }
};

class BusRental
{
private:
// Costul pentru închirierea unui autocar
    int rentalCost;

// Capacitatea unui autocar
    int busCapacity;

// Numărul de persoane care trebuie transportate
    int numPersons;

// Numărul de autocare necesare pentru a transporta persoanele
    int numBuses;
public:
// Constructor pentru clasa BusRental
    // Constructor pentru clasa BusRental
    BusRental(int cost, int capacity) : rentalCost(cost), busCapacity(capacity)
    {
// Inițializăm numărul de persoane care trebuie transportate și numărul de autocare necesare la 0
        numPersons = 0;
        numBuses = 0;
    }

// Destructor pentru clasa BusRental
    ~BusRental()
    {
        std::cout << "\nObiectul BusRental a fost distrus." << std::endl;
    }

// Getter pentru numărul de autocare necesare
    int getNumBuses() const
    {
        return numBuses;
    }

// Getter pentru costul total pentru închirierea autocarelor
    int getTotalCost() const
    {
        return numBuses * rentalCost;
    }

// Metodă pentru a citi datele despre persoanele care trebuie transportate din fișier
    void readPersonsFromFile(const std::string& fileName)
    {
        std::ifstream file(fileName);

        std::string line;
        while (std::getline(file, line))
        {
            // Adăugăm numărul de persoane care trebuie transportate
            numPersons++;
        }

        // Închide fișierul
        file.close();
    }

// Metodă pentru a calcula numărul de autocare necesare pentru a transporta persoanele
    void calculateNumBuses()
    {
        numBuses = numPersons / busCapacity;
        if (numPersons % busCapacity > 0)
        {
            numBuses++;
        }
    }

// Metodă pentru a transporta persoanele de la aeroport la castel
    int transportPersons()
    {
        calculateNumBuses();
        std::cout << "Numarul de persoane care trebuie transportate: " << numPersons << std::endl;
        std::cout << "Numarul de autocare necesare: " << numBuses << std::endl;
        //   std::cout << "Costul total pentru închirierea autocarelor: " << numBuses * rentalCost << " lei" << std::endl;
        return numBuses * rentalCost;
    }
};

class InchiriereCastel
{
private:
    int rata_zilnica;
    int rata_reducere;

public:

    int get_pret_redus(int zile)
    {
        if (zile <= 0)
            throw std::invalid_argument("Numar de zile invalid");

        int pret_total = rata_zilnica * zile;
        int reducere = 0;
        if (zile >= 10)
        {
            while (zile >= 10)
            {
                reducere += pret_total * rata_reducere / 100;
                zile -= 10;
            }
        }
        return pret_total - reducere;
    }

    int calcul()
    {
        int rata_zilnica = 10000, rata_reducere = 2, zile;
        std::cout << "Introduceti numarul de zile: ";
        std::cin >> zile;
        InchiriereCastel inchiriere;
        inchiriere.rata_zilnica = rata_zilnica;
        inchiriere.rata_reducere = rata_reducere;
        try
        {
            int pret_redus = inchiriere.get_pret_redus(zile);
            return pret_redus;
            // std::cout << "Pretul redus este: " << pret_redus << " lei." << std::endl;
        }
        catch (const std::invalid_argument& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
};

class Camera
{
public:
    virtual int getNumarPersoane() const = 0;
    virtual int getCostPeNoapte() const = 0;
    virtual int calculeazaCostTotal(int numarCamere) const
    {
        return numarCamere * getCostPeNoapte();
    }
};

class Camera2Persoane : public Camera
{
public:
    int getNumarPersoane() const
    {
        return 2;
    }
    int getCostPeNoapte() const
    {
        return 350;
    }

    static int calculeazaNumarCamere(int numarPersoane)
    {
        return (numarPersoane + 1) / 2;
    }
};

class Camera3Persoane : public Camera
{
public:
    int getNumarPersoane() const
    {
        return 3;
    }
    int getCostPeNoapte() const
    {
        return 420;
    }

    static int calculeazaNumarCamere(int numarPersoane)
    {
        return (numarPersoane + 2) / 3;
    }
};

int camereHotel()
{
    int numarActoriFiguranti = 132;
    int numarActoriCastInit = 735;
    int numarCamere2Persoane = Camera2Persoane::calculeazaNumarCamere(numarActoriCastInit);
    int numarCamere3Persoane = Camera3Persoane::calculeazaNumarCamere(numarActoriFiguranti);

    Camera2Persoane camera2persoane;
    Camera3Persoane camera3persoane;

    int costTotal2Persoane = camera2persoane.calculeazaCostTotal(numarCamere2Persoane);
    int costTotal3Persoane = camera3persoane.calculeazaCostTotal(numarCamere3Persoane);

    std::cout << "Cost total camere 2 persoane pentru " << numarActoriCastInit
              << " persoane: " << costTotal2Persoane << " lei pe noapte" << std::endl;
    std::cout << "Cost total camere 3 persoane pentru " << numarActoriFiguranti
              << " persoane: " << costTotal3Persoane << " lei pe noapte" << std::endl;
    return costTotal2Persoane + costTotal3Persoane;
}

template <typename T>
class BeverageCostCalculator
{
public:
    T CalculateCost(T water_cost, T coffee_cost, T juice_cost, int num_people, T water_consumption, T coffee_consumption, T juice_consumption)
    {
        if(num_people % 2 == 1)return water_cost * (((num_people + 1) * water_consumption)/2) + coffee_cost * (((num_people + 1) * coffee_consumption)/1) + juice_cost * (((num_people + 1) * juice_consumption)/2);
        else return water_cost * ((num_people  * water_consumption)/2) + coffee_cost * ((num_people * coffee_consumption)/1) + juice_cost * ((num_people * juice_consumption)/2);
    }
};

class actorCastFull
{
private:
    string nume;
    string dieta;
public:
    // constructor pentru a inițializa numele și dieta actorului
    actorCastFull(string nume, string dieta)
    {
        this->nume = nume;
        this->dieta = dieta;
    }

    // metodă pentru a obține numele actorului
    string getNume()
    {
        return nume;
    }

    // metodă pentru a obține dieta actorului
    string getDieta()
    {
        return dieta;
    }

    double calculeazaCostTotal(int orice, int vegetariana, int flexitariana)
    {
        // asociem fiecarui tip de dieta un cost diferit
        double costOrice = 100;
        double costVegetariana = 120;
        double costFlexitariana = 110;
        // calculam costul total pentru fiecare tip de dieta
        double costOriceTotal = orice * costOrice;
        double costVegetarianaTotal = vegetariana * costVegetariana;
        double costFlexitarianaTotal = flexitariana * costFlexitariana;
        // calculam costul total pentru toate dietele
        double costTotal = costOriceTotal + costVegetarianaTotal + costFlexitarianaTotal;
        // returnam costul total
        return costTotal;
    }

    int dietaFisier()
    {
        // array cu tipurile de diete posibile
        string diete[] = {"orice", "vegetariană", "flexitariană"};

        // contoare pentru diete oricare, vegetariane si flexitariane
        int orice = 0, vegetariana = 0, flexitariana = 0;

        // deschidem fișierul CSV de intrare
        ifstream fisierIntrare("wednesdayCast.csv");
        // verificăm dacă fișierul a putut fi deschis
        if (!fisierIntrare.is_open())
        {
            cerr << "Eroare la deschiderea fisierului de intrare!" << endl;
            return 1;
        }

        // deschidem fișierul text de ieșire
        ofstream fisierIesire("diete.csv");
        // verificăm dacă fișierul a putut fi deschis
        if (!fisierIesire.is_open())
        {
            cerr << "Eroare la deschiderea fisierului de iesire!" << endl;
            return 1;
        }

        // citiți linie cu linie din fișierul CSV
        string linie;
        while (getline(fisierIntrare, linie))
        {
            // utilizați un obiect stringstream pentru a descompune linia în valori separate
            stringstream ss(linie);
            string nume, rol;
            // citiți numele și rolul actorului
            getline(ss, nume, ',');
            getline(ss, rol, ',');
            // alegem aleatoriu o dieta din cele 3 tipuri posibile
            string dieta = diete[rand() % 3];
            // creați un obiect actor cu numele și dieta
            actorCastFull a(nume, dieta);
// scrieți informațiile despre actor în fișierul de ieșire
            fisierIesire << a.getNume() << ", " << a.getDieta() << endl;


// incrementam contorul pentru tipul de dieta ales
            if (dieta == "orice") orice++;
            else if (dieta == "vegetariană") vegetariana++;
            else if (dieta == "flexitariană") flexitariana++;
        }

// închideți fișierele
        fisierIntrare.close();
        fisierIesire.close();

// afisam numarul de diete de fiecare tip
        cout << "Numarul de diete oricare: " << orice << endl;
        cout << "Numarul de diete vegetariane: " << vegetariana << endl;
        cout << "Numarul de diete flexitariane: " << flexitariana << endl;

        double costTotal = calculeazaCostTotal(orice, vegetariana, flexitariana);
        return costTotal;
        return 0;
    }
};

class Menu
{
public:
    // Constructor
    Menu(std::string dietType) : dietType_(dietType) {}

    // Virtual function for generating a menu
    virtual void generateMenu() = 0;

    // Function for writing the menu to a CSV file
    void writeToCSV(std::string filename)
    {
        std::ofstream file(filename);
        file << "Ciorba,Fel principal,Desert\n";
        for (const auto& menu : menus_)
        {
            file << menu[0] << "," << menu[1] << "," << menu[2] << "\n";
        }
        file.close();
    }

//protected:
    std::string dietType_;
    std::vector<std::vector<std::string>> menus_;
};

class OmnivorousMenu : public Menu
{
public:
    // Constructor
    OmnivorousMenu() : Menu("Orice") {}

    // Generate a random omnivorous menu
    void generateMenu()
    {
        std::vector<std::string> menu;
        menu.push_back(getRandomSoup());
        menu.push_back(getRandomMainCourse());
        menu.push_back(getRandomDessert());
        menus_.push_back(menu);
    }

private:
    // Private functions for generating random menu items
    std::string getRandomSoup()
    {
        std::vector<std::string> soups = {"Ciorba de pui", "Ciorba de perisoare", "Ciorba de vacuta", "Supa de pui"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, soups.size() - 1);
        return soups[distribution(generator)];
    }

    std::string getRandomMainCourse()
    {
        std::vector<std::string> mainCourses = {"Friptura", "Tochitura", "Pui la cuptor", "Chiftele cu sos"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, mainCourses.size() - 1);
        return mainCourses[distribution(generator)];
    }
    std::string getRandomDessert()
    {
        std::vector<std::string> desserts = {"Cheesecake", "Prajitura cu ciocolata", "Placinta cu mere", "Inghetata"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, desserts.size() - 1);
        return desserts[distribution(generator)];
    }
};

class VegetarianMenu : public Menu
{
public:
    // Constructor
    VegetarianMenu() : Menu("Vegetarian") {}

    // Generate a random vegetarian menu
    void generateMenu()
    {
        std::vector<std::string> menu;
        menu.push_back(getRandomSoup());
        menu.push_back(getRandomMainCourse());
        menu.push_back(getRandomDessert());
        menus_.push_back(menu);
    }

private:
    // Private functions for generating random menu items
    std::string getRandomSoup()
    {
        std::vector<std::string> soups = {"Ciorba de legume", "Ciorba de fasole", "Supa de dovleac"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, soups.size() - 1);
        return soups[distribution(generator)];
    }

    std::string getRandomMainCourse()
    {
        std::vector<std::string> mainCourses = {"Mancarica de ciuperci", "Sala de vinete", "Legume la gratar", "Spaghete"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, mainCourses.size() - 1);
        return mainCourses[distribution(generator)];
    }

    std::string getRandomDessert()
    {
        std::vector<std::string> desserts = {"Chocolate Chip Cookies", "Fursecuri", "Tarta de fructe", "Inghetata"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, desserts.size() - 1);
        return desserts[distribution(generator)];
    }
};

class FlexitarianMenu : public Menu
{
public:
    // Constructor
    FlexitarianMenu() : Menu("Flexitarian") {}

    // Generate a random flexitarian menu
    void generateMenu()
    {
        std::vector<std::string> menu;
        menu.push_back(getRandomSoup());
        menu.push_back(getRandomMainCourse());
        menu.push_back(getRandomDessert());
        menus_.push_back(menu);
    }

private:
    // Private functions for generating random menu items
    std::string getRandomSoup()
    {
        std::vector<std::string> soups = {"Ciorba de peste", "Ciorba de perisoare", "Ciorba de burta", "Ciorba de legume"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, soups.size() - 1);
        return soups[distribution(generator)];
    }

    std::string getRandomMainCourse()
    {
        std::vector<std::string> mainCourses = {"Peste la gratar", "Peste la cuptop", "Chiftelute", "Mancarica de ciuperci"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, mainCourses.size() - 1);
        return mainCourses[distribution(generator)];
    }

    std::string getRandomDessert()
    {
        std::vector<std::string> desserts = {"Cheesecake", "Tort de ciocoalta", "Placinta de mere", "Inghetata"};
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_int_distribution<int> distribution(0, desserts.size() - 1);
        return desserts[distribution(generator)];
    }
};

int menuGeneratorCSV()
{
    OmnivorousMenu omnivorousMenu;
    VegetarianMenu vegetarianMenu;
    FlexitarianMenu flexitarianMenu;

    std::vector<Menu*> menus = {&omnivorousMenu, &vegetarianMenu, &flexitarianMenu};
    std::vector<std::string> dietTypes = {"omnivorous", "vegetarian", "flexitarian"};

    std::ofstream file("meniuri.csv");
    file << "Tip de dieta,Ciorba,Fel principal,Desert\n";
    for (size_t i = 0; i < menus.size(); ++i)
    {
        switch (i)
        {
        case 0:
            omnivorousMenu.generateMenu();
            omnivorousMenu.generateMenu();
            omnivorousMenu.generateMenu();
            break;
        case 1:
            vegetarianMenu.generateMenu();
            vegetarianMenu.generateMenu();
            vegetarianMenu.generateMenu();

            break;
        case 2:
            flexitarianMenu.generateMenu();
            flexitarianMenu.generateMenu();
            flexitarianMenu.generateMenu();
            break;
        }
        for (const auto& items : menus[i]->menus_)
        {
            file << dietTypes[i] << "," << items[0] << "," << items[1] << "," << items[2] << "\n";
        }
    }
    file.close();

    return 0;
}

double convertLeiToDollar(double lei)
{
// presupunem că cota de schimb leu/dolar este 4.5
    double exchangeRate = 4.62;
    return lei / exchangeRate;
}

int main()
{
    string nume,dieta;
    actori a;
    MonstersCounter b;
    BusRental rental(5680, 50);
    InchiriereCastel d;
    BeverageCostCalculator<double> calculator;
    actorCastFull e(nume,dieta);
    system("COLOR 2f");
    int ch;
    int numarZile;
    time_t currentTime;
    time(&currentTime);
    cout<<endl<<ctime(&currentTime);
    cout<<endl<<"                                       ^^^^^^^^^^^^^^^^^^^^^"<<endl;
    cout<<"          ^^^^^^^^^^^^^^^^^^^^^WednesdayProduction Project in C++^^^^^^^^^^^^^^^^^^^^^"<<endl;
    cout<<"                                  *********************************"<<endl;
    cout<<endl<<"                                  <<<<<<<<<<WELCOME BOSS>>>>>>>>>>"<<endl;
    cout<<endl<<"                                                MENU"<<endl;
    cout<<"                                              ********";
    cout<<endl<<"\t\t\t(1) Lista Actorilor";
    cout<<endl<<"\t\t\t(2) Monstri numar";
    cout<<endl<<"\t\t\t(3) Autobuze si pret";
    cout<<endl<<"\t\t\t(4) CastelChirie-CalculatorReducere";
    cout<<endl<<"\t\t\t(5) CamereHotel";
    cout<<endl<<"\t\t\t(6) Cost Bauturi intr-o zi";
    cout<<endl<<"\t\t\t(7) Meniuri Cheltuiala intr-o zi";
    cout<<endl<<"\t\t\t(8) Calculator pe perioade de timp";
    cout<<endl<<"\t\t\t(9) EXIT\n\n";
    cout<<endl<<"\t\t\t^^^^^^^^^^^^^^^^^^^^^";
    cout<<endl<<"\n\t\t\t^^^^^^^^^^^^^^^^^^^^^";
    cout<<endl<<"        \t\t Please ENTER YOUR CHOICE: ";
    cin>>ch;
    switch(ch)
    {
    case 1:
    {
        a.generatoractorifig();
        a.listaActori();
    }
    break;
    case 2:
    {
        int totalMachiajperzi=b.calculateProduct();
        cout<<"Pretul machiajului intr-o zi este "<<totalMachiajperzi<<" de lei.";
    }
    break;
    case 3:
    {
        rental.readPersonsFromFile("wednesdayCast.csv");
// Transportăm persoanele de la aeroport la castel
        int totalBusesDus = rental.transportPersons();
        cout<<"Bani pentru autobuze "<<totalBusesDus<<" de lei."<<endl;
    }
    break;
    case 4:
    {
        int chirieCastel = d.calcul();
        cout<<"Chirie caste "<<chirieCastel<<" lei.";
    }
    break;
    case 5:
    {
        int costTotalHotel = camereHotel();
        cout<< "Hotel pret pe zi "<<costTotalHotel <<" lei.";
    }
    break;
    case 6:
        std::cout <<"Costul total intr-o zi :"<<calculator.CalculateCost(6.0, 30.0, 8.0, 867, 1.0, 0.5, 0.8)<<" lei." << std::endl;
        break;
    case 7:
    {
        menuGeneratorCSV();
        int costDieta = e.dietaFisier();
        cout<<"Cost meniuri "<<costDieta<<" lei.";
    }
    break;
    case 8:
    {
        cout << "Introduceti numarul de zile: ";
        cin>>numarZile;
        ofstream fisierCSV;
        fisierCSV.open("costuri.csv", ios::app);
        fisierCSV << "Numar zile," << "Cost Meniuri," << "Cost machiaj," << "Cost cazare," << "Cost Autobuze," << "Cost Chirie Castel," << "Cost Bauturi," <<"Cost total" << endl;
        switch(numarZile)
        {
        case 30:
        {
            rental.readPersonsFromFile("wednesdayCast.csv");
            int costDieta = convertLeiToDollar(30*e.dietaFisier());
            int totalMachiajperzi =convertLeiToDollar(30*b.calculateProduct());
            int totalBusesDus = convertLeiToDollar(2*rental.transportPersons());
            int chirieCastel = convertLeiToDollar(d.calcul());
            int costTotalHotel =convertLeiToDollar( 30*camereHotel());
            int costBauturi = convertLeiToDollar(30*calculator.CalculateCost(6.0, 30.0, 8.0, 867, 1.0, 0.5, 0.8));
// Calculați costul total pentru 30 de zile
            int costTotal = costDieta + totalMachiajperzi + totalBusesDus + chirieCastel + costTotalHotel + costBauturi;

            // Afișați costul total pentru 30 de zile
            cout << "Costul total pentru " << numarZile << " zile este de " <<costTotal << " $." << endl;

            // Scrieți costul total în fișierul CSV
            fisierCSV << numarZile << ",$ " << costDieta << " ,$" << totalMachiajperzi << " ,$" << costTotalHotel << " ,$" << totalBusesDus << " ,$" << chirieCastel << " ,$"<<costBauturi<< ",$" << costTotal << endl;
        }
        break;
        case 45:
        {
            rental.readPersonsFromFile("wednesdayCast.csv");
            int costDieta = convertLeiToDollar(45*e.dietaFisier());
            int totalMachiajperzi =convertLeiToDollar(45*b.calculateProduct());
            int totalBusesDus = convertLeiToDollar(2*rental.transportPersons());
            int chirieCastel = convertLeiToDollar(d.calcul());
            int costTotalHotel =convertLeiToDollar( 45*camereHotel());
            int costBauturi = convertLeiToDollar(45*calculator.CalculateCost(6.0, 30.0, 8.0, 867, 1.0, 0.5, 0.8));

            // Calculați costul total pentru 45 de zile
            int costTotal = costDieta + totalMachiajperzi + totalBusesDus + chirieCastel + costTotalHotel + costBauturi;

            // Afișați costul total pentru 45 de zile
            cout << "Costul total pentru " << numarZile << " zile este de " << costTotal << " $." << endl;

            // Scrieți costul total în fișierul CSV
            fisierCSV << numarZile << ",$ " << costDieta << " ,$" << totalMachiajperzi << " ,$" << costTotalHotel << " ,$" << totalBusesDus << " ,$" << chirieCastel << " ,$"<<costBauturi<< ",$" << costTotal << endl;
        }
        break;
        case 60:
        {
            rental.readPersonsFromFile("wednesdayCast.csv");
            int costDieta = convertLeiToDollar(60*e.dietaFisier());
            int totalMachiajperzi =convertLeiToDollar(60*b.calculateProduct());
            int totalBusesDus = convertLeiToDollar(2*rental.transportPersons());
            int chirieCastel = convertLeiToDollar(d.calcul());
            int costTotalHotel =convertLeiToDollar( 60*camereHotel());
            int costBauturi = convertLeiToDollar(60*calculator.CalculateCost(6.0, 30.0, 8.0, 867, 1.0, 0.5, 0.8));

            // Calculați costul total pentru 60 de zile
            int costTotal = costDieta + totalMachiajperzi + totalBusesDus + chirieCastel + costTotalHotel + costBauturi;

            // Afișați costul total pentru 60 de zile
            cout << "Costul total pentru " << numarZile << " zile este de " << costTotal << " $." << endl;

            // Scrieți costul total în fișierul CSV

            fisierCSV << numarZile << ",$ " << costDieta << " ,$" << totalMachiajperzi << " ,$" << costTotalHotel << " ,$" << totalBusesDus << " ,$" << chirieCastel << " ,$"<<costBauturi<< ",$" << costTotal << endl;
        }
            break;
            case 100:
            {
                rental.readPersonsFromFile("wednesdayCast.csv");
                int costDieta = convertLeiToDollar(100*e.dietaFisier());
                int totalMachiajperzi =convertLeiToDollar(100*b.calculateProduct());
                int totalBusesDus = convertLeiToDollar(2*rental.transportPersons());
                int chirieCastel = convertLeiToDollar(d.calcul());
                int costTotalHotel =convertLeiToDollar( 100*camereHotel());
                int costBauturi = convertLeiToDollar(100*calculator.CalculateCost(6.0, 30.0, 8.0, 867, 1.0, 0.5, 0.8));

                // Calculați costul total pentru 100 de zile
                int costTotal = costDieta + totalMachiajperzi + totalBusesDus + chirieCastel + costTotalHotel + costBauturi;

                // Afișați costul total pentru 100 de zile
                cout << "Costul total pentru " << numarZile << " zile este de " << costTotal << " $." << endl;

                // Scrieți costul total în fișierul CSV
                fisierCSV << numarZile << ",$ " << costDieta << " ,$" << totalMachiajperzi << " ,$" << costTotalHotel << " ,$" << totalBusesDus << " ,$" << chirieCastel << " ,$"<<costBauturi<< ",$" << costTotal << endl;
            }
            break;
        }
        fisierCSV.close();
        }
        break;
        case 9:
            system("cls");
            cout<<endl<<"\n\t\t\t ^^^^^^^^^^^^^^^^^^^^^\n"<<endl;
            cout<<"\t\t\t ^^^^^^^^^^^^^^^^^^^^^WednesdayProduction Project^^^^^^^^^^^^^^^^^^^^^\n"<<endl;
            cout<<"\t\t\t ^^^^^^^^^^^^^^^^^^^^^\n"<<endl;
            cin.get();
            cin.get();
            exit(0);
            break;
        default:
            system("cls");
            cout<<endl<<"\n\t\t\t^^^^^^^^^^^^^^^^^^^^^\n"<<endl;
            cout<<"\t\t\t   ^^^^^^^^^^^^^^^^^^^^^WednesdayProduction Project IN C++^^^^^^^^^^^^^^^^^^^^^\n"<<endl;
            cout<<"\t\t\t  ^^^^^^^^^^^^^^^^^^^^^\n"<<endl;
            cout<<endl<<endl<<"\n\n\t\t\t<<<Sorry YOU ENTERED WRONG CHOICE>>>>>>>>\n"<<endl;
            cout<<"\t\t\t<<<Hello! PLEASE ENTER the suitable choice>>>>>>>>\n"<<endl;
            cin.get();
            cin.get();
            system("cls");
            main();
        }
        return 0;
    }
