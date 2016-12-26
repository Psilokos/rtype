//
// ComponentTypes.hpp for R-Type in /home/lecouv_v/rendu/rtype
//
// Made by Victorien LE COUVIOUR--TUFFET
// Login   <lecouv_v@epitech.eu>
//
// Started on  Sat Dec 17 20:03:54 2016 Victorien LE COUVIOUR--TUFFET
// Last update Mon Dec 26 16:03:23 2016 Victorien LE COUVIOUR--TUFFET
//

#pragma once

#include "CompileTime.hpp"
#include "ComponentTypeID.hpp"
#include "ComponentTypePair.hpp"

namespace	entity_component_system
{
  namespace	database
  {
    //! \brief All component types (see its specialization below)
    template<typename...> struct	ComponentTypes;

    //! \brief All component types, wrapped in a list of ComponentTypePair
    template<ComponentTypeID... componentTypes, typename... Components>
    struct	ComponentTypes<ComponentTypePair<componentTypes, Components>...>
    {
      //! \brief Gets the ComponentTypePair for a given index
      //! \tparam idx the index of the ComponentTypePair to retrieve
      template<unsigned idx>
      struct	GetComponentTypePair
      {
	template<unsigned, typename, typename = void> struct _GetComponentTypePair;

	template<unsigned _idx, typename CTPair, typename... CTPairs>
	struct	_GetComponentTypePair<_idx, ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<_idx>::type>
	{
	  typedef typename _GetComponentTypePair<_idx - 1, ct::TypesWrapper<CTPairs...>>::Type	Type;
	};

	template<unsigned _idx, typename CTPair, typename... CTPairs>
	struct	_GetComponentTypePair<_idx, ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<!_idx>::type>
	{
	  typedef CTPair	Type;
	};

	//! \brief the requested ComponentTypePair
	typedef typename _GetComponentTypePair<idx, ct::TypesWrapper<ComponentTypePair<componentTypes, Components>...>>::Type	Type;
      };

      //! \brief Gets the component type for a given enum value
      //! \tparam typeID the enum value attached to the requested component type
      template<ComponentTypeID typeID>
      struct	GetComponentType
      {
	template<typename, typename = void> struct _GetComponentType;

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentType<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<typeID != CTPair::typeID>::type>
	{
	  typedef typename _GetComponentType<ct::TypesWrapper<CTPairs...>>::Type	Type;
	};

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentType<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<typeID == CTPair::typeID>::type>
	{
	  typedef typename CTPair::Type		Type;
	};

	//! \brief the component type attached to the enum value 'typeID'
	typedef typename _GetComponentType<ct::TypesWrapper<ComponentTypePair<componentTypes, Components>...>>::Type	Type;
      };

      //! \brief Gets the enum value for a given component type
      //! \tparam Component the component type attached to the requested enum value
      template<typename Component>
      struct	GetComponentTypeID
      {
	template<typename, typename = void> struct	_GetComponentTypeID;

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentTypeID<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<!std::is_same<typename std::decay<Component>::type, typename CTPair::Type>::value>::type>
	{
	  static constexpr ComponentTypeID	typeID = _GetComponentTypeID<ct::TypesWrapper<CTPairs...>>::typeID;
	};

	template<typename CTPair, typename... CTPairs>
	struct	_GetComponentTypeID<ct::TypesWrapper<CTPair, CTPairs...>, typename std::enable_if<std::is_same<typename std::decay<Component>::type, typename CTPair::Type>::value>::type>
	{
	  static constexpr ComponentTypeID	typeID = CTPair::typeID;
	};

	//! \brief the enum value attached to the component type 'Component'
	static constexpr ComponentTypeID	typeID = _GetComponentTypeID<ct::TypesWrapper<ComponentTypePair<componentTypes, Components>...>>::typeID;
      };
    };
  }
}
