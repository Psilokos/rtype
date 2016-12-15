//
// RTEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sun Dec 11 21:42:46 2016 Victorien LE COUVIOUR--TUFFET
// Last update Thu Dec 15 19:27:24 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include <cstddef>
#include <functional>
#include <map>
#include <memory>
#include <tuple>
#include "BadType.hpp"
#include "Component.hpp"
#include "IdentifierFound.hpp"
#include "IdentifierNotFound.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    class	Entity;
  }

  namespace	entity
  {
    template<typename, char const *...>
    class	CTEntity;

    template<typename... ComponentsTypes, char const *... names>
    class	CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>;

    //! \brief Runtime entity class
    //!
    //! This class can contain a mutable number of compile time components (component::Component template class)
    class	RTEntity
    {
      class	Component;

    public:
      //! \brief Default constructor
      RTEntity(void) = default;

      //! \brief Constructor initializing components by copying or moving the ones given as parameter
      //! \param [in] components a tuple of component::Component template class
      //! \param [in] names the names of the components, must be given in same order as the components in the tuple (can either be std::string or cstring)
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity(std::tuple<ComponentsTypes...> && components, ComponentsNames&&... names)
	: _components(_initComponents<0>(std::move(components), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...))) {}

      //! \brief Constructor initializing the components by copy from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
	: _components(_initComponents<0>(databaseEntity, std::move(componentsTypes), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...))) {}

      //! \brief Constructor initializing the components by move from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity(database::Entity && databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
	: _components(_initComponents<0>(std::move(databaseEntity), std::move(componentsTypes), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...))) {}

      //! \brief Constructor initializing the components by copy from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity) : _components(_initComponents<0, names...>(ctEntity)) {}

      //! \brief Constructor initializing the components by move from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity) : _components(_initComponents<0, names...>(std::move(ctEntity))) {}

      //! \brief Default copy constructor
      RTEntity(RTEntity const &) = default;

      //! \brief Default move constructor
      RTEntity(RTEntity &&) = default;

      //! \brief Default destructor
      ~RTEntity(void) = default;

      //! \brief Sets the components by copy from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity &
      assign(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
      {
	_components = _initComponents<0>(databaseEntity, std::move(componentsTypes), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...));
	return *this;
      }

      //! \brief Sets the components by move from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity &
      assign(database::Entity && databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
      {
	_components = _initComponents<0>(std::move(databaseEntity), std::move(componentsTypes), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...));
	return *this;
      }

      //! \brief Assignement operator, setting the components by copy from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity &
      operator=(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity)
      {
	_components = _initComponents<0, names...>(ctEntity);
	return *this;
      }

      //! \brief Assignement operator, setting the components by move from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity &
      operator=(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity)
      {
	_components = _initComponents<0, names...>(std::move(ctEntity));
	return *this;
      }

      //! \brief Default copy assignement operator
      RTEntity &	operator=(RTEntity const &) = default;

      //! \brief Default move assignement operator
      RTEntity &	operator=(RTEntity &&) = default;

      //! \brief Checks if a component exists
      //! \param [in] name the name of the component to check
      //! \return true if the component exists, false otherwise
      bool	hasComponent(std::string const & name) { return _components.find(std::hash<std::string>{}(name)) != _components.end(); }

      //! \brief Adds a component by copy
      //! \param [in] name the name of the component to add
      //! \param [in] component the component to add
      //! \throw IdentifierFound if a component with the same name already exists
      template<typename T>
      void
      addComponent(std::string const & name, T const & component)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) != _components.end())
	  throw IdentifierFound(name);
	_components.emplace(hashedKey, new Component(component));
      }

      //! \brief Adds a component by move
      //! \param [in] name the name of the component to add
      //! \param [in] component the component to add
      //! \throw IdentifierFound if a component with the same name already exists
      template<typename T>
      void
      addComponent(std::string const & name, T && component)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) != _components.end())
	  throw IdentifierFound(name);
	_components.emplace(hashedKey, new Component(std::forward<T>(component)));
      }

      //! \brief Removes a component
      //! \tparam T the type of the component to remove (must be component::Component template class)
      //! \param [in] name the name of the component to remove
      //! \return a copy of the removed component
      //! \throw IdentifierNotFound if the component does not exist
      //! \throw BadType if the type of the component is not the expected one
      template<typename T>
      T
      delComponent(std::string const & name)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) == _components.end())
	  throw IdentifierNotFound(name);
	{
	  Component const		component = _components.at(hashedKey)->component<T>(name);

	  _components.erase(hashedKey);
	  return component;
	}
      }

      //! \brief Removes a component
      //! \param [in] name the name of the component to remove
      //! \throw IdentifierNotFound if the component does not exist
      void
      delComponent(std::string const & name)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) == _components.end())
	  throw IdentifierNotFound(name);
	_components.erase(hashedKey);
      }

      //! \brief Gets a component
      //! \tparam T the type of the component to get (must be component::Component template class)
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the requested component
      //! \throw IdentifierNotFound if the component does not exist
      //! \throw BadType if the type of the component is not the expected one
      template<typename T>
      T &
      getComponent(std::string const & name)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) == _components.end())
	  throw IdentifierNotFound(name);
	return _components.at(hashedKey)->component<T>(name);
      }

      //! \brief Gets a component
      //! \tparam T the type of the component to get (must be component::Component template class)
      //! \param [in] name the name of the component to get
      //! \return an lvalue reference to the constant requested component
      //! \throw IdentifierNotFound if the component does not exist
      //! \throw BadType if the type of the component is not the expected one
      template<typename T>
      T const &
      getComponent(std::string const & name) const
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) == _components.end())
	  throw IdentifierNotFound(name);
	return _components.at(hashedKey)->component<T>(name);
      }

      //! \brief Sets a component by copy
      //! \param [in] name the name of the component to set
      //! \param [in] component the component to set
      //! \throw IdentifierNotFound if the component does not exist
      template<typename T>
      void
      setComponent(std::string const & name, T const & component)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) == _components.end())
	  throw IdentifierNotFound(name);
	if (&component != &_components.at(hashedKey)->component<T>(name))
	  _components.at(hashedKey)->component<T>(name) = component;
      }

      //! \brief Sets a component by move
      //! \param [in] name the name of the component to set
      //! \param [in] component the component to set
      //! \throw IdentifierNotFound if the component does not exist
      template<typename T>
      void
      setComponent(std::string const & name, T && component)
      {
	std::size_t const	hashedKey = std::hash<std::string>{}(name);

	if (_components.find(hashedKey) == _components.end())
	  throw IdentifierNotFound(name);
	if (&component != &_components.at(hashedKey)->component<T>(name))
	  _components.at(hashedKey)->component<T>(name) = std::forward<T>(component);
      }

      //! \brief Inserts a RTEntity into an output stream
      //! \param [out] os the output stream in which the given RTEntity will be inserted
      //! \param [in] e the RTEntity to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &
      operator<<(std::ostream & os, RTEntity const & e)
      {
	auto	it = e._components.begin();

	os << "[with ";
	while (it != e._components.end())
	  {
	    os << it->first << ": " << *it->second;
	    if (++it != e._components.end())
	      os << ", ";
	  }
	return os << ']';
      }

    private:
      std::map<std::size_t, std::shared_ptr<Component>>	_components;

    private:
      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(std::tuple<ComponentsTypes...> && components, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents,
		      typename std::enable_if<idx < sizeof...(ComponentsTypes)>::type * = nullptr)
      {
	return _initComponents<idx + 1, WrappedComponents..., std::shared_ptr<Component>>
	  (std::move(components), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...,
	   std::shared_ptr<Component>(new Component(std::forward<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(components)))));
      }

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(std::tuple<ComponentsTypes...> &&, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents,
		      typename std::enable_if<idx == sizeof...(ComponentsTypes)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(ComponentsNames)>(), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type * = nullptr);

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(database::Entity const &, ct::TypesWrapper<ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx == sizeof...(ComponentsNames)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(ComponentsNames)>(), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(database::Entity && databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type * = nullptr);

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(database::Entity &&, ct::TypesWrapper<ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx == sizeof...(ComponentsNames)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(ComponentsNames)>(), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<unsigned idx, char const * name, char const *... _names, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(names)>::type * = nullptr);

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx == sizeof...(names)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(names)>(), ct::Wrapper<decltype(std::string(names))...>(std::string(names)...), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<unsigned idx, char const * name, char const *... _names, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(names)>::type * = nullptr);

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&,
		      WrappedComponents&&... wrappedComponents, typename std::enable_if<idx == sizeof...(names)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(names)>(), ct::Wrapper<decltype(std::string(names))...>(std::string(names)...), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<typename... ComponentsNames, typename... WrappedComponents, unsigned... i>
      std::map<std::size_t, std::shared_ptr<Component>>
      _initComponents(ct::Index<i...>, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents)
      {
	return std::map<std::size_t, std::shared_ptr<Component>>({{std::hash<std::string>{}(std::get<i>(names.values)), std::forward<WrappedComponents>(wrappedComponents)}...});
      }

    private:
      class	Component
      {
	class	Base;

      public:
	template<typename T>
	Component(T const & component) : _component(new Model<T>(component)) {}

	template<typename T>
	Component(T && component) : _component(new Model<T>(std::forward<T>(component))) {}

	template<typename T>
	T &	component(std::string const & componentName) const	{ return *reinterpret_cast<T *>(_component->component(componentName, typeid(T))); }

	friend std::ostream &	operator<<(std::ostream & os, Component const & c)	{ return c._component->dump(os); }

      private:
	std::shared_ptr<Base>	_component;

      private:
	class	Base
	{
	public:
	  virtual ~Base(void) {}

	  virtual void *		component(std::string const & componentName, std::type_info const & typeInfo) = 0;

	  virtual std::ostream &	dump(std::ostream & os) const = 0;
	};

	template<typename T>
	class	Model : public Base
	{
	public:
	  Model(T const & component) : _component(component), _typeInfo(&typeid(T)) {}
	  Model(T && component) : _component(std::forward<T>(component)), _typeInfo(&typeid(T)) {}

	  void *	component(std::string const & componentName, std::type_info const & typeInfo)
	  {
	    if (typeInfo != *_typeInfo)
	      throw BadType(componentName, _typeInfo, &typeInfo);
	    return reinterpret_cast<void *>(&_component);
	  }

	  std::ostream &	dump(std::ostream & os) const { return os << _component; }

	private:
	  T				_component;
	  std::type_info const *	_typeInfo;
	};
      };
    };
  }
}

#include "CTEntity.hpp"

namespace	entity_component_system::entity
{
  template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
  std::map<std::size_t, std::shared_ptr<RTEntity::Component>>
  RTEntity::_initComponents(entity_component_system::database::Entity const & databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
			    ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type *)
  {
    return _initComponents<idx + 1, WrappedComponents..., std::shared_ptr<Component>>(databaseEntity, ct::TypesWrapper<ComponentsTypes...>(),
										      std::move(names), std::forward<WrappedComponents>(wrappedComponents)...,
										      std::shared_ptr<RTEntity::Component>(new RTEntity::Component(ComponentType(databaseEntity[std::get<idx>(names.values)]))));
  }

  template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
  std::map<std::size_t, std::shared_ptr<RTEntity::Component>>
  RTEntity::_initComponents(entity_component_system::database::Entity && databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
			    ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type *)
  {
    return _initComponents<idx + 1, WrappedComponents..., std::shared_ptr<Component>>(std::move(databaseEntity), ct::TypesWrapper<ComponentsTypes...>(),
										      std::move(names), std::forward<WrappedComponents>(wrappedComponents)...,
										      std::shared_ptr<RTEntity::Component>
										      (new RTEntity::Component(ComponentType(std::move(databaseEntity[std::get<idx>(names.values)])))));
  }

  template<unsigned idx, char const * name, char const *... _names, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
  std::map<std::size_t, std::shared_ptr<RTEntity::Component>>
  RTEntity::_initComponents(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(names)>::type *)
  {
    return _initComponents<idx + 1, _names..., WrappedComponents..., std::shared_ptr<Component>>
      (ctEntity, std::forward<WrappedComponents>(wrappedComponents)..., std::shared_ptr<Component>(new Component(ctEntity.getComponent<name>())));
  }

  template<unsigned idx, char const * name, char const *... _names, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
  std::map<std::size_t, std::shared_ptr<RTEntity::Component>>
  RTEntity::_initComponents(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(names)>::type *)
  {
    return _initComponents<idx + 1, _names..., WrappedComponents..., std::shared_ptr<Component>>
      (std::move(ctEntity), std::forward<WrappedComponents>(wrappedComponents)..., std::shared_ptr<Component>(new Component(std::move(ctEntity.getComponent<name>()))));
  }
}
