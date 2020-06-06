#include <utils/CEvent.hpp>

namespace stk
{

std::uint32_t CEventHandler::GetId() const
{
    return m_id;
}

void CEventHandler::CallFn(const void * const _data)
{
    if (m_evt.get())
    {
        m_evt->OnCall(_data);
    }
}

CEvent::CEventPtr CEvent::Instance()
{
    static CEvent::CEventPtr instance = std::make_shared<CEvent>();

    return instance;
}


void CEvent::Send(std::uint32_t _id, EVT_MODE const _mode, const void * const _data)
{
    if (EVT_MODE::SYNC == _mode)
    {
        for (std::uint32_t i = 0U; i < m_events.size(); ++i)
        {
            if (m_events[i].GetId() == _id)
            {
                m_events[i].CallFn(_data);
            }
        }
    }
    else
    {
        
    }
}

}