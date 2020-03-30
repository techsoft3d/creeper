#include <Types.h>

// static 
QString ts3d::Types::toString( HPS::Type const &type ) {
    auto idx = staticMetaObject.indexOfEnumerator( "HPSTypes" );
    if(-1 != idx) {
        auto const e = staticMetaObject.enumerator( idx );
        return e.valueToKey( static_cast<int>( type ) );
    }
    return QString();
}
