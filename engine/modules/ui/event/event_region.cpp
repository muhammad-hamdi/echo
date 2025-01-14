#include "event_region.h"
#include "event_processor.h"

namespace Echo
{
    UiEventRegion::UiEventRegion()
    {
		UiEventProcessor::instance()->registerEventRegion(this);
    }
    
    UiEventRegion::~UiEventRegion()
    {
		UiEventProcessor::instance()->unregisterEventRegion(this);
    }
    
    void UiEventRegion::bindMethods()
    {
        CLASS_BIND_METHOD(UiEventRegion, setType,       DEF_METHOD("setType"));
        CLASS_BIND_METHOD(UiEventRegion, getType,       DEF_METHOD("getType"));
        
        CLASS_REGISTER_PROPERTY(UiEventRegion, "Type", Variant::Type::StringOption, "getType", "setType");
        
        CLASS_REGISTER_SIGNAL(UiEventRegion, clicked);
    }
}
