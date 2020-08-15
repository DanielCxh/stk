#ifndef C_TASK_HPP
#define C_TASK_HPP

#include <memory>
#include <functional>

#include <core/CTypeDef.hpp>

namespace stk
{

enum class TASK_MODE : std::uint32_t
{
    UNDEF = 0U,
    SYNC,
    ASYNC,
    MAX
};

class CTask
{

public:

    using Ptr    = std::shared_ptr<CTask>;
    using Action = std::function<void()>;

public:
    CTask(Action _action, TASK_MODE _mode = TASK_MODE::ASYNC, cuint32 _priority = 0U, bool _consume = true);
    ~CTask();

    void Exec();

    // unsigned int GetID() const;

private:
    static int m_ID;
    int        m_id;
    Action     m_action;
    TASK_MODE  m_mode;
    int        m_priority;
    bool       m_consume;
};

}

#endif /* C_TASK_HPP */
