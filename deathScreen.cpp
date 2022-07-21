#include "deathScreen.h"

DeathScreen::DeathScreen(int finalScore){

    QInputDialog *test = new QInputDialog();
    test->setLabelText(QString("Enter your name:"));
    
    int result = test->exec();
    if(result == 1){
        Leaderboard::instance().submitScore(finalScore, test->textValue().toStdString().c_str());
    }
    

}
DeathScreen::~DeathScreen(){

}
