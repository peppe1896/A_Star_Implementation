//
// Created by giuseppe on 30/03/20.
//

#ifndef LABPROGRAMMAZIONE_OBSERVER_H
#define LABPROGRAMMAZIONE_OBSERVER_H

class Observer
{
public:
    virtual void attach() = 0;
    virtual void detach() = 0;
    virtual void update_observer() = 0;

    virtual ~Observer() {}
};

#endif //LABPROGRAMMAZIONE_OBSERVER_H
