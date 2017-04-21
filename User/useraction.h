#ifndef USERACTION_H
#define USERACTION_H

#include <QStack>
#include <QDebug>

class UserAction
{
public:
    virtual void revert();
    virtual void restore();

    static void revertLastAction();
    static void restoreLastRevertedAction();
    static void addAction(UserAction *action);

private:
    static QStack<UserAction *> s_reverseStack;
    static QStack<UserAction *> s_restoreStack;
};

#endif // USERACTION_H
