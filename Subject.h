//
// Created by giuseppe on 30/03/20.
//

#ifndef LABPROGRAMMAZIONE_SUBJECT_H
#define LABPROGRAMMAZIONE_SUBJECT_H

#include "Observer.h"

class Subject
{
public:
    virtual void addObserver(Observer* obs) = 0;
    virtual void remObserver(Observer* obs) = 0;
    virtual void notify() = 0;

    virtual ~Subject() {}
};
#endif //LABPROGRAMMAZIONE_SUBJECT_H
