#ifndef CF_Common_ObjectProvider_hpp
#define CF_Common_ObjectProvider_hpp

////////////////////////////////////////////////////////////////////////////////

#include "Common/CF.hpp"
#include "Common/Log.hpp"


#include "Common/ModuleRegister.hpp"

////////////////////////////////////////////////////////////////////////////////

namespace CF {
namespace Common {

////////////////////////////////////////////////////////////////////////////////

  /// Operator to delete the contents of the boost::shared_ptr
  template < typename BASE >
      struct deleter { void operator()( BASE * p ) { delete_ptr<BASE>(p); } };

/// This class represents a concrete templated provider to create
/// whatever kind of polymorphic objects. By default it takes two
/// template parameters and it builds a non configurable object
/// whose create() method accepts no arguments.
/// @author Andrea Lani
/// @author Tiago Quintino
template <class CONCRETE, class BASE, class MODULE, int NBARGS = 0>
class ObjectProvider : public BASE::PROVIDER {
public:

  /// Constructor
  explicit ObjectProvider(const std::string& name) : BASE::PROVIDER(name)
  {
    CFLogDebugVerbose (  "Creating provider \'" << name << "\' of type \'" << BASE::getClassName() << "\'\n" );
    //Common::ModuleRegister<MODULE>::getInstance().getSelfRegistry().regist(this);
  }

  /// Destructor
  /// @todo unregistration is currently not working
  ~ObjectProvider()
  {
    // Common::ModuleRegister<MODULE>::getInstance().getSelfRegistry().unregist(this);
  }

  /// Polymorphic function to create objects of dynamical type BASE
  /// @return boost::shared_ptr olding the created object
  boost::shared_ptr<BASE> create()
  {
    return boost::shared_ptr<BASE>(new CONCRETE(), deleter<BASE>() );
  }

}; // end of class ObjectProvider

////////////////////////////////////////////////////////////////////////////////

/// This class represents a concrete templated provider to create
/// whatever kind of polymorphic objects. It takes four
/// template parameters and it builds a non configurable object
/// whose create() method accepts one arguments.
/// @author Andrea Lani
/// @author Tiago Quintino
template <class CONCRETE, class BASE, class MODULE>
class ObjectProvider<CONCRETE,BASE,MODULE, 1> : public BASE::PROVIDER {
public:

  /// Constructor
  explicit ObjectProvider(const std::string& name) : BASE::PROVIDER(name)
  {
    CFLogDebugVerbose (  "Creating provider \'" << name << "\' of type \'" << BASE::getClassName() << "\'\n" );
//    MODULE::getInstance().getSelfRegistry().regist(this);
  }

  /// Destructor
  /// @todo unregistration is currently not working
  ~ObjectProvider()
  {
    // Common::ModuleRegister<MODULE>::getInstance().getSelfRegistry().unregist(this);
  }

  /// Polymorphic function to create objects of dynamical type BASE
  /// @return boost::shared_ptr olding the created object
  boost::shared_ptr<BASE> create(typename BASE::ARG1 arg)
  {
    return boost::shared_ptr<BASE>(new CONCRETE(arg), deleter<BASE>());
  }

}; // end of class ObjectProvider

////////////////////////////////////////////////////////////////////////////////

/// This class represents a concrete templated provider to create
/// whatever kind of polymorphic objects. It takes four
/// template parameters and it builds a non configurable object
/// whose create() method accepts one arguments.
/// @author Andrea Lani
/// @author Tiago Quintino
template <class CONCRETE, class BASE, class MODULE>
class ObjectProvider<CONCRETE,BASE,MODULE, 2> : public BASE::PROVIDER {
public:

  /// Constructor
  explicit ObjectProvider(const std::string& name) :
    BASE::PROVIDER(name)
  {
    CFLogDebugVerbose (  "Creating provider \'" << name << "\' of type \'" << BASE::getClassName() << "\'\n" );
//    MODULE::getInstance().getSelfRegistry().regist(this);
  }

  /// Destructor
  /// @todo unregistration is currently not working
  ~ObjectProvider()
  {
    // Common::ModuleRegister<MODULE>::getInstance().getSelfRegistry().unregist(this);
  }

  /// Polymorphic function to create objects of dynamical type BASE
  /// @param arg1 first parameter
  /// @param arg2 first parameter
  /// @return boost::shared_ptr olding the created object
  boost::shared_ptr<BASE> create(typename BASE::ARG1 arg1,
                                 typename BASE::ARG2 arg2)
  {
    return boost::shared_ptr<BASE>(new CONCRETE(arg1, arg2), deleter<BASE>());
  }

  /// Polymorphic function to create objects of dynamical type BASE
  /// @return boost::shared_ptr olding the created object
  boost::shared_ptr<BASE> create()
  {
  }

}; // end of class ObjectProvider

////////////////////////////////////////////////////////////////////////////////

  } // namespace Common
} // namespace CF

////////////////////////////////////////////////////////////////////////////////

#endif // CF_Common_ObjectProvider_hpp
