//FORZA 4 - Citarella Emanuele

// LIBRERIE
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <unistd.h>

// TIPI DI DATO impostazioni - posizione - campo

/*	Tipo di dato che contiene le impostazioni principali del gioco variabili e non, come
	le righe, le colonne, i giocatori, le pedine di ciascun giocatore,
	campoX e campoY ed infine il valore della CPU, necessario per capire se debba essere
	inclusa nel gioco.
*/
typedef struct
	{
		int righe;
		int colonne;
		int giocatori;
		int* pedine;
		int campoX;
		int campoY;
		int CPU;
	}impostazioni;

// Tipo di dato che indica le righe e le colonne nel campo da gioco
typedef int posizione;

// Tipo di dato contenente i valori del campo da gioco
typedef int** campo;

// PROTOTIPI
void Titolo();
void PaginaIniziale();
void PaginaImpostazioni();
void gotoxy(short x, short y);
int ControlloFile(FILE *impostazioni);
campo AllocazioneCampo(impostazioni imp);
impostazioni AllocazionePedine(impostazioni imp);
impostazioni RiallocazionePedine(impostazioni imp);
campo ScritturaValoreCampo(campo tabella, posizione riga, posizione colonna, int pedina); int LetturaValoreCampo(campo tabella, posizione riga, posizione colonna);
impostazioni ScritturaRighe(impostazioni imp, int n); posizione LetturaRighe(impostazioni imp);
impostazioni ScritturaColonne(impostazioni imp, int m); posizione LetturaColonne(impostazioni imp);
impostazioni ScritturaGiocatori(impostazioni imp, int g); int LetturaGiocatori(impostazioni imp);
impostazioni ScritturaPedina(impostazioni imp, int i, int pedina); int LetturaPedina(impostazioni imp, int i);
impostazioni ScritturaCoordinataX(impostazioni imp, int x); int LetturaCoordinataX(impostazioni imp);
impostazioni ScritturaCoordinataY(impostazioni imp, int x); int LetturaCoordinataY(impostazioni imp);
impostazioni ScritturaValoreCPU(impostazioni imp, int i); int LetturaValoreCPU(impostazioni imp);
impostazioni ScritturaImpostazioniDefault(impostazioni imp);
impostazioni ImpostazioneValoreCPU(impostazioni imp);
impostazioni AcquisizioneRighe(); int ControlloRighe(int righe);
impostazioni AcquisizioneColonne(impostazioni imp); int ControlloColonne(int colonne);
impostazioni AcquisizioneGiocatori(impostazioni imp); int ControlloGiocatori(int giocatori);
impostazioni AcquisizionePedine(impostazioni imp);
impostazioni ScritturaImpostazioniUtente(impostazioni imp);
impostazioni Menu(impostazioni imp); int ControlloSceltaMenu(int scelta);
impostazioni RichiestaImpostazioni(impostazioni imp); int ControlloSceltaImpostazioni(int scelta);
void MostraImpostazioni(impostazioni imp);
void StampaNumeriSuperiori(impostazioni imp,posizione colonne);
void StampaRigheSuperiori(posizione colonne);
void StampaRigheCentrali(posizione colonne);
void StampaRigheInferiori(posizione colonne);
void StampaCampo(impostazioni imp,posizione righe, posizione colonne);
void RiempimentoCampo(campo tabella,posizione righe, posizione colonne);
int Mossa(campo tabella, impostazioni imp, int i);
int MossaCPU(campo tabella, impostazioni imp, int i);
int Turno(campo tabella, impostazioni imp);
int TurnoGiocatoreCPU(campo tabella, impostazioni imp);
int Gioco(campo tabella, impostazioni imp);
posizione SceltaColonnaCPU(campo tabella,impostazioni imp, posizione righe, int giocatore, int pedina);
posizione SceltaColonna(impostazioni imp, int i); int ControlloSceltaColonna(posizione colonna, posizione colonneTotali);
posizione InserisciPedina(campo tabella, posizione righe, posizione colonna, int pedina);
void DisegnaPedina(impostazioni imp,  posizione riga, posizione colonna, int pedina);
int ControlloCampo(impostazioni imp, campo tabella);
int ControlloVittoriaDiagonalePrincipale(impostazioni imp, posizione riga, posizione colonna, campo tabella);
int ControlloVittoriaDiagonaleSecondaria(impostazioni imp, posizione riga, posizione colonna, campo tabella);
int ControlloVittoriaColonna(impostazioni imp, posizione riga,campo tabella, int pedina);
int ControlloVittoriaRiga(impostazioni imp,posizione colonna, campo tabella, int pedina);
int ControlloVittoria(impostazioni imp, posizione riga, posizione colonna, campo tabella, int pedina);
void Vittoria();
void Pareggio();
void MessaggioFinale(int vittoria);

// PROGRAMMA
int main()
{
	// Dichiarazione Variabili
	impostazioni ImpostazioniGioco;
	campo Tabella;
	// Scrittura Valori di Default dal file alla struct
	ImpostazioniGioco = ScritturaImpostazioniDefault(ImpostazioniGioco);
	// Pagina iniziale del gioco
	Titolo();
	// Mostra le impostazioni di Default del gioco
	ImpostazioniGioco = Menu(ImpostazioniGioco);
	// Ottenimento valori del campo, allocamento e realizzazione
	posizione colonne = LetturaColonne(ImpostazioniGioco);
	posizione righe = LetturaRighe(ImpostazioniGioco);
	Tabella = AllocazioneCampo(ImpostazioniGioco);
	RiempimentoCampo(Tabella,righe,colonne);
	// Stampa del campo da gioco
	StampaCampo(ImpostazioniGioco,righe,colonne);
	// Inizio del gioco
	int vittoria = Gioco(Tabella, ImpostazioniGioco);
	// Fine del gioco e chiusura programma
	MessaggioFinale(vittoria);
	return 0;
}

// FUNZIONI UTILIZZATE

// Funzione che mostra il titolo del gioco
void Titolo()
{
	// Impostazione colore
	system("color F");
	// Visualizzazione titolo
	int x=15;
	int y=3;

	gotoxy(x,y++);
	printf(" ______ ___________ ______  ___      ___ \n");
	gotoxy(x,y++);
	printf("	|  ___|  _  | ___ \\___  / / _ \\    /   |\n");
	gotoxy(x,y++);
	printf("	| |_  | | | | |_/ /  / / / /_\\ \\  / /| |\n");
	gotoxy(x,y++);
	printf("	|  _| | | | |    /  / /  |  _  | / /_| |\n");
	gotoxy(x,y++);
	printf("	| |   \\ \\_/ / |\\ \\./ /___| | | | \\___  |\n");
	gotoxy(x,y++);
	printf("	\\_|    \\___/\\_| \\_\\_____/\\_| |_/     |_/\n");

	x = 17;
	y = 11;

	gotoxy(x,y++);
	printf("Programma Creato da Citarella Emanuele\n");

	x = 18;
	y = 14;

	gotoxy(x,y++);
	printf("Premi un tasto qualsiasi per giocare \n");
	getch();
	system ("cls");
}

// Funzione che mostra la pagina iniziale del gioco
void PaginaIniziale()
{
	int x=25;
	int y=2;

	gotoxy(x,y++);
	printf("___  ________ _   _ _   _ _ ");

	gotoxy(x,y++);
	printf("|  \\/  |  ___| \\ | | | | ( )");

	gotoxy(x,y++);
	printf("| .  . | |__ |  \\| | | | |/ ");

	gotoxy(x,y++);
	printf("| |\\/| |  __|| . ` | | | |  ");

	gotoxy(x,y++);
	printf("| |  | | |___| |\\  | |_| |  ");

	gotoxy(x,y++);
	printf("\\_|  |_\\____/\\_| \\_/\\___/   ");
}

// Funzione che mostra la pagina di impostazioni del gioco
void PaginaImpostazioni()
{
	int x=3;
	int y=2;

	gotoxy(x,y++);
	printf(" ________  _________ _____ _____ _____ ___   ___________ _____ _   _ _____ ");

	gotoxy(x,y++);
	printf("|_   _|  \\/  || ___ \\  _  /  ___|_   _/ _ \\ |___  /_   _|  _  | \\ | |_   _|");

	gotoxy(x,y++);
	printf("  | | | .  . || |_/ / | | \\ `--.  | |/ /_\\ \\   / /  | | | | | |  \\| | | |  ");

	gotoxy(x,y++);
	printf("  | | | |\\/| ||  __/| | | |`--. \\ | ||  _  |  / /   | | | | | | . ` | | |  ");

	gotoxy(x,y++);
	printf(" _| |_| |  | || |   \\ \\_/ /\\__/ / | || | | |./ /____| |_\\ \\_/ / |\\  |_| |_ ");

	gotoxy(x,y++);
	printf(" \\___/\\_|  |_/\\_|    \\___/\\____/  \\_/\\_| |_/\\_____/\\___/ \\___/\\_| \\_/\\___/ ");
}

// Sposta in un punto x (NUMERO DI COLONNA ->) e y (NUMERO DI RIGA ^) dello schermo qualcosa
// PS : La coordinata 0,0 è in alto a sinistra, perciò le y quando aumentano vanno verso il
// Basso dello schermo
void gotoxy(short x, short y)
{
	HANDLE h;
	COORD coord;

	h = GetStdHandle(STD_OUTPUT_HANDLE);
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(h, coord);
}

// Funzione che controlla se il file è vuoto o meno
int ControlloFile(FILE *impostazioni)
{
	/*
	-INPUT : File, file di impostazioni del gioco di cui controllare se è NULL o meno
  	-OUTPUT : Esito, Valore che indica con 1 se il file non è NULL, e con 0 se invece lo è
	*/

	int esito=0;

	if (impostazioni != NULL)
	{
		esito=1;
	}else
		{
		printf("Il file non può essere aperto!");
		}
	return esito;
}

// Funzione che alloca il campo prendendo dalla struct IMPOSTAZIONI il valore di righe e colonne
campo AllocazioneCampo(impostazioni imp)
{
	campo tabella;
	posizione righe = LetturaRighe(imp);
	posizione colonne = LetturaColonne(imp);
	tabella = malloc(righe*colonne*sizeof(int*));
	int i=0;
		while(i<righe)
		{
			*(tabella+i)=malloc(colonne*sizeof(int));
			i++;
		}

	return tabella;
}

// Funzione che alloca le pedine per quanti sono i giocatori
impostazioni AllocazionePedine(impostazioni imp)
{
	int giocatori = LetturaGiocatori(imp);
	imp.pedine = malloc(giocatori*sizeof(int));
	return imp;
}

// Funzione che rialloca le pedine per quanti sono i nuovi giocatori
impostazioni RiallocazionePedine(impostazioni imp)
{
	int giocatori = LetturaGiocatori(imp);
	imp.pedine = realloc(imp.pedine,giocatori*sizeof(int));
	return imp;
}

// Funzione che SCRIVE le righe nel tipo di dato IMPOSTAZIONI in RIGHE
impostazioni ScritturaRighe(impostazioni imp, int n)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere il valore delle righe
			Righe, valore intero >=4 che indica la dimensione delle righe del campo
	OUTPUT : Impostazioni, Dato contentente la dimensione N delle righe
	*/
	imp.righe=n;
	return imp;
}

// Funzione che LEGGE le righe nel tipo di dato IMPOSTAZIONI in RIGHE
posizione LetturaRighe(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il valore delle righe contenuto
			      	      all'interno
	OUTPUT : Righe, dimensione N delle righe
	*/
	posizione righe;
	righe = imp.righe;
	return righe;
}

// Scrittura di un valore all'interno del dato CAMPO
campo ScritturaValoreCampo(campo tabella, posizione riga, posizione colonna, int pedina)
{
	/*
	INPUT : Tabella, tipo di dato campo dal quale andiamo a prelevare i valori presneti all'interno
			Riga, tipo di dato posizione,intero >=4 e <=7 che indica in che riga
				   vogliamo scrivere il valore
			Colonna, tipo di dato posizione,intero >=4 e <=7 che indica in che colonna
					vogliamo scrivere il valore
			Pedina, intero >=2 o <=4 che vogliamo scrivere all'interno di tabella
	OUTPUT : Tabella, contenente il valore che volevamo scrivere
	*/
	*(*(tabella+riga)+colonna) = pedina;
	return tabella;
}

// Lettura di un valore all'interno del dato CAMPO
int LetturaValoreCampo(campo tabella, posizione riga, posizione colonna)
{
	/*
	INPUT : Tabella, tipo di dato campo dal quale andiamo a prelevare i valori presenti all'interno
			Riga, tipo di dato posizione,intero >=4 e <=7 che indica in che riga
					vogliamo leggere il valore
			Colonna, tipo di dato posizione,intero >=4 e <=7 che indica in che colonna
					vogliamo leggere il valore
	OUTPUT :Valore, valore intero >=0, presente in tabella che volevamo leggere
	*/
	int val;
	val = *(*(tabella+riga)+colonna);
	return val;
}

// Funzione che SCRIVE le colonne nel tipo di dato IMPOSTAZIONI in COLONNE
impostazioni ScritturaColonne(impostazioni imp, int m)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere il valore M delle colonne
			Colonne, valore intero >=4 che indica la dimensione delle colonne del campo
	OUTPUT : Impostazioni, Dato contentente la dimensione M delle righe
	*/
	imp.colonne=m;
	return imp;
}

// Funzione che LEGGE le colonne nel tipo di dato IMPOSTAZIONI
posizione LetturaColonne(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il valore delle colonne contenuto
			      	  	  all'interno
	OUTPUT : Colonne, dimensione M delle righe
	*/
	posizione colonne;
	colonne = imp.colonne;
	return colonne;
}

// Funzione che SCRIVE i giocatori nel tipo di dato IMPOSTAZIONI in GIOCATORI
impostazioni ScritturaGiocatori(impostazioni imp, int g)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere il numero di giocatori G presenti
			Giocatori, valore intero >=2 e <=4 che indica quante persone giocano
	OUTPUT : Impostazioni, Dato contentente il numero G di giocatori
	*/
	imp.giocatori=g;
	return imp;
}

// Funzione che LEGGE i giocatori nel tipo di dato IMPOSTAZIONI
int LetturaGiocatori(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il numero dei giocatori contenuto
			      	  	  all'interno
	OUTPUT : Giocatori, numero G di giocatori presenti
	*/
	int giocatori;
	giocatori = imp.giocatori;
	return giocatori;
}

// Funzione che SCRIVE le pedine nel tipo di dato IMPOSTAZIONI in PEDINE
impostazioni ScritturaPedina(impostazioni imp, int i, int pedina)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere il numero di giocatori G presenti
			Pedina, valore intero >=2 e <=4 che vogliamo scrivere in Impostazioni
			i, valore intero >=0 che indica in che posizione vogliamo scrivere la pedina
	OUTPUT : Impostazioni, Dato contentente la pedina al suo interno
	*/
	*(imp.pedine+i)=pedina;
	return imp;
}

// Funzione che LEGGE le pedine nel tipo di dato IMPOSTAZIONI
int LetturaPedina(impostazioni imp, int i)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il numero dei giocatori contenuto
			      	  	  all'interno
			i, valore intero >=0 che indica in che posizione vogliamo leggere la pedina
	OUTPUT : Pedina, valore intero >=2 e <=4 che ci viene restituito
	*/
	int pedina;
	pedina = *(imp.pedine+i);
	return pedina;
}

// Funzione che SCRIVE la coordinata x nel tipo di dato IMPOSTAZIONI in CAMPOX
impostazioni ScritturaCoordinataX(impostazioni imp, int x)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere la coordinata X dalla quale iniziare a
			      	  	  stampare il campo
			x, valore intero >=0 che indica in che punto iniziare a stampare il campo
	OUTPUT : Impostazioni, Dato contentente la coordinata X di x
	*/
	imp.campoX=x;
	return imp;
}

// Funzione che LEGGE la coordinata x nel tipo di dato IMPOSTAZIONI
int LetturaCoordinataX(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il numero della coordinata X contenuto
			      	  	  all'interno
	OUTPUT : x, numero intero X presente all'interno del dato
	*/
	int x;
	x = imp.campoX;
	return x;
}

// Funzione che SCRIVE la coordinata y nel tipo di dato IMPOSTAZIONI in CAMPOX
impostazioni ScritturaCoordinataY(impostazioni imp, int y)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere la coordinata Y dalla quale iniziare a
			      	  	  stampare il campo
			y, valore intero >=0 che indica in che punto iniziare a stampare il campo
	OUTPUT : Impostazioni, Dato contentente la coordinata Y di y
	*/
	imp.campoY=y;
	return imp;
}

// Funzione che LEGGE la coordinata y nel tipo di dato IMPOSTAZIONI
int LetturaCoordinataY(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il numero della coordinata Y contenuto
			    	 	  all'interno
	OUTPUT : y, numero intero Y presente all'interno del dato che indica la coordinata
	*/
	int y;
	y = imp.campoY;
	return y;
}

// Funzione che SCRIVE il valore CPU nel tipo di dato IMPOSTAZIONI in CPU
impostazioni ScritturaValoreCPU(impostazioni imp, int i)
{
	/*
	INPUT : Impostazioni, tipo di dato in cui scrivere il valore che avrà la CPU nel gioco
			i, valore intero >=0 e <=1 che indica se la CPU giocherà o meno
	OUTPUT : i, valore intero contentente il valore che verrà assegnato alla CPU
	*/
	imp.CPU = i;
	return imp;
}

// Funzione che LEGGE il valore CPU nel tipo di dato IMPOSTAZIONI in CPU
int LetturaValoreCPU(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato nel quale leggere il valore della CPU
	OUTPUT : i, numero intero >=0 contenente il valore
	*/
	int i;
	i = imp.CPU;
	return i;
}

// Funzione che SCRIVE le impostazioni di default nella STRUCT
impostazioni ScritturaImpostazioniDefault(impostazioni imp)
{
	/*
	-INPUT : File, file di impostazioni del gioco dal quale prelevare le impostazioni
		       	   di default
	-OUTPUT : Impostazioni, tipo di dato contenente tutte le impostazioni di default
	*/
	FILE* fileImpostazioni;
	// Apertura del file
	fileImpostazioni=fopen("C:\\Users\\Ivan\\ProgettiEclipse\\Prova1\\impostazioni.f4","r");

	fscanf(fileImpostazioni,"%d", &(imp.righe));

	fscanf(fileImpostazioni,"%d", &(imp.colonne));

	fscanf(fileImpostazioni,"%d", &(imp.giocatori));

	imp=AllocazionePedine(imp);

	int i=0;
		while(i<imp.giocatori)
			{
				fscanf(fileImpostazioni,"%d",(imp.pedine+i));
				i++;
			}

	fscanf(fileImpostazioni,"%d", &(imp.campoX));
	fscanf(fileImpostazioni,"%d", &(imp.campoY));
	fscanf(fileImpostazioni,"%d", &(imp.CPU));
	// Chiusura del file
	fclose(fileImpostazioni);

	return imp;
}

// Funzione che mostra le impostazioni di default del gioco
void MostraImpostazioni(impostazioni imp)
{
	PaginaImpostazioni();
	int x=7;
	int y=10;

	int righe=LetturaRighe(imp);
	gotoxy(x,y);
	printf("Le righe sono %d,",righe);

	x=25;

	int colonne=LetturaColonne(imp);
	gotoxy(x,y);
	printf("le colonne sono %d,",colonne);

	x=45;

	int giocatori=LetturaGiocatori(imp);
	gotoxy(x,y);
	printf("mentre i giocatori sono %d.\n",giocatori);

	x=22;
	y=12;
	gotoxy(x,y);
	printf("Le pedine presenti sono : ");

	int i=0;
	int pedina;
	while(i<giocatori)
		{
			pedina=LetturaPedina(imp,i);
			printf(" '%d' ", pedina);
			i++;
		}
}

// Funzione che controlla la scelta effettuata nel menù di gioco
int ControlloSceltaMenu(int scelta)
{
	/*
	INPUT : Scelta, valore intero >=0 che indica la scelta effettuata nel menù dall'utente
	OUTPUT : Esito, valore intero >=0 e <=1 che indicherà l'esito del controllo della Scelta
	*/
	int esito=0;
		if(scelta!=1 && scelta!=2 && scelta!=3)
			{
				int x=7;
				int y=21;
				gotoxy(x,y);
				printf("Puoi soltanto scegliere tra '1','2' o '3'\n");
				return esito;
			}else
				{
					return esito=1;
				}
}

// Funzione che mostra il menù iniziale
impostazioni Menu(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato sul quale verranno effettuate le operazioni previste
			      	  	  in base alla scelta
	OUTPUT: Scelta, valore intero >=0 che indicherà la scelta effettuata dall'utente
	*/
	PaginaIniziale();

	int x;
	int y;
	int scelta;
	int esito;

	do{
		x=7;
		y=9;
		gotoxy(x,y);
		printf("Effettua una scelta : ");
		x++;
		y=11;
		gotoxy(x,y);
		printf("1) Inizia una Nuova Partita\n");

		y=13;
		gotoxy(x,y);
		printf("2) Visualizza/Modifica Impostazioni\n");

		y=15;
		gotoxy(x,y);
		printf("3) YOU vs CPU");

		x=15;
		y=19;
		gotoxy(x,y);
		printf("Scelta : ");
		scanf("%d", &scelta);

		if(scelta==1)
			{
				// Vai direttamente al campo da gioco
				system("cls");
			}

			if(scelta==2)
				{
					// Mostra la pagina di richiesta impostazioni
					system("cls");
					imp=RichiestaImpostazioni(imp);
				}

				if(scelta==3)
					{
						// Gioca contro la cpu, impostando il valore della CPU a 1
						imp = ImpostazioneValoreCPU(imp);
						system("cls");
					}

		esito = ControlloSceltaMenu(scelta);
	}while(esito==0);

	return imp;
	system("cls");
}

// Funzione che controlla la scelta effettuata nelle impostazioni
int ControlloSceltaImpostazioni(int scelta)
{
	/*
	INPUT : Scelta, valore intero >=0 che indica la scelta effettuata nel menù
					delle impostazioni dall'utente
	OUTPUT : Esito, valore intero >=0 e <=1 che indicherà l'esito del controllo della Scelta
	*/
	int esito=0;

		if(scelta!=1 && scelta!=2 )
			{
				int x=7;
				int y=20;
				gotoxy(x,y);
				printf("Puoi soltanto scegliere tra '1' o '2'\n");
				return esito;
			}
		return esito=1;
}

// Funzione che chiede cosa vuole fare l'utente
impostazioni RichiestaImpostazioni(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato sul quale verranno effettuate le operazioni previste
			      	  	  in base alla scelta
	OUTPUT: Scelta, valore intero >=0 che indicherà la scelta effettuata dall'utente
	*/
	int scelta;
	int x;
	int y;
	int esito;

	do{
		MostraImpostazioni(imp);
		x=7;
		y=15;
		gotoxy(x,y++);
		printf("Vorresti modificare le impostazioni?\n");

		gotoxy(x,y++);
		printf("1) Si\n");

		gotoxy(x,y++);
		printf("2) No, voglio giocare!\n");

		x=15;
		y=19;
		gotoxy(x,y);
		printf("Scelta : ");
		scanf("%d", &scelta);

		if(scelta==1)
			{
				imp=ScritturaImpostazioniUtente(imp);
				system("cls");
			}

			if(scelta==2)
					{
						// Vai direttamente al campo da gioco
						system("cls");
					}

			esito = ControlloSceltaImpostazioni(scelta);

	}while(esito==0);

	return imp;
	system("cls");
}

// Funzione che pone a 1 il valore CPU presente nel tipo di dato IMPOSTAZIONI
impostazioni ImpostazioneValoreCPU(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato su cui verrà scritto il nuovo valore che avrà
			      	  	  la CPU nel gioco, attivandola
	OUTPUT : Impostazioni, tipo di dato in cui è stato scritto il nuovo valore intero 1
	DATI DI LAVORO : i, variabile contenente il valore intero 1
	*/
	int i = 1;
	imp = ScritturaValoreCPU(imp,i);
	return imp;
}

// Funzione che controlla se il numero di righe inserito è corretto o meno
int ControlloRighe(int righe)
{
	/*
	INPUT : Righe, valore intero >=4 e <=7 che verrà controllato
	OUTPUT : Esito, valore intero al quale verrà assegnato 1 se i vincoli sono stati rispettati
					assegnerà invece 0 se non lo sono stati
	*/
	int esito=0;
		if(righe<4 || righe>7)
			{
				int x=7;
				int y=2;
				gotoxy(x,y);
				printf("Sicuro di aver inserito il valore giusto? Riprova!\n");
				return esito;
			}else
				{
					return esito=1;
				}
}

// Funzione per acquisire le righe se l'utente volesse modificare le impostazioni
impostazioni AcquisizioneRighe(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato su cui verrà scritto il nuovo valore N che
			    	 	  avranno le righe
			Righe, valore intero >=4 e <=7 che verrà scritto
	OUTPUT : Impostazioni, tipo di dato in cui è stato scritto il nuovo valore N delle righe
	*/
	int righe;
	int esito;

	do
	{
		int x=7;
		int y=10;
		gotoxy(x,y++);
		printf("Di quante righe vuoi il campo?\n");
		gotoxy(x,y++);
		printf("Non possono essere piu' di 7 e piu' piccole di 4!");
		gotoxy(x,y++);
		scanf("%d", &righe);
		esito=ControlloRighe(righe);

	}while(esito==0);

	imp = ScritturaRighe(imp,righe);
	system("cls");
	return imp;
}

// Funzione che controlla se il numero di colonne inserito è corretto o meno
int ControlloColonne(int colonne)
{
	/*
	INPUT : Colonne, valore intero >=4 e <=15 che verrà controllato
	OUTPUT : Esito, valore intero al quale verrà assegnato 1 se i vincoli sono stati rispettati
					assegnerà invece 0 se non lo sono stati
	*/
	int esito=0;
		if(colonne<4 || colonne>15)
			{
				int x=7;
				int y=2;
				gotoxy(x,y);
				printf("Sicuro di aver inserito il valore giusto? Riprova!\n");
				return esito;
			}else
				{
					return esito=1;
				}
}

// Funzione per acquisire le colonne se l'utente volesse modificare le impostazioni
impostazioni AcquisizioneColonne(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato su cui verrà scritto il nuovo valore M che
			      avranno le colonne
			Righe, valore intero >=4 e <=15 che verrà scritto
	OUTPUT : Impostazioni, tipo di dato in cui è stato scritto il nuovo valore M delle righe
	DATI DI LAVORO : Esito, valore intero che indicherà l'esito del controllo del valore M
	*/
	int esito;
	int colonne;

	do
	{
		int x=7;
		int y=10;

		gotoxy(x,y++);
		printf("Di quante colonne invece vuoi il campo?\n");

		gotoxy(x,y++);
		printf("Non possono essere piu' di 15 e piu' piccole di 4!");

		gotoxy(x,y++);
		scanf("%d", &colonne);

		esito = ControlloColonne(colonne);
	}while(esito==0);

	imp = ScritturaColonne(imp,colonne);
	system("cls");
	return imp;
}

// Funzione che controlla se il numero di colonne inserito è corretto o meno
int ControlloGiocatori(int giocatori)
{
	/*
	INPUT : Giocatori, valore intero >=2 e <=4 che verrà controllato
	OUTPUT : Esito, valore intero al quale verrà assegnato 1 se i vincoli sono stati rispettati
					assegnerà invece 0 se non lo sono stati
	*/
	int esito=0;
		if(giocatori<2 || giocatori>4)
			{
				int x=7;
				int y=2;
				gotoxy(x,y);
				printf("Sicuro di aver inserito il valore giusto? Riprova!\n");
				return esito;
			}else
				{
					return esito=1;
				}
}

// Funzione per acquisire i giocatori se l'utente volesse modificare le impostazioni
impostazioni AcquisizioneGiocatori(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato su cui verrà scritto il nuovo valore G che
			      avrà il numero di giocatori
			Giocatori, valore intero >=2 e <=4 che verrà scritto
	OUTPUT : Impostazioni, tipo di dato in cui è stato scritto il nuovo valore G dei giocatori
	DATI DI LAVORO : Esito, valore intero che indicherà l'esito del controllo del valore M
	*/
	int giocatori;
	int esito;
	do
	{
		int x=7;
		int y=17;

		gotoxy(x,y++);
		printf("ATTENZIONE: Verrano utilizzate soltanto pedine numeriche!");
		gotoxy(x,y++);
		printf("Il programma le assegnera' automaticamente per ciascun giocatore.");
		y=10;
		gotoxy(x,y++);
		printf("Quanti giocatori sono presenti?\n");

		gotoxy(x,y++);
		printf("Non possono essere piu' di 4 e devono essere minimo 2!");

		gotoxy(x,y++);
		scanf("%d", &giocatori);

		esito = ControlloGiocatori(giocatori);
	}while(esito==0);

	imp = ScritturaGiocatori(imp,giocatori);
	system("cls");
	return imp;
}

// Funzione per acquisire le pedine da assegnare a ciascun giocatore
impostazioni AcquisizionePedine(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato su cui verranno scritte le pedine
	OUTPUT : Impostazioni, dato contenenente le pedine dei giocatori
	*/
	int x = 7;
	int y = 10;
	int i=0;

	int giocatori = LetturaGiocatori(imp);

	while (i<giocatori)
	{
		gotoxy(x,y);
		imp = ScritturaPedina(imp,i,i+1);
		i++;
		y=y+2;
	}
	return imp;
}

// Funzione che chiede all'utente che impostazioni vuole inserire nel gioco
impostazioni ScritturaImpostazioniUtente(impostazioni imp)
{
	/*
	INPUT : Impostazioni, tipo di dato sul quale verranno scritte le impostazioni che l'utente
			      	  	  vorrà cambiare
	OUTPUT : Impostazioni, dato contenente le nuove impostazioni scelte dall'utente
	*/
	system ("cls");
	imp=AcquisizioneRighe(imp);
	imp=AcquisizioneColonne(imp);
	imp=AcquisizioneGiocatori(imp);
	imp=RiallocazionePedine(imp);
	imp=AcquisizionePedine(imp);
	return imp;
}

/* Parte sopra la parte superiore del campo da gioco, che indica con dei numeri, le
   Relative colonne
*/
void StampaNumeriSuperiori(impostazioni imp,posizione colonne)
{
	int x = LetturaCoordinataX(imp)+1;
	int y= LetturaCoordinataY(imp)-1;
	int j=0;

		while(j<colonne)
			{
				gotoxy(x,y);
				printf("%d",j+1);
				x=x+3;
				j++;
			}
}

// Parte superiore del campo da gioco
void StampaRigheSuperiori(posizione colonne)
{
	int j;

	char car=218;
	char car1=196;
	char car2=191;

	j=0;

	while(j<colonne)
	{
		printf("%c",car);
		printf("%c",car1);
		printf("%c",car2);
		j++;
	}
	printf("\n");
}

// Parte centrale del campo da gioco
void StampaRigheCentrali(posizione colonne)
{
	int j = 0;
	char car=179;
	char car1=255;

	while (j<colonne)
	{
		printf ("%c", car);
		printf ("%c", car1);
		printf ("%c", car);
		j++;
	}
	printf("\n");
}

// Parte inferiore dela campo da gioco
void StampaRigheInferiori(posizione colonne)
{
	int j;
		char car=192;
		char car1=196;
		char car2=217;
		j=0;

		while(j<colonne)
		{
			printf("%c",car);
			printf("%c",car1);
			printf("%c",car2);
			j++;
		}
		printf("\n");
}

// Stampa interamente il campo da gioco
void StampaCampo(impostazioni imp, posizione righe, posizione colonne)
{
	/*
	INPUT : Impostazioni, tipo di dato dal quale prelevare le informazioni necessarie
			      	  	  per la stampa del campo
			Righe, tipo di dato posizione che indica le righe totali del campo da gioco
			Colonne, tipo di dato posizione che indica le colonne totali del campo da gioco
	OUTPUT : Campo, campo da gioco visualizzato a schermo
	DATI DI LAVORO : i, indice del ciclo
	*/
	StampaNumeriSuperiori(imp,colonne);

	int x = LetturaCoordinataX(imp);
	int y = LetturaCoordinataY(imp);

	int i=0;

	while(i<righe)
			{
				gotoxy(x,y);
				StampaRigheSuperiori(colonne);
				y++;

				gotoxy(x,y);
				StampaRigheCentrali(colonne);
				y++;

				gotoxy(x,y);
				StampaRigheInferiori(colonne);
				y++;

				i++;
			}
}

// Riempie il tipo di dato CAMPO di soli numeri interi 0
void RiempimentoCampo(campo tabella,posizione righe, posizione colonne)
{
	/*
	INPUT : Tabella, tipo di dato campo nel quale inserire i valori interi 0
			Righe, tipo di dato posizione che indica le righe totali del campo da gioco
			Colonne, tipo di dato posizione che indica le colonne totali del campo da gioco
	OUTPUT : Tabella, tipo di dato campo contenente in tutte le posizioni i valori 0
	DATI DI LAVORO : i, indice del ciclo per le righe
			 	 	 j, indice del ciclo per le colonne
			 	 	 Valore, valore intero 0 da inserire nella posizione del campo
	*/
	posizione j;
	int valore = 0;

	posizione i=0;
	while(i<righe)
		{
				j=0;
				while(j<colonne)
					{
						tabella = ScritturaValoreCampo(tabella,i,j,valore);
						j++;
					}
				i++;
		}
}

// Funzione che permette di far effettuare una mossa ad un giocatore
int Mossa(campo tabella, impostazioni imp, int i)
{
	/*
	INPUT : Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
			Impostazioni, tipo di dato dal quale prelevare le informazioni principali
			i, Valore intero >=2 o <=4 che indica il giocatore corrente
	OUTPUT : Vittoria, Valore >=0 o <=1 che indica con 1 se la partita è vinta, e restituisce
		           	   invece -1 se la partita si è conclusa in pareggio
	*/
	int vittoria=0;
	// Lettura della pedina del giocatore corrente
	int pedina = LetturaPedina(imp,i);
	// Lettura delle righe totali presenti nel campo da gioco
	posizione riga = LetturaRighe(imp);
	// Richiesta Colonna in cui inserire la pedina
	posizione colonna = SceltaColonna(imp,i+1);
	// Inserimento nel Campo
	riga = InserisciPedina(tabella,riga-1,colonna,pedina);

		if(riga==-1)
			{
				int x = 2;
				int y= 15;
				gotoxy(x,y);
				printf("Turno perso per\n  giocatore %d!",i+1);
			}else
				{
					int x = 2;
					int y= 15;
					gotoxy(x,y);
					printf("               \n               ");
					// Disegno della pedina sul campo visualizzato a video
					DisegnaPedina(imp,riga,colonna,pedina);
					// Controllo della vittoria del giocatore
					vittoria = ControlloVittoria(imp,riga,colonna,tabella,pedina);
				}
	return vittoria;
}

// Funzione che permette di far effettuare una mossa alla CPU
int MossaCPU(campo tabella, impostazioni imp,int i)
{
	/*
	INPUT : Tabella, tipo di dato campo con il quale verificare la situazione attuale del campo
			Impostazioni, tipo di dato contenente le informazioni necessarie quali righe e colonne
			      	  	  del campo da gioco
			i, valore intero >=1 o <=2 che indica la pedina della CPU
	OUTPUT : Vittoria, valore intero <=1 che indica se la partita è stata vinta dal giocatore
			   	   	   CPU o meno
	DATI DI LAVORO : Riga, numero intero >=4 e <=7 che indica la riga nella quale verrà inserita
							la pedina della CPU, restituirà -1 se la riga è piena, facendo
							perdere il turno alla CPU
			 	 	 Colonna, numero intero >=4 e <=15 che indica la colonna scelta dalla CPU
				  	  	  	  nella quale inserire la propria pedina
	*/
	int vittoria=0;
	// Lettura della pedina del giocatore
	int pedina = LetturaPedina(imp,i);
	// Lettura delle righe totali presenti nel campo da gioco
	posizione riga = LetturaRighe(imp);
	posizione colonna = SceltaColonnaCPU(tabella,imp,riga-1,i+1,pedina);
	riga = InserisciPedina(tabella,riga-1,colonna,pedina);
		if(riga==-1)
			{
				int x = 2;
				int y= 15;
				gotoxy(x,y);
				printf("Turno perso per\n  giocatore %d!",i+1);
			}else
				{
					int x = 2;
					int y= 15;
					gotoxy(x,y);
					printf("               \n               ");
					// Disegno della pedina della CPU sul campo visualizzato a video
					DisegnaPedina(imp,riga,colonna,pedina);
					// Controllo della vittoria della CPU
					vittoria = ControlloVittoria(imp,riga,colonna,tabella,pedina);
				}
		return vittoria;
}

// Funzione che gestisce i turni tra il giocatore ed altri giocatori
int Turno(campo tabella, impostazioni imp)
{
	/*
	INPUT : Tabella, tipo di dato campo da utilizzare per far effettuare la mossa al giocatore
			Impostazioni, tipo di dato dal quale prelevare le informazioni necessarie per
			      	  	  consentire ai giocatori di giocare tra loro
	OUTPUT : Vittoria, valore intero >=0 o <=1 che indica la vittoria tra i giocatori presenti
			   	   	   Restituirà -1 se il campo sarà al completo
	DATI DI LAVORO : i, valore intero >=0 indice del ciclo
			 	 	 giocatori, valore intero >=2 che indica quanti giocatori ci sono
	*/
	int vittoria=0;
	int giocatori = LetturaGiocatori(imp);
	int i=0;
	while(i<giocatori && vittoria==0)
		{
			vittoria=Mossa(tabella,imp,i);
			i++;

				if(i==giocatori)
					{
						i=0;
					}
		}
	return vittoria;
}

// Funzione che gestisce i turni tra il giocatore e la CPU
int TurnoGiocatoreCPU(campo tabella, impostazioni imp)
{
	/*
	INPUT : Tabella, tipo di dato campo con il quale controllare la situazione del campo da gioco
			Impostazioni, tipo di dato attraverso il quale prelevare le informazioni necessarie
	OUTPUT : Vittoria, valore intero <=1 che indicare se la partita è stata persa o vinta, oppure
		           	   è terminata in pareggio, quest'ultimo caso viene indicato con il valore -1
	DATI DI LAVORO : i, valore intero >=0 indice del ciclo
			 	 	 Giocatori, valore intero <=2 che indica il numero di giocatori presenti nel gioco
	*/
	int vittoria=0;
	int giocatori = LetturaGiocatori(imp);
	int i=0;

	while(i<giocatori && vittoria==0)
		{
				if(i==1) // GIOCA LA CPU
					{
						vittoria = MossaCPU(tabella,imp,i);
					}else // ALTRIMENTI GIOCA IL GIOCATORE
						{
							vittoria = Mossa(tabella, imp ,i);
						}

				i++;

				if(i==giocatori)
					{
						i=0;
					}
		}
	return vittoria;
}

// Funzione che permette di far giocare tra di loro i giocatori presenti sul campo
int Gioco(campo tabella, impostazioni imp)
{
	/*
	INPUT : Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
			Impostazioni, tipo di dato dal quale prelevare le informazioni principali
	OUTPUT : Vittoria, Valore >=0 o <=1 che indica con 1 se la partita è vinta, e restituisce
		           	   invece -1 se la partita si è conclusa in pareggio
	 */
	int vittoria;
	// Controllo della cpu e Inizio del gioco
	if(LetturaValoreCPU(imp)==0)
		{
			// Gioco tra Giocatore e altri giocatori
			vittoria = Turno(tabella, imp);
		}else
			{
				// Gioco tra Giocatore e cpu
				vittoria = TurnoGiocatoreCPU(tabella, imp);
			}

	return vittoria;
}

// Funzione che permette alla CPU di inserire un valore in una colonna
posizione SceltaColonnaCPU(campo tabella,impostazioni imp, posizione righe,int giocatore, int pedina)
{
	/*
	INPUT : Tabella, dato di tipo campo necessario per controllare la situazione attuale
			 	 	 del campo
			Impostazioni, dato di tipo impostazioni dal quale prelevare le informazioni necessarie
							queli numero di colonne
			Righe, dato di tipo posizione che indica il numero totale delle righe presenti nel
					campo da gioco
			Giocatore, valore intero >=0 o <=1 che indica il numero del giocatore corrispondente
			Pedina, valore intero >=2 o <=4 che indica la pedina corrispondente del giocatore
	OUTPUT : Colonna, tipo di dato posizione che indica la colonna nella quale la CPU vorrà inserire
			 	 	 la propria pedina
	*/
	posizione colonneTotali = LetturaColonne(imp);
	posizione colonna=0;

	int x=2;
	int y=18;

	gotoxy(x,y);
	printf("Giocatore %d",giocatore);
	y=20;
	gotoxy(x,y);
	printf("In che colonna \n  vuoi inserire la pedina? ");
	sleep(1);

	int i=0;
	while(i<colonneTotali && colonna==0)
			{
				int valore1 = LetturaValoreCampo(tabella,righe,i);
				int valore2=-1;
				int valore3=-1;

					if(colonneTotali-1>=i && valore1!=0)
						{
							if(valore1!=pedina)
								{
									valore2 = LetturaValoreCampo(tabella,righe,i+1);
								}
						}

					if(colonneTotali-2>=i && valore2!=0)
						{
							if(valore2!=-1 && valore2!=pedina)
								{
									valore3 = LetturaValoreCampo(tabella,righe,i+2);
								}
						}

					if(valore1==valore2 && valore2==valore3)
						{
							if(LetturaValoreCampo(tabella,righe-1,i+3)==0)
							{
								colonna=colonna+4;
							}else
								{
									colonna = (rand()%colonneTotali)+1;
								}
						}
					i++;
			}

	if (colonna==0)
		{
			colonna = (rand()%colonneTotali)+1;
		}

	x=2;
	y=10;
	gotoxy(x,y);
	printf("                       \n                       \n            \n ");
	colonna = colonna-1;

	return colonna;
}

// Funzione che controlla se la colonna scelta è presente nel campo da gioco
int ControlloSceltaColonna(posizione colonna, posizione colonneTotali)
{
	/*
	INPUT : Colonna, tipo di dato posizione, intero >0 e <ColonneTotali
			 	 	 che indica la scelta effettuata dall'
			 	 	 utente riguardo alla colonna nella quale inserire il valore
			ColonneTotali, tipo di dato posizione, intero >0 che indica il numero massimo di
							colonne presenti nel campo da gioco
	OUTPUT : Esito, valore intero >=0 e <=1 che indicherà l'esito del controllo della Scelta
	*/
	int esito=0;

		if(colonna>colonneTotali || colonna==0)
				{
					int x=2;
					int y=10;
					gotoxy(x,y);
					printf("A quanto pare il valore\n  inserito non va bene. \n  Riprova!\n");
					return esito;
				}else
					{
						return esito=1;
					}

}

// Funzione che permette al giocatore di inserire la pedina in una colonna da lui selezionata
posizione SceltaColonna(impostazioni imp, int giocatore)
{
	/*
	INPUT : Impostazioni, tipo di dato dal quale prelevare le informazioni necessarie per
			      	  	  effettuare la scelta della colonna
			Giocatori, valore intero >=2 e <=4 che indica quanti giocatori sono presenti
			 	 	   in partita
			Colonna, tipo di dato posizione, intero <ColonneTotali che indica in quale colonna inserire il valore
	OUTPUT : Colonna, tipo di dato posizione, intero che indica la posizione nella quale il giocatore inserirà
			  	  	  la pedina
	DATI DI LAVORO : Esito, valore intero >=0 o <=1 che indicherà l'esito del controllo della
			        		colonna selezionata
			 	 	 ColonneTotali, tipo di dato posizione che indica quante colonne totali sono
									presenti nel campo
	*/
	posizione colonneTotali = LetturaColonne(imp);
	posizione colonna;
	int esito;

	do
	{
		int x=2;
		int y=18;
		gotoxy(x,y);
		printf("Giocatore %d",giocatore);
		y=20;
		gotoxy(x,y);
		printf("In che colonna \n  vuoi inserire la pedina? ");
		scanf("%d",&colonna);
		esito = ControlloSceltaColonna(colonna,colonneTotali);
		// Stampa la parte vuota per l'inserimento del numero
		x = 26;
		y=21;
		gotoxy(x,y);
		printf("      ");

	}while(esito==0);

	// Stampa la parte vuota nel caso esca il messaggio di errore
	int x=2;
	int y=10;
	gotoxy(x,y);
	printf("                       \n                       \n            \n ");
	colonna = colonna-1;
	return colonna;
}

// Funzione che inserisce la pedina nella posizione specificata
posizione InserisciPedina(campo tabella, posizione righe, posizione colonna, int pedina)
{
	/*
	INPUT : Tabella, tipo di dato campo con il quale scrivere il valore nella posizione desiderata
			Righe, tipo di dato posizione <N che indica le righe totali presenti nel campo
					da gioco
			Colonna, tipo di dato posizione che indica la colonna scelta dall'utente
			Pedina, intero >=2 o <=4 che indica la pedina del giocatore corrente
	OUTPUT : Righe, tipo di dato posizione che indica la riga nella quale è possibile
					inserire la pedina, Restituirà 0 se la posizione è libera, e -1
					se l'intera riga è occupata
	*/
	if(righe>=0)
		{
			int valore = LetturaValoreCampo(tabella,righe,colonna);

			if(valore==0)
			{
				tabella = ScritturaValoreCampo(tabella,righe,colonna,pedina);
				return righe;
			}else
				{
					return InserisciPedina(tabella,righe=righe-1,colonna,pedina);
				}
		}else
			{
				return righe=-1;
			}
}

// Funzione che disegna la pedina nel campo da gioco
void DisegnaPedina(impostazioni imp,  posizione riga, posizione colonna, int pedina)
{
	int x = LetturaCoordinataX(imp)+1;
	int y = LetturaCoordinataY(imp)+2;
	x=x+(3*colonna);
	y=y+(3*riga)-1;
	gotoxy(x,y);
	printf("%d",pedina);
}

// Funzione che controlla il campo da gioco per verificare se la partita finirà in pareggio
int ControlloCampo(impostazioni imp, campo tabella)
{
	/*
	INPUT : Impostazioni, tipo di dato dal quale prelevare le informazioni necessarie
			Tabella,  tipo di dato campo con il quale controllare la situazione del campo
	OUTPUT : Pareggio, intero >=0 o <=1 che indica se la partità finirà in pareggio o meno
	DATI DI LAVORO : i, valore intero >=0, indice del ciclo
			 	 	 valore, valore intero >=0 che leggerà il valore del campo nella posizione
				 	 	 	 specificata
			 	 	 Colonne, tipo di dato posizione che indica il numero M totale di colonne
				 	 	 	  presenti nel campo da gioco
	*/
	int pareggio=0;
	posizione colonne = LetturaColonne(imp)-1;
	int i=0;
	int valore;
		while(i<colonne)
			{
			valore = LetturaValoreCampo(tabella,0,i);
				if(valore!=0)
				{
					pareggio++;
				}
				i++;
			}

	if(pareggio==colonne)
	{
		return pareggio=1;
	}else
		{
			return pareggio=0;
		}
}

// Funzione che controlla le righe del campo da gioco per verificare la vittoria
int ControlloVittoriaRiga(impostazioni imp, posizione colonna, campo tabella, int pedina)
{
	/*
	INPUT : Impostazioni, tipo di dato impostazioni dal quale prelevare le informazioni
			      	  	  necessarie del campo
			Colonna, tipo di dato posizione che indica la colonna scelta dall'utente
			Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
			Pedina, valore intero >=2 o <=4 che indica la pedina del giocatore corrente
	OUTPUT : Vittoria, Valore intero >=0 o <=1 che indica con 0 se non c'è stata nessuna vittoria
			   	   	   e con 1 se invece la vittoria è presente
	*/
	posizione righe = LetturaRighe(imp)-1;

	int valore1;
	int valore2;
	int valore3;
	int valore4;

	int vittoria=0;
	int i=0;

	while(i<righe && vittoria!=1)
		{

			valore1 = LetturaValoreCampo(tabella,i,colonna);
			valore2=0;
			valore3=0;
			valore4=0;

				if(righe-1>=i)
					{
						valore2 = LetturaValoreCampo(tabella,i+1,colonna);
					}

				if(righe-2>=i)
					{
						valore3 = LetturaValoreCampo(tabella,i+2,colonna);
					}

				if(righe-3>=i)
					{
						valore4 = LetturaValoreCampo(tabella,i+3,colonna);
					}

				if(pedina==valore1 && pedina == valore2)
					{
						if(pedina==valore3 && pedina==valore4)
							{
								vittoria=1;
							}
					}
			i++;
		}

	return vittoria;
}

// Funzione che controlla le colonne del campo da gioco per verificare la vittoria
int ControlloVittoriaColonna(impostazioni imp, posizione riga,campo tabella, int pedina)
{
	/*
	INPUT : Impostazioni, tipo di dato impostazioni dal quale prelevare le informazioni
			      	  	  necessarie del campo
			Riga, tipo di dato posizione che indica la riga
			Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
			Pedina, valore intero >=2 o <=4 che indica la pedina del giocatore corrente
		OUTPUT : Vittoria, Valore intero >=0 o <=1 che indica con 0 se non c'è stata nessuna vittoria
			   	   	   	   e con 1 se invece la vittoria è presente
	*/
	posizione colonne = LetturaColonne(imp)-1;

	int valore1;
	int valore2;
	int valore3;
	int valore4;

	int vittoria=0;
	int i=0;

	while(i<colonne && vittoria!=1)
		{
			valore1 = LetturaValoreCampo(tabella,riga,i);
			valore2=0;
			valore3=0;
			valore4=0;

				if(colonne-1>=i)
					{
						valore2 = LetturaValoreCampo(tabella,riga,i+1);
					}

				if(colonne-2>=i)
					{
						valore3 = LetturaValoreCampo(tabella,riga,i+2);
					}

				if(colonne-3>=i)
					{
						valore4 = LetturaValoreCampo(tabella,riga,i+3);
					}

				if(pedina==valore1 && pedina == valore2)
					{
						if(pedina==valore3 && pedina==valore4)
						{
							vittoria=1;
						}
					}

			i++;
		}

	return vittoria;
}

// Funzione che controlla la diagonale principale del campo da gioco per verificare la vittoria
int ControlloVittoriaDiagonalePrincipale(impostazioni imp, posizione riga, posizione colonna, campo tabella)
{
	/*
	INPUT : Impostazioni, tipo di dato impostazioni dal quale prelevare le informazioni
			      	  	  necessarie del campo
			Riga, tipo di dato posizione che indica la riga
			Colonna, tipo di dato posizione che indica la colonna
			Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
	OUTPUT : Vittoria, Valore intero >=0 o <=1 che indica con 0 se non c'è stata nessuna vittoria
			   e con 1 se invece la vittoria è presente
	*/
	int vittoria=0;

	posizione righe = LetturaRighe(imp)-1;

	int valore1;
	int valore2;
	int valore3;
	int valore4;


	if(riga!= righe && riga!= righe-1 && riga!= righe-2)
			{
				valore1 = LetturaValoreCampo(tabella,riga+3,colonna-3);
				valore2 = LetturaValoreCampo(tabella,riga+2,colonna-2);
				valore3 = LetturaValoreCampo(tabella,riga+1,colonna-1);
				valore4 = LetturaValoreCampo(tabella,riga,colonna);

				if(valore1 == valore2 && valore2==valore3)
					{
						if(valore3==valore4)
							{
								vittoria++;
							}
					}
			}

	if(riga!= 0 && riga!= righe && riga!= righe-1)
			{
				valore1 = LetturaValoreCampo(tabella,riga+2,colonna-2);
				valore2 = LetturaValoreCampo(tabella,riga+1,colonna-1);
				valore3 = LetturaValoreCampo(tabella,riga,colonna);
				valore4 = LetturaValoreCampo(tabella,riga-1,colonna+1);

				if(valore1 == valore2 && valore2==valore3)
					{
						if(valore3==valore4)
							{
								vittoria++;
							}
					}
			}

	if(riga!= 0 && riga!= 1 && riga!= righe)
		{
			valore1 = LetturaValoreCampo(tabella,riga+1,colonna-1);
			valore2 = LetturaValoreCampo(tabella,riga,colonna);
			valore3 = LetturaValoreCampo(tabella,riga-1,colonna+1);
			valore4 = LetturaValoreCampo(tabella,riga-2,colonna+2);
		}
			if(valore1 == valore2 && valore2==valore3)
				{
					if(valore3==valore4)
						{
							vittoria++;
						}
				}

	if(riga!= 0 && riga!= 1 && riga!= 2)
			{
				valore1 = LetturaValoreCampo(tabella,riga,colonna);
				valore2 = LetturaValoreCampo(tabella,riga-1,colonna+1);
				valore3 = LetturaValoreCampo(tabella,riga-2,colonna+2);
				valore4 = LetturaValoreCampo(tabella,riga-3,colonna+3);

				if(valore1 == valore2 && valore2==valore3)
					{
						if(valore3==valore4)
							{
								vittoria++;
							}
					}
			}

	return vittoria;
}

// Funzione che controlla la diagonale secondaria del campo da gioco per verificare la vittoria
int ControlloVittoriaDiagonaleSecondaria(impostazioni imp, posizione riga, posizione colonna, campo tabella)
{
	/*
	INPUT : Impostazioni, tipo di dato impostazioni dal quale prelevare le informazioni
			      	  	  necessarie del campo
			Riga, tipo di dato posizione che indica la riga
			Colonna, tipo di dato posizione che indica la colonna
			Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
	OUTPUT : Vittoria, Valore intero >=0 o <=1 che indica con 0 se non c'è stata nessuna vittoria
			   e con 1 se invece la vittoria è presente
	*/
	int vittoria=0;

	posizione righe = LetturaRighe(imp)-1;

	int valore1;
	int valore2;
	int valore3;
	int valore4;

	if(riga!=righe && riga!=righe-1 && riga!=righe-2)
			{
				valore1 = LetturaValoreCampo(tabella,riga,colonna);
				valore2 = LetturaValoreCampo(tabella,riga+1,colonna+1);
				valore3 =  LetturaValoreCampo(tabella,riga+2,colonna+2);
				valore4 =  LetturaValoreCampo(tabella,riga+3,colonna+3);

					if(valore1 == valore2 && valore2==valore3)
						{
							if(valore3==valore4)
								{
									vittoria++;
								}
						}
			}

	if(riga!=0 && riga!=righe && riga!=righe-1)
			{
				valore1 = LetturaValoreCampo(tabella,riga-1,colonna-1);
				valore2 = LetturaValoreCampo(tabella,riga,colonna);
				valore3 = LetturaValoreCampo(tabella,riga+1,colonna+1);
				valore4 = LetturaValoreCampo(tabella,riga+2,colonna+2);

					if(valore1 == valore2 && valore2==valore3)
						{
							if(valore3==valore4)
								{
									vittoria++;
								}
						}
			}

	if(riga!=0 && riga!=1 && riga!=righe)
		{
			valore1 = LetturaValoreCampo(tabella,riga-2,colonna-2);
			valore2 =  LetturaValoreCampo(tabella,riga-1,colonna-1);
			valore3 = LetturaValoreCampo(tabella,riga,colonna);
			valore4 = LetturaValoreCampo(tabella,riga+1,colonna+1);

				if(valore1 == valore2 && valore2==valore3)
					{
						if(valore3==valore4)
							{
								vittoria++;
							}
					}
		}

	if(riga!= 0 && riga!= 1 && riga!= 2)
		{
			valore1 = LetturaValoreCampo(tabella,riga,colonna);
			valore2 = LetturaValoreCampo(tabella,riga-1,colonna-1);
			valore3 = LetturaValoreCampo(tabella,riga-2,colonna-2);
			valore4 = LetturaValoreCampo(tabella,riga-3,colonna-3);

			if(valore1 == valore2 && valore2==valore3)
				{
					if(valore3==valore4)
						{
							vittoria++;
						}
				}
		}

	return vittoria;
}

// Funzione che effettua il controllo della vittoria su riga, colonna, diagonale principale e secondaria
int ControlloVittoria(impostazioni imp, posizione riga, posizione colonna, campo tabella, int pedina)
{
	/*
	INPUT : INPUT : Impostazioni, tipo di dato impostazioni dal quale prelevare le informazioni
			      	      	  	  necessarie del campo
			Riga, tipo di dato posizione che indica la riga
			Colonna, tipo di dato posizione che indica la colonna
			Tabella, tipo di dato campo con il quale controllare la situazione del campo da
			 	 	 gioco
	OUTPUT : Vittoria, Valore intero >=0 che indica con 0 se non c'è stata nessuna vittoria,
			   	   	   con 1 se la vittoria è presente e con -1 se la partita è finita in
			   	   	   pareggio
	 */
	int pareggio;
	int vittoriaColonna;
	int vittoriaRiga;
	int vittoriaDiagonalePrincipale;
	int vittoriaDiagonaleSecondaria;

	int vittoria;

	pareggio=ControlloCampo(imp,tabella);

		if(pareggio==1)
			{
				return vittoria=-1;
			}else
				{
					vittoriaDiagonalePrincipale = ControlloVittoriaDiagonalePrincipale(imp,riga,colonna,tabella);
					vittoriaDiagonaleSecondaria = ControlloVittoriaDiagonaleSecondaria(imp,riga,colonna,tabella);
					vittoriaColonna = ControlloVittoriaColonna(imp,riga,tabella,pedina);
					vittoriaRiga = ControlloVittoriaRiga(imp,colonna,tabella,pedina);

					vittoria = vittoriaDiagonalePrincipale+vittoriaDiagonaleSecondaria+vittoriaRiga+vittoriaColonna;

					return vittoria;
				}
}

// Funzione che restituisce il messaggio di vittoria
void Vittoria()
{
	int x=2;
	int y=17;
	gotoxy(x,y);
	printf("Ha vinto il ");
	x=7;
	y=24;
	gotoxy(x,y);
	printf("IL PROGRAMMA SI CHIUDERA' AUTOMATICAMENTE! GRAZIE PER AVER GIOCATO!");
	sleep(7);
}

// Funzione che restituisce il messaggio di pareggio
void Pareggio()
{
	int x=2;
	int y=16;
	gotoxy(x,y);
	printf("Partita Conclusa\n  in Pareggio.");
	x=7;
	y=24;
	gotoxy(x,y);
	printf("IL PROGRAMMA SI CHIUDERA' AUTOMATICAMENTE! GRAZIE PER AVER GIOCATO!");
	sleep(7);
}

// Funzione che restituisce il messaggio di vittoria o di pareggio in base ai casi
void MessaggioFinale(int vittoria)
{
	/*
	INPUT : Vittoria, valore intero <=1 che indica se la partita è stata vinta con il valore 1
			  	  	  oppure se si è conclusa in pareggio,
			  	  	  quest'ultimo caso viene indicato con il valore -1
	OUTPUT : Messaggio, Messaggio che indica la vittoria di uno dei giocatori o il pareggio della
			    partita
	*/
	if(vittoria>0)
	{
		Vittoria();
	}else
		{
			Pareggio();
		}
}








