//
// CTEntity.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 10 04:57:13 2016 Victorien LE COUVIOUR--TUFFET
// Last update Wed Dec 21 22:13:36 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "Component.hpp"
#include "IAssembly.hpp"
#include "ID.hpp"
#include "WrongAssemblyType.hpp"

template<typename Assembly>
void	visitImpl(Assembly & self, ecs::database::IAssemblyDispatcher & dispatcher)
{
  IDispatcherPart<Assembly> &	dsp = dispatcher;

  dsp.dispatch(self);
}

namespace	entity_component_system
{
  namespace	database
  {
    class	IAssembly;
    class	Entity;
  }

  namespace	entity
  {
    class	RTEntity;

    template<typename, typename = void> class	_CTEntity;

    template<typename CTEntity>
    class	_CTEntity<CTEntity, typename std::enable_if<ecs::database::Assemblies::IsWrapped<CTEntity>::value>::type> : public database::IAssembly
    {
      virtual void	visit(database::IAssemblyDispatcher & dsp) { ::visitImpl(static_cast<CTEntity &>(*this), dsp); }
    };

    template<typename CTEntity>
    class	_CTEntity<CTEntity, typename std::enable_if<!ecs::database::Assemblies::IsWrapped<CTEntity>::value>::type> {};

    //! \brief Compile time entity class (see its specialization below)
    template<typename, char const *...>
    class	CTEntity;

    class	CTEntity<ct::TypesWrapper<>>;

    //! \brief Compile time entity class
    //!
    //! The structure of this class is not mutable. This means that you cannot add or delete components, but you can modify the attributes' value
    //!
    //! \tparam ComponentsTypes types of the components (must be component::Component template class)
    //! \tparam names the names of the components, must be given in the same order as the ComponentsTypes, and declared as follow (in the global scope):
    //! \code constexpr char componentName[] = "componentName"; \endcode
    template<typename... ComponentsTypes, char const *... names>
    class	CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> : public _CTEntity<CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>>
    {
    public:
      //! \brief Default constructor
      //!
      //! initializes the attributes of all the components with their default values
      CTEntity(void) = default;

      //! \brief Constructor initializing the id
      //! \param [in] id the ID of the entity in database
      CTEntity(ID<ecs::Entity> const & id) : _id(id) {}

      //! \brief Constructor initializing the components by copy
      //! \param [in] id the ID of the entity in database
      //! \param [in] components the components to copy
      CTEntity(ID<ecs::Entity> const & id, ComponentsTypes const &... components) : _id(id), _components(components...) {}

      //! \brief Constructor initializing the components by move
      //! \param [in] id the ID of the entity in database
      //! \param [in] components the components to move
      CTEntity(ID<ecs::Entity> const & id, ComponentsTypes&&... components) : _id(id), _components(std::forward<ComponentsTypes>(components)...) {}

      //! \brief Constructor initializing the components by copy from a database::Entity
      //! \param [in] databaseEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'databaseEntity'
      CTEntity(database::Entity const & databaseEntity);

      //! \brief Constructor initializing the components by move from a database::Entity
      //! \param [in] databaseEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'databaseEntity'
      CTEntity(database::Entity && databaseEntity);

      //! \brief Constructor initializing the components by copy from an entity::RTEntity
      //! \param [in] rtEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'rtEntity'
      CTEntity(RTEntity const & rtEntity);

      //! \brief Constructor initializing the components by move from an entity::RTEntity
      //! \param [in] rtEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'rtEntity'
      CTEntity(RTEntity && rtEntity);

      //! \brief Default copy constructor
      CTEntity(CTEntity const &) = default;

      //! \brief Default move constructor
      CTEntity(CTEntity &&) = default;

      //! \brief Default destructor
      ~CTEntity(void) = default;

      //! \brief Assignement operator, setting the components by copy from a database::Entity
      //! \param [in] databaseEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'databaseEntity'
      CTEntity &
      operator=(database::Entity const & databaseEntity);

      //! \brief Assignement operator, setting the components by move from a database::Entity
      //! \param [in] databaseEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'databaseEntity'
      CTEntity &
      operator=(database::Entity && databaseEntity);

      //! \brief Assignement operator, setting the components by copy from an entity::RTEntity
      //! \param [in] rtEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'rtEntity'
      CTEntity &
      operator=(RTEntity const & rtEntity);

      //! \brief Assignement operator, setting the components by move from an entity::RTEntity
      //! \param [in] rtEntity the source entity
      //! \throw IdentifierNotFound if a component is not found in 'rtEntity'
      CTEntity &
      operator=(RTEntity && rtEntity);

      //! \brief Default copy assignement operator
      CTEntity &	operator=(CTEntity const &) = default;

      //! \brief Default move assignement operator
      CTEntity &	operator=(CTEntity &&) = default;

      //! \brief Gets the entity ID
      //! \return a copy of the entity's ID
      ID<ecs::Entity>	getID(void) const { return _id; }

      //! \brief Sets the entity ID
      //! \param [in] id the new ID
      void	setID(ID<ecs::Entity> const & id) { _id = id; }

      //! \brief Gets a component
      //! \tparam name the name of the requested component, must be declared as follow (in the global scope): \code constexpr char componentName[] = "componentName"; \endcode
      //! \return an lvalue reference to the requested component
      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type &
      getComponent(void)
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      //! \brief Gets a constant component
      //! \tparam name the name of the requested component, must be declared as follow (in the global scope): \code constexpr char componentName[] = "componentName"; \endcode
      //! \return an lvalue reference to the constant requested component
      template<char const * name>
      typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type const &
      getComponent(void) const
      {
	return std::get<ct::getIdx<name, names...>()>(_components);
      }

      //! \brief Sets a component by copy
      //! \tparam name the name of the requested component, must be declared as follow (in the global scope): \code constexpr char componentName[] = "componentName"; \endcode
      //! \param [in] component an lvalue reference to the component to set
      template<char const * name>
      void
      setComponent(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type const & component)
      {
	if (&component != &std::get<ct::getIdx<name, names...>()>(_components))
	  std::get<ct::getIdx<name, names...>()>(_components) = component;
      }

      //! \brief Sets a component by move
      //! \tparam name the name of the requested component, must be declared as follow (in the global scope): \code constexpr char componentName[] = "componentName"; \endcode
      //! \param [in] component an rvalue reference to the component to set
      template<char const * name>
      void
      setComponent(typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type && component)
      {
	if (&component != &std::get<ct::getIdx<name, names...>()>(_components))
	  std::get<ct::getIdx<name, names...>()>(_components) = std::forward<typename std::tuple_element<ct::getIdx<name, names...>(), std::tuple<ComponentsTypes...>>::type>(component);
      }

      //! \brief Inserts a CTEntity into an output stream
      //! \param [out] os the output stream in which the given CTEntity will be inserted
      //! \param [in] e the CTEntity to insert in the stream
      //! \return a reference to the given output stream 'os' to allow operator chaining
      friend std::ostream &	operator<<(std::ostream & os, CTEntity const & e)
      {
	os << '(' << e._id << ") [with ";
	return e._print<names...>(os) << ']' << std::flush;
      }

    private:
      ID<ecs::Entity>			_id;
      std::tuple<ComponentsTypes...>	_components;

    private:
      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity const & databaseEntity, std::true_type, Components&&... components);

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity const &, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentsTypes...>(std::forward<Components>(components)...);
      }

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity && databaseEntity, std::true_type, Components&&... components);

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(database::Entity &&, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentsTypes...>(std::forward<Components>(components)...);
      }

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(RTEntity const & rtEntity, std::true_type, Components&&... components);

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(RTEntity const &, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentsTypes...>(std::forward<Components>(components)...);
      }

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(RTEntity && rtEntity, std::true_type, Components&&... components);

      template<typename... Components>
      std::tuple<ComponentsTypes...>
      _initComponents(RTEntity &&, std::false_type, Components&&... components)
      {
	return std::tuple<ComponentsTypes...>(std::forward<Components>(components)...);
      }

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<sizeof...(_names)>::type * = nullptr) const
      {
	os << name << ": " << std::get<sizeof...(names) - sizeof...(_names) - 1>(_components) << ", ";
	return _print<_names...>(os);
      }

      template<char const * name, char const *... _names>
      std::ostream &
      _print(std::ostream & os, typename std::enable_if<!sizeof...(_names)>::type * = nullptr) const
      {
	return os << name << ": " << std::get<sizeof...(names) - 1>(_components);
      }
    };
  }
}

#include "DataBaseEntity.hpp"

namespace	entity_component_system::entity
{
  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::CTEntity(database::Entity const & databaseEntity) : _id(databaseEntity.getID()), _components(_initComponents(databaseEntity, std::true_type())) {}

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::CTEntity(database::Entity && databaseEntity) : _id(databaseEntity.getID()), _components(_initComponents(std::move(databaseEntity), std::true_type())) {}

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::CTEntity(RTEntity const & rtEntity) : _id(rtEntity.getID()), _components(_initComponents(rtEntity, std::true_type())) {}

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::CTEntity(RTEntity && rtEntity) : _id(rtEntity.getID()), _components(_initComponents(std::move(rtEntity), std::true_type())) {}

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::operator=(database::Entity const & databaseEntity)
  {
    _id = databaseEntity.getID();
    _components = _initComponents(databaseEntity, std::true_type());
    return *this;
  }

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::operator=(database::Entity && databaseEntity)
  {
    _id = databaseEntity.getID();
    _components = _initComponents(std::move(databaseEntity), std::true_type());
    return *this;
  }

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::operator=(RTEntity const & rtEntity)
  {
    _id = rtEntity.getID();
    _components = _initComponents(rtEntity, std::true_type());
    return *this;
  }

  template<typename... ComponentsTypes, char const *... names>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...> &
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::operator=(RTEntity && rtEntity)
  {
    _id = rtEntity.getID();
    _components = _initComponents(std::move(rtEntity), std::true_type());
    return *this;
  }

  template<typename... ComponentsTypes, char const *... names> template<typename... Components>
  std::tuple<ComponentsTypes...>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::_initComponents(ecs::database::Entity const & databaseEntity, std::true_type, Components&&... components)
  {
    return _initComponents(databaseEntity,
			   std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentsTypes)>(),
			   std::forward<Components>(components)...,
			   databaseEntity[std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...))]);
  }

  template<typename... ComponentsTypes, char const *... names> template<typename... Components>
  std::tuple<ComponentsTypes...>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::_initComponents(ecs::database::Entity && databaseEntity, std::true_type, Components&&... components)
  {
    return _initComponents(std::move(databaseEntity),
			   std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentsTypes)>(),
			   std::forward<Components>(components)...,
			   std::move(databaseEntity[std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...))]));
  }

  template<typename... ComponentsTypes, char const *... names> template<typename... Components>
  std::tuple<ComponentsTypes...>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::_initComponents(RTEntity const & rtEntity, std::true_type, Components&&... components)
  {
    return _initComponents(rtEntity,
			   std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentsTypes)>(),
			   std::forward<Components>(components)...,
			   rtEntity.getComponent<typename std::tuple_element<sizeof...(Components), std::tuple<ComponentsTypes...>>::type>
			   (std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...))));
  }

  template<typename... ComponentsTypes, char const *... names> template<typename... Components>
  std::tuple<ComponentsTypes...>
  CTEntity<ct::TypesWrapper<ComponentsTypes...>, names...>::_initComponents(RTEntity && rtEntity, std::true_type, Components&&... components)
  {
    return _initComponents(std::move(rtEntity),
			   std::integral_constant<bool, sizeof...(Components) + 1 < sizeof...(ComponentsTypes)>(),
			   std::forward<Components>(components)...,
			   std::move(rtEntity.getComponent<typename std::tuple_element<sizeof...(Components), std::tuple<ComponentsTypes...>>::type>
				     (std::get<sizeof...(Components)>(std::tuple<decltype(names)...>(names...)))));
  }
}