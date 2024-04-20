#include<string>
#include<random>
#include<iostream>
#include<ctime>

std::random_device rd;
std::default_random_engine e(rd());

enum class Resultat { j1gagne, j0gagne, partieNulle };

template <typename P> struct noeud
{
  noeud<P>* pere;
  noeud<P>** fils;
  unsigned nbfils;
  P p;
  unsigned cross, win;
  unsigned indiceMeilleurFils;

  static unsigned compt;

  explicit noeud(noeud<P>* pere, P p);
  ~noeud();

  std::string ToString() const;
  void CalculMeilleurFils(double a);
  noeud<P>* MeilleurFils();
};

template <typename P>
unsigned noeud<P>::compt{0};

template <typename P>
noeud<P>::noeud(noeud<P>* pere, P p) :pere(pere), p(p), cross{0}, win{0}
{
  ++compt;
  nbfils = p.Nbcoups();
  fils = new noeud<P>*[nbfils];
  for (unsigned i=0; i<nbfils;++i) fils[i]=nullptr;
}

template <typename P>
noeud<P>::~noeud()
{
  for (unsigned i=0; i<nbfils;++i) { delete fils[i];}
  delete[] fils;
  --compt;
}

template <typename P>
noeud<P>* noeud<P>::MeilleurFils()
{
    if (fils[indiceMeilleurFils] != nullptr)
    {
        return fils[indiceMeilleurFils];
    }
    P q = p;
    q.EffectuerCoup(indiceMeilleurFils);
    fils[indiceMeilleurFils] = new noeud<P>(this, q);
    return fils[indiceMeilleurFils];
}

template <typename P>
void noeud<P>::CalculMeilleurFils(double a)
{
    double s;
    double sM = 0;
    if (p.j1aletrait)
    {
        for (unsigned i = 0; i < nbfils; ++i)
        {
            if (fils[i] == nullptr) { s = 1; }
            else { s = (fils[i]->win +a)/(fils[i]->cross +a); }
            if (s > sM) { sM = s; indiceMeilleurFils = i; }
        }
    }
    else
    {
        for (unsigned i = 0; i < nbfils; ++i)
        {
            if (fils[i] == nullptr) { s = 1; }
            else { s = (fils[i]->cross - fils[i]->win +a)/(fils[i]->cross +a);; }
            if (s > sM) { sM = s; indiceMeilleurFils = i; }
        }
    }
}

template <typename P>
std::string noeud<P>::ToString() const
{
  std::string s = "";
  s = s + "indice MF = " + std::to_string(indiceMeilleurFils);
  double note;
  s+= "\n note=";
  if (fils[indiceMeilleurFils])
  {
    note= (1.0*fils[indiceMeilleurFils]->win)/fils[indiceMeilleurFils]->cross;
    s+=std::to_string(note);
  }
  else s+="?";
  s+="\n nbC="+std::to_string(cross/2);
  s+="\n"+std::to_string(compt);
  return s;
}

template <typename P> class Joueur
{
  public:
    std::string nom;
    virtual unsigned Jouer(P p) =0;
    virtual void FinPartie() { }
    std::string message;
};

template <typename P> class JMCTS: public Joueur<P>
{
    double a;
    unsigned temps; // temps de réflexion
    noeud<P>* racine;
  public:
    JMCTS(double a , unsigned temps):a(a), temps(temps)
    {
      this->nom = "JMCTS(a="+std::to_string(a)+",temps="+std::to_string(temps)+")";
    }

    unsigned JeuHasard(P p) const
    {
        unsigned re = 1;
        while (p.Nbcoups() > 0) { p.EffectuerCoup( e()%p.Nbcoups() );}
        if (p.Eval()==Resultat::j1gagne) { re = 2; }
        if (p.Eval() == Resultat::j0gagne) { re = 0; }
        return re;
    }

    unsigned Jouer(P p) override
    {
      std::clock_t t0 = std::clock();
      std::clock_t t1 = t0+ temps*(CLOCKS_PER_SEC/1000);

        racine = new noeud<P>(nullptr, p);
        unsigned iter = 0;
        while (std::clock() < t1)
        {
            noeud<P>* no = racine;

            do // Sélection
            {
                no->CalculMeilleurFils(a);
                no = no->MeilleurFils();

            } while (no->cross>0 && no->nbfils > 0);

            unsigned re = JeuHasard(no->p); // Simulation

            while (no != nullptr) // Rétropropagation
            {
                no->cross += 2;
                no->win += re;
                no = no->pere;
            }
            ++iter;
        }
        racine->CalculMeilleurFils(a);

        this->message = std::to_string(iter) + " itérations\n";
        this->message+= racine->ToString();

        unsigned res = racine->indiceMeilleurFils;
        delete racine;
        return res;
    }
};


template <typename P> class Partie
{
  P pCourante;
  Joueur<P> &j1, &j0;
public:
  bool affichage;
  Resultat r;
  Partie(Joueur<P> &j1, Joueur<P> &j0, P pInitiale, bool aff=true):
    j1(j1), j0(j0), pCourante(pInitiale), affichage(aff) {}
  void Commencer();
};

template <typename P>
void Partie<P>::Commencer()
{
  if (affichage)
  std::cout << pCourante.ToString() << std::endl;
  while(pCourante.Nbcoups()>0)
  {
    if (pCourante.j1aletrait)
    {
      if (affichage)
      std::cout << j1.nom << "(j1) joue" << std::endl;
      pCourante.EffectuerCoup(j1.Jouer(pCourante));
      if (affichage)
      std::cout << j1.message << std::endl;
    }
    else
    {
      if (affichage)
      std::cout << j0.nom << "(j0) joue" << std::endl;
      pCourante.EffectuerCoup(j0.Jouer(pCourante));
      if (affichage)
      std::cout << j0.message << std::endl;
    }
    if (affichage)
    std::cout << pCourante.ToString() << std::endl;
  }
  r=pCourante.Eval();
  if (affichage){
  switch(r)
  {
    case Resultat::j1gagne:
      std::cout << "j1 a gagné" << std::endl; break;
    case Resultat::j0gagne:
      std::cout << "j0 a gagné" << std::endl; break;
    case Resultat::partieNulle:
      std::cout << "Partie nulle" << std::endl; break;
  }
  }
  j1.FinPartie(); j0.FinPartie();
}

class PA
{
  unsigned nba;
  unsigned nbcoups;
  Resultat eval;
  void Eval(Resultat r){ eval = r;};
  void Nbcoups(unsigned n){ nbcoups=n;}
  void Maj_nbcoups() { Nbcoups((nba >=3)? 3:nba);}
public:
  bool j1aletrait;
  PA(unsigned n, bool j1aletrait): j1aletrait(j1aletrait), nba(n){ Maj_nbcoups();}
  unsigned Nbcoups(){ return nbcoups;}
  Resultat Eval() const { return eval;}
  void EffectuerCoup(unsigned i)
  {
    nba = nba - i -1; Maj_nbcoups();
    if (nba==0) Eval(j1aletrait? Resultat::j0gagne : Resultat::j1gagne);
    j1aletrait = !j1aletrait;
  }
  std::string ToString() const
  {
    return (j1aletrait? "j1 a le trait": "j0 a le trait")
    + (" nb alu = " + std::to_string(nba));
  }
};

int main()
{
  JMCTS<PA> j1(1.1,1), j0(1.1,1);
  Partie<PA> part(j1,j0, PA(100,true));
  part.Commencer();
}
