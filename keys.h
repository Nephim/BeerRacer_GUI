#ifndef KEYS_H
#define KEYS_H

#include <QPushButton>
#include <QKeyEvent>
#include <QHash>

class Keys
{
public:
    Keys()
    {}

    void addKey(QChar keyName, QPushButton* button)
    {                                                               //Link the pushButtons to keys and put them into a the QMap
        keyMap_[keyName] = button;                                  //The findChild function is used to find the pushButton pointer
    }

    void pressEvent(QKeyEvent* event)
    {
        char key = static_cast<char>(event->key());
            if(keyMap_.contains(key))                               //If the key pressed is in our map do:
            {
                emit keyMap_[key]->pressed();                       //Call the pushButton_Key_pressed function for the event variable key
                keyMap_[key]->setDown(1);                           //Set the pushButton_Key to down for the event variable key
            }
    }

    void releaseEvent(QKeyEvent* event)
    {
        char key = static_cast<char>(event->key());
        if(!event->isAutoRepeat())
        {
            if(keyMap_.contains(key))                               //If the key pressed is in our map do:
            {
                emit keyMap_[key]->released();                      //Call the pushButton_Key_released function for the event variable key
                keyMap_[key]->setDown(0);                           //Set the pushButton_Key to up for the event variable key
            }
        }
    }

    void setStyle(QChar keyName, QString style)
    {
        keyMap_[keyName]->setStyleSheet(style);                     //Set button style
    }

private:
    QHash<QChar, QPushButton*> keyMap_;                              //Map used to store the keys we use
};

#endif // KEYS_H
