#pragma once

#include "engine/core/memory/MemAllocDef.h"

namespace Echo
{
	class Variant;
	class Signal;
	class Object;
	class ClassMethodBind;

	// Connect
	struct Connect
	{
        virtual ~Connect() {}
        
        // emit Signal
        virtual void emitSignal(const Variant** args, int argCount) {}
        
        // save
        virtual void save(void* pugiNode) {}
	};
    
    struct ConnectClassMethod : public Connect
    {
        Signal*             m_signal;
        Object*             m_target;
        ClassMethodBind*    m_method;
        
		ConnectClassMethod(Signal* signal, Object* target, ClassMethodBind* method);
        
        // emit
        virtual void emitSignal(const Variant** args, int argCount) override;
    };
    
    struct ConnectLuaMethod : public Connect
    {
        Signal*           m_signal;
        String            m_targetPath;
        String            m_functionName;
        Object*           m_target = nullptr;

		ConnectLuaMethod(Signal* signal, Object* target, const String& functionName);
		ConnectLuaMethod(Signal* signal, const String& target, const String& functionName);
        
        // emit
        virtual void emitSignal(const Variant** args, int argCount) override;
        
        // save
        virtual void save(void* pugiNode) override;
        
    private:
        // build target
        void buildTarget();
    };

	// Signal
    // Reference: https://github.com/pbhogan/Signals
    // A lightweight signals and slots implementation
	class Signal
	{
	public:
        Signal(Object* owner);
        virtual ~Signal();
        
		// connect
		bool connectClassMethod(Object* obj, ClassMethodBind* method);
		bool connectLuaMethod(Object* obj, const String& luaMethodName);
        bool connectLuaMethod(const String& obj, const String& luaMethodName);

		// disconnect
		void disconnectLuaMethod(Object* obj, const String& luaMethodName);
		void disconnectLuaMethod(const String& obj, const String& luaMethodName);
		void disconnect(Connect* connect);
		void disconnectAll();
        
        // is have connect
        bool isHaveConnects() { return m_connects && !m_connects->empty(); }

		// get all connects
		vector<Connect*>::type* getConnects() { return m_connects; }
        
        // owner
        Object* getOwner() { return m_owner; }
        
        // load/save
        void load(void* pugiNode);
        void save(void* pugiNode);

	protected:
        Object*                 m_owner = nullptr;
		vector<Connect*>::type*	m_connects = nullptr;
	};

	class Signal0 : public Signal
	{
	public:
        Signal0(Object* owner) : Signal(owner) {}
        
		// operate ()
		void operator() ()
		{
            if(m_connects)
            {
                for (Connect* connect : *m_connects)
                    connect->emitSignal(nullptr, 0);
            }
		}
	};
}

#define DECLARE_SIGNAL(type, signal) \
    Signal* getSignal##signal() { return &signal; } \
    type    signal = type(this);
