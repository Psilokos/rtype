//
// RTEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sun Dec 11 21:42:46 2016 Victorien LE COUVIOUR--TUFFET
// Last update Sat Dec 31 19:44:24 2016 Gabriel CADET
//

#pragma once

#include <cstddef>
#include <functional>
#include <iterator>
#include <map>
#include <memory>
#include <tuple>
#include "BadType.hpp"
#include "Component.hpp"
#include "ID.hpp"
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
    template<char const *...> struct	_InitComponentsFromCTEntity;

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
      class	Iterator;
      class	ConstIterator;

    public:
      //! \brief Default constructor
      RTEntity(void) = default;

      //! \brief Constructor initializing the id
      //! \param [in] id the ID of the entity in database
      RTEntity(ID<ecs::Entity> const & id) : _id(id) {}

      //! \brief Constructor initializing components by copying or moving the ones given as parameter
      //! \param [in] id the ID of the entity in database
      //! \param [in] components a tuple of component::Component template class
      //! \param [in] names the names of the components, must be given in same order as the components in the tuple (can either be std::string or cstring)
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity(ID<ecs::Entity> const & id, std::tuple<ComponentsTypes...> && components, ComponentsNames&&... names)
	: _id(id), _components(_initComponents<0>(std::move(components), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...))) {}

      //! \brief Constructor initializing the components by copy from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names);

      //! \brief Constructor initializing the components by move from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity(database::Entity && databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names);

      //! \brief Constructor initializing the components by copy from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity);

      //! \brief Constructor initializing the components by move from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity);

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
      assign(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names);

      //! \brief Sets the components by move from a database::Entity
      //!
      //! Just indicate the components that you want to retrieve
      //! \param [in] databaseEntity the source entity
      //! \param [in] componentsTypes a compile_time::TypesWrapper that contains the types of the components to be stored
      //! \param [in] names the names of the components, must be given in same order as the ComponentsTypes (can either be std::string or cstring)
      //! \throw IdentifierNotFound if a component's name is not found in the databaseEntity
      template<typename... ComponentsTypes, typename... ComponentsNames>
      RTEntity &
      assign(database::Entity && databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names);

      //! \brief Assignement operator, setting the components by copy from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity &
      operator=(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity);

      //! \brief Assignement operator, setting the components by move from a CTEntity
      //!
      //! This will retrieve all the components of the source entity
      //! \param [in] ctEntity the source entity
      template<typename... ComponentsTypes, char const *... names>
      RTEntity &
      operator=(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity);

      //! \brief Default copy assignement operator
      RTEntity &	operator=(RTEntity const &) = default;

      //! \brief Default move assignement operator
      RTEntity &	operator=(RTEntity &&) = default;

      //! \brief Gets the entity ID
      //! \return a copy of the entity's ID
      ID<ecs::Entity>	getID(void) const { return _id; }

      //! \brief Sets the entity ID
      //! \param [in] id the new ID
      void	setID(ID<ecs::Entity> const & id) { _id = id; }

      //! \brief Checks if a component exists
      //! \param [in] name the name of the component to check
      //! \return true if the component exists, false otherwise
      bool	hasComponent(std::string const & name) { return _components.find(name) != _components.end(); }

      //! \brief Adds a component by copy
      //! \param [in] name the name of the component to add
      //! \param [in] component the component to add
      //! \throw IdentifierFound if a component with the same name already exists
      template<typename T>
      void
      addComponent(std::string const & name, T const & component)
      {
	if (_components.find(name) != _components.end())
	  throw IdentifierFound(name);
	_components.emplace(name, new Component(component));
      }

      //! \brief Adds a component by move
      //! \param [in] name the name of the component to add
      //! \param [in] component the component to add
      //! \throw IdentifierFound if a component with the same name already exists
      template<typename T>
      void
      addComponent(std::string const & name, T && component)
      {
	if (_components.find(name) != _components.end())
	  throw IdentifierFound(name);
	_components.emplace(name, new Component(std::forward<T>(component)));
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
	auto	it = _components.find(name);

	if (it == _components.end())
	  throw IdentifierNotFound(name);
	{
	  Component const		component = it->second->component<T>(name);

	  _components.erase(it);
	  return component;
	}
      }

      //! \brief Removes a component
      //! \param [in] name the name of the component to remove
      //! \throw IdentifierNotFound if the component does not exist
      void
      delComponent(std::string const & name)
      {
	auto	it = _components.find(name);

	if (it == _components.end())
	  throw IdentifierNotFound(name);
	_components.erase(it);
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
	auto	it = _components.find(name);

	if (it == _components.end())
	  throw IdentifierNotFound(name);
	return it->second->component<T>(name);
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
	auto	it = _components.find(name);

	if (it == _components.end())
	  throw IdentifierNotFound(name);
	return it->second->component<T>(name);
      }

      //! \brief Sets a component by copy
      //! \param [in] name the name of the component to set
      //! \param [in] component the component to set
      //! \throw IdentifierNotFound if the component does not exist
      template<typename T>
      void
      setComponent(std::string const & name, T const & component)
      {
	auto	it = _components.find(name);

	if (it == _components.end())
	  throw IdentifierNotFound(name);
	if (&component != &it->second->component<T>(name))
	  it->second->component<T>(name) = component;
      }

      //! \brief Sets a component by move
      //! \param [in] name the name of the component to set
      //! \param [in] component the component to set
      //! \throw IdentifierNotFound if the component does not exist
      template<typename T>
      void
      setComponent(std::string const & name, T && component)
      {
	auto	it = _components.find(name);

	if (it == _components.end())
	  throw IdentifierNotFound(name);
	if (&component != &it->second->component<T>(name))
	  it->second->component<T>(name) = std::forward<T>(component);
      }

      //! Gets an Iterator to the first component
      //! \return An Iterator to the first component
      Iterator		begin(void)		{ return Iterator(_components.begin()); }

      //! Gets a ConstIterator to the first component
      //! \return A ConstIterator to the first component
      ConstIterator	begin(void) const	{ return ConstIterator(_components.begin()); }

      //! Gets an Iterator to the first element following the last component
      //! \return An Iterator to the first element following the last component
      Iterator		end(void)	{ return Iterator(_components.end()); }

      //! Gets a ConstIterator to the first element following the last component
      //! \return A ConstIterator to the first element following the last component
      ConstIterator	end(void) const	{ return ConstIterator(_components.end()); }

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
      ID<ecs::Entity>					_id;
      std::map<std::string, std::shared_ptr<Component>>	_components;

    private:
      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(std::tuple<ComponentsTypes...> && components, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents,
		      typename std::enable_if<idx < sizeof...(ComponentsTypes)>::type * = nullptr)
      {
	return _initComponents<idx + 1, WrappedComponents..., std::shared_ptr<Component>>
	  (std::move(components), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...,
	   std::shared_ptr<Component>(new Component(std::forward<typename std::tuple_element<idx, std::tuple<ComponentsTypes...>>::type>(std::get<idx>(components)))));
      }

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(std::tuple<ComponentsTypes...> &&, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents,
		      typename std::enable_if<idx == sizeof...(ComponentsTypes)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(ComponentsNames)>(), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type * = nullptr);

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(database::Entity const &, ct::TypesWrapper<ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx == sizeof...(ComponentsNames)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(ComponentsNames)>(), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(database::Entity && databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type * = nullptr);

      template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, typename... ComponentsNames>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(database::Entity &&, ct::TypesWrapper<ComponentsTypes...> &&,
		      ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx == sizeof...(ComponentsNames)>::type * = nullptr)
      {
	return _initComponents(ct::Indexer<sizeof...(ComponentsNames)>(), std::move(names), std::forward<WrappedComponents>(wrappedComponents)...);
      }

      template<typename... ComponentsNames, typename... WrappedComponents, unsigned... i>
      std::map<std::string, std::shared_ptr<Component>>
      _initComponents(ct::Index<i...>, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents)
      {
	return std::map<std::string, std::shared_ptr<Component>>({{std::get<i>(names.values), std::forward<WrappedComponents>(wrappedComponents)}...});
      }

      template<char const *...>
      friend struct	_InitComponentsFromCTEntity;

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

      //! \brief An iterator to the stored components
      class	Iterator : public std::iterator<std::bidirectional_iterator_tag,
						decltype(RTEntity::_components)::value_type,
						decltype(RTEntity::_components)::difference_type,
						decltype(RTEntity::_components)::pointer,
						decltype(RTEntity::_components)::reference>
      {
      public:
	Iterator(void) = default;
	Iterator(decltype(RTEntity::_components)::iterator && it);

	//! \brief Pre decrement operator
	//! \return A reference to the previous iterator
	Iterator &	operator--(void);

	//! \brief Post decrement operator
	//! \return A copy of the iterator before the call
	Iterator	operator--(int);

	//! \brief Pre increment operator
	//! \return A reference to the next iterator
	Iterator &	operator++(void);

	//! \brief Post increment operator
	//! \return A copy of the iterator before the call
	Iterator	operator++(int);

	//! \brief Dereference operator
	//! \return A reference to the contained element
	reference	operator*(void);

	//! \brief Arrow operator
	//! \return A pointer to the contained element
	pointer		operator->(void);

	//! \brief Comparison operator. Checks if two iterators are different
	bool	operator!=(Iterator const & oth) const;

	//! \brief Comparison operator. Checks if two iterators are equal
	bool	operator==(Iterator const & oth) const;

      private:
	decltype(RTEntity::_components)::iterator	_it;
      };

      //! \brief A constant iterator to the stored components
      class	ConstIterator : public std::iterator<std::bidirectional_iterator_tag,
						     decltype(RTEntity::_components)::value_type,
						     decltype(RTEntity::_components)::difference_type,
						     decltype(RTEntity::_components)::const_pointer,
						     decltype(RTEntity::_components)::const_reference>
      {
      public:
	ConstIterator(void) = default;
	ConstIterator(decltype(RTEntity::_components)::const_iterator && it);

	//! \brief Pre decrement operator
	//! \return A reference to the previous iterator
	ConstIterator &	operator--(void);

	//! \brief Post decrement operator
	//! \return A copy of the iterator before the call
	ConstIterator	operator--(int);

	//! \brief Pre increment operator
	//! \return A reference to the next iterator
	ConstIterator &	operator++(void);

	//! \brief Post increment operator
	//! \return A copy of the iterator before the call
	ConstIterator	operator++(int);

	//! \brief Dereference operator
	//! \return A reference to the contained element
	reference	operator*(void);

	//! \brief Arrow operator
	//! \return A pointer to the contained element
	pointer		operator->(void);

	//! \brief Comparison operator. Checks if two iterators are different
	bool	operator!=(ConstIterator const & oth) const;

	//! \brief Comparison operator. Checks if two iterators are equal
	bool	operator==(ConstIterator const & oth) const;

      private:
	decltype(RTEntity::_components)::const_iterator	_it;
      };
    };
  }
}

#include "CTEntity.hpp"

namespace	entity_component_system::entity
{
  template<char const * _name, char const *... _names>
  struct	_InitComponentsFromCTEntity<_name, _names...>
  {
    template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
    static std::map<std::string, std::shared_ptr<RTEntity::Component>>
    init(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity, WrappedComponents&&... wrappedComponents)
    {
      return _InitComponentsFromCTEntity<_names...>::template init<idx + 1, WrappedComponents..., std::shared_ptr<RTEntity::Component>>
	(ctEntity, std::forward<WrappedComponents>(wrappedComponents)..., std::shared_ptr<RTEntity::Component>(new RTEntity::Component(ctEntity.template getComponent<_name>())));
    }

    template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
    static std::map<std::string, std::shared_ptr<RTEntity::Component>>
    init(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity, WrappedComponents&&... wrappedComponents)
    {
      return _InitComponentsFromCTEntity<_names...>::template init<idx + 1, WrappedComponents..., std::shared_ptr<RTEntity::Component>>
	(std::move(ctEntity), std::forward<WrappedComponents>(wrappedComponents)...,
	 std::shared_ptr<RTEntity::Component>(new RTEntity::Component(std::move(ctEntity.template getComponent<_name>()))));
    }
  };

  template<>
  struct	_InitComponentsFromCTEntity<>
  {
    template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
    static std::map<std::string, std::shared_ptr<RTEntity::Component>>
    init(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const &, WrappedComponents&&... wrappedComponents)
    {
      return _InitComponentsFromCTEntity::initializedComponents(ct::Indexer<sizeof...(names)>(),
								ct::Wrapper<decltype(std::string(names))...>(std::string(names)...),
								std::forward<WrappedComponents>(wrappedComponents)...);
    }

    template<unsigned idx, typename... WrappedComponents, typename... ComponentsTypes, char const *... names>
    static std::map<std::string, std::shared_ptr<RTEntity::Component>>
    init(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &&, WrappedComponents&&... wrappedComponents)
    {
      return _InitComponentsFromCTEntity::initializedComponents(ct::Indexer<sizeof...(names)>(),
								ct::Wrapper<decltype(std::string(names))...>(std::string(names)...),
								std::forward<WrappedComponents>(wrappedComponents)...);
    }

    template<typename... ComponentsNames, typename... WrappedComponents, unsigned... i>
    static std::map<std::string, std::shared_ptr<RTEntity::Component>>
    initializedComponents(ct::Index<i...>, ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents)
    {
      return std::map<std::string, std::shared_ptr<RTEntity::Component>>({{std::get<i>(names.values), std::forward<WrappedComponents>(wrappedComponents)}...});
    }
  };

  template<typename... ComponentsTypes, typename... ComponentsNames>
  RTEntity::RTEntity(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
    : _id(databaseEntity.getID()),
      _components(_initComponents<0>(databaseEntity, std::move(componentsTypes), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...))) {}

  template<typename... ComponentsTypes, typename... ComponentsNames>
  RTEntity::RTEntity(database::Entity && databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
    : _id(databaseEntity.getID()),
      _components(_initComponents<0>(std::move(databaseEntity), std::move(componentsTypes),
				     ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...)))
  {}

  template<typename... ComponentsTypes, char const *... names>
  RTEntity::RTEntity(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity)
    : _id(ctEntity.getID()), _components(_InitComponentsFromCTEntity<names...>::template init<0>(ctEntity)) {}

  template<typename... ComponentsTypes, char const *... names>
  RTEntity::RTEntity(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity)
    : _id(ctEntity.getID()), _components(_InitComponentsFromCTEntity<names...>::template init<0>(std::move(ctEntity))) {}

  template<typename... ComponentsTypes, typename... ComponentsNames>
  RTEntity &
  RTEntity::assign(database::Entity const & databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
  {
    _id = databaseEntity.getID();
    _components = _initComponents<0>(databaseEntity, std::move(componentsTypes), ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...));
    return *this;
  }

  template<typename... ComponentsTypes, typename... ComponentsNames>
  RTEntity &
  RTEntity::assign(database::Entity && databaseEntity, ct::TypesWrapper<ComponentsTypes...> && componentsTypes, ComponentsNames&&... names)
  {
    _id = databaseEntity.getID();
    _components = _initComponents<0>(std::move(databaseEntity), std::move(componentsTypes),
				     ct::Wrapper<decltype(std::string(names))...>(std::string(std::forward<ComponentsNames>(names))...));
    return *this;
  }

  template<typename... ComponentsTypes, char const *... names>
  RTEntity &
  RTEntity::operator=(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> const & ctEntity)
  {
    _id = ctEntity.getID();
    _components = _InitComponentsFromCTEntity<names...>::init<0>(ctEntity);
    return *this;
  }

  template<typename... ComponentsTypes, char const *... names>
  RTEntity &
  RTEntity::operator=(CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> && ctEntity)
  {
    _id = ctEntity.getID();
    _components = _InitComponentsFromCTEntity<names...>::init<0>(std::move(ctEntity));
    return *this;
  }

  template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
  std::map<std::string, std::shared_ptr<RTEntity::Component>>
  RTEntity::_initComponents(entity_component_system::database::Entity const & databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
			    ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type *)
  {
    return _initComponents<idx + 1, WrappedComponents..., std::shared_ptr<Component>>
      (databaseEntity, ct::TypesWrapper<ComponentsTypes...>(),
       std::move(names), std::forward<WrappedComponents>(wrappedComponents)...,
       std::shared_ptr<RTEntity::Component>(new RTEntity::Component(ComponentType(databaseEntity[std::get<idx>(names.values)]))));
  }

  template<unsigned idx, typename... WrappedComponents, typename ComponentType, typename... ComponentsTypes, typename... ComponentsNames>
  std::map<std::string, std::shared_ptr<RTEntity::Component>>
  RTEntity::_initComponents(entity_component_system::database::Entity && databaseEntity, ct::TypesWrapper<ComponentType, ComponentsTypes...> &&,
			    ct::Wrapper<ComponentsNames...> && names, WrappedComponents&&... wrappedComponents, typename std::enable_if<idx < sizeof...(ComponentsNames)>::type *)
  {
    return _initComponents<idx + 1, WrappedComponents..., std::shared_ptr<Component>>(std::move(databaseEntity), ct::TypesWrapper<ComponentsTypes...>(),
										      std::move(names), std::forward<WrappedComponents>(wrappedComponents)...,
										      std::shared_ptr<RTEntity::Component>
										      (new RTEntity::Component(ComponentType(std::move(databaseEntity[std::get<idx>(names.values)])))));
  }
}
