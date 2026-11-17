#include"absence.h"
#include <iostream>
#include<iomanip>
#include<cmath>
#include<algorithm>
using namespace std;

// [ TODO 2.1] Verification de validite : notes dans [0 , 20] et participation dans [0 , 2]
bool verifierNotes(double exam, double td, double tp, double participation) {
    if (exam < 0 || exam > 20) return false;
    if (td < 0 || td > 20) return false;
    if (tp < 0 || tp > 20) return false;
    if (participation < 0 || participation > BONUS_MAX_PART) return false;
    return true;
}
double calculerHeuresAbsence(int absCours, int absTD, int absTP) {
    absCours = max(0, absCours);
    absTD = max(0, absTD);
    absTP = max(0, absTP);
    return absCours * DUREE_COURS + absTD * DUREE_TD + absTP * DUREE_TP;
}
double calculerTauxAbsence ( double heuresAbsence ) {

    return (heuresAbsence/VOLUME_TOTAL)*100.0;
}
double calculerMalusAbsence ( double tauxAbsence ) {
// A COMPLETER : <= 5% -> 0 pt ; <= 10% -> 0.5 pt ; <= 20% -> 0.5 + 0.15*( taux - 10) ; >
    if(tauxAbsence <=0.05){
        return 0.0;
    }
    else if(tauxAbsence <=0.10){
        return 0.5;
    }
    else if(tauxAbsence <=0.20){
        return 0.5+0.15*(tauxAbsence-10);  
    }
    return 20.0;
}
double calculerNoteBrute ( double noteExam , double noteTD , double noteTP ) {
// A COMPLETER : 0.50 * noteExam + 0.30 * noteTD + 0.20 * noteTP
    return (0.50*noteExam+0.30*noteTD+0.20*noteTP);
}
double calculerNoteFinale ( double noteBrute , double bonusPart , double malusAbs ) {
// A COMPLETER : noteBrute + bonusPart - malusAbs , bornee dans [0.0 , 20.0] avec std :: min
    return min(20.0,max(0.0,noteBrute+bonusPart-malusAbs));

}
void calculerBilanModule ( double exam , double td , double tp , int absCours , int absTD , int absTP,double participation , double &tauxAbs , double &malus , double &noteFinale , bool &elimine ) {
    double heures = calculerHeuresAbsence(absCours, absTD, absTP);
    tauxAbs = calculerTauxAbsence(heures);
    malus = calculerMalusAbsence(tauxAbs);
    if (tauxAbs > SEUIL_ELIMINATION) {
        elimine = true;
        noteFinale = 0.0;
    } else {
        elimine = false;
        double brute = calculerNoteBrute(exam, td, tp);
        noteFinale = calculerNoteFinale(brute, participation, malus);
    }
}
int similerAbsencesMaxAvantElimination(int absCours,int absTP){
    int tauxAbs;
    int tdAjoutes=0;
    while(true){
        tauxAbs = ((absCours+tdAjoutes+1+absTP)/VOLUME_TOTAL)*100.0;
        if(tauxAbs > SEUIL_ELIMINATION){
            break;
        }
        else{
            tdAjoutes++;
        }
    }
    return tdAjoutes;
}
void afficherSimulationAbsences(double noteExam, double noteTD, double noteTP, double participation){
    string separateur = "+---------+------------+----------+-------------+--------------+------------------+";

    cout << fixed <<setprecision(2);
    cout << separateur << "\n";
    cout << "| " << setw(7) << "Abs. TD" << " | "
        << setw(10) << "Heures" << "|"
        <<setw(8) <<"Taux (%)"<< "|"
        <<setw(11) <<"Malus (pts)"<< "|"
        <<setw(12) <<"Note (/20)"<< "|"
        <<left<<setw(16) <<"Decision"<< "|"<<right<<"\n";
    cout << separateur << "\n";
    for(int nbTD =0 ; nbTD <=6 ;nbTD++){
        double heures = calculerHeuresAbsence(0,nbTD,0);
        double taux = calculerTauxAbsence(heures);
        double malus = calculerMalusAbsence(taux);
        double noteFinale;
        string decision;
        if (taux > SEUIL_ELIMINATION){
            noteFinale = 0.0;
            decision = "Elimine (>20%)";
        }
        else{
            noteFinale = calculerNoteFinale(calculerNoteBrute(noteExam,noteTD,noteTP),participation,malus);
            if (noteFinale >= 12) {
                decision = "Valide (Bien)";
            } else if (noteFinale >= 10) {
                decision = "Valide (Passable)";
            } else {
                decision = "Rattrapage (<10)";
            }
        }
        cout << fixed <<setprecision(2);
        cout << separateur << "\n";
        cout << "| " << setw(7) << "Abs. TD" << " | "
            << setw(10) << "Heures" << "|"
            <<setw(8) <<"Taux (%)"<< "|"
            <<setw(11) <<"Malus (pts)"<< "|"
            <<setw(12) <<"Note (/20)"<< "|"
            <<left<<setw(16) <<"Decision"<< "|"<<right<<"\n";
        
    }

    cout << separateur << "\n";

}