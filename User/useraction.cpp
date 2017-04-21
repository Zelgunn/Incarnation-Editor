#include "useraction.h"

QStack<UserAction *> UserAction::s_reverseStack;
QStack<UserAction *> UserAction::s_restoreStack;

void UserAction::revert()
{

}

void UserAction::restore()
{

}

void UserAction::revertLastAction()
{
    if(s_reverseStack.isEmpty())
    {
        return;
    }

    UserAction *lastAction = s_reverseStack.pop();
    lastAction->revert();
    s_restoreStack.append(lastAction);
}

void UserAction::restoreLastRevertedAction()
{
    if(s_restoreStack.isEmpty())
    {
        return;
    }

    UserAction *action = s_restoreStack.pop();
    action->restore();
    s_reverseStack.append(action);
}

void UserAction::addAction(UserAction *action)
{
    s_reverseStack.append(action);

    while(!s_restoreStack.empty())
    {
        UserAction *action = s_restoreStack.pop();
        delete action;
    }
}
