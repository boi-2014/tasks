/* Generator danych wejsciowych do zadania Demarkacja
 * Autor: Marek Sommer
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <string>
#include <cstring>
#include <set>
#include <vector>
#include <list>

#include "oi.h"

using namespace std;

typedef long long int ll;
const int infty=2*1000*1000*1000;

// HINT: Uzywamy liczb losowych wylacznie z pakietu oi.h
oi::Random RG(0xC0FFEE);

// losuje licze z przedzialu [a,b], przy pomocy RG
inline int rand_range(int a,int b) { return (RG.rand()%(b-a+1))+a; }

// wartosc bezwzgledna
int bez(int x) { return x<0?-x:x; }
ll bez(ll x) { return x<0?-x:x; }
int signum(int x) { return x?(x<0?-1:1):0; }
int signum(ll x) { return x?(x<0?-1:1):0; }
bool w_przedziale(int p,int k,int x)
{
  if(p>k) return w_przedziale(k,p,x);
  return p < x && x < k;
}

struct wielokat;

vector<wielokat*>dous;

// element listy wierzcholkow wielokata
struct wielokat
{
	wielokat *nas; // wskaznik na nastepny wierzcholek wielokata
	wielokat *pop; // wskaznik na poprzedni wierzcholek wielokata
	int x,y; // wspolrzdne wierzcholka
  int kierunek;

  // czysty konstruktor
  wielokat()
  {
    nas=pop=NULL;
    x=y=0; kierunek=0;
    dous.push_back(this);
  }

  // konstruktor poczatku
  wielokat(int _x,int _y,int _k=0)
  {
    x=_x; y=_y;
    kierunek = _k;
    nas=this; pop=this;
    dous.push_back(this);
  }

	// dodaje nowy wierzcholek, za aktualnym
	wielokat *dodaj_za(int _x,int _y,int _k=0)
	{
		wielokat *wie=new wielokat;
		wie->x=_x; wie->y=_y; wie->kierunek=_k;
		wie->pop=this;
		wie->nas=this->nas;
		this->nas->pop=wie;
		this->nas=wie;
		return wie;
	}

  void podlacz(wielokat *w)
  {
    this->nas=w;
    w->pop=this;
  }

	// usuwa dany wierzcholek
	// !!! nie wywoluje delete !!!
	void usun()
	{
		this->nas->pop = this->pop;
		this->pop->nas = this->nas;
	}

	// dodaje nowy wierzcholek przed aktualnym
	wielokat *dodaj_przed(int _x,int _y,int _k=0) { return this->pop->dodaj_za(_x,_y,_k); }

	// cztery ponizsze funkcje stwierdzaja, czy krawedz za/przed tym wierzcholkiem jest pionowa/pozioma
	bool nas_poz() { return (this->y == this->nas->y); }
	bool nas_pio() { return (this->x == this->nas->x); }
	bool pop_poz() { return this->pop->nas_poz(); }
	bool pop_pio() { return this->pop->nas_pio(); }

	// funkcje, ktore stwierdzaja, czy nastepny/poprzedni wierzcholek ma wporzedna wieksza (1), czy mniejsza (-1)
	int nas_znak()
	{
		if(nas_poz()) return ((this->x)<(this->nas->x))?1:-1;
		else return ((this->y)<(this->nas->y))?1:-1;
	}
	int pop_znak() { return -(this->pop->nas_znak()); }

	// dlugosc krawedzi za/przed aktualnym wierzcholkiem
	int nas_odl() { return bez((this->x)-(this->nas->x))+bez((this->y)-(this->nas->y)); }
	int pop_odl() { return this->pop->nas_odl(); }

	// pole prostokata miedzy nastepna/poprzednia krawedzia, a osia x
	// to pole ma byc skierowane!
	ll nas_pol() { return static_cast<ll>((this->nas->x)-(this->x))*(this->y); }
	ll pop_pol() { return this->pop->nas_pol(); }

  // sprawdza czy punkt (x,y) nalezy do wielokata, jesli nie to go tworzy
  // wartoscia zwracana jest wskaznik na punkt (x,y) w tym wielokacie
  wielokat *wymus_punkt(int x,int y)
  {
    wielokat *p = this;
    do
    {
      if(p->x == x && p->y == y) return p;
      if(p->x == x && p->nas_pio() && w_przedziale(p->y,p->nas->y,y)) return p->dodaj_za(x,y);
      if(p->y == y && p->nas_poz() && w_przedziale(p->x,p->nas->x,x)) return p->dodaj_za(x,y);
      p = p->nas;
    } while ( p != this );
    return NULL;
  }

  // zlicza wierzcholki w wielokacie ! UWAGA ! dziala w O(n)
  int ile_wierzcholkow()
  {
    wielokat *p=this;
    int wyn=0;
    do
    {
      wyn++;
      p=p->nas;
    }
    while(p!=this);
    return wyn;
  }

  wielokat *kopiuj()
  {
    wielokat *p=this;
    wielokat *nowy=new wielokat(p->x,p->y);
    p=p->nas;
    while(p!=this)
    {
      nowy->dodaj_przed(p->x,p->y);
      p=p->nas;
    }
    return nowy;
  }

  void odwroc()
  {
    wielokat *p=this;
    do
    {
      swap(p->nas,p->pop);
      p=p->pop;
    }
    while(p!=this);
  }

  void odbij()
  {
    wielokat *p=this;
    do
    {
      swap(p->x,p->y);
      p=p->nas;
    }
    while(p!=this);
  }

  void obroc()
  {
    wielokat *p = this;
    do
    {
      swap(p->x,p->y);
      p->x *= -1;
      p = p->nas;
    } while ( p != this );
    this->unormuj();
  }

  void przesun(int x,int y)
  {
    wielokat *p=this;
    do
    {
      p->x += x;
      p->y += y;
      p = p->nas;
    }
    while(p!=this);
  }

  void unormuj()
  {
    wielokat *p = this;
    int x = infty, y = infty;
    do
    {
      x = min( x, p->x );
      y = min( y, p->y );
      p = p->nas;
    } while (p != this);
    this->przesun(-x,-y);
  }

  ll skierowane_pole()
  {
    wielokat *p = this;
    ll pole=0LL;
    do
    {
      pole += p->nas_pol();
      p = p->nas;
    } while (p != this);
    return pole;
  }

  ll pole()
  {
    ll x = this->skierowane_pole();
    return x<0?-x:x;
  }

  void ze_wskazowkami()
  {
    if(this->skierowane_pole() < 0LL) this->odwroc();
  }

  void przeciwnie_do_wskazowek()
  {
    if(this->skierowane_pole() > 0LL) this->odwroc();
  }

  pair<int,int>max_wsp_y()
  {
    wielokat *p = this;
    pair<int,int>m = make_pair(infty,-infty);
    do
    {
      m.first = min( m.first, p->y );
      m.second = max( m.second, p->y );
      p = p->nas;
    } while ( p != this );
    return m;
  }

  pair<int,int>max_wsp_x()
  {
    wielokat *p = this;
    pair<int,int>m = make_pair(infty,-infty);
    do
    {
      m.first = min( m.first, p->x );
      m.second = max( m.second, p->x );
      p = p->nas;
    } while ( p != this );
    return m;
  }
};

void czysc()
{
  for(int i=0;i<((int)dous.size());i++) delete dous[i];
  dous.clear();
}

struct drzewo_przedzialowe
{
  int n,n2;
  int *poz;
  ll *drz;
  void czysc()
  {
    for(int i=1;i<n2*2;i++) drz[i] = 0LL;
  }
  int get_poz(int w)
  {
    int p = lower_bound(poz,poz+n,w)-poz;
    assert(0<=p && p<n); assert(poz[p]==w);
    return p;
  }
  void dodaj(int a,int b,int x)
  {
    if( a == b ) return;
    if(a > b)
    {
      dodaj(b,a,-x);
      return;
    }
    a = get_poz(a) + n2; b = get_poz(b)-1 + n2;
    drz[a] += x;
    if( a != b ) drz[b] += x;
    while( (a/2) != (b/2) )
    {
      if(a%2==0) drz[a+1] += x;
      if(b%2==1) drz[b-1] += x;
      a /= 2; b /= 2;
    }
  }
  ll odczyt(int w)
  {
    w = this->get_poz(w) + n2;
    ll wyn = 0LL;
    while(w)
    {
      wyn += drz[w];
      w/=2;
    }
    return wyn;
  }
  drzewo_przedzialowe(vector<int>v)
  {
    sort(v.begin(),v.end());
    v.resize(unique(v.begin(),v.end())-v.begin());
    n = v.size();
    poz = new int[n];
    for(int i=0;i<n;i++) poz[i] = v[i];
    n2 = 1;
    while (n2 < n) n2*=2;
    drz = new ll[2*n2];
    for(int i=1;i<n2*2;i++) drz[i]=0LL;
  }
  ~drzewo_przedzialowe()
  {
    delete poz;
    delete drz;
  }
};

bool popsuty_test;

class TestCase {
  public:
    friend ostream& operator << (ostream& out, const TestCase& testCase) {
      if(popsuty_test)
      {
        wielokat *tmp = testCase.poc;
        pair<int,wielokat*>wyn = make_pair(((int)1e9)+5,tmp);
        do
        {
          if(tmp->nas_poz()) wyn = min( wyn, make_pair(tmp->y,tmp));
          tmp = tmp->nas;
        } while ( tmp != testCase.poc );
        wyn.second->y--;
        wyn.second->nas->y--;
        wyn.second->przesun(0,1);
      }
      if(testCase.poc == NULL)
      {
        popsuty_test = true;
        return out;
      }
      popsuty_test = false;
      out << testCase.poc->ile_wierzcholkow() << "\n";
      wielokat *p=testCase.poc;
      do
      {
        out << p->x << " " << p->y << "\n";
        p=p->nas;
      }
      while(p!=testCase.poc);
      return out;
    }
    TestCase() {}
    wielokat *poc; // wskaznik na pierwszy wierzcholek wielokata
    void usuwaj()
    {
      wielokat *p=poc;
      wielokat *f=NULL;
      do
      {
        f=p->nas;
        delete p;
        p=f;
      }
      while(p!=poc);
    }
};

wielokat *tworz_spirale(int n,int x,int y);
wielokat *tworz_prostokat(int x,int y,int a,int b);
wielokat *tworz_parzysty_wezyk(int os,int y,int min_d,int max_d,int n);
wielokat *tworz_nieparzysty_wezyk(int os,int y,int min_d,int max_d,int n);
wielokat *tworz_podwojna_spirale(int n,int x,int y,int a,int b);
wielokat *tworz_losowy(int n,int min_x,int max_x,int min_y,int max_y);
wielokat *tworz_sklejenie(wielokat *a,wielokat *b);
wielokat *tworz_obok_siebie_rec(int n,int max_wsp,int r);
wielokat *tworz_combo_obok_siebie_rec(int n,int max_wsp,int r);
wielokat *sklej_boczkiem(wielokat *a,wielokat *b);

class ComboObokSiebieRecCase : public TestCase {
  public:
    ComboObokSiebieRecCase (int n,int max_wsp,int r)
    {
      assert ( r<10 );
      poc = tworz_combo_obok_siebie_rec(n,max_wsp,r);
    }
};

class ObokSiebieRecCase : public TestCase {
  public:
    ObokSiebieRecCase (int n,int max_wsp,int r)
    {
      assert( r<10 ); // r nie moze byc zbyt duze
      poc = tworz_obok_siebie_rec(n,max_wsp,r);
    }
};

class ObokSiebieCase : public TestCase {
  public:
    ObokSiebieCase (int n,int min_x,int max_x,int min_y,int max_y)
    {
      poc = tworz_losowy(n/2,min_x,(min_x+max_x)/2,(min_y+max_y)/2,max_y);
      poc = tworz_sklejenie(poc,poc->kopiuj());
    }
};

class LosowyCase : public TestCase {
  public:
    LosowyCase (int n,int min_x,int max_x,int min_y,int max_y)
    {
      poc = tworz_losowy(n,min_x,max_x,min_y,max_y);
    }
};

class ProstokatCase : public TestCase {
  public:
    ProstokatCase (int x,int y,int n,int m)
    {
      poc = tworz_prostokat(x,y,n,m);
    }
};

class WezykParzystyCase : public TestCase {
  public:
    WezykParzystyCase (int os,int y,int min_d,int max_d,int n)
    {
      poc = tworz_parzysty_wezyk(os,y,min_d,max_d,n);
      if(rand_range(0,1)) poc->odbij();
    }
};

class WezykNieparzystyCase : public TestCase {
  public:
    WezykNieparzystyCase (int os,int y,int min_d,int max_d,int n)
    {
      poc = tworz_nieparzysty_wezyk(os,y,min_d,max_d,n);
      if(rand_range(0,1)) poc->odbij();
    }
};

class SpiralaCase : public TestCase {
  public:
    SpiralaCase (int n,int x,int y)
    {
      poc = tworz_spirale(n,x,y);
      if(rand_range(0,1)) poc->odbij();
      else if(rand_range(0,1)) poc->obroc();
      if(rand_range(0,1)) poc->odwroc();
      poc->unormuj();
      poc->przesun(x,y);
    }
};

class PodwojnaSpiralaCase : public TestCase {
  public:
    PodwojnaSpiralaCase (int n,int x,int y,int a,int b)
    {
      poc = tworz_podwojna_spirale(n,x,y,a,b);
      if(rand_range(0,1)) poc->odbij();
      else if(rand_range(0,1)) poc->obroc();
      if(rand_range(0,1)) poc->odwroc();
      poc->unormuj();
      poc->przesun(x,y);
    }
};

class SklejBokiemWezykCase : public TestCase {
  public:
    SklejBokiemWezykCase (int n,int x,int min_d,int max_d)
    {
      poc = tworz_nieparzysty_wezyk(500*1000*1000,0,min_d,max_d,n);
      for(int i=0;i<x;i++)
      {
        wielokat *tmp = poc->kopiuj();
        tmp->odbij();
        poc->unormuj();
        tmp->unormuj();
        poc->przesun(0,1);
        poc = sklej_boczkiem(poc,tmp);
      }
      if(rand_range(0,1)) poc->odbij();
      else if(rand_range(0,1)) poc->obroc();
      if(rand_range(0,1)) poc->odwroc();
      poc->unormuj();
      poc->przesun(x,rand_range(0,100));
    }
};

class SklejBokiemSpiralaCase : public TestCase {
  public:
    SklejBokiemSpiralaCase (int n,int x,int przesuniecie)
    {
      poc = tworz_spirale(n,500*1000*1000,500*1000*1000);
      for(int i=0;i<x;i++)
      {
        wielokat *tmp = poc->kopiuj();
        tmp->odbij();
        poc->unormuj();
        tmp->unormuj();
        poc->przesun(0,przesuniecie);
        poc = sklej_boczkiem(poc,tmp);
      }
      if(rand_range(0,1)) poc->odbij();
      else if(rand_range(0,1)) poc->obroc();
      if(rand_range(0,1)) poc->odwroc();
      poc->unormuj();
      poc->przesun(x,rand_range(0,100));
    }
};

class SklejBokiemLosowyCase : public TestCase {
  public:
    SklejBokiemLosowyCase (int n,int x,int min_w,int max_w,int przesuniecie)
    {
      poc = tworz_losowy(n,min_w,max_w,min_w,max_w);
      for(int i=0;i<x;i++)
      {
        wielokat *tmp = poc->kopiuj();
        tmp->odbij();
        poc->unormuj();
        tmp->unormuj();
        poc->przesun(0,przesuniecie);
        poc = sklej_boczkiem(poc,tmp);
      }
      if(rand_range(0,1)) poc->odbij();
      else if(rand_range(0,1)) poc->obroc();
      if(rand_range(0,1)) poc->odwroc();
      poc->unormuj();
      poc->przesun(x,rand_range(0,100));
    }
};

class WrednyCase : public TestCase {
  public:
    WrednyCase ()
    {
      poc = new wielokat(0,0); poc->dodaj_za(6,0); poc->dodaj_za(6,2);
      poc->dodaj_za(12,2); poc->dodaj_za(12,3); poc->dodaj_za(6,3);
      poc->dodaj_za(6,5); poc->dodaj_za(0,5); poc->dodaj_za(0,3);
      poc->dodaj_za(4,3); poc->dodaj_za(4,2); poc->dodaj_za(0,2);
    }
};

class WrednyCase2 : public TestCase {
  public:
    WrednyCase2 ()
    {
      poc = new wielokat(0,0); poc->dodaj_za(0,4);
      poc->dodaj_za(1,4); poc->dodaj_za(1,1); poc->dodaj_za(5,1);
      poc->dodaj_za(5,2); poc->dodaj_za(6,2); poc->dodaj_za(6,0);
    }
};

class ZapychaczCase : public TestCase {
  public:
    ZapychaczCase (int h,int x,int wys=0)
    {
      assert(h>1);
      poc = new wielokat (0,0);
      wielokat *tmp = poc->dodaj_za(0,1);
      for(int i=1;i<=h;i++)
      {
        tmp = tmp->dodaj_za(1,2*i-1);
        tmp = tmp->dodaj_za(1,2*i);
        tmp = tmp->dodaj_za(0,2*i);
        tmp = tmp->dodaj_za(0,2*i+1);
      }
      if(wys)
      {
        int y = tmp->y;
        tmp = tmp->dodaj_za(1,y);
        tmp = tmp->dodaj_za(1,wys);
        tmp = tmp->dodaj_za(2,wys);
        tmp = tmp->dodaj_za(2,y);
      }
      for(int i=h;i>=1;i--)
      {
        tmp = tmp->dodaj_za(3,2*i+1);
        tmp = tmp->dodaj_za(3,2*i);
        tmp = tmp->dodaj_za(2,2*i);
        tmp = tmp->dodaj_za(2,2*i-1);
      }
      tmp = tmp->dodaj_za(3,1);
      tmp = tmp->dodaj_za(3,0);

      tmp = poc->kopiuj();
      wielokat *prostokat = tworz_prostokat(0,0,1,1);

      vector<int>v;
      
      x+=2;

      for(int i=1;i<x/2;i++) v.push_back(rand_range(0,1));

      for(int i=0;i+1<((int)v.size());i++)
      {
        wielokat *f = prostokat->kopiuj();
        if(v[i]) f->przesun(0,h*2);
        tmp = sklej_boczkiem(tmp,f);
        tmp = sklej_boczkiem(tmp,poc->kopiuj());
      }

      if(true)
      {
        wielokat *f = prostokat->kopiuj();
        if(v.back()) f->przesun(0,h*2);
        tmp = sklej_boczkiem(tmp,f);
        f = poc->kopiuj();
        wielokat *g = f; do
        {
          if(g->x >= 2) g->x++;
          g = g->nas;
        } while ( f != g );
        tmp = sklej_boczkiem(tmp,f);
      }

      for(int i=((int)v.size())-1;i>=0;i--)
      {
        wielokat *f = prostokat->kopiuj();
        if((!!v[i]) == (!!wys)) f->przesun(0,h*2);
        tmp = sklej_boczkiem(tmp,f);
        tmp = sklej_boczkiem(tmp,poc->kopiuj());
      }

      poc = tmp;

      if(rand_range(0,1)) poc->odbij();
    }
};

class PiramidkaCase : public TestCase {
  public:
    PiramidkaCase (int n)
    {
      assert(n>=6);
      poc = new wielokat(0,0);
      for(int i=1;i<=n;i++) poc = poc->dodaj_za(i,i-1)->dodaj_za(i,i);
      poc = poc->dodaj_za(n-1,n)->dodaj_za(n-1,n+1)->dodaj_za(2*n-1,n+1)->dodaj_za(2*n-1,n+2);
      poc = poc->dodaj_za(n-2,n+2)->dodaj_za(n-2,n)->dodaj_za(1,n)->dodaj_za(1,n+1);
      for(int i=2;i<=n;i++) poc = poc->dodaj_za(i,n+i-1)->dodaj_za(i,n+i);
      poc->dodaj_za(0,2*n);

      if(rand_range(0,1)) poc->odbij();
      if(rand_range(0,1)) poc->odwroc();
      if(rand_range(0,1)) poc->obroc();
      poc->przesun(rand_range(0,3242343),rand_range(0,3243242));
    }
};

class Popsuj : public TestCase {
  public:
    Popsuj() { poc = NULL; }
};

void write(const char* filename,const TestCase& testCase) {
  ofstream file(filename);
  file << testCase;
  if(!popsuty_test) cout << "Writing " << filename << "..." << endl;
  file.close();
}

void testGroup(const vector<TestCase>& cases) {
  static int test_no = 0;
  ++test_no;
  int przesuniecie=0;
  popsuty_test = false;
  for (int i = 0; i < (int) cases.size(); ++i) {
    stringstream ss;
    ss << "dem";
    ss << test_no;
    if (cases.size() > 1U) {
      ss << char('a' + i - przesuniecie);
    }
    ss << ".in";
    write(ss.str().c_str(), cases[i]);
    if(popsuty_test) przesuniecie++;
  }
}

int main()
{
  // HINT: Osobny setSeed przed kazdym testem lub grupa testow!
  // HINT: Nie generujemy testu 0.
  RG.setSeed(42); // pierwsza grupa - male przypadki szczegolne
  {
    const TestCase t[] = {
      WrednyCase (),
      WrednyCase2 (), // dla programu demb3.cpp
      ProstokatCase (0,0,1,1),
      ProstokatCase (0,11,10,10),
      WezykNieparzystyCase (10,2,1,9,8),
      WezykParzystyCase (10,2,1,9,12),
      //ObokSiebieCase (52,0,200,0,200),
      //SklejBokiemCase (32),
      //ComboObokSiebieRecCase (20,50,2),
      //ComboObokSiebieRecCase (172,124,6),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(128); // druga grupa - male spirale pojedyncze, lub sklejone wielokrotnie
  {
    const TestCase t[] = {
      SpiralaCase (50,15,55),
      PodwojnaSpiralaCase (48,145,11,7,7),
      PodwojnaSpiralaCase (48,145,11,7,18),
      SklejBokiemSpiralaCase (10,2,1),
      SklejBokiemSpiralaCase (16,3,0),
      SklejBokiemLosowyCase (8,3,1,12,1),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(876); // trzecia grupa - male wezyki pojedyncze, lub sklejone wielokrotnie
  {
    const TestCase t[] = {
      WezykNieparzystyCase (150,0,15,17,16),
      WezykParzystyCase (150,0,15,17,20),
      SklejBokiemWezykCase (8,2,1,10),
      SklejBokiemLosowyCase (22,3,1,48,1),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(923348); // czwarta grupa - n <= 5000 i maly obwod (wsp <= 200)
  {
    const TestCase t[] = {
      WezykNieparzystyCase (50,1,1,50,160),
      WezykParzystyCase (50,1,1,50,196),
      ObokSiebieCase (200,0,100,0,100),
      ZapychaczCase (9,13,200),
      ZapychaczCase (25,23,200),
      ObokSiebieRecCase (10,30,3),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(2389837); // piata grupa - n <= 5000, long longi
  {
    const TestCase t[] = {
      WezykNieparzystyCase (500*1000*1000,100234522,1,500*1000*1000,5000),
      PodwojnaSpiralaCase (5000,124000,900000000,12400,14218),
      ProstokatCase (0,0,1000*1000*1000,1000*1000*1000),
      SklejBokiemSpiralaCase (72*5,4,1),
      SklejBokiemLosowyCase (14*5,6,0,100000,10),
      ComboObokSiebieRecCase (10*5, 1000*1000, 5),
      Popsuj(),
      ComboObokSiebieRecCase (10*5, 1000*1000, 5),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(9873456); // szosta grupa - n spore (nie maksymalne), long longi
  {
    const TestCase t[] = {
      WezykParzystyCase (10001,0,10,10000,40004),
      WezykNieparzystyCase (22,0,1,11,40008),
      WezykParzystyCase (777*1000*1001,23555,1,100000000,2228),
      PiramidkaCase (10000),
      ComboObokSiebieRecCase (10, 1000*1000, 9),
      ComboObokSiebieRecCase (36, 80, 8),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(9873456); // siodma grupa - n spore (nie maksymalne), nie long longi
  {
    const TestCase t[] = {
      ComboObokSiebieRecCase (50,104,8),
      ComboObokSiebieRecCase (50,104,8),
      Popsuj(),
      ComboObokSiebieRecCase (50,104,8),
      PiramidkaCase (20000),
      ZapychaczCase (170,41),
      SklejBokiemLosowyCase (4142,3,1241,5841,233),
      Popsuj(),
      SklejBokiemLosowyCase (5000,2,1,32100,32000),
      PodwojnaSpiralaCase (22344,32590,5232,123,456),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();

  RG.setSeed(9873456); // osma grupa - wszystko maksymalne
  {
    const TestCase t[] = {
      ZapychaczCase (961,12),
      ZapychaczCase (1000,11),
      ComboObokSiebieRecCase (64,1241241,9),
      PodwojnaSpiralaCase (100000,1000*1000*1000-500000,1000*1000*1000-500000,123424,141241),
      SklejBokiemWezykCase (96,10,121,1244),
      SklejBokiemSpiralaCase (52,11,23),
      SklejBokiemLosowyCase (1562,6,235,25233,782),
      Popsuj(),
      SklejBokiemLosowyCase (780,7,1,10*1000*1000,100*1000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  czysc();
	return 0;
}

/* przyjmuje zbior przedzialow z wagami, zwraca ciag posortowany przedzialow,
   ktory pokrywa ten poprzedni zbior, zadne przedzialy sie nie przecinaja
   i kazdy z tych przedzialow ma taka wage, jak minimum z tych pierwotnych,
   ktore obejmowal */
void licz_minimalne_przedzialy(vector<pair<pair<int,int>,int> > &v)
{
  vector<pair<int,pair<int,int> > >kon;
  for(int i=0;i<((int)v.size());i++)
  {
    kon.push_back(make_pair(v[i].first.first,make_pair(1,v[i].second)));
    kon.push_back(make_pair(v[i].first.second,make_pair(-1,v[i].second)));
  }
  sort(kon.begin(),kon.end());
  v.clear();
  multiset<int>wagi;
  int pop=0;
  for(int i=0;i<((int)kon.size());i++)
  {
    if((!wagi.empty()) && pop < kon[i].first) v.push_back(make_pair(make_pair(pop,kon[i].first),*wagi.begin()));
    if(kon[i].second.first==1) wagi.insert(kon[i].second.second); // poczatek przedzialu
    else wagi.erase(wagi.find(kon[i].second.second)); // koniec przedzialu
    pop = kon[i].first;
  }
  for(int i=1;i<((int)v.size());i++)
  {
    if(v[i-1].second == v[i].second && v[i-1].first.second==v[i].first.first)
    {
      v[i].first.first=v[i-1].first.first;
      v[i-1].first.first= -1;
    }
  }
  for(int i=0;i<((int)v.size());i++)
  {
    if(v[i].first.first<0)
    {
      swap(v[i],v.back());
      v.pop_back();
      i--;
    }
  }
  sort(v.begin(),v.end());
}

/* przyjmuje zbior przedzialow z wagami, zwraca ciag posortowany przedzialow,
   ktory pokrywa ten poprzedni zbior w miejscach, gdzie były dwie warstwy przedzialow,
   zadne przedzialy sie nie przecinaja
   i kazdy z tych przedzialow ma taka wage, jak suma z tych pierwotnych,
   ktore obejmowal */
void licz_sume_przedzialow(vector<pair<pair<int,int>,int> > &v)
{
  vector<pair<int,pair<int,int> > >kon;
  for(int i=0;i<((int)v.size());i++)
  {
    kon.push_back(make_pair(v[i].first.first,make_pair(1,v[i].second)));
    kon.push_back(make_pair(v[i].first.second,make_pair(-1,v[i].second)));
  }
  sort(kon.begin(),kon.end());
  v.clear();
  int sumka=0;
  int ile=0;
  int pop=0;
  for(int i=0;i<((int)kon.size());i++)
  {
    if(ile==2 && pop < kon[i].first) v.push_back(make_pair(make_pair(pop,kon[i].first),sumka));
    if(kon[i].second.first==1) ile++, sumka += kon[i].second.second; // poczatek przedzialu
    else ile--, sumka -= kon[i].second.second; // koniec przedzialu
    pop = kon[i].first;
  }
  for(int i=1;i<((int)v.size());i++)
  {
    if(v[i-1].second == v[i].second && v[i-1].first.second==v[i].first.first)
    {
      v[i].first.first=v[i-1].first.first;
      v[i-1].first.first= -1;
    }
  }
  for(int i=0;i<((int)v.size());i++)
  {
    if(v[i].first.first<0)
    {
      swap(v[i],v.back());
      v.pop_back();
      i--;
    }
  }
  sort(v.begin(),v.end());
}

wielokat *sklej_boczkiem(wielokat *a,wielokat *b) // mhmmm... boczek
{
  a->przeciwnie_do_wskazowek(); b->przeciwnie_do_wskazowek();
  wielokat *tmp;
  vector<pair<pair<int,int>,int> >tab_a,tab_b,last;
  tmp = a; do
  {
    if(tmp->nas_pio())
      tab_a.push_back(make_pair(make_pair(min(tmp->y,tmp->nas->y),max(tmp->y,tmp->nas->y)),-tmp->x));
    tmp = tmp->nas;
  } while( tmp != a );
  tmp = b; do
  {
    if(tmp->nas_pio())
      tab_b.push_back(make_pair(make_pair(min(tmp->y,tmp->nas->y),max(tmp->y,tmp->nas->y)),tmp->x));
    tmp = tmp->nas;
  } while( tmp != b );
  licz_minimalne_przedzialy(tab_a);
  licz_minimalne_przedzialy(tab_b);
  for(int i=0;i<((int)tab_a.size());i++) last.push_back(tab_a[i]);
  for(int i=0;i<((int)tab_b.size());i++) last.push_back(tab_b[i]);
  tab_b.clear();
  licz_sume_przedzialow(last);
  int m = last[0].second;
  for(int i=0;i<((int)last.size());i++) m = min(m, last[i].second);
  m *= -1;
  for(int i=0;i<((int)last.size());i++) last[i].second += m;
  b->przesun(m,0);
  int dx=0,dy=0,gx=0,gy=0;
  for(int i=0;i<((int)last.size());i++) if(last[i].second==0) { dy=last[i].first.first; break; }
  for(int i=((int)last.size())-1;i>=0;i--) if(last[i].second==0) { gy=last[i].first.second; break; }
  for(int i=0;i<((int)tab_a.size());i++)
  {
    if(tab_a[i].first.first <= dy && dy <= tab_a[i].first.second) dx = max(dx,-tab_a[i].second);
    if(tab_a[i].first.first <= gy && gy <= tab_a[i].first.second) gx = max(gx,-tab_a[i].second);
  }
  wielokat *ad = a->wymus_punkt(dx,dy); wielokat *ag = a->wymus_punkt(gx,gy);
  wielokat *bd = b->wymus_punkt(dx,dy); wielokat *bg = b->wymus_punkt(gx,gy);
  ad->nas = bd; bd->pop = ad;
  bg->nas = ag; ag->pop = bg;
  ad->usun(); bg->usun();
  if(ag->nas_poz() == ag->pop_poz()) ag->usun();
  if(bd->nas_poz() == bd->pop_poz()) bd->usun();
  return ag->nas;
}

wielokat *tworz_combo_obok_siebie_rec(int n,int max_wsp,int r)
{
  if(r==0) return tworz_losowy(n,0,max_wsp,0,max_wsp);
  wielokat *a = tworz_combo_obok_siebie_rec(n,max_wsp,r-1);
  a = tworz_sklejenie(a,tworz_losowy(n,0,max_wsp,0,max_wsp));
  if(rand_range(0,1)) a->odbij();
  if(rand_range(0,1)) a->obroc();
  wielokat *b = a->kopiuj();
  if(rand_range(0,1)) b->odbij();
  if(rand_range(0,1)) b->obroc();
  if(rand_range(0,1)) return tworz_sklejenie(b,a);
  else return tworz_sklejenie(a,b);
}

wielokat *tworz_obok_siebie_rec(int n,int max_wsp,int r)
{
  if(r==0) return tworz_losowy(n,0,max_wsp,0,max_wsp);
  wielokat *a = tworz_obok_siebie_rec(n,max_wsp,r-1);
  wielokat *b = a->kopiuj();
  b->odbij();
  if(rand_range(0,1)) b->obroc();
  if(rand_range(0,1)) return tworz_sklejenie(b,a);
  else return tworz_sklejenie(a,b);
}

//wielokat *tworz_obok_siebie(int n,int min_x,int max_x,int min_y,int max_y)
bool tworz_sklejenie_agor(wielokat *x,wielokat *y) { if(x->x == y->x) return x->y > y->y; return x->x > y->x; }
bool tworz_sklejenie_adol(wielokat *x,wielokat *y) { if(x->x == y->x) return x->y < y->y; return x->x > y->x; }
bool tworz_sklejenie_bgor(wielokat *x,wielokat *y) { if(x->x == y->x) return x->y > y->y; return x->x < y->x; }
bool tworz_sklejenie_bdol(wielokat *x,wielokat *y) { if(x->x == y->x) return x->y < y->y; return x->x < y->x; }
wielokat *tworz_sklejenie (wielokat *a,wielokat *b)
{
  wielokat *agor = a, *adol = a;
  wielokat *bgor = b, *bdol = b;
  wielokat *tmp;

  ll pola=0LL,polb=0LL;
  tmp = a; do
  {
    agor = min (agor,tmp,tworz_sklejenie_agor);
    adol = min (adol,tmp,tworz_sklejenie_adol);
    pola += tmp->nas_pol();
    tmp = tmp->nas;
  } while (tmp != a);

  tmp = b; do
  {
    bgor = min (bgor,tmp,tworz_sklejenie_bgor);
    bdol = min (bdol,tmp,tworz_sklejenie_bdol);
    polb += tmp->nas_pol();
    tmp = tmp->nas;
  } while (tmp != b);

  if(signum(pola)*signum(polb)<0) b->odwroc();

  b->przesun ( agor->x - bgor->x, rand_range(adol->y - bgor->y + 1,agor-> y - bdol->y - 1) );
  if(agor->nas==adol)
  {
    agor->podlacz(bgor);
    bdol->podlacz(adol);
  }
  else
  {
    adol->podlacz(bdol);
    bgor->podlacz(agor);
  }
  a = bgor->nas->nas;
  if(agor->y == bgor->y) agor->usun(),bgor->usun();
  if(adol->y == bdol->y) adol->usun(),bdol->usun();
  a->unormuj();
  return a;
}

wielokat *tworz_losowy(int n,int min_x,int max_x,int min_y,int max_y)
{
  assert(max_x-min_x >= n/2 && max_y-min_y >= n/2); // musi starczyc wspolrzednych na ten wielokat
  assert(n%2==0 && n>=4);
  list<int>wsp_x,wsp_y;
  vector<list<int>::iterator>wskaz_x,wskaz_y;
  // tworzenie poczatkowego prostokata
  wsp_x.push_back(-1); wskaz_x.push_back(wsp_x.begin());
  wsp_x.push_front(-1); wskaz_x.push_back(wsp_x.begin());
  wsp_y.push_back(-1); wskaz_y.push_back(wsp_y.begin());
  wsp_y.push_front(-1); wskaz_y.push_back(wsp_y.begin());
  swap(wskaz_x[0],wskaz_x[1]);
  swap(wskaz_y[0],wskaz_y[1]);
  vector<wielokat*>wierzcholki;
  wielokat *poc = new wielokat(0,0,1); wierzcholki.push_back(poc);
  poc = poc->dodaj_za(1,0,1); wierzcholki.push_back(poc);
  poc = poc->dodaj_za(1,1,-1); wierzcholki.push_back(poc);
  poc = poc->dodaj_za(0,1,-1); wierzcholki.push_back(poc);
  n-=4;
  n/=2;
  while(n--)
  {
    wielokat *s = wierzcholki[rand_range(0,wierzcholki.size()-1)];
    wielokat *p = NULL;
    if(s->nas_pio())
    {
      if(rand_range(0,1)) // ,-' ->
      {
        int k = s->kierunek;
        s->x = wskaz_x.size();
        wskaz_x.push_back(wsp_x.insert(wskaz_x[s->nas->x],-1));
        s = s->dodaj_za(s->x,wskaz_y.size(),1);
        p = s->dodaj_za(s->nas->x,wskaz_y.size(),k);
        if(k>0) wskaz_y.push_back(wsp_y.insert(wskaz_y[p->nas->y],-1));
        else wskaz_y.push_back(wsp_y.insert(wskaz_y[s->pop->y],-1));
      }
      else // ,-' <-
      {
        int k = s->kierunek;
        s->nas->x = wskaz_x.size();
        wskaz_x.push_back(wsp_x.insert(wskaz_x[s->x],-1));
        s = s->dodaj_za(s->x,wskaz_y.size(),-1);
        p = s->dodaj_za(s->nas->x,wskaz_y.size(),k);
        if(k>0) wskaz_y.push_back(wsp_y.insert(wskaz_y[p->nas->y],-1));
        else wskaz_y.push_back(wsp_y.insert(wskaz_y[s->pop->y],-1));
      }
    }
    else
    {
      if(rand_range(0,1)) // "|_ \/
      {
        int k = s->kierunek;
        s->nas->y = wskaz_y.size();
        wskaz_y.push_back(wsp_y.insert(wskaz_y[s->y],-1));
        s = s->dodaj_za(wskaz_x.size(),s->y,-1);
        p = s->dodaj_za(wskaz_x.size(),s->nas->y,k);
        if(k>0) wskaz_x.push_back(wsp_x.insert(wskaz_x[p->nas->x],-1));
        else wskaz_x.push_back(wsp_x.insert(wskaz_x[s->pop->x],-1));
      }
      else // "|_ /\ .
      {
        int k = s->kierunek;
        s->y = wskaz_y.size();
        wskaz_y.push_back(wsp_y.insert(wskaz_y[s->nas->y],-1));
        s = s->dodaj_za(wskaz_x.size(),s->y,1);
        p = s->dodaj_za(wskaz_x.size(),s->nas->y,k);
        if(k>0) wskaz_x.push_back(wsp_x.insert(wskaz_x[p->nas->x],-1));
        else wskaz_x.push_back(wsp_x.insert(wskaz_x[s->pop->x],-1));
        poc = s->pop;
      }
    }
    wierzcholki.push_back(s);
    wierzcholki.push_back(p);
  }
  set<int>wsp_uzyte;
  vector<int>wx,wy;
  int z=wsp_x.size();
  while(((int)wsp_uzyte.size())<z) wsp_uzyte.insert(rand_range(min_x,max_x));
  for(set<int>::iterator i=wsp_uzyte.begin();i!=wsp_uzyte.end();i++) wx.push_back(*i);
  wsp_uzyte.clear();
  z=wsp_y.size();
  while(((int)wsp_uzyte.size())<z) wsp_uzyte.insert(rand_range(min_y,max_y));
  for(set<int>::iterator i=wsp_uzyte.begin();i!=wsp_uzyte.end();i++) wy.push_back(*i);
  wsp_uzyte.clear();
  z=0;
  for(list<int>::iterator i=wsp_x.begin();i!=wsp_x.end();i++) (*i)=wx[z++];
  z=0;
  for(list<int>::iterator i=wsp_y.begin();i!=wsp_y.end();i++) (*i)=wy[z++];
  int ox=rand_range(0,1);
  int oy=rand_range(0,1);
  wielokat *p = poc;
  do
  {
    p->x = *wskaz_x[p->x];
    p->y = *wskaz_y[p->y];
    if(ox) p->x = max_x - (p->x-min_x);
    if(oy) p->y = max_y - (p->y-min_y);
    p = p->nas;
  }
  while(p!=poc);
  return poc;
}

wielokat *tworz_podwojna_spirale(int n,int x,int y,int aa,int bb)
{
  assert(aa>0 && bb>0);
  assert(n%4==0); // n musi byc postaci 4k
  assert(n>8);
  n/=4;
  n--;
  wielokat *poc = new wielokat(x+aa+2,y+bb+1);
  wielokat *a = poc;
  wielokat *b = a->dodaj_za(x,y+bb+1)->dodaj_za(x,y)->dodaj_za(x-1,y);
  wielokat *c = new wielokat (x-2,y-1);
  wielokat *d = c->dodaj_za(x+aa,y-1)->dodaj_za(x+aa,y+bb)->dodaj_za(x+aa+1,y+bb);
  const int kx[4]={0,1,0,-1};
  const int ky[4]={1,0,-1,0};
  int kad=2,kbc=0;
  for(int i=1;i<n;i++)
  {
    int o=(((i+1)/2)*4+((i+1)%2)+((i%2==0)?(aa-1):(bb-2)));
    a = a->dodaj_przed(a->x+kx[kad]*(o+2),a->y+ky[kad]*(o+2));
    b = b->dodaj_za(b->x+kx[kbc]*o,b->y+ky[kbc]*o);
    c = c->dodaj_przed(c->x+kx[kbc]*(o+2),c->y+ky[kbc]*(o+2));
    d = d->dodaj_za(d->x+kx[kad]*o,d->y+ky[kad]*o);
    kad=(kad+1)&3;
    kbc=(kbc+1)&3;
  }
  kbc=(kbc+3)&3; kad=(kad+3)&3;
  c->x-=2*kx[kbc]; c->y-=2*ky[kbc];
  a->x-=2*kx[kad]; a->y-=2*ky[kad];
  b->x-=kx[kbc]; b->y-=ky[kbc];
  d->x-=kx[kad]; d->y-=ky[kad];
  b->podlacz(c);
  d->podlacz(a);
  return poc;
}

wielokat *tworz_prostokat(int x,int y,int a,int b)
{
  wielokat *poc=new wielokat(x,y);
  poc->dodaj_za(x,y+b);
  poc->dodaj_za(x+a,y+b);
  poc->dodaj_za(x+a,y);
  return poc;
}

wielokat *tworz_parzysty_wezyk(int os,int y,int min_d,int max_d,int n)
{
  assert(n%4==0 && n%8!=0); // n musi byc postaci 4(2k+1)
  n/=4; n++;
  vector<int>wyb;
  for(int i=0;i<n/2;i++) wyb.push_back(rand_range(min_d,max_d));
  for(int i=0;i<n/2;i++) wyb.push_back(wyb[n/2-1-i]);
  wielokat *poc = new wielokat(os-wyb[0]-1,y);
  for(int i=0;i<n/2-1;i++)
  {
    poc = poc->dodaj_za(os+wyb[1+2*i]+1,y+i*4);
    poc = poc->dodaj_za(os+wyb[1+2*i]+1,y+i*4+3);
    poc = poc->dodaj_za(os-wyb[2+2*i],y+i*4+3);
    poc = poc->dodaj_za(os-wyb[2+2*i],y+i*4+4);
  }
  poc = poc->dodaj_za(os+wyb[n-1]+1,y+(n/2-1)*4);
  poc = poc->dodaj_za(os+wyb[n-1]+1,y+(n/2-1)*4+1);
  for(int i=n/2-2;i>=0;i--)
  {
    poc = poc->dodaj_za(os-wyb[2+2*i]-1,y+i*4+5);
    poc = poc->dodaj_za(os-wyb[2+2*i]-1,y+i*4+2);
    poc = poc->dodaj_za(os+wyb[1+2*i],y+i*4+2);
    poc = poc->dodaj_za(os+wyb[1+2*i],y+i*4+1);
  }
  poc = poc->dodaj_za(os-wyb[0]-1,y+1);
  return poc;
}

wielokat *tworz_nieparzysty_wezyk(int os,int y,int min_d,int max_d,int n)
{
  assert(n%8==0); // n musi byc postaci 8k
  n/=4; n++;
  vector<int>wyb;
  for(int i=0;i<=n/2;i++) wyb.push_back(rand_range(min_d,max_d));
  for(int i=0;i<n/2;i++) wyb.push_back(wyb[n/2-1-i]);
  wielokat *poc = new wielokat(os-wyb[0]-1,y);
  for(int i=0;i<n/2-1;i++)
  {
    poc = poc->dodaj_za(os+wyb[1+2*i]+1,y+i*5);
    poc = poc->dodaj_za(os+wyb[1+2*i]+1,y+i*5+4);
    poc = poc->dodaj_za(os-wyb[2+2*i],y+i*5+4);
    poc = poc->dodaj_za(os-wyb[2+2*i],y+i*5+5);
  }
  poc = poc->dodaj_za(os+wyb[n-2]+1,y+(n/2-1)*5);
  poc = poc->dodaj_za(os+wyb[n-2]+1,y+(n/2-1)*5+4);
  poc = poc->dodaj_za(os-wyb[n-1]-1,y+(n/2-1)*5+4);
  poc = poc->dodaj_za(os-wyb[n-1]-1,y+(n/2-1)*5+3);
  poc = poc->dodaj_za(os+wyb[n-2],y+(n/2-1)*5+3);
  poc = poc->dodaj_za(os+wyb[n-2],y+(n/2-1)*5+1);
  for(int i=n/2-2;i>=0;i--)
  {
    poc = poc->dodaj_za(os-wyb[2+2*i]-1,y+i*5+6);
    poc = poc->dodaj_za(os-wyb[2+2*i]-1,y+i*5+3);
    poc = poc->dodaj_za(os+wyb[1+2*i],y+i*5+3);
    poc = poc->dodaj_za(os+wyb[1+2*i],y+i*5+1);
  }
  poc = poc->dodaj_za(os-wyb[0]-1,y+1);
  return poc;
}

wielokat *tworz_spirale(int n,int x,int y)
{
  assert(n%2==0); // spirala ma parzyscie wiele wierzcholkow
  assert(n>7); // na wszelki wypadek
  n-=2;
  wielokat *poc = new wielokat (x,y);
  const int kx[4]={0,-1,0,1};
  const int ky[4]={1,0,-1,0};
  wielokat *kon = poc->dodaj_za(x+1,y);
  int kpoc=2,kkon=0;
  for(int i=1;i<n/2;i++)
  {
    kon = kon->dodaj_za(kon->x+kx[kkon]*i,kon->y+ky[kkon]*i);
    poc = poc->dodaj_przed(poc->x+kx[kpoc]*i,poc->y+ky[kpoc]*i);
    kpoc=(kpoc+1)&3;
    kkon=(kkon+1)&3;
  }
  kon = kon->dodaj_za(kon->x+kx[kkon]*(n/2),kon->y+ky[kkon]*(n/2));
  kkon=(kkon+1)&3;
  kon = kon->dodaj_za(kon->x+kx[kkon]*(n/2),kon->y+ky[kkon]*(n/2));
  return poc;
}
