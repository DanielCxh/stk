#include <thread/CTask.hpp>

namespace stk
{

int CTask::m_ID { 0U };

CTask::CTask(Action _action, TASK_MODE _mode, cuint32 _priority, bool _consume)
    : m_action(_action)
{
    m_id = m_ID++;
}

CTask::~CTask()
{
    /* do nothing */
}

void CTask::Exec()
{
    if (m_action)
    {
        m_action();
    }
}

}
