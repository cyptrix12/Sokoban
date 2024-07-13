#include <iostream>
#include <iomanip>

using namespace std;


const int ilosc_ruchow[3] = {10, 50, 25};
const int mapa_wiersze[3]={5, 8, 8};
const int mapa_kolumny[3]={16, 10, 8};
const int pozycja_gracza[3][2] = 
{
    {3, 7},
    {1, 1},
    {2, 2}
};

const char mapa[3][129] = { 
    {
        "################"
        "#         X    #"
        "#      b       #"
        "#              #"
        "################"
    },
    {
        "##########"
        "#    #  X#"
        "#bbb #   #"
        "#    #   #"
        "#    #   #"
        "#X   X   #"
        "#######  #"
        "      ####"
        
    },
    {
        "  ##### "
        "###   # "
        "#X b  # "
        "### bX# "
        "#X##b # "
        "#b# X ##"
        "#      #"
        "########"
    }
};



void wyswietlanie_mapy(int numer_mapy, int &poziom, bool &trzyxtrzy);

void wyswietlenie_menu(int &poziom, bool &trzyxtrzy);

void wygrana_etapu(int etap, int &poziom, bool &trzyxtrzy);

void przegranie_etapu(int etap);

void godmode(int &poziom, bool &trzyxtrzy);

bool can_move(char kierunek, char *plansza, int *lokalizacja, int numer_mapy);

bool can_move_pudelko(char kierunek, char *plansza, int *lokalizacja, int numer_mapy);

int main()
{
    int poziom=0;

    bool trzyxtrzy=true;

    wyswietlenie_menu(poziom, trzyxtrzy);

    return 0;
}

void wyswietlenie_menu(int &poziom, bool &trzyxtrzy)
{
    system("cls");
    char napis[456] = {
    " _______  _______  ___   _  _______  _______  _______  __    _  \n"
    "|       ||       ||   | | ||       ||  _    ||   _   ||  |  | | \n"
    "|  _____||   _   ||   |_| ||   _   || |_|   ||  |_|  ||   |_| | \n"
    "| |_____ |  | |  ||      _||  | |  ||       ||       ||       | \n"
    "|_____  ||  |_|  ||     |_ |  |_|  ||  _   | |       ||  _    | \n"
    " _____| ||       ||    _  ||       || |_|   ||   _   || | |   | \n"
    "|_______||_______||___| |_||_______||_______||__| |__||_|  |__| \n"
    };
    cout << napis;

    cout << endl <<  "cyptrix12" << endl;
    cout << endl << "Wybor etapu - 1, 2, 3\nWyjscie z gry - p\n";

    char input_menu;
    while(cin >> input_menu)
    {
        if(input_menu=='p' || input_menu=='P') exit(0); 
        else if(input_menu=='q' || input_menu=='Q') wyswietlenie_menu(poziom, trzyxtrzy);
        else if(input_menu>='1' && input_menu<='9') 
        {
            const char *wsk_input = &input_menu;
            wyswietlanie_mapy((atoi(wsk_input)-1), poziom, trzyxtrzy);
        }
        else if(input_menu=='~') godmode(poziom, trzyxtrzy);
    }
}

void wyswietlanie_mapy(int numer_mapy, int &poziom, bool &trzyxtrzy)
{
    
    
    if(unsigned(numer_mapy)>((sizeof(mapa))/sizeof(mapa[0])))
    {
        system("cls");
        cout << "Ups, nie ma takiego poziomu! Na razie dostepne sa " << ((sizeof(mapa))/sizeof(mapa[0])) << " etapy!\n\n";
        cout << "Powrot do menu - q\nWyjscie z gry - p\n";
        char input_ups;
        while(cin>>input_ups)
        {
            if(input_ups=='q' || input_ups=='Q') wyswietlenie_menu(poziom, trzyxtrzy);
            else if(input_ups=='p' || input_ups=='P') exit(0);
        }

        wyswietlenie_menu(poziom, trzyxtrzy);
    }
    if(poziom<numer_mapy)
    {
        system("cls");
        cout << "Ups, nie masz jeszcze dostepu do tej mapy!\nPrzejdz najpierw etap " << poziom+1 << endl << endl;
        cout << "Powrot do menu - q\nWyjscie z gry - p\n";
        char input_ups;
        while(cin>>input_ups)
        {
            if(input_ups=='q' || input_ups=='Q') wyswietlenie_menu(poziom, trzyxtrzy);
            else if(input_ups=='p' || input_ups=='P') exit(0);
        }
    }
    int ilosc_X=0;

    char klon_mapy[sizeof(mapa[numer_mapy])];
    for(unsigned int i=0; i<sizeof(klon_mapy); i++)
    {
        if(mapa[numer_mapy][i]=='X') ilosc_X++;
        klon_mapy[i] = mapa[numer_mapy][i];
    }
    
    
    int klon_pozycji_gracza[2]={pozycja_gracza[numer_mapy][0], pozycja_gracza[numer_mapy][1]};
    int ruchy_gracza=0;
    while(true)
    {
        system("cls");

        int ilosc_B=0;

        klon_mapy[(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]]='@';
        if(trzyxtrzy==true)
        {
            for(int i_wiersze=0; i_wiersze<mapa_wiersze[numer_mapy]; i_wiersze++)
            {
                for(int i=0; i<3; i++)
                {    
                    for(int i_kolumny=0; i_kolumny<mapa_kolumny[numer_mapy]; i_kolumny++)
                        {
                            if(klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='B' && i==0) ilosc_B++;
                            
                            
                            if((klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='b' || klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='B') && (i==0 || i==2)) cout << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]] << " " << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]];
                            else if((klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='b' || klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='B') && i==1) cout << " " << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]] << " ";
                            
                            else if(klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='@' && (i==0 || i==2)) cout << " " << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]] << " ";

                            else cout << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]] << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]] << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]];
                            
                            
                            if(i==0 && i_wiersze==0 && i_kolumny+1==mapa_kolumny[numer_mapy]) cout << "\tPoruszanie magazynierem - wsad";
                            else if(i==2 && i_wiersze==0 && i_kolumny+1==mapa_kolumny[numer_mapy]) cout << "\tPowrot do menu - q";
                            else if(i==1 && i_wiersze==1 && i_kolumny+1==mapa_kolumny[numer_mapy]) cout << "\tPozostale skrzynie: " << ilosc_X-ilosc_B;
                            else if(i==0 && i_wiersze==2 && i_kolumny+1==mapa_kolumny[numer_mapy]) cout << "\tDostepne ruchy: " << ilosc_ruchow[numer_mapy]-ruchy_gracza;
                        }
                    cout << endl;
                }

            }
        }
        else
        {
            for(int i_wiersze=0; i_wiersze<mapa_wiersze[numer_mapy]; i_wiersze++)
            {
                for(int i_kolumny=0; i_kolumny<mapa_kolumny[numer_mapy]; i_kolumny++)
                {
                    if(klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]]=='B') ilosc_B++;
                    cout << klon_mapy[i_kolumny+i_wiersze*mapa_kolumny[numer_mapy]];

                }
                cout << endl;
            }

            cout << endl << "Poruszanie magazynierem - wsad\nPowrot do menu - q\n" << endl << "Pozostale skrzynie: " << ilosc_X-ilosc_B << endl;
        
            cout << "Dostepne ruchy: " << ilosc_ruchow[numer_mapy]-ruchy_gracza << endl;
        }

        if((ilosc_X-ilosc_B)==0) wygrana_etapu(numer_mapy, poziom, trzyxtrzy);
        else if(ilosc_ruchow[numer_mapy]-ruchy_gracza==0) wyswietlanie_mapy(numer_mapy, poziom, trzyxtrzy);

        char input_w_grze;
        cin >> input_w_grze;

        switch (input_w_grze)
        {
        case 'q':
        case 'Q':
            wyswietlenie_menu(poziom, trzyxtrzy);
            break;
        case 'w':
        case 'W':
            if(can_move(input_w_grze, klon_mapy, klon_pozycji_gracza, numer_mapy)==true)
            {
                if(mapa[numer_mapy][(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] == 'X')
                {
                    klon_mapy[(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] = 'X';
                }
                else 
                {
                    klon_mapy[klon_pozycji_gracza[0]*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]]=' ';
                }
                klon_pozycji_gracza[0]--;
                ruchy_gracza++;
            }
            break;
        case 's':
        case 'S':
            if(can_move(input_w_grze, klon_mapy, klon_pozycji_gracza, numer_mapy)==true)
            {
                if(mapa[numer_mapy][(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] == 'X')
                {
                    klon_mapy[(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] = 'X';
                }
                else klon_mapy[klon_pozycji_gracza[0]*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]]=' ';
                klon_pozycji_gracza[0]++;
                ruchy_gracza++;
            }
            break;
        case 'a':
        case 'A':
            if(can_move(input_w_grze, klon_mapy, klon_pozycji_gracza, numer_mapy)==true)
            {
                if(mapa[numer_mapy][(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] == 'X')
                {
                    klon_mapy[(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] = 'X';
                }
                else klon_mapy[klon_pozycji_gracza[0]*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]]=' ';
                klon_pozycji_gracza[1]--;
                ruchy_gracza++;
            }
            break;
        case 'd':
        case 'D':
            if(can_move(input_w_grze, klon_mapy, klon_pozycji_gracza, numer_mapy)==true)
            {
                
                if(mapa[numer_mapy][(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] == 'X')
                {
                    klon_mapy[(klon_pozycji_gracza[0])*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]] = 'X';
                }
                else klon_mapy[klon_pozycji_gracza[0]*mapa_kolumny[numer_mapy]+klon_pozycji_gracza[1]]=' ';
                klon_pozycji_gracza[1]++;
                ruchy_gracza++;
            }
            break;
        
        
        default:
            break;
        }


    }
}

void wygrana_etapu(int etap, int &poziom, bool &trzyxtrzy)
{
    system("cls");

    cout << "GRATULACJE UKONCZYLES ETAP " << etap+1 << endl << endl;
    if(poziom==etap && poziom!=2)
    {
        cout << "ODBLOKOWANO KOLEJNY ETAP!" << endl << endl;
        poziom++;
    }
    else if(poziom==2)
    {
        cout << "GRATULACJE PRZESZEDLES WSZYSTKIE POZIOMY!!!" << endl << endl;
    }

    cout << "Powrot do menu - q\nWyjscie z gry - p\n";

    char input_wygrana;
        while(cin>>input_wygrana)
        {
            if(input_wygrana=='q' || input_wygrana=='Q') wyswietlenie_menu(poziom, trzyxtrzy);
            else if(input_wygrana=='p' || input_wygrana=='P') exit(0);
        }
}

bool can_move(char kierunek, char *plansza, int *lokalizacja, int numer_mapy)
{
    switch (kierunek)
    {
    case 'w':
    case 'W':
        if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]==' ')
        {
            return true;
        }
        else if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='b' || plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='B')
        {
            int lokalizacja_pudelka[2] = {(lokalizacja[0]-1), lokalizacja[1]};
            if(can_move_pudelko(kierunek, plansza, lokalizacja_pudelka, numer_mapy)==true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='X')
        {
            return true;
        }
        break;
    case 's':
    case 'S':
        if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]==' ')
        {
            return true;
        }
        else if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='b' || plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='B')
        {
            int lokalizacja_pudelka[2] = {(lokalizacja[0]+1), lokalizacja[1]};
            if(can_move_pudelko(kierunek, plansza, lokalizacja_pudelka, numer_mapy)==true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='X')
        {
            return true;
        }
        break;
    case 'a':
    case 'A':
        if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]==' ')
        {
            return true;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='b' || plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='B')
        {
            int lokalizacja_pudelka[2] = {(lokalizacja[0]), lokalizacja[1]-1};
            if(can_move_pudelko(kierunek, plansza, lokalizacja_pudelka, numer_mapy)==true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='X')
        {
            return true;
        }
        break;
    case 'd':
    case 'D':
        if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]==' ')
        {
            return true;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='b' || plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='B')
        {
            
            int lokalizacja_pudelka[2] = {(lokalizacja[0]), lokalizacja[1]+1};
            if(can_move_pudelko(kierunek, plansza, lokalizacja_pudelka, numer_mapy)==true)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='X')
        {
            return true;
        }
        break;

    default:
        break;
    }
    return false;
}

bool can_move_pudelko(char kierunek, char *plansza, int *lokalizacja, int numer_mapy)
{
    switch (kierunek)
    {
    case 'w':
    case 'W':
        if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]==' ')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]='b';
            return true;
        }
        else if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='b' || plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='B')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='X')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0]-1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]='B';
            return true;
        }
        break;
    case 's':
    case 'S':
        if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]==' ')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]='b';
            return true;
        }
        else if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='b' || plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='B')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]=='X')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0]+1)*mapa_kolumny[numer_mapy]+lokalizacja[1]]='B';
            return true;
        }
        break;
    case 'a':
    case 'A':
        if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]==' ')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]='b';
            return true;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='b' || plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='B')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]=='X')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]-1]='B';
            return true;
        }
        break;
    case 'd':
    case 'D':
        
        if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]==' ')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]='b';
            return true;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='#')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='b' || plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='B')
        {
            return false;
        }
        else if(plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]=='X')
        {
            plansza[lokalizacja[0]*mapa_kolumny[numer_mapy]+lokalizacja[1]]=' ';
            plansza[(lokalizacja[0])*mapa_kolumny[numer_mapy]+lokalizacja[1]+1]='B';
            return true;
        }
        break;
    

    default:
        return false;
        break;
    }
    return false;
}

void godmode(int &poziom, bool &trzyxtrzy)
{
    system("cls");
    cout << "Witaj w admin roomie!\n\n";
    
    char input_godmode;
    
    while(true)
    {
    cin >> input_godmode;
    if(input_godmode>='1' && input_godmode<='9') 
        {
            const char *wsk_input = &input_godmode;
            poziom = atoi(wsk_input);
            break;
        }
    }
    cin >> input_godmode;
    if(input_godmode=='t' || input_godmode=='T') trzyxtrzy=true;
    else if(input_godmode=='n' || input_godmode=='N') trzyxtrzy=false;
    wyswietlenie_menu(poziom, trzyxtrzy);
}