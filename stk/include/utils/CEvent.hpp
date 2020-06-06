#ifndef C_EVENT_HPP
#define C_EVENT_HPP

#include <memory>
#include <vector>

namespace stk
{

enum class  EVT_MODE : std::uint32_t
{
    SYNC  = 0U,
    ASYNC,
    MAX
};

class CEventBase
{

public:
    virtual void OnCall(const void * const _data) const = 0;

};

template<class T, class F>
class CEventFunc : public CEventBase
{

public:
    CEventFunc() = delete;

    CEventFunc(T * const _tp, F const & _fn)
        : m_obj(_tp), m_func(_fn), CEventBase() {}


    void OnCall(const void * const _data) const
    {
        ((m_obj)->*m_func)(_data);
    }

private:
    T * const m_obj;
    F const   m_func;
};

class CEventHandler
{
public:
    CEventHandler() = delete;

    template<class T, class F>
    CEventHandler(const std::uint32_t _id, const F _fn, T * const _tp)
        : m_id(_id), m_evt(std::make_shared< CEventFunc<T, F> >(_tp, _fn)) {}

    ~CEventHandler() {}

    std::uint32_t GetId() const;

    /*
     * Function used to call CallBack.
     */
    void CallFn(const void * const _data);

private:
    std::uint32_t               m_id;
    std::shared_ptr<CEventBase> m_evt;
};

class CEvent
{

public:
    using CEventPtr = std::shared_ptr<CEvent>;

public:

    CEvent() {}
    ~CEvent() {}

    static CEvent::CEventPtr Instance();
    
    template<class T, class F>
    void Registe(std::uint32_t const _id, F const _fn, T * const _tp)
    {
        CEventHandler handler(_id, _fn, _tp);
        m_events.push_back(handler);
    }

    void Unregiste();

    void Send(std::uint32_t _id, EVT_MODE const _mode = EVT_MODE::SYNC, const void * const _data = std::nullptr_t());

private:
    std::vector<CEventHandler>  m_events;
};

}

#endif /* C_EVENT_HPP */