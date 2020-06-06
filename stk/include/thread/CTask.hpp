#ifndef C_TASK_HPP
#define C_TASK_HPP

#include <memory>
#include <functional>

#include <core/TypeDef.hpp>

namespace stk
{

class CTask
{

public:

    using Ptr    = std::shared_ptr<CTask>;
    using Action = std::function<void()>;

public:
    CTask(Action _action, cuint32 _priority = 0U, bool _consume = true);
    ~CTask();

    void Exec();

    unsigned int GetID() const;

private:
    static unsigned int m_ID;
    int    m_priority;
    Action m_action;

};

static unsigned int CTaskID::m_ID { 0U };

}

#endif /* C_TASK_HPP */