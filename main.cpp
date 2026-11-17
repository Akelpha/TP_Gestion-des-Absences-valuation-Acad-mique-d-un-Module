#include"absence.h"
#include <iostream>
#include<iomanip>
#include<string>
using namespace std;



double saisirReel(const string &msg) {
    double val;
    while (true) {
        cout << msg;
        if (cin >> val) {
            return val;
        }
        cout << "Erreur : veuillez saisir un nombre.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
}


double saisirNote(const string &msg) {
    while (true) {
        double val = saisirReel(msg);
        if (val >= 0.0 && val <= 20.0) {
            return val;
        }
        cout << "Erreur : la note doit etre comprise entre 0 et 20.\n";
    }
}
int saisirEntierPositif(const string &msg) {
    int val;
    while (true) {
        cout << msg;
        if (cin >> val && val >= 0) {
            return val;
        }
        cout << "Erreur : entrez un entier positif ou nul.\n";
        cin.clear();
        cin.ignore(1000, '\n');
    }
} 
int main(){
    double exam = 14.0 , td = 12.0 , tp = 16.0 , participation = 1.0;
    int absCours = 2 , absTD = 2 , absTP = 1 , choix = -1;
    do{
        cout << "\n=== MENU ===\n"
             << "1- Saisir notes et absences\n"
             << "2- Bilan academique\n"
             << "3- Simulation absences TD max\n"
             << "4- Tableau impact absences\n"
             << "5- Decomposition note brute / ajustee\n"
             << "0- Quitter\n";
        choix = saisirEntierPositif("Votre choix : ");

        switch (choix) {
            case 1:
                exam = saisirNote("Note d'examen (0-20) : ");
                td = saisirNote("Note de TD (0-20) : ");
                tp = saisirNote("Note de TP (0-20) : ");
                do {
                    participation = saisirReel("Bonus de participation (0-2) : ");
                } while (participation < 0.0 || participation > 2.0);
                absCours = saisirEntierPositif("Nombre de cours manques : ");
                absTD = saisirEntierPositif("Nombre de TD manques : ");
                absTP = saisirEntierPositif("Nombre de TP manques : ");
                break;

            case 2: {
                double tauxAbs, malus, noteFinale;
                bool elimine;
                calculerBilanModule(exam, td, tp, absCours, absTD, absTP,
                                    participation, tauxAbs, malus, noteFinale, elimine);
                cout << fixed << setprecision(2);
                cout << "Taux d'absence : " << tauxAbs << " %\n";
                cout << "Malus : " << malus << " pts\n";
                if (elimine) {
                    cout << "Decision : Elimine (note 0/20)\n";
                } else {
                    cout << "Note finale : " << noteFinale << "/20\n";
                }
                break;
            }

            case 3:
                cout << "Nombre maximal de TD manquables : "
                     << similerAbsencesMaxAvantElimination(absCours, absTP) << "\n";
                break;

            case 4:
                afficherSimulationAbsences(exam, td, tp, participation);
                break;

            case 5: {
                double brute = calculerNoteBrute(exam, td, tp);
                double taux = calculerTauxAbsence(calculerHeuresAbsence(absCours, absTD, absTP));
                double malus = calculerMalusAbsence(taux);
                cout << fixed << setprecision(2);
                cout << "Note brute : " << brute << "\n";
                cout << "Bonus : " << participation << " | Malus : " << malus << "\n";
                cout << "Note ajustee : " << calculerNoteFinale(brute, participation, malus) << "/20\n";
                break;
            }

            case 0:
                cout << "Au revoir !\n";
                break;

            default:
                cout << "Choix invalide.\n";
        }
    }while(choix!=0);
    return 0;
}
