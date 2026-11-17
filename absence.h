#ifndef ABSENCE_H
#define ABSENCE_H



const double DUREE_COURS = 1.5 , DUREE_TD = 1.5 , DUREE_TP = 2.0 , VOLUME_TOTAL = 60.0;
const double SEUIL_TOLERANCE = 5.0 , SEUIL_AVERTISSEMENT = 10.0 , SEUIL_ELIMINATION = 20.0 ,BONUS_MAX_PART = 2.0;


bool verifierNotes ( double exam , double td , double tp , double participation ) ;
double calculerHeuresAbsence ( int absCours , int absTD , int absTP ) ;
double calculerTauxAbsence ( double heuresAbsence ) ;
double calculerMalusAbsence ( double tauxAbsence ) ;
double calculerNoteBrute ( double noteExam , double noteTD , double noteTP ) ;
double calculerNoteFinale ( double noteBrute , double bonusPart , double malusAbs ) ;
void calculerBilanModule ( double exam , double td , double tp , int absCours , int absTD , int
absTP ,double participation , double & tauxAbs , double & malus , double &
noteFinale , bool & elimine ) ;
int similerAbsencesMaxAvantElimination(int absCours,int absTP);
void afficherSimulationAbsences(double noteExam , double noteTD , double noteTP , double
participation ) ;



#endif //ABSENCE_H

