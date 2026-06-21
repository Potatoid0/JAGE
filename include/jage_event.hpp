#ifndef JAGE_EVENT_HPP
#define JAGE_EVENT_HPP


namespace JAGE
{
    enum class EventType { KeyPress, KeyRelease, MouseMove, WindowClose };

    class Event
    {
    public:
        virtual ~Event() = default;
        virtual EventType GetType() const = 0;
    };

    class KeyPressEvent : public Event
    {
    public:
        KeyPressEvent(int key) : m_Key(key) {}
        EventType GetType() const override { return EventType::KeyPress; }
        int GetKey() const { return m_Key; }
        
    private:
        int m_Key;
    };
    class KeyReleaseEvent : public Event
    {
    public:
        KeyReleaseEvent(int key) : m_Key(key) {}
        EventType GetType() const override { return EventType::KeyRelease; }
        int GetKey() const { return m_Key; }
    private:
        int m_Key;
    };
    
}


#endif
