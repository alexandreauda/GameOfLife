        /*CODE Game Of Life*/

        #include <stdio.h>
        #include <stdlib.h>
        #include <curses.h>    /*importation de la bibliotheque curses*/
        #include <time.h>      /*importation de la bibliotheque time*/
        #include <string.h>    /*importation de la bibliotheque string qui permet d'utiliser la fonction strlen()*/


        /*DEFINITION DES VARIABLES ET DES FONCTIONS QUI SERVIRONT DANS LE MAIN*/

        #define TAILLEX 80     /*on declare une variable constante TAILLEX=80*/
        #define TAILLEY  9    /*on declare une variable constante TAILLEY=9*/
        #define TAILLEX_C 500     /*on declare une variable constante TAILLEX_C=500*/
        #define TAILLEY_C  500    /*on declare une variable constante TAILLEY_C=500*/

        #define TAILLEX2 80     /*on declare une variable constante TAILLEX2=80*/
        #define TAILLEY2 9     /*on declare une variable constante TAILLEY2=9*/


        int row1;
        int col1;

        char monde[TAILLEX][TAILLEY];  /*fabrique une matrice de char de taille 8x80(ie TAILLEY*TAILLEX) (ie 8 lignes et 80 colonnes et pas le
                                         contraire!).*/

        char monde2[TAILLEX2][TAILLEY2];  /*fabrique une matrice de char de taille 8x80(ie TAILLEY2*TAILLEX2) (ie 8 lignes et 80 colonnes et pas le
                                         contraire!).*/


        char monde_c[TAILLEX_C][TAILLEY_C];  /*fabrique une matrice de char de taille 50x100(ie TAILLEY_C*TAILLEX_C) (ie 500 lignes et 500 colonnes et pas le
                                         contraire!).*/

        int usecolors=0;               /*on stocke le nombre 0 dans la variable usecolors*/




        /* Procedure de temporisation qui permet de gérer le temps d'animation en mode continu */
        void temporise (int t)
        {
          int j,i;  /*declaration des variables locales i et j.*/
          for (j=0;j<t;j++)
            for(i=0;i<32000;i++)   /*Le i<32000 gere le temps d'animation: Ainsi,Si on met un nombre plus grand que 32000 alors on va ralentir le temps d'animation.
                                    Inversement, si on met un nombre plus petit que 32000 alors on va accelerer le temps d'animation.*/
              {
              }
        }


        /* Initialisation de ncurses et definition des couleurs */
        void init_curses(void)
        {
          initscr();            /* Start curses mode: ouvre un nouveau terminal(nouvelle fenetre) que l'on appelera par la suite terminal_ext par opposition
                                   au terminal normal de Linux que l'on appelera terminal_int(sous window,c'est le meme terminal)*/

          if (has_colors())     /*Si le terminal supporte la couleur, alors...*/
            {
              start_color();    /*on demarre la couleur: on autorise l'utilisation de la couleur*/
              init_pair(1,COLOR_WHITE,COLOR_BLUE);   /*On associe au nombre 1 la pair de couleur: blanche pour l'ecriture et bleu pour le fond*/
              init_pair(2,COLOR_WHITE,COLOR_GREEN);  /*On associe au nombre 2 la pair de couleur: blanche pour l'ecriture et vert pour le fond*/
              init_pair(3,COLOR_RED,COLOR_BLACK);    /*On associe au nombre 3 la pair de couleur: rouge pour l'ecriture et noir pour le fond*/
              init_pair(4,COLOR_WHITE,COLOR_RED);    /*On associe au nombre 4 la pair de couleur: blanc pour l'ecriture et rouge pour le fond*/
              init_pair(5,COLOR_WHITE,COLOR_YELLOW); /*On associe au nombre 5 la pair de couleur: blanc pour l'ecriture et jaune pour le fond*/
              init_pair(6,COLOR_WHITE,COLOR_MAGENTA);/*On associe au nombre 6 la pair de couleur: blanc pour l'ecriture et magenta pour le fond*/
              init_pair(7,COLOR_WHITE,COLOR_CYAN );  /*On associe au nombre 7 la pair de couleur: blanc pour l'ecriture et cyan pour le fond*/
              init_pair(8,COLOR_WHITE,COLOR_WHITE);  /*On associe au nombre 8 la pair de couleur: blanc pour l'ecriture et blanc pour le fond*/
              usecolors=1;  /*lors de l'initialisation de curses, on met 1 dans la variable usecolors*/
            }
        }


        /* Terminaison propre de ncurses */
        void fin_curses(void)
        {
          endwin();   /* End curses mode: si on enleve cette commande, alors apres la fin du programme, on reste dans le terminal_ext de ncurses
                         et on n'a donc plus acces au terminal_int.(cf remarque de initscr() pour la definition de termminal_int et terminal_ext)*/
        }


        /* Affichage du damier et coloration des cellules pour le mode pas a pas */
        void affiche(int col)        /*Prend en argument la couleur des cellules*/
        {
          int i,j;        /*declaration des variables locales i, j (qui sont des int)*/
          /*Les deux boucles for suivantes sont la pour parcourir la matrice(ie le damier) */
          for (j=0;j<TAILLEY;j++)
            {
              for (i=0;i<TAILLEX;i++)
            {
              move(j+3,i);   /*on bouge le curseur:au début, on est au point (0,0) qui est le coin inferieur gauche, puis on se deplace vers la droite
             (on parcourt la première ligne), puis a la fin de la ligne on monte d'une ligne(on passe à la deuxieme ligne), on la parcout et ainsi de suite...
             On parcourt ainsi toute la matrice*/
              if (monde[i][j]) /*i.e: if (monde[i][j]==1)  (voir la fonction damier_hasard)*/
                {
                  if (usecolors)       /*i.e: if (usecolors==1)*/
                {
                  wattrset(stdscr,COLOR_PAIR(col)); /*Couleur des cellules: Avec col=1 defini juste avant la "Procedure de temporisation".Ainsi si on
                                                      remplace col par 2, les cellules seront vertes et si on remplace col par 3 les cellules seront
                                                      noir. En effet, les cellules sont des espaces donc si on met col qui vaut 1 alors si on regarde
                                                      dans "Initialisation de ncurses et definition des couleurs" le 1 correspond à une ecriture en
                                                      blanc et un fond bleu. Or comme les cellules sont definis par des espaces, il n'y a rien qui
                                                      est ecrit en blanc mais le fond lui est bleu*/

                  addch(' ');
                  wattrset(stdscr,COLOR_PAIR(0));  /*Couleur du fond de la fenetre: le fond de la fenetre est noir car on a mis 0 en parametre de COLOR_PAIR*/
                }
                  else
                {
                  addch('@');
                }
                }
              else
                {
                  addch(' ');
                }
            }
            }
          refresh();
        }


        /* Affichage du damier et coloration des cellules pour le mode continu */
        void affiche_c(int col)        /*Prend en argument la couleur des cellules*/
        {
          int i,j;        /*declaration des variables locales i, j (qui sont des int)*/
          /*Les deux boucles for suivantes sont la pour parcourir la matrice(ie le damier) */
          for (j=0;j<TAILLEY_C;j++)
            {
              for (i=0;i<TAILLEX_C;i++)
            {
              move(j,i);   /*on bouge le curseur:au début, on est au point (0,0) qui est le coin inferieur gauche, puis on se deplace vers la droite
             (on parcourt la première ligne), puis a la fin de la ligne on monte d'une ligne(on passe à la deuxieme ligne), on la parcourt et ainsi de suite...
             On parcourt ainsi toute la matrice*/
              if (monde_c[i][j]) /*i.e: if (monde[i][j]==1)  (voir la fonction damier_hasard)*/
                {
                  if (usecolors)       /*i.e: if (usecolors==1)*/
                {
                  wattrset(stdscr,COLOR_PAIR(col)); /*Couleur des cellules: Avec col=1 defini juste avant la "Procedure de temporisation".Ainsi si on
                                                      remplace col par 2, les cellules seront vertes et si on remplace col par 3 les cellules seront
                                                      noir. En effet, les cellules sont des espaces donc si on met col qui vaut 1 alors si on regarde
                                                      dans "Initialisation de ncurses et definition des couleurs" le 1 correspond à une ecriture en
                                                      blanc et un fond bleu. Or comme les cellules sont definis par des espaces, il n'y a rien qui
                                                      est écrit en blanc mais le fond lui est bleu*/

                  addch(' ');
                  wattrset(stdscr,COLOR_PAIR(0));  /*Couleur du fond de la fenetre: le fond de la fenetre est noir car on a mis 0 en paramètre de COLOR_PAIR*/
                }
                  else
                {
                  addch('@');
                }
                }
              else
                {
                  addch(' ');
                }
            }
            }
          refresh();
        }


        /* Renvoie le nombre de voisins vivants de la cellule (x,y)*/
        /* monde est le damier 1 en mode pas à pas (ie la matrice)*/
        /* TAILLEX et TAILLEY les dimensions du damier 1 */
        int nombre_voisins(int x,int y)        /*Soit une  cellule aux coordonnees (x;y): Renvoie le nombre de voisins vivants de cette cellule*/
        {
          int ofx,ofy;
          int x0,y0;
          int n=0;
          for (ofx=-1;ofx<=1;ofx++)
            {
              for (ofy=-1;ofy<=1;ofy++)
            {
              x0=x+ofx%TAILLEX;
              y0=y+ofy%TAILLEY;
              while (x0<0) x0+=TAILLEX;
              while (y0<0) y0+=TAILLEY;
              n+=monde[x0][y0];
            }
            }
          n-=monde[x][y];
          return n;
        }

        /* Renvoie le nombre de voisins vivants de la cellule (x,y)*/
        /* monde2 est le damier2 en mode pas à pas (ie la matrice)*/
        /* TAILLEX2 et TAILLEY2 les dimensions du damier 2 en mode pas à pas*/
        int nombre_voisins2(int x,int y)        /*Soit une  cellule aux coordonnees (x;y): Renvoie le nombre de voisins vivants de cette cellule*/
        {
          int ofx,ofy;
          int x0,y0;
          int n=0;
          for (ofx=-1;ofx<=1;ofx++)
            {
              for (ofy=-1;ofy<=1;ofy++)
            {
              x0=x+ofx%TAILLEX2;
              y0=y+ofy%TAILLEY2;
              while (x0<0) x0+=TAILLEX2;
              while (y0<0) y0+=TAILLEY2;
              n+=monde2[x0][y0];
            }
            }
          n-=monde2[x][y];
          return n;
        }

/* Renvoie le nombre de voisins vivants de la cellule (x,y)*/
/* monde_c est le damier du mode continu (ie la matrice)*/
/* TAILLEX_C et TAILLEY_C les dimensions du damier en mode continu*/
int nombre_voisins_c(int x,int y)        /*Soit une  cellule aux coordonnees (x;y): Renvoie le nombre de voisins vivants de cette cellule*/
{
  int ofx,ofy;
  int x0,y0;
  int n=0;
  for (ofx=-1;ofx<=1;ofx++)
    {
      for (ofy=-1;ofy<=1;ofy++)
	{
	  x0=x+ofx%TAILLEX_C;
	  y0=y+ofy%TAILLEY_C;
	  while (x0<0) x0+=TAILLEX_C;
	  while (y0<0) y0+=TAILLEY_C;
	  n+=monde_c[x0][y0];
	}
    }
  n-=monde_c[x][y];
  return n;
}


        /* Rempli au hasard de cellules vivantes le damier 1 en mode pas à pas*/
        void damier_hasard(int perc)
        {
          int i,j;
          perc=perc%101;        /*Si on met un nombre beaucoup plus grand que 101 trop peu de cellules verifiront la condition if (rand()%101 > perc). Inversement si on met un nombre beaucoup plus petit*/
          srand(time(NULL));    /*initialisation du rand pour que les nombres soit reellement aleatoire: la configuration initiale du damier est differente a chaque compilation*/
          for (j=0;j<TAILLEY;j++)    /*Permet de parcourir le damier*/
            for (i=0;i<TAILLEX;i++)  /*Permet de parcourir le damier*/
              {
            if (rand()%101 > perc)
              monde[i][j]=1;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
                                           Ainsi, on initialise le damier avec des valeurs qui serviront dans l'affichage du damier
                                           par le biais de la fonction "affiche".*/
            else
              monde[i][j]=0;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
                                           Ainsi, on initialise le damier avec des valeurs qui serviront dans l'affichage du damier
                                           par le biais de la fonction "affiche".*/
              }
        }

        /* Rempli au hasard de cellules vivantes le damier 2 (damier des evolutions) en mode pas à pas*/
        void damier_hasard2(int perc)
        {
          int i,j;
          perc=perc%101;        /*Si on met un nombre beaucoup plus grand que 101 trop peu de cellules vérifiront la condition if (rand()%101 > perc). Inversement si on met un nombre beaucoup plus petit*/
          srand(time(NULL));    /*initialisation du rand pour que les nombres soit reellement aleatoire: la configuration initiale du damier est différente a chaque compilation*/
          for (j=0;j<TAILLEY2;j++)    /*Permet de parcourir le damier*/
            for (i=0;i<TAILLEX2;i++)  /*Permet de parcourir le damier*/
              {
            if (rand()%101 > perc)
              monde2[i][j]=1;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
                                           Ainsi, on initialise le damier avec des valeurs qui serviront dans l'affichage du damier
                                           par le biais de la fonction "affiche".*/
            else
              monde2[i][j]=0;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
                                           Ainsi, on initialise le damier avec des valeurs qui serviront dans l'affichage du damier
                                           par le biais de la fonction "affiche".*/
              }
        }


/* Rempli au hasard de cellules vivantes le damier en mode continu */
void damier_hasard_c(int perc)
{
  int i,j;
  perc=perc%101;        /*Si on met un nombre beaucoup plus grand que 101 trop peu de cellules verifiront la condition if (rand()%101 > perc). Inversement si on met un nombre beaucoup plus petit*/
  srand(time(NULL));    /*initialisation du rand pour que les nombres soit reellement aleatoire: la configuration initiale du damier est différente a chaque compilation*/
  for (j=0;j<TAILLEY_C;j++)    /*Permet de parcourir le damier*/
    for (i=0;i<TAILLEX_C;i++)  /*Permet de parcourir le damier*/
      {
	if (rand()%101 > perc)
	  monde_c[i][j]=1;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
	                               Ainsi, on initialise le damier avec des valeurs qui servira dans l'affichage du damier
                                   par le biais de la fonction "affiche".*/
	else
	  monde_c[i][j]=0;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
	                               Ainsi, on initialise le damier avec des valeurs qui servira dans l'affichage du damier
                                   par le biais de la fonction "affiche".*/
      }
}



/* Calcule la generation suivante en mode normal pour le mode pas a pas(damier 1) */

        void generation_suivante(void)
        {
          int x,y;
          char monde_aux[TAILLEX][TAILLEY];   /*On fabrique un damier auxiliaire(une copie du damier affiche)*/
          /* Calcul de la nouvelle generation dans le tableau auxiliaire*/
          for(x=0;x<TAILLEX;x++)
            {
              for(y=0;y<TAILLEY;y++)
            {
              if(monde[x][y]==(char)1){                  /*Si la cellule est en vie*/
              switch(nombre_voisins(x,y))                /*selon le nombre de voisins, les cellules meurent,naissent ou continuent à vivre*/
                {
                case 0: monde_aux[x][y]=(char)0;break;        /*Meurt par isolement.*/
                case 1: monde_aux[x][y]=(char)0;break;        /*Meurt par isolement.*/
                case 2: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
                case 3: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
               default: monde_aux[x][y]=(char)0;break;        /* la cellule meurt par etouffement*/
                }
                  }
                else{   /*Si la cellule est morte*/
             switch(nombre_voisins(x,y))
                {
                case 0: monde_aux[x][y]=monde[x][y];break;       /* la cellule reste morte*/
                case 1: monde_aux[x][y]=monde[x][y];break;       /* la cellule reste morte*/
                case 2: monde_aux[x][y]=monde[x][y];break;       /* la cellule reste morte*/
                case 3: monde_aux[x][y]=(char)1;break;            /* la cellule nait*/
               default: monde_aux[x][y]=monde[x][y];break;       /*la cellule reste morte*/
                }

                   }

            }
            }

          /* Recopie du tableau auxiliaire dans le tableau courant*/
          for(x=0;x<TAILLEX;x++)
            {
              for(y=0;y<TAILLEY;y++)
            {
              monde[x][y]=monde_aux[x][y];
            }
            }
        }


/* Calcule la generation suivante en mode normal pour le mode pas a pas(damier 2) */
        void generation_suivante2(void)
        {
          int x,y;
          char monde_aux2[TAILLEX2][TAILLEY2];   /*On fabrique un damier auxiliaire(une copie du damier affiche)*/
          /* Calcul de la nouvelle generation dans le tableau auxiliaire*/
          for(x=0;x<TAILLEX2;x++)
            {
              for(y=0;y<TAILLEY2;y++)
            {move(y+16,x);
                if(monde2[x][y]==(char)1){                  /*Si la cellule est en vie*/
              switch(nombre_voisins2(x,y))                  /*selon le nombre de voisins, les cellules meurent,naissent ou continuent à vivre*/
                {
                case 0: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(5));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /*Meurt par isolement.*/
                case 1: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(5));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /*Meurt par isolement.*/
                case 2: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
                case 3: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
               default: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(6));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /* la cellule meurt par étouffement*/
                }
                  }
                else{   /*Si la cellule est morte*/
             switch(nombre_voisins2(x,y))
                {
                case 0: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /* la cellule reste morte*/
                case 1: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /* la cellule reste morte*/
                case 2: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /* la cellule reste morte*/
                case 3: monde_aux2[x][y]=(char)1;wattrset(stdscr,COLOR_PAIR(1));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule nait*/
               default: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /*la cellule reste morte*/
                }

                         }

            }
            }

          /* Recopie du tableau auxiliaire dans le tableau courant*/
          for(x=0;x<TAILLEX2;x++)
            {
              for(y=0;y<TAILLEY2;y++)
            {
              monde2[x][y]=monde_aux2[x][y];
            }
            }
        }


        /* Calcule la generation suivante pour le mode continu */
        void generation_suivante_c(void)
        {
          int x,y;
          char monde_aux_c[TAILLEX_C][TAILLEY_C];   /*On fabrique un damier auxiliaire(une copie du damier affiche)*/
          /* Calcul de la nouvelle generation dans le tableau auxiliaire*/
          for(x=0;x<TAILLEX_C;x++)
            {
              for(y=0;y<TAILLEY_C;y++)
            {
              switch(nombre_voisins_c(x,y))                  /*selon le nombre de voisins, les cellules meurent,naissent ou continuent à vivre*/
                {
                case 2: /* la cellule reste dans le même état*/
                  monde_aux_c[x][y]=monde_c[x][y];
                  break;
                case 3: /* la cellule nait*/
                  monde_aux_c[x][y]=(char)1;
                  break;
                default:  /* la cellule meurt dans les autres cas*/
                  monde_aux_c[x][y]=(char)0;
                  break;
                }
            }
            }


          /* Recopie du tableau auxiliaire dans le tableau courant*/
          for(x=0;x<TAILLEX_C;x++)
            {
              for(y=0;y<TAILLEY_C;y++)
            {
              monde_c[x][y]=monde_aux_c[x][y];
            }
            }
        }


/* Calcule la generation suivante en mode days and Nigth pour le mode pas a pas(damier 1) */
void generation_suivante_DN(void)
{
  int x,y;
  char monde_aux[TAILLEX][TAILLEY];   /*On fabrique un damier auxiliaire(une copie du damier affiche)*/
  /* Calcul de la nouvelle generation dans le tableau auxiliaire*/
  for(x=0;x<TAILLEX;x++)
    {
      for(y=0;y<TAILLEY;y++)
	{
	  if(monde[x][y]==(char)1){                  /*Si la cellule est en vie*/
	  switch(nombre_voisins(x,y))                /*selon le nombre de voisins, les cellules meurent,naissent ou continuent a vivre*/
	    {
        case 0: monde_aux[x][y]=(char)0;break;        /*Meurt par isolement.*/
        case 1: monde_aux[x][y]=(char)0;break;        /*Meurt par isolement.*/
	    case 2: monde_aux[x][y]=(char)0;break;        /*Meurt par isolement.*/
	    case 3: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
	    case 4: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
	    case 6: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
	    case 7: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
	    case 8: monde_aux[x][y]=monde[x][y];break;   /* la cellule reste en vie*/
       default: monde_aux[x][y]=(char)0;break;       /* la cellule meurt par etouffement*/
	    }
	      }
	    else{   /*Si la cellule est morte*/
     switch(nombre_voisins(x,y))       /*selon le nombre de voisins, les cellules meurent,naissent ou continuent a vivre*/
	    {
        case 0: monde_aux[x][y]=monde[x][y];break;       /* la cellule reste morte*/
        case 1: monde_aux[x][y]=monde[x][y];break;       /* la cellule reste morte*/
	    case 2: monde_aux[x][y]=monde[x][y];break;       /* la cellule reste morte*/
	    case 3: monde_aux[x][y]=(char)1;break;            /* la cellule nait*/
	    case 6: monde_aux[x][y]=(char)1;break;            /* la cellule nait*/
	    case 7: monde_aux[x][y]=(char)1;break;            /* la cellule nait*/
	    case 8: monde_aux[x][y]=(char)1;break;            /* la cellule nait*/
       default: monde_aux[x][y]=monde[x][y];break;       /*la cellule reste morte*/
	    }

           }

	}
    }

  /* Recopie du tableau auxiliaire dans le tableau courant*/
  for(x=0;x<TAILLEX;x++)
    {
      for(y=0;y<TAILLEY;y++)
	{
	  monde[x][y]=monde_aux[x][y];
	}
    }
}


/* Calcule la generation suivante en mode days and Nigth pour le mode pas a pas(damier 2) */
void generation_suivante2_DN(void)
{
  int x,y;
  char monde_aux2[TAILLEX2][TAILLEY2];   /*On fabrique un damier auxiliaire(une copie du damier affiche)*/
  /* Calcul de la nouvelle generation dans le tableau auxiliaire*/
  for(x=0;x<TAILLEX2;x++)
    {
      for(y=0;y<TAILLEY2;y++)
	{move(y+16,x);
	    if(monde2[x][y]==(char)1){                  /*Si la cellule est en vie*/
	  switch(nombre_voisins2(x,y))                  /*selon le nombre de voisins, les cellules meurent,naissent ou continuent a vivre*/
	    {
        case 0: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(5));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /*Meurt par isolement.*/
        case 1: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(5));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /*Meurt par isolement.*/
	    case 2: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(5));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /*Meurt par isolement.*/
	    case 3: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
	    case 4: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
	    case 6: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
	    case 7: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
	    case 8: monde_aux2[x][y]=monde2[x][y];wattrset(stdscr,COLOR_PAIR(2));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule reste en vie*/
       default: monde_aux2[x][y]=(char)0;wattrset(stdscr,COLOR_PAIR(6));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;         /* la cellule meurt par etouffement*/
	    }
	      }
	    else{   /*Si la cellule est morte*/
     switch(nombre_voisins2(x,y))         /*selon le nombre de voisins, les cellules meurent,naissent ou continuent a vivre*/
	    {
        case 0: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /* la cellule reste morte*/
        case 1: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /* la cellule reste morte*/
	    case 2: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /* la cellule reste morte*/
	    case 3: monde_aux2[x][y]=(char)1;wattrset(stdscr,COLOR_PAIR(1));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule nait*/
	    case 6: monde_aux2[x][y]=(char)1;wattrset(stdscr,COLOR_PAIR(1));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule nait*/
	    case 7: monde_aux2[x][y]=(char)1;wattrset(stdscr,COLOR_PAIR(1));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule nait*/
	    case 8: monde_aux2[x][y]=(char)1;wattrset(stdscr,COLOR_PAIR(1));addch(' ');wattrset(stdscr,COLOR_PAIR(0));break;    /* la cellule nait*/
       default: monde_aux2[x][y]=monde2[x][y];addch(' ');break;       /*la cellule reste morte*/
	    }

	             }

	}
    }

  /* Recopie du tableau auxiliaire dans le tableau courant*/
  for(x=0;x<TAILLEX2;x++)
    {
      for(y=0;y<TAILLEY2;y++)
	{
	  monde2[x][y]=monde_aux2[x][y];
	}
    }
}



/* Calcule la generation suivante pour la variante Days and Nigth en mode continue */
void generation_suivante_DN_c(void)
{
  int x,y;
  char monde_aux_c[TAILLEX_C][TAILLEY_C];   /*On fabrique un damier auxiliaire(une copie du damier affiche)*/
  /* Calcul de la nouvelle generation dans le tableau auxiliaire*/
  for(x=0;x<TAILLEX_C;x++)
    {
      for(y=0;y<TAILLEY_C;y++)
	{
	  switch(nombre_voisins_c(x,y))   /*selon le nombre de voisins, les cellules meurent,naissent ou continuent a vivre*/
	    {
	    case 4: /* la cellule reste dans le meme etat*/
	      monde_aux_c[x][y]=monde_c[x][y];
	      break;
	    case 3: /* la cellule nait*/
	      monde_aux_c[x][y]=(char)1;break;
	      case 6: /* la cellule nait*/
	      monde_aux_c[x][y]=(char)1;break;
	      case 7: /* la cellule nait*/
	      monde_aux_c[x][y]=(char)1;break;
	      case 8: /* la cellule nait*/
	      monde_aux_c[x][y]=(char)1;break;
	    default:  /* la cellule meurt dans les autres cas*/
	      monde_aux_c[x][y]=(char)0;
	      break;
	    }
	}
    }

  /* Recopie du tableau auxiliaire dans le tableau courant*/
  for(x=0;x<TAILLEX_C;x++)
    {
      for(y=0;y<TAILLEY_C;y++)
	{
	  monde_c[x][y]=monde_aux_c[x][y];
	}
    }
}




/*FONCTIONS PERMETTANT L'AFFICHAGE DES STRUCTURES CLASSIQUES*/

void carre_c(void)
{
	  monde_c[40][11]=1;             /*Voir la fonction "affiche" qui effectue un teste sur la valeur de monde[i][j].
                                       Ainsi, on initialise le damier avec des valeurs qui serviront dans l'affichage du damier*/

     monde_c[41][11]=1;
     monde_c[40][12]=1;
     monde_c[41][12]=1;
}

void tube_c(void)
{
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
}

void bateau_c(void)
{
     monde_c[39][11]=1;
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
}

void navire_c(void){
     monde_c[39][11]=1;
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
     monde_c[41][13]=1;
}

void serpent_c(void){
     monde_c[39][11]=1;
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[42][11]=1;
     monde_c[41][12]=1;
     monde_c[42][12]=1;
}

void barge_c(void){
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
     monde_c[41][10]=1;
     monde_c[42][11]=1;
}

void porte_avion_c(void){
     monde_c[39][13]=1;
     monde_c[40][13]=1;
     monde_c[39][12]=1;
     monde_c[42][12]=1;
     monde_c[41][11]=1;
     monde_c[42][11]=1;
}

void ruche_c(void){
    monde_c[41][9]=1;
    monde_c[40][10]=1;
    monde_c[42][10]=1;
    monde_c[40][11]=1;
    monde_c[42][11]=1;
    monde_c[41][12]=1;
}

void miche_de_pain_c(void){
    monde_c[41][9]=1;
    monde_c[40][10]=1;
    monde_c[42][9]=1;
    monde_c[40][11]=1;
    monde_c[42][11]=1;
    monde_c[41][12]=1;
    monde_c[43][10]=1;
}

void hamecon_c(void){
     monde_c[38][10]=1;
     monde_c[39][10]=1;
     monde_c[39][11]=1;
     monde_c[39][12]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
     monde_c[41][13]=1;
}

void canoe_c(void){
     monde_c[39][11]=1;
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[43][14]=1;
     monde_c[42][15]=1;
     monde_c[43][15]=1;
     monde_c[41][14]=1;
     monde_c[40][13]=1;
}

void long_barge_c(void){
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
     monde_c[41][10]=1;
     monde_c[42][11]=1;
     monde_c[43][10]=1;
     monde_c[42][9]=1;
}

void long_navire_c(void){
     monde_c[38][10]=1;
     monde_c[39][10]=1;
     monde_c[38][11]=1;
     monde_c[39][12]=1;
     monde_c[40][11]=1;
     monde_c[41][12]=1;
     monde_c[40][13]=1;
     monde_c[41][13]=1;
}

void mare_c(void){
    monde_c[41][9]=1;
    monde_c[42][9]=1;
    monde_c[40][10]=1;
    monde_c[43][10]=1;
    monde_c[40][11]=1;
    monde_c[43][11]=1;
    monde_c[41][12]=1;
    monde_c[42][12]=1;
}

void long_canoe_c(void){
     monde_c[39][11]=1;
     monde_c[40][11]=1;
     monde_c[39][12]=1;
     monde_c[44][15]=1;
     monde_c[43][16]=1;
     monde_c[44][16]=1;
     monde_c[41][14]=1;
     monde_c[42][15]=1;
     monde_c[40][13]=1;
}

void double_hamecon_c(void){
     monde_c[45][12]=1;
     monde_c[45][11]=1;
     monde_c[44][11]=1;
     monde_c[43][12]=1;
     monde_c[43][13]=1;
     monde_c[43][14]=1;
     monde_c[42][14]=1;
     monde_c[41][14]=1;
     monde_c[40][15]=1;
     monde_c[41][16]=1;
     monde_c[40][16]=1;
}

void clignotant_c(void){
monde_c[40][11]=1;
monde_c[41][11]=1;
monde_c[42][11]=1;
}

void grenouille_c(void){
monde_c[40][11]=1;
monde_c[41][11]=1;
monde_c[42][11]=1;
monde_c[41][10]=1;
monde_c[42][10]=1;
monde_c[43][10]=1;
}

void croix_c(void){
int i,h,k,u,l;
for(i=38;i<=41;i++)
{monde_c[i][11]=1;
monde_c[i][18]=1;}
for(h=36;h<=38;h++)
{monde_c[h][13]=1;
monde_c[h][16]=1;}
for(k=14;k<=15;k++)
{monde_c[36][k]=1;
monde_c[43][k]=1;}
for(u=12;u<=13;u++)
{monde_c[38][u]=1;
monde_c[41][u]=1;}
for(l=41;l<=43;l++)
{monde_c[l][16]=1;}
monde_c[38][17]=1;
monde_c[42][13]=1;
monde_c[41][17]=1;
monde_c[43][13]=1;
}

void horloge_c(void){
monde_c[30][9]=1;
monde_c[30][10]=1;
monde_c[31][9]=1;
monde_c[31][10]=1;

monde_c[34][15]=1;
monde_c[34][16]=1;
monde_c[35][15]=1;
monde_c[35][16]=1;

monde_c[36][5]=1;
monde_c[36][6]=1;
monde_c[37][5]=1;
monde_c[37][6]=1;

monde_c[40][11]=1;
monde_c[40][12]=1;
monde_c[41][11]=1;
monde_c[41][12]=1;

monde_c[33][9]=1;
monde_c[33][10]=1;
monde_c[33][11]=1;
monde_c[33][12]=1;

monde_c[34][8]=1;
monde_c[35][8]=1;
monde_c[36][8]=1;
monde_c[37][8]=1;

monde_c[34][13]=1;
monde_c[35][13]=1;
monde_c[36][13]=1;
monde_c[37][13]=1;

monde_c[38][9]=1;
monde_c[38][10]=1;
monde_c[38][11]=1;
monde_c[38][12]=1;

monde_c[34][10]=1;
monde_c[35][11]=1;
monde_c[36][11]=1;
}

void diagonale_c(void){
monde_c[40][19]=1;
monde_c[41][19]=1;
monde_c[41][18]=1;
monde_c[41][17]=1;
monde_c[42][16]=1;
monde_c[43][17]=1;
monde_c[44][17]=1;
monde_c[45][16]=1;
monde_c[45][15]=1;
monde_c[44][15]=1;
monde_c[44][14]=1;
monde_c[43][14]=1;
monde_c[43][13]=1;
monde_c[44][12]=1;
monde_c[45][12]=1;
monde_c[46][13]=1;
monde_c[47][12]=1;
monde_c[47][11]=1;
monde_c[47][10]=1;
monde_c[48][10]=1;
}



void octogone_c(void){
int i,j;
for(i=38;i<=39;i++)
{monde_c[i][10]=1;
monde_c[i][17]=1;}
for(j=13;j<=14;j++)
{monde_c[35][j]=1;
monde_c[42][j]=1;}
monde_c[37][11]=1;
monde_c[36][12]=1;
monde_c[40][11]=1;
monde_c[41][12]=1;
monde_c[41][15]=1;
monde_c[40][16]=1;
monde_c[36][15]=1;
monde_c[37][16]=1;
}


void fontaine_c(void){
monde_c[43][11]=1;
monde_c[44][11]=1;
monde_c[41][12]=1;
monde_c[41][13]=1;
monde_c[42][12]=1;
monde_c[45][12]=1;
monde_c[46][12]=1;
monde_c[46][13]=1;
monde_c[42][14]=1;
monde_c[42][15]=1;
monde_c[45][14]=1;
monde_c[45][15]=1;
monde_c[40][15]=1;
monde_c[40][16]=1;
monde_c[41][16]=1;
monde_c[46][16]=1;
monde_c[47][16]=1;
monde_c[47][15]=1;
}

void galaxie_de_Kok_c(void){
int i,h,k,u;
for(i=3;i<=8;i++)
{monde_c[43][i]=1;
monde_c[44][i]=1;}
for(h=46;h<=51;h++)
{monde_c[h][3]=1;
monde_c[h][4]=1;}
for(k=43;k<=48;k++)
{monde_c[k][10]=1;
monde_c[k][11]=1;}
for(u=6;u<=11;u++)
{monde_c[50][u]=1;
monde_c[51][u]=1;}
}

void  pentadecathlon_c(void){
    monde_c[45][9]=1;
    monde_c[44][9]=1;
    monde_c[42][10]=1;
    monde_c[41][11]=1;
    monde_c[40][12]=1;
    monde_c[40][13]=1;
    monde_c[40][14]=1;
    monde_c[41][15]=1;
    monde_c[42][16]=1;
    monde_c[45][17]=1;
    monde_c[44][17]=1;
    monde_c[47][10]=1;
    monde_c[48][11]=1;
    monde_c[49][13]=1;
    monde_c[49][14]=1;
    monde_c[49][12]=1;
    monde_c[47][16]=1;
    monde_c[48][15]=1;
}

void planeur_c(void){
    monde_c[16][2]=1;
    monde_c[17][2]=1;
    monde_c[18][2]=1;
    monde_c[18][1]=1;
    monde_c[17][0]=1;
}

void LWSS_c(void){
    monde_c[14][9]=1;
    monde_c[15][10]=1;
    monde_c[16][10]=1;
    monde_c[17][10]=1;
    monde_c[18][10]=1;
    monde_c[18][9]=1;
    monde_c[18][8]=1;
    monde_c[17][7]=1;
    monde_c[14][7]=1;
}

void HWSS_c(void){
    monde_c[15][8]=1;
    monde_c[14][8]=1;
    monde_c[12][9]=1;
    monde_c[12][11]=1;
    monde_c[13][12]=1;
    monde_c[14][12]=1;
    monde_c[15][12]=1;
    monde_c[16][12]=1;
    monde_c[17][12]=1;
    monde_c[18][12]=1;
    monde_c[18][11]=1;
    monde_c[18][10]=1;
    monde_c[17][9]=1;
}


void canon_c(void)
{
    /*creation du premier carre a gauche*/
     monde_c[0][4]=1;
     monde_c[0][5]=1;
     monde_c[1][4]=1;
     monde_c[1][5]=1;

/*creation du second carre a droite*/
     monde_c[34][2]=1;
     monde_c[34][3]=1;
     monde_c[35][2]=1;
     monde_c[35][3]=1;

monde_c[13][2]=1;
monde_c[12][2]=1;
monde_c[11][3]=1;
monde_c[10][4]=1;
monde_c[10][5]=1;
monde_c[10][6]=1;
monde_c[11][7]=1;
monde_c[12][8]=1;
monde_c[13][8]=1;

monde_c[14][5]=1;

monde_c[15][3]=1;
monde_c[16][4]=1;
monde_c[16][5]=1;
monde_c[16][6]=1;
monde_c[15][7]=1;

monde_c[17][5]=1;

monde_c[20][4]=1;
monde_c[20][3]=1;
monde_c[20][2]=1;

monde_c[21][4]=1;
monde_c[21][3]=1;
monde_c[21][2]=1;

monde_c[22][1]=1;
monde_c[22][5]=1;

monde_c[24][1]=1;
monde_c[24][0]=1;

monde_c[24][5]=1;
monde_c[24][6]=1;



}

/*FIN DES FONCTIONS PERMETTANT L'AFFICHAGE DES STRUCTURES CLASSIQUES*/



/*fonction qui permet de lancer le mode continue avec une structure classique qui est précisee par la valeur de l'argument n*/
void continue_c(int n){
        int i=0;         /*Variable permettant de repeter la question: "Voulez vous personnaliser votre jeu?" si l'utilisateur saisi un chiffre incorrecte.*/
        int reponse;     /*Variable que l'on switch pour savoir si l'utilisateur souhaite personaliser ou non le jeu*/
        int j=0;         /*Variable permettant de repeter la question: "Choisissez la couleur des cellules" si l'utilisateur saisi un chiffre incorrecte.*/
        int temp;        /*Variable gerant le temps d'animation dans le mode continu*/
        int col;         /*Variable que l'on switch pour savoir la couleur des cellules que souhaite l'utilisateur */

printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                     scanf("%d",&reponse);
                     while(i==0){              /*Permet de repeter la question "Voulez vous personnaliser votre jeu?" si l'utilisateur ne saisie ni 0 ni 1*/
                     switch(reponse)
                      {
                        case 0: temp=500;col=1;i++; break; /*si le mode par defaut est choisi...*/
                        case 1: printf("\n\n\nChoisissez le temps d'animation:\n\n(Une valeur de 500 est raisonable: Si vous saisissez un nombre plus grand, vous ralentirez l'animation et inversement, si vous saisissez un nombre plus petit\n)\n\n"); /*si on personnalise le jeu...*/
                                scanf("%d",&temp);
                                while(j==0){           /*Permet de repeter la question "Choisissez la couleur des cellules" si l'utilisateur ne saisie pas un nombre entre 1 et 8*/
                                printf("\nChoisissez la couleur des cellules: (Saisissez un chiffre)\n 1=bleu\n 2=vert\n 3=noir    (Pas judicieux. Vous ne verrez rien!)\n 4=rouge\n 5=jaune\n 6=magenta\n 7=cyan\n 8=blanc\n\n");
                                scanf("%d",&col);   /*Saisie de la couleur des cellules*/
                                switch(col)
                                {
                                  case 1:j++;break;  /*L'instruction j++ permet de ne plus repeter la question "Choisissez la couleur des cellules" */
                                  case 2:j++;break;  /*idem*/
                                  case 3:j++;break;  /*idem*/
                                  case 4:j++;break;  /*idem*/
                                  case 5:j++;break;  /*idem*/
                                  case 6:j++;break;  /*idem*/
                                  case 7:j++;break;  /*idem*/
                                  case 8:j++;break;  /*idem*/
                                  default:break;     /*Ici, j vaut toujours 0 donc on repose la question "choisissez la couleur des cellules"*/
                                }
                                            }
                            i++;
                            break;
                        default:printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                                scanf("%d",&reponse);
                                break;
                      }
                                    }

          char d=' ';
          init_curses();     /*Fonction qui contient initscr(): ouvre un nouveau terminal(nouvelle fenetre) que l'on appelera par la suite terminal_ext
                            par opposition au terminal normal de Linux que l'on appelera terminal_int(sous window,c'est le meme terminal)*/
          noecho();  /*On ne veut pas d'echo*/
          nodelay(stdscr,TRUE);
          switch(n){
          case 0: carre_c();break;
          case 1: tube_c();break;
          case 2: bateau_c();break;
          case 3: navire_c();break;
          case 4: serpent_c();break;
          case 5: barge_c();break;
          case 6: porte_avion_c();break;
          case 7: ruche_c();break;
          case 8: miche_de_pain_c();break;
          case 9: hamecon_c();break;
          case 10: canoe_c();break;
          case 11: long_barge_c();break;
          case 12: long_navire_c();break;
          case 13: mare_c();break;
          case 14: long_canoe_c();break;
          case 15: double_hamecon_c();break;
          case 16: clignotant_c();break;
          case 17: grenouille_c();break;
          case 18: horloge_c();break;
          case 19: pentadecathlon_c();break;
          case 20: planeur_c();break;
          case 21: LWSS_c();break;
          case 22: HWSS_c();break;
          case 23: canon_c();break;
          case 24: galaxie_de_Kok_c();break;
          case 25: croix_c();break;
          case 26: octogone_c();break;
          case 27: fontaine_c();break;
          case 28: diagonale_c();break;
          }
          refresh();
          while(d!='q')  /*tant que la saisie clavier est differente de 'q', alors on affiche le damier, les generations suivantes et on demande
                           une saisie clavier pour demander ce qu'il faut faire ensuite*/
            {
              affiche_c(col);
              generation_suivante_c();
              d=getch();   /*d stocke une saisie clavier*/
              switch(d)   /*on fait un switch sur c: c'est a dire sur la saisie clavier*/
               {
                 case 'q': break;  /*si on saisie 'q', on arrete la boucle while et donc on arrete d'afficher*/
                 }
              temporise(temp);
              }
          fin_curses();  /* End curses mode: fonction qui execute endwin ie si on enleve cette commande, alors apres la fin du programme, on reste dans le terminal_ext de ncurses et on n'a donc plus
                                   acces au terminal_int.(cf remarque de initscr() pour la definition de termminal_int et terminal_ext) */

}


        /*DEBUT DU MAIN (PARTIE QUI EST EXECUTE)*/

        int main(void)
        { printf("                Bienvenue dans notre application du Jeu de la vie!\n\n");
          printf("                Code developpe par AUDA Alexandre & AUDA Remy\n\n\n");
          printf("-->Vous pourrez a tout moment relancer le jeu en appuyant sur la touche r et\n   quitter le jeu en appuyant sur la touche q.\n\n\n\n\n");
        int reponsestructure; /*Variable que l'on switch pour savoir quelles structures l'utilisateur souhaite visualiser*/
        int reponseStable;  /*Variable que l'on switch pour savoir quelles structures stables l'utilisateur souhaite visualiser*/
        int reponsePeriodique;/*Variable que l'on switch pour savoir quelles structures perodiques l'utilisateur souhaite visualiser*/
        int reponseVaissaux;/*Variable que l'on switch pour savoir quels vaissaux l'utilisateur souhaite visualiser*/
        int reponseModeDeJeu; /*Variable que l'on switch pour savoir si l'utilisateur souhaite le mode normal ou le mode D&N ou visualiser des structures classiques*/
        int reponseMode; /*Variable que l'on switch pour savoir si l'utilisateur souhaite le mode pas a pas ou le mode continu*/
        int s=0;         /*Variable permettant de repeter la question: Choisissez le type de structures stables que vous souhaitez visualiser"*/
        int p=0;          /*Variable permettant de repeter la question: Choisissez le type de structures periodiues que vous souhaitez visualiser"*/
        int v=0;          /*Variable permettant de repeter la question: Choisissez le type de vaissaux que vous souhaitez visualiser"*/
        int r=0;         /*Variable permettant de repeter la question: "Quels structures (stable, periodique ou vaissaux...) souhaitez vous visualiser*/
        int t=0;         /*Variable permettant de repeter la question: "Voulez-vous lancer le mode de jeu normal ou la variante Days and Nigth ou les structures classiques?"*/
        int k=0;         /*Variable permettant de repeter la question: "Choisissez le mode de jeu" si l'utilisateur saisi un chiffre incorrecte.*/
        int i=0;         /*Variable permettant de repeter la question: "Voulez vous personnaliser votre jeu?" si l'utilisateur saisi un chiffre incorrecte.*/
        int reponse;     /*Variable que l'on switch pour savoir si l'utilisateur souhaite personaliser ou non le jeu*/
        int j=0;         /*Variable permettant de repeter la question: "Choisissez la couleur des cellules" si l'utilisateur saisi un chiffre incorrecte.*/
        int w=0;         /*Variable utilisee pour gerer le fait que dans le mode pas a pas, on affiche d'abord "generation 0" puis on affiche ensuite "Evolution".*/
        int x=0;         /*Variable utilisee pour decaler d'une iteration l'evolution a la premiere saisie clavier dans le mode pas a pas*/
        int temp;        /*Variable gerant le temps d'animation dans le mode continu*/
        int col;         /*Variable que l'on switch pour savoir la couleur des cellules que souhaite l'utilisateur */




        printf("Voulez-vous lancer le mode de jeu normal ; la variante Days and Night           ou visualiser les structures classiques?:  (Saisissez un chiffre)\n 0=jeu normal\n 1=variante Days and Nigth\n 2=structures classiques\n\n");        scanf("%d",&reponseModeDeJeu);
        while(t==0){
         switch(reponseModeDeJeu){

             case 0:/*si le mode normal est choisi...*/


        printf("Choisisser le mode de jeu:  (Saisissez un chiffre)\n 0=pas a pas\n 1=continu\n\n");
        scanf("%d",&reponseMode);
          while(k==0){                 /*Permet de repeter la question: "Choisisser le mode de jeu" si l'utilisateur saisi un chiffre incorrecte.*/
            switch(reponseMode)
        {
            case 0:     /*si le mode pas a pas est choisi...*/

                   printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                   scanf("%d",&reponse);
                   while(i==0){              /*Permet de repeter la question "Voulez vous personnaliser votre jeu?" si l'utilisateur ne saisie ni 0 ni 1*/
                   switch(reponse)
                   {
                    case 0: col=2;i++; break;   /*Permet de ne pas personnaliser le jeu, à savoir choisir une couleur verte pour les cellules(col=2) et le i++ sert à ce que l'on ne repose pas la question "Voulez vous personnaliser votre jeu?"*/
                    case 1:
                            while(j==0){           /*Permet de repeter la question "Choisissez la couleur des cellules" si l'utilisateur ne saisie pas un nombre entre 1 et 8*/
                            printf("\nChoisissez la couleur des cellules: (Saisissez un chiffre)\n 1=bleu\n 2=vert\n 3=noir    (Pas judicieux. Vous ne verrez rien!)\n 4=rouge\n 5=jaune\n 6=magenta\n 7=cyan\n 8=blanc\n\n");
                            scanf("%d",&col);   /*Saisie de la couleur des cellules*/
                            switch(col)
                            {
                              case 1:j++;break;  /*L'instruction j++ permet de ne plus repeter la question "Choisissez la couleur des cellules" */
                              case 2:j++;break;  /*idem*/
                              case 3:j++;break;  /*idem*/
                              case 4:j++;break;  /*idem*/
                              case 5:j++;break;  /*idem*/
                              case 6:j++;break;  /*idem*/
                              case 7:j++;break;  /*idem*/
                              case 8:j++;break;  /*idem*/
                              default:break;     /*Ici, j vaut toujours 0 donc on repose la question "choisissez la couleur des cellules"*/
                            }
                                       }
                              i++;   /*le i++ sert à ce que l'on ne repose pas la question "Voulez vous personnaliser votre jeu?"*/
                              break;
                    default:
                             printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                             scanf("%d",&reponse);
                             break;
                  }
                }

          char c=' ';
          init_curses();     /*Fonction qui contient initscr(): ouvre un nouveau terminal(nouvelle fenetre) que l'on appelera par la suite terminal_ext
                            par opposition au terminal normal de Linux que l'on appelera terminal_int(sous window,c'est le meme terminal)*/
          noecho();
          nodelay(stdscr,TRUE);
          damier_hasard(50);
          damier_hasard2(50);
          refresh();
          keypad(stdscr, TRUE);  /*Permet d'inclure toutes les saisies clavier*/
          while(c!='q')  /*tant que la saisie clavier est differente de 'q', alors on affiche le damier, les generations suivantes et on demande
                           une saisie clavier pour demander ce qu'il faut faire ensuite*/
            {
                mvprintw(0,0,"Le jeu de la vie: génération %d",w);
                mvprintw(12,0,"------------------------------------------------------------------------------------------ ");
                if(w==0){
                mvprintw(13,0,"génération 0");
                           }
                else{
                mvprintw(13,11,"  ");   /*On efface le 0 de "generation 0" ecrit precedement*/
                mvprintw(13,0,"Evolution:vert=rester vivant/jaune=mourir par isolement\n          mauve=mourir par étouffement/bleu=naissance");
                      }
              affiche(col); /*on affiche le damier 1*/

              c=getch();   /*c stocke une saisie clavier*/

              switch(c)   /*on fait un switch sur c: c'est a dire sur la saisie clavier*/
            {
              case 'q': break;  /*si on saisie 'q', on arrete la boucle while et donc on arrete d'afficher*/
              case 'r': damier_hasard(50);damier_hasard2(50);mvprintw(0,30,"               ");x=0;w=0; break; /*si on saisie 'r', on reinitialise:on reinitialise le damier 1 avec damier_hasard et le damier 2 avec damier_hasard2. Le print est fait pour effacer les affichage de generations precedents. De plus, comme on reinitialise, on remet à 0 les variables x et w.*/
              default : if(c!=ERR && x==0){ generation_suivante();generation_suivante2();generation_suivante2();x++;w++;}/*si x=0 on decale l'evolution pour que le damier2 soit d'1 cran plus avance que celle du damier1*/
                        else if(c!=ERR) { generation_suivante();generation_suivante2();w++;}/*si x!=0,alors l'evolution du damier 1 et la meme que celle du damier 2*/
                        break;
             }

            }
          fin_curses();  /* End curses mode: fonction qui execute endwin ie si on enleve cette commande, alors apres la fin du programme, on reste dans le terminal_ext de ncurses et on n'a donc plus
                  //                 acces au terminal_int.(cf remarque de initscr() pour la definition de termminal_int et terminal_ext) */
            k++;
            break;


             case 1:        /*si le mode continu est choisi...*/
                     printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                     scanf("%d",&reponse);
                     while(i==0){              /*Permet de repeter la question "Voulez vous personnaliser votre jeu?" si l'utilisateur ne saisie ni 0 ni 1*/
                     switch(reponse)
                      {
                        case 0: temp=500;col=1;i++; break;   /*si le mode par defaut est choisi...*/
                        case 1: printf("\n\n\nChoisissez le temps d'animation:\n\n(Une valeur de 500 est raisonable: Si vous saisissez un nombre plus grand, vous ralentirez l'animation et inversement, si vous saisissez un nombre plus petit\n)\n\n");  /*si on personnalise le jeu...*/
                                scanf("%d",&temp);
                                while(j==0){           /*Permet de repeter la question "Choisissez la couleur des cellules" si l'utilisateur ne saisie pas un nombre entre 1 et 8*/
                                printf("\nChoisissez la couleur des cellules: (Saisissez un chiffre)\n 1=bleu\n 2=vert\n 3=noir    (Pas judicieux. Vous ne verrez rien!)\n 4=rouge\n 5=jaune\n 6=magenta\n 7=cyan\n 8=blanc\n\n");
                                scanf("%d",&col);   /*Saisie de la couleur des cellules*/
                                switch(col)
                                {
                                  case 1:j++;break;  /*L'instruction j++ permet de ne plus repeter la question "Choisissez la couleur des cellules" */
                                  case 2:j++;break;  /*idem*/
                                  case 3:j++;break;  /*idem*/
                                  case 4:j++;break;  /*idem*/
                                  case 5:j++;break;  /*idem*/
                                  case 6:j++;break;  /*idem*/
                                  case 7:j++;break;  /*idem*/
                                  case 8:j++;break;  /*idem*/
                                  default:break;     /*Ici, j vaut toujours 0 donc on repose la question "choisissez la couleur des cellules"*/
                                }
                                            }
                            i++;
                            break;
                        default:printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                                scanf("%d",&reponse);
                                break;
                      }
                                    }

          char d=' ';
          init_curses();     /*Fonction qui contient initscr(): ouvre un nouveau terminal(nouvelle fenetre) que l'on appelera par la suite terminal_ext
                            par opposition au terminal normal de Linux que l'on appelera terminal_int(sous window,c'est le meme terminal)*/
          noecho();  /*On ne veut pas d'echo*/
          nodelay(stdscr,TRUE);
          damier_hasard_c(50);
          refresh();
          while(d!='q')  /*tant que la saisie clavier est differente de 'q', alors on affiche le damier, les generations suivantes et on demande
                           une saisie clavier pour demander ce qu'il faut faire ensuite*/
            {
              affiche_c(col);
              generation_suivante_c();
              d=getch();   /*c stocke une saisie clavier*/
              switch(d)   /*on fait un switch sur c: c'est a dire sur la saisie clavier*/
               {
                 case 'q': break;  /*si on saisie 'q', on arrete la boucle while et donc on arrete d'afficher*/
                 case 'r': damier_hasard_c(50); break; /*si on saisie 'r', on reinitialise*/
                 }
              temporise(temp);
              }
          fin_curses();  /* End curses mode: fonction qui execute endwin ie si on enleve cette commande, alors apres la fin du programme, on reste dans le terminal_ext de ncurses et on n'a donc plus
                                   acces au terminal_int.(cf remarque de initscr() pour la definition de termminal_int et terminal_ext) */
           k++;
           break;

                        default:/*si ni le mode pas a pas ni le mode continu n'a ete choisi...*/
                                 printf("Choisisser le mode de jeu.  (Saisissez un chiffre)\n 0=pas a pas\n 1=continu\n\n");
                                 scanf("%d",&reponseMode);
                                 break;
            }
          }

          t++;
               break;

case 1:   /*si le mode days and nigth est choisi...*/
                printf("Choisisser le mode de jeu:  (Saisissez un chiffre)\n 0=pas a pas\n 1=continu\n\n");
                scanf("%d",&reponseMode);
                while(k==0){                 /*Permet de repeter la question: "Choisisser le mode de jeu" si l'utilisateur saisi un chiffre incorrecte.*/
                switch(reponseMode)
                  {
                case 0:     /*si le mode pas a pas est choisi...*/

                   printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                   scanf("%d",&reponse);
                   while(i==0){              /*Permet de repeter la question "Voulez vous personnaliser votre jeu?" si l'utilisateur ne saisie ni 0 ni 1*/
                   switch(reponse)
                   {
                    case 0: col=2;i++; break;   /*Permet de ne pas personnaliser le jeu, à savoir choisir une couleur verte pour les cellules(col=2) et le i++ sert à ce que l'on ne repose pas la question "Voulez vous personnaliser votre jeu?"*/
                    case 1:
                            while(j==0){           /*Permet de repeter la question "Choisissez la couleur des cellules" si l'utilisateur ne saisie pas un nombre entre 1 et 8*/
                            printf("\nChoisissez la couleur des cellules: (Saisissez un chiffre)\n 1=bleu\n 2=vert\n 3=noir    (Pas judicieux. Vous ne verrez rien!)\n 4=rouge\n 5=jaune\n 6=magenta\n 7=cyan\n 8=blanc\n\n");
                            scanf("%d",&col);   /*Saisie de la couleur des cellules*/
                            switch(col)
                            {
                              case 1:j++;break;  /*L'instruction j++ permet de ne plus repeter la question "Choisissez la couleur des cellules" */
                              case 2:j++;break;  /*idem*/
                              case 3:j++;break;  /*idem*/
                              case 4:j++;break;  /*idem*/
                              case 5:j++;break;  /*idem*/
                              case 6:j++;break;  /*idem*/
                              case 7:j++;break;  /*idem*/
                              case 8:j++;break;  /*idem*/
                              default:break;     /*Ici, j vaut toujours 0 donc on repose la question "choisissez la couleur des cellules"*/
                            }
                                       }
                              i++;   /*le i++ sert à ce que l'on ne repose pas la question "Voulez vous personnaliser votre jeu?"*/
                              break;
                    default:
                             printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                             scanf("%d",&reponse);
                             break;
                  }
                }

          char c=' ';
          init_curses();     /*Fonction qui contient initscr(): ouvre un nouveau terminal(nouvelle fenetre) que l'on appelera par la suite terminal_ext
                            par opposition au terminal normal de Linux que l'on appelera terminal_int(sous window,c'est le meme terminal)*/
          noecho();
          nodelay(stdscr,TRUE);
          damier_hasard(50);
          damier_hasard2(50);
          refresh();
          keypad(stdscr, TRUE);  /*Permet d'inclure toutes les saisies clavier*/
          while(c!='q')  /*tant que la saisie clavier est differente de 'q', alors on affiche le damier, les generations suivantes et on demande
                           une saisie clavier pour demander ce qu'il faut faire ensuite*/
            {
                mvprintw(0,0,"Le jeu de la vie: génération %d",w);
                mvprintw(12,0,"------------------------------------------------------------------------------------------ ");
                if(w==0){
                mvprintw(13,0,"génération 0");
                           }
                else{
                mvprintw(13,11,"  ");   /*On efface le 0 de "generation 0" ecrit precedement*/
                mvprintw(13,0,"Evolution:vert=rester vivant/jaune=mourir par isolement\n          mauve=mourir par étouffement/bleu=naissance");
                      }
              affiche(col); /*on affiche le damier 1*/

              c=getch();   /*c stocke une saisie clavier*/

              switch(c)   /*on fait un switch sur c: c'est a dire sur la saisie clavier*/
            {
              case 'q': break;  /*si on saisie 'q', on arrete la boucle while et donc on arrete d'afficher*/
              case 'r': damier_hasard(50);damier_hasard2(50);mvprintw(0,30,"               ");x=0;w=0; break; /*si on saisie 'r', on réinitialise:on réinitialise le damier 1 avec damier_hasard et le damier 2 avec damier_hasard2. Le print est fait pour effacer les affichage de générations précédents. De plus, comme on réinitialise, on remet à 0 les variables x et w.*/
              default : if(c!=ERR && x==0){ generation_suivante_DN();generation_suivante2_DN();generation_suivante2_DN();x++;w++;}/*si x=0 on décale l'évolution pour que le damier2 soit d'1 cran plus avancé que celle du damier1*/
                        else if(c!=ERR) { generation_suivante_DN();generation_suivante2_DN();w++;}/*si x!=0,alors l'évolution du damier 1 et la même que celle du damier 2*/
                        break;
             }

            }
          fin_curses();  /* End curses mode: fonction qui execute endwin ie si son enleve cette commande, alors apres la fin du programme, on reste dans le terminal_ext de ncurses et on n'a donc plus
                  //                 acces au terminal_int.(cf remarque de initscr() pour la definition de termminal_int et terminal_ext) */
            k++;
            break;


             case 1:        /*si le mode continu est choisi...*/
                     printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                     scanf("%d",&reponse);
                     while(i==0){              /*Permet de repeter la question "Voulez vous personnaliser votre jeu?" si l'utilisateur ne saisie ni 0 ni 1*/
                     switch(reponse)
                      {
                        case 0: temp=500;col=1;i++; break; /*Si on choisi de ne pas personnaliser le jeu en mode continu alors on prend un temps d'animation de 500 et et la couleur bleu pour la couleur des cellules */
                        case 1: printf("\n\n\nChoisissez le temps d'animation:\n\n(Une valeur de 500 est raisonable: Si vous saisissez un nombre plus grand, vous ralentirez l'animation et inversement, si vous saisissez un nombre plus petit\n)\n\n");
                                scanf("%d",&temp);     /*Si on personalise le jeu en mode continu alors on demande à l'utilisateur le temps d'animation*/
                                while(j==0){           /*Permet de repeter la question "Choisissez la couleur des cellules" si l'utilisateur ne saisie pas un nombre entre 1 et 8*/
                                printf("\nChoisissez la couleur des cellules: (Saisissez un chiffre)\n 1=bleu\n 2=vert\n 3=noir    (Pas judicieux. Vous ne verrez rien!)\n 4=rouge\n 5=jaune\n 6=magenta\n 7=cyan\n 8=blanc\n\n");
                                scanf("%d",&col);   /*Saisie de la couleur des cellules*/
                                switch(col)
                                {
                                  case 1:j++;break;  /*L'instruction j++ permet de ne plus repeter la question "Choisissez la couleur des cellules" */
                                  case 2:j++;break;  /*idem*/
                                  case 3:j++;break;  /*idem*/
                                  case 4:j++;break;  /*idem*/
                                  case 5:j++;break;  /*idem*/
                                  case 6:j++;break;  /*idem*/
                                  case 7:j++;break;  /*idem*/
                                  case 8:j++;break;  /*idem*/
                                  default:break;     /*Ici, j vaut toujours 0 donc on repose la question "choisissez la couleur des cellules"*/
                                }
                                            }
                            i++;
                            break;
                        default:printf("Voulez vous personnaliser votre jeu?  (Saisissez un chiffre)\n 0=non\n 1=oui\n\n");
                                scanf("%d",&reponse);
                                break;
                      }
                                    }

          char d=' ';
          init_curses();     /*Fonction qui contient initscr(): ouvre un nouveau terminal(nouvelle fenetre) que l'on appelera par la suite terminal_ext
                            par opposition au terminal normal de Linux que l'on appelera terminal_int(sous window,c'est le meme terminal)*/
          noecho();  /*On ne veut pas d'echo*/
          nodelay(stdscr,TRUE);  /*Permet d'inclure toutes les saisies clavier*/
          damier_hasard_c(50);
          refresh();
          while(d!='q')  /*tant que la saisie clavier est differente de 'q', alors on affiche le damier, les generations suivantes et on demande
                           une saisie clavier pour demander ce qu'il faut faire ensuite*/
            {
              affiche_c(col);
              generation_suivante_DN_c();
              d=getch();   /*c stocke une saisie clavier*/
              switch(d)   /*on fait un switch sur c: c'est a dire sur la saisie clavier*/
               {
                 case 'q': break;  /*si on saisie 'q', on arrete la boucle while et donc on arrete d'afficher*/
                 case 'r': damier_hasard_c(50); break; /*si on saisie 'r', on reinitialise*/
                 }
              temporise(temp);
              }
          fin_curses();  /* End curses mode: fonction qui execute endwin ie si on enleve cette commande, alors apres la fin du programme, on reste dans le terminal_ext de ncurses et on n'a donc plus
                                   acces au terminal_int.(cf remarque de initscr() pour la definition de termminal_int et terminal_ext) */
           k++;
           break;

                        default:/*si ni le mode pas a pas ni le mode continu n'a ete choisi...*/
                                 printf("Choisisser le mode de jeu.  (Saisissez un chiffre)\n 0=pas a pas\n 1=continu\n\n");
                                 scanf("%d",&reponseMode);
                                 break;
            }
          }

         t++;
         break;

 case 2:   /*Si le mode des structures classiques est choisi...*/
            printf("Choisissez le type de structure que vous souhaitez visualiser:\n(Saisissez un chiffre)\n 0=structure stables\n 1=structure periodiques\n 2=vaisseaux\n\n");
            scanf("%d",&reponsestructure);
            while(r==0)
            {
           switch(reponsestructure)
          {
               case 0:  /*Dans le cas on l'on choisit des structures stables...*/
                       printf("Choisissez le type de structures stables que vous souhaitez visualiser:\n(Saisissez un chiffre)\n");
                       printf(" 0=carre\n 1=tube\n 2=bateau\n 3=navire\n 4=serpent\n 5=barge\n 6=porte-avion\n 7=ruche\n 8=miche de pain\n 9=hamecon\n 10=canoe\n 11=longue barge\n 12=long-navire\n 13=mare\n 14=long-canoe\n 15=double hamecon \n\n");
                       scanf("%d",&reponseStable);
                         while(s==0)
                         {
                       switch(reponseStable)
                       {
                       case 0:  /*Dans le cas ou l'on veut lancer la structure stable "carre"*/
                              continue_c(0);
                              s++;
                              break;

                       case 1:/*Dans le cas ou l'on veut lancer la structure stable "tube"*/
                             continue_c(1);
                              s++;
                              break;

                       case 2:/*Dans le cas ou l'on veut lancer la structure stable "bateau"*/
                             continue_c(2);
                              s++;
                              break;

                       case 3:/*Dans le cas ou l'on veut lancer la structure stable "navire"*/
                             continue_c(3);
                              s++;
                              break;

                       case 4:/*Dans le cas ou l'on veut lancer la structure stable "serpent"*/
                             continue_c(4);
                              s++;
                              break;

                       case 5:/*Dans le cas ou l'on veut lancer la structure stable "barge"*/
                             continue_c(5);
                              s++;
                              break;

                       case 6:/*Dans le cas ou l'on veut lancer la structure stable "porte-avion"*/
                             continue_c(6);
                              s++;
                              break;

                       case 7:/*Dans le cas ou l'on veut lancer la structure stable "ruche"*/
                             continue_c(7);
                              s++;
                              break;

                       case 8:/*Dans le cas ou l'on veut lancer la structure stable "miche de pain"*/
                             continue_c(8);
                              s++;
                              break;

                       case 9:/*Dans le cas ou l'on veut lancer la structure stable "hamecon"*/
                             continue_c(9);
                              s++;
                              break;

                       case 10:/*Dans le cas ou l'on veut lancer la structure stable "canoe"*/
                             continue_c(10);
                              s++;
                              break;

                       case 11:/*Dans le cas ou l'on veut lancer la structure stable "longue-barge"*/
                             continue_c(11);
                              s++;
                              break;

                       case 12:/*Dans le cas ou l'on veut lancer la structure stable "long-navire"*/
                             continue_c(12);
                              s++;
                              break;

                       case 13:/*Dans le cas ou l'on veut lancer la structure stable "mare"*/
                             continue_c(13);
                              s++;
                              break;

                       case 14:/*Dans le cas ou l'on veut lancer la structure stable "long-canoe"*/
                             continue_c(14);
                              s++;
                              break;

                       case 15:/*Dans le cas ou l'on veut lancer la structure stable "double hamecon"*/
                             continue_c(15);
                              s++;
                              break;


                       default: /*si on a saisi une valeur incorect a la question quel type de structure stable vous souhaitez visualiser*/
                                printf("Choisissez le type de structures stables que vous souhaitez visualiser:\n(Saisissez un chiffre)\n");
                                printf(" 0=carre\n 1=tube\n 2=bateau\n 3=navire\n 4=serpent\n 5=barge\n 6=porte-avion\n 7=ruche\n 8=miche de pain\n 9=hamecon\n 10=canoe\n 11=longue barge\n 12=long-navire\n 13=mare\n 14=long-canoe\n 15=double hamecon \n\n");
                                scanf("%d",&reponseStable);
                                break;
                       }
                       }
                       r++;
                       break;


               case 1:/*Dans le cas on l'on choisit des structures periodiques*/
                        printf("Choisissez le type de structures périodiques que vous souhaitez visualiser:\n(Saisissez un chiffre)\n");
                        printf(" 0=clignotant\n 1=grenouille\n 2=horloge\n 3=pentadecathlon\n 4=Galaxie de KOK\n 5=Croix\n 6=Octogone\n 7=Fontaine\n 8=Diagonale  \n\n");
                        scanf("%d",&reponsePeriodique);
                       while(p==0)
                         {
                       switch(reponsePeriodique)
                       {
                       case 0:  /*Dans le cas ou l'on veut lancer la structure periodique "clignotant"*/
                              continue_c(16);
                              p++;
                              break;

                       case 1:/*Dans le cas ou l'on veut lancer la structure periodique "grenouille"*/
                             continue_c(17);
                              p++;
                              break;

                       case 2:/*Dans le cas ou l'on veut lancer la structure periodique "horloge"*/
                             continue_c(18);
                              p++;
                              break;

                       case 3:/*Dans le cas ou l'on veut lancer la structure periodique "pentadecathlon"*/
                             continue_c(19);
                              p++;
                              break;

                       case 4:/*Dans le cas ou l'on veut lancer la structure periodique "galaxie de KOK"*/
                             continue_c(24);
                              p++;
                              break;


                       case 5:/*Dans le cas ou l'on veut lancer la structure periodique "croix"*/
                             continue_c(25);
                              p++;
                              break;

                       case 6:/*Dans le cas ou l'on veut lancer la structure periodique "octogone"*/
                             continue_c(26);
                              p++;
                              break;

                       case 7:/*Dans le cas ou l'on veut lancer la structure periodique "fontaine"*/
                             continue_c(27);
                              p++;
                              break;


                      case 8:/*Dans le cas ou l'on veut lancer la structure periodique "diagonale"*/
                             continue_c(28);
                              p++;
                              break;


                       default: /*si on a saisi une valeur incorect a la question quel type de structure stable vous souhaitez visualiser*/
                                 printf("Choisissez le type de structures périodiques que vous souhaitez visualiser:\n(Saisissez un chiffre)\n");
                                 printf(" 0=clignotant\n 1=grenouille\n 2=horloge\n 3=pentadecathlon\n 4=Galaxie de KOK\n 5=Croix\n 6=Octogone\n 7=Fontaine\n 8=Diagonale  \n\n");
                                 scanf("%d",&reponsePeriodique);
                                 break;
                       }
                       }
                      r++;
                      break;


               case 2:/*Dans le cas on l'on choisit des vaissaux*/
                          printf("Choisissez le type de vaissaux que vous souhaitez visualiser:\n(Saisissez un chiffre)\n");
                          printf(" 0=planeur\n 1=vaissaux LWSS\n 2=vaissaux HWSS\n 3=canon \n\n");
                          scanf("%d",&reponseVaissaux);
                         while(v==0)
                         {
                       switch(reponseVaissaux)
                       {
                       case 0:  /*Dans le cas ou l'on veut lancer le vaisseau "planeur"*/
                              continue_c(20);
                              v++;
                              break;

                       case 1:/*Dans le cas ou l'on veut lancer le vaisseau "LWSS"*/
                             continue_c(21);
                              v++;
                              break;

                       case 2:/*Dans le cas ou l'on veut lancer le vaisseau "HWSS"*/
                             continue_c(22);
                              v++;
                              break;

                       case 3:/*Dans le cas ou l'on veut lancer le "canon"*/
                             continue_c(23);
                              v++;
                              break;


                       default: /*si on a saisi une valeur incorect à la question quel type de structure stable vous souhaitez visualiser*/
                                 printf("Choisissez le type de vaissaux que vous souhaitez visualiser:\n(Saisissez un chiffre)\n");
                                 printf(" 0=planeur\n 1=vaissaux LWSS\n 2=vaissaux HWSS\n 3=canon \n\n");
                                 scanf("%d",&reponseVaissaux);
                                 break;
                       }
                       }
                      r++;
                      break;


               default:
                       printf("Choisissez le type de structure que vous souhaitez visualiser:\n(Saisissez un chiffre)\n 0=structure stables\n 1=structure periodiques\n 2=vaisseaux\n\n");
                       scanf("%d",&reponsestructure);
                       break;

         }
         }
           t++;
          break;



         default: /*Dans le cas ou l'utilisateur a saisi un chiffre incorrect a la question: Voulez-vous lancer le mode de jeu normal , la variante Days and Night ou visualiser les structures classiques?*/
                  printf("Voulez-vous lancer le mode de jeu normal ; la variante Days and Night           ou visualiser les structures classiques?:  (Saisissez un chiffre)\n 0=jeu normal\n 1=variante Days and Nigth\n 2=structures classiques\n\n");
                  scanf("%d",&reponseModeDeJeu);
                  break;
         }
        }

          return (0);
        }

